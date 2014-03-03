/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef MADS_SCENE_DATA_H
#define MADS_SCENE_DATA_H

#include "common/scummsys.h"
#include "common/array.h"
#include "common/str.h"
#include "common/str-array.h"
#include "common/rect.h"
#include "mads/action.h"
#include "mads/assets.h"
#include "mads/game_data.h"

namespace MADS {

class MADSEngine;
class Scene;

#define MADS_INTERFACE_HEIGHT 44
#define MADS_SCENE_HEIGHT 156

#define DEPTH_BANDS_SIZE 15
#define MAX_ROUTE_NODES 22

enum ScrCategory {
	CAT_NONE = 0, CAT_ACTION = 1, CAT_INV_LIST = 2, CAT_INV_VOCAB = 3,
	CAT_HOTSPOT = 4, CAT_INV_ANIM = 5, CAT_6 = 6, CAT_INV_SCROLLER = 7,
	CAT_12 = 12
};

enum Layer {
	LAYER_GUI = 19
};

enum SpriteType {
	ST_NONE = 0, ST_FOREGROUND = 1, ST_BACKGROUND = -4,
	ST_FULL_SCREEN_REFRESH = -2, ST_EXPIRED = -1
};

class VerbInit {
public:
	int _id;
	int _action1;
	int _action2;

	VerbInit() {}
	VerbInit(int id, int action1, int action2): _id(id), _action1(action1), _action2(action2) {}
};

class ScreenObject {
public:
	Common::Rect _bounds;
	ScrCategory _category;
	int _descId;
	int _layer;

	ScreenObject();
};

class ScreenObjects: public Common::Array<ScreenObject> {
private:
	MADSEngine *_vm;

	int scanBackwards(const Common::Point &pt, int layer);

	void proc1();
public:
	int _v832EC;
	int _v7FECA;
	int _v7FED6;
	int _v8332A;
	int _yp;
	int _v8333C;
	int _selectedObject;
	ScrCategory _category;
	int _objectIndex;
	bool _released;

	/*
	 * Constructor
	 */
	ScreenObjects(MADSEngine *vm);

	/**
	 * Add a new item to the list
	 */
	void add(const Common::Rect &bounds, ScrCategory category, int descId);

	/**
	 */
	void check(bool scanFlag);
};

class SpriteSlotSubset {
public:
	int _spritesIndex;
	int _frameNumber;
	Common::Point _position;
	int _depth;
	int _scale;
};

class SpriteSlot: public SpriteSlotSubset {
public:
	SpriteType _spriteType;
	int _seqIndex;
public:
	SpriteSlot();
	SpriteSlot(SpriteType type, int seqIndex);
};

class SpriteSlots: public Common::Array<SpriteSlot> {
private:
	MADSEngine *_vm;
public:
	SpriteSlots(MADSEngine *vm): _vm(vm) {}

	/**
	 * Clears any pending slot data and schedules a full screen refresh.
	 * @param flag		Also reset sprite list
	 */
	void clear(bool flag);

	/**
	 * Delete any sprites used by the player
	 */
	void releasePlayerSprites();

	/**
	 * Delete a sprite entry
	 * @param index		Specifies the index in the array
	 */
	void deleteEntry(int index);
};

class SpriteSets: public Common::Array<SpriteAsset *> {
public:
	/**
	 * Add a sprite asset to the list
	 */
	int add(SpriteAsset *asset, int idx = 0);
};

class TextDisplay {
public:
	bool _active;
	int _spacing;
	Common::Rect _bounds;
	int _expire;
	int _col1;
	int _col2;
	Common::String _fontName;
	Common::String _msg;

	TextDisplay();
};

class DynamicHotspot {
public:
	int _seqIndex;
	Common::Rect _bounds;
	Common::Point _feetPos;
	int _facing;
	int _descId;
	int _field14;
	int _articleNumber;
	int _cursor;

	DynamicHotspot();
};

class DynamicHotspots : public Common::Array<DynamicHotspot> {
private:
	MADSEngine *_vm;
public:
	bool _changed;

	/**
	 * Constructor
	 */
	DynamicHotspots(MADSEngine *vm);

	/**
	 * Clear the list
	 */
	void clear();

	/**
	 * Refresh the list
	 */
	void refresh();
};

class SequenceEntry {
public:
	int _spritesIndex;
	int _flipped;
	int _frameIndex;
	int _frameStart;
	int _numSprites;
	int _animType;
	int _frameInc;
	int _depth;
	int _scale;
	int _dynamicHotspotIndex;
	
