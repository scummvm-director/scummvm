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
 *
 */

#ifndef TOLTECS_H
#define TOLTECS_H

#include "common/scummsys.h"
#include "common/endian.h"
#include "common/util.h"
#include "common/file.h"
#include "common/savefile.h"
#include "common/system.h"
#include "common/hash-str.h"
#include "common/events.h"
#include "common/keyboard.h"

#include "sound/audiostream.h"
#include "sound/mixer.h"
#include "sound/voc.h"
#include "sound/audiocd.h"

#include "engines/engine.h"

namespace Toltecs {

enum ToltecsGameFeatures {
	GF_PACKED = (1 << 0)
};

struct ToltecsGameDescription;

class AnimationPlayer;
class ArchiveReader;
class Input;
class Palette;
class ResourceCache;
class ScriptInterpreter;
class Screen;
class SegmentMap;

class ToltecsEngine : public ::Engine {
	Common::KeyState _keyPressed;

protected:
	int init();
	int go();
//	void shutdown();

public:
	ToltecsEngine(OSystem *syst, const ToltecsGameDescription *gameDesc);
	virtual ~ToltecsEngine();

	Common::RandomSource *_rnd;
	const ToltecsGameDescription *_gameDescription;
	uint32 getFeatures() const;
	Common::Language getLanguage() const;

	void loadScene(uint resIndex);

	void updateScreen();

	void setCamera(int16 x, int16 y);
	void setCameraTop(int16 top);
	void scrollCameraUp(int16 delta);
	void scrollCameraDown(int16 delta);
	void scrollCameraLeft(int16 delta);
	void scrollCameraRight(int16 delta);
	void updateCamera();
	
	void talk(int16 slotIndex, int16 slotOffset);
	void playText(int16 slotIndex, int16 slotOffset);

	void walk(byte *walkData);
	
	int16 findRectAtPoint(byte *rectData, int16 x, int16 y, int16 index, int16 itemSize);

public:
	AnimationPlayer *_anim;
	ArchiveReader *_arc;
	Input *_input;
	Palette *_palette;
	ResourceCache *_res;
	ScriptInterpreter *_script;
	Screen *_screen;
	SegmentMap *_segmap;

	uint _sceneResIndex;
	int16 _sceneWidth, _sceneHeight;
	//byte _scenePalette[768];

	bool _quitGame;
	int _counter01, _counter02;
	bool _movieSceneFlag;
	byte _flag01;

	// TODO: Move camera stuff into own Scene class
	int16 _cameraX, _cameraY;
	int16 _newCameraX, _newCameraY;
	int16 _cameraTop, _cameraHeight;
	int16 _yetAnotherX;

	bool _doSpeech, _doText;
	
	int16 _walkSpeedY, _walkSpeedX;

};

} // End of namespace Toltecs

#endif /* TOLTECS_H */