	Common::Point _msgPos;

	int _triggerCountdown;
	bool _doneFlag;
	struct {
		int _count;
		int _mode[5];
		int _frameIndex[5];
		int _abortVal[5];
	} _entries;
	int _abortMode;
	int _actionNouns[3];
	int _numTicks;
	int _extraTicks;
	int _timeout;

	SequenceEntry();
};

class KernelMessage {
public:
	int _flags;
	int _seqInex;
	char _asciiChar;
	char _asciiChar2;
	int _colors;
	Common::Point _posiition;
	int _msgOffset;
	int _numTicks;
	int _frameTimer2;
	int _frameTimer;
	int _timeout;
	int _field1C;
	int _abortMode;
	int _nounList[3];
	Common::String _msg;

	KernelMessage();
};

class Hotspot {
public:
	Common::Rect _bounds;
	Common::Point _feetPos;
	int _facing;
	int _articleNumber;
	int _cursor;
	int _vocabId;
	int _verbId;

	Hotspot();
	Hotspot(Common::SeekableReadStream &f);
};

class SceneLogic {
protected:
	Scene *_scene;
public:
	/**
	 * Constructor
	 */
	SceneLogic(Scene *scene): _scene(scene) {}

	/**
	 * Destructor
	 */
	virtual ~SceneLogic() {}

	/**
	 * Called to initially setup a scene
	 */
	virtual void setup() = 0;

	/**
	 * Called as the scene is entered (made active)
	 */
	virtual void enter() = 0;

	/**
	 * Called one per frame
	 */
	virtual void step() = 0;

	/**
	 * Called before an action is started
	 */
	virtual void preActions() = 0;

	/**
	 * Handles scene actions
	 */
	virtual void actions() = 0;

	/**
	 * Post-action handling
	 */
	virtual void postActions() = 0;
};

struct ARTHeader {
	int _width;
	int _height;
	Common::Array<RGB6> _palette;
	Common::Array<RGB4> _palAnimData;

	void load(Common::SeekableReadStream *f);
};

class SceneNode {
public:
	Common::Point _walkPos;
	int _indexes[MAX_ROUTE_NODES];
	bool _active;

	/**
	 * Constructor
	 */
	SceneNode() : _active(false) {}

	/**
	 * Loads the scene node
	 */
	void load(Common::SeekableReadStream *f);
};
typedef Common::Array<SceneNode> SceneNodeList;

class InterfaceSurface : public MSurface {
private:
	MADSEngine *_vm;
public:
	ScrCategory _category;
public:
	/**
	 * Constructor
	 */
	InterfaceSurface(MADSEngine *vm);

	/**
	 * Loads an interface from a specified resource
	 */
	void load(const Common::String &resName);

	void elementHighlighted();
};

/**
 * Handles general data for a given scene
 */
class SceneInfo {
	class SpriteInfo {
	public:
		int _spriteSetIndex;
		Common::Point _position;
		int _depth;
		int _scale;

		void load(Common::SeekableReadStream *f);
	};
protected:
	MADSEngine *_vm;

	/**
	 * Constructor
	 */
	SceneInfo(MADSEngine *vm) : _vm(vm) {}
	
	/**
	 * Loads the given surface with depth information of a given scene
	 */
	virtual void loadCodes(MSurface &depthSurface);
public:
	int _sceneId;
	int _artFileNum;
	int _depthStyle;
	int _width;
	int _height;

	int _yBandsEnd;
	int _yBandsStart;
	int _maxScale;
	int _minScale;
	int _depthList[DEPTH_BANDS_SIZE];
	int _field4A;

	int _field4C;
	Common::Array<RGB4> _palAnimData;
	SceneNodeList _nodes;
public:
	/**
	 * Destructor
	 */
	virtual ~SceneInfo() {}

	/**
	 * Instantiates the class
	 */
	static SceneInfo *init(MADSEngine *vm);

	/**
	 loads the data
	 */
	void load(int sceneId, int flags, const Common::String &resName, int v3, 
		MSurface &depthSurface, MSurface &bgSurface);
};

class SceneInfoNebular : public SceneInfo {
	friend class SceneInfo;
protected:
	virtual void loadCodes(MSurface &depthSurface);

	/**
	* Constructor
	*/
	SceneInfoNebular(MADSEngine *vm) : SceneInfo(vm) {}
};

} // End of namespace MADS

#endif /* MADS_SCENE_DATA_H */
