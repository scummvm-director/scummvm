/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
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

#ifndef PEGASUS_INPUT_H
#define PEGASUS_INPUT_H

#include "common/rect.h"

#include "pegasus/constants.h"
#include "pegasus/types.h"

namespace Pegasus {

class Hotspot;
class Input;

class InputDevice {
public:
	InputDevice();
	~InputDevice();

	void getInput(Input&, const tInputBits);

	void waitInput(const tInputBits);

protected:
	tInputBits _lastRawBits;
};

enum {
	kButtonDownBit = 0,
	kAutoButtonBit = 1,
	kBitsPerButton = 2,
	
	kButtonDownMask = 1 << kButtonDownBit,
	kAutoButtonMask = 1 << kAutoButtonBit,
	
	kButtonStateBits = kButtonDownMask | kAutoButtonMask,
	
	kRawButtonUp = 0,
	kRawButtonDown = kButtonDownMask | kAutoButtonMask,
	
	kButtonUp = 0,
	kButtonDown = kButtonDownMask,
	kButtonAutoUp = kAutoButtonMask,
	kButtonAutoDown = kButtonDownMask | kAutoButtonMask
};

enum {
	kUpButtonNum = 0,
	kLeftButtonNum = 1,
	kDownButtonNum = 2,
	kRightButtonNum = 3,
	kLeftFireButtonNum = 4,
	kRightFireButtonNum = 5,
	kOneButtonNum = 6,
	kTwoButtonNum = 7,
	kThreeButtonNum = 8,
	kFourButtonNum = 9,
	kMod1ButtonNum = 10,
	kMod2ButtonNum = 11,
	kMod3ButtonNum = 12
};

enum {
	kUpButtonShift = kUpButtonNum * kBitsPerButton,
	kLeftButtonShift = kLeftButtonNum * kBitsPerButton,
	kDownButtonShift = kDownButtonNum * kBitsPerButton,
	kRightButtonShift = kRightButtonNum * kBitsPerButton,
	kLeftFireButtonShift = kLeftFireButtonNum * kBitsPerButton,
	kRightFireButtonShift = kRightFireButtonNum * kBitsPerButton,
	kOneButtonShift = kOneButtonNum * kBitsPerButton,
	kTwoButtonShift = kTwoButtonNum * kBitsPerButton,
	kThreeButtonShift = kThreeButtonNum * kBitsPerButton,
	kFourButtonShift = kFourButtonNum * kBitsPerButton,
	kMod1ButtonShift = kMod1ButtonNum * kBitsPerButton,
	kMod2ButtonShift = kMod2ButtonNum * kBitsPerButton,
	kMod3ButtonShift = kMod3ButtonNum * kBitsPerButton
};

enum {
	kAllUpBits =	(kButtonUp << kUpButtonShift) |
					(kButtonUp << kLeftButtonShift) |
					(kButtonUp << kDownButtonShift) |
					(kButtonUp << kRightButtonShift) |
					(kButtonUp << kLeftFireButtonShift) |
					(kButtonUp << kRightFireButtonShift) |
					(kButtonUp << kOneButtonShift) |
					(kButtonUp << kTwoButtonShift) |
					(kButtonUp << kThreeButtonShift) |
					(kButtonUp << kFourButtonShift) |
					(kButtonUp << kMod1ButtonShift) |
					(kButtonUp << kMod2ButtonShift) |
					(kButtonUp << kMod3ButtonShift),
	kDirectionBits =	(kButtonDownMask << kUpButtonShift) |
						(kButtonDownMask << kLeftButtonShift) |
						(kButtonDownMask << kDownButtonShift) |
						(kButtonDownMask << kRightButtonShift),
	kButtonBits =	(kButtonDownMask << kLeftFireButtonShift) |
					(kButtonDownMask << kRightFireButtonShift) |
					(kButtonDownMask << kOneButtonShift) |
					(kButtonDownMask << kTwoButtonShift) |
					(kButtonDownMask << kThreeButtonShift) |
					(kButtonDownMask << kFourButtonShift) |
					(kButtonDownMask << kMod1ButtonShift) |
					(kButtonDownMask << kMod2ButtonShift) |
					(kButtonDownMask << kMod3ButtonShift),
	kAllButtonDownBits = kDirectionBits | kButtonBits,
	kAllAutoBits =	(kAutoButtonMask << kUpButtonShift) |
					(kAutoButtonMask << kLeftButtonShift) |
					(kAutoButtonMask << kDownButtonShift) |
					(kAutoButtonMask << kRightButtonShift) |
					(kAutoButtonMask << kLeftFireButtonShift) |
					(kAutoButtonMask << kRightFireButtonShift) |
					(kAutoButtonMask << kOneButtonShift) |
					(kAutoButtonMask << kTwoButtonShift) |
					(kAutoButtonMask << kThreeButtonShift) |
					(kAutoButtonMask << kFourButtonShift) |
					(kAutoButtonMask << kMod1ButtonShift) |
					(kAutoButtonMask << kMod2ButtonShift) |
					(kAutoButtonMask << kMod3ButtonShift),
	
	kFilterUpButton =			kButtonDownMask << kUpButtonShift,
	kFilterUpAuto =				kAutoButtonMask << kUpButtonShift,
	kFilterUpButtonAny =		kFilterUpButton | kFilterUpAuto,
	kFilterLeftButton =			kButtonDownMask << kLeftButtonShift,
	kFilterLeftAuto =			kAutoButtonMask << kLeftButtonShift,
	kFilterLeftButtonAny =		kFilterLeftButton | kFilterLeftAuto,
	kFilterDownButton =			kButtonDownMask << kDownButtonShift,
	kFilterDownAuto =			kAutoButtonMask << kDownButtonShift,
	kFilterDownButtonAny =		kFilterDownButton | kFilterDownAuto,
	kFilterRightButton =		kButtonDownMask << kRightButtonShift,
	kFilterRightAuto =			kAutoButtonMask << kRightButtonShift,
	kFilterRightButtonAny =		kFilterRightButton | kFilterRightAuto,
	kFilterLeftFireButton =		kButtonDownMask << kLeftFireButtonShift,
	kFilterLeftFireAuto =		kAutoButtonMask << kLeftFireButtonShift,
	kFilterLeftFireButtonAny =	kFilterLeftFireButton | kFilterLeftFireAuto,
	kFilterRightFireButton =	kButtonDownMask << kRightFireButtonShift,
	kFilterRightFireAuto =		kAutoButtonMask << kRightFireButtonShift,
	kFilterRightFireButtonAny =	kFilterRightFireButton | kFilterRightFireAuto,
	kFilterOneButton =			kButtonDownMask << kOneButtonShift,
	kFilterOneAuto =			kAutoButtonMask << kOneButtonShift,
	kFilterOneButtonAny =		kFilterOneButton | kFilterOneAuto,
	kFilterTwoButton =			kButtonDownMask << kTwoButtonShift,
	kFilterTwoAuto =			kAutoButtonMask << kTwoButtonShift,
	kFilterTwoButtonAny =		kFilterTwoButton | kFilterTwoAuto,
	kFilterThreeButton =		kButtonDownMask << kThreeButtonShift,
	kFilterThreeAuto =			kAutoButtonMask << kThreeButtonShift,
	kFilterThreeButtonAny =		kFilterThreeButton | kFilterThreeAuto,
	kFilterFourButton =			kButtonDownMask << kFourButtonShift,
	kFilterFourAuto =			kAutoButtonMask << kFourButtonShift,
	kFilterFourButtonAny =		kFilterFourButton | kFilterFourAuto,
	kFilterMod1Button =			kButtonDownMask << kMod1ButtonShift,
	kFilterMod1Auto =			kAutoButtonMask << kMod1ButtonShift,
	kFilterMod1ButtonAny =		kFilterMod1Button | kFilterMod1Auto,
	kFilterMod2Button =			kButtonDownMask << kMod2ButtonShift,
	kFilterMod2Auto =			kAutoButtonMask << kMod2ButtonShift,
	kFilterMod2ButtonAny =		kFilterMod2Button | kFilterMod2Auto,
	kFilterMod3Button =			kButtonDownMask << kMod3ButtonShift,
	kFilterMod3Auto =			kAutoButtonMask << kMod3ButtonShift,
	kFilterMod3ButtonAny =		kFilterMod3Button | kFilterMod3Auto,
	
	kFilterNoInput =			0,
	kFilterAllInput =			kFilterUpButton |
								kFilterUpAuto |
								kFilterLeftButton |
								kFilterLeftAuto |
								kFilterDownButton |
								kFilterDownAuto |
								kFilterRightButton |
								kFilterRightAuto |
								kFilterLeftFireButton |
								kFilterLeftFireAuto |
								kFilterRightFireButton |
								kFilterRightFireAuto |
								kFilterOneButton |
								kFilterOneAuto |
								kFilterTwoButton |
								kFilterTwoAuto |
								kFilterThreeButton |
								kFilterThreeAuto |
								kFilterFourButton |
								kFilterFourAuto |
								kFilterMod1Button |
								kFilterMod1Auto |
								kFilterMod2Button |
								kFilterMod2Auto |
								kFilterMod3Button |
								kFilterMod3Auto,
	
	kFilterAllDirections =		kFilterUpButton |
								kFilterUpAuto |
								kFilterLeftButton |
								kFilterLeftAuto |
								kFilterDownButton |
								kFilterDownAuto |
								kFilterRightButton |
								kFilterRightAuto,
	
	kFilterButtons =			kFilterOneButton |
								kFilterOneAuto |
								kFilterTwoButton |
								kFilterTwoAuto |
								kFilterThreeButton |
								kFilterThreeAuto |
								kFilterFourButton |
								kFilterFourAuto,
	
	kFilterFireButtons =		kFilterLeftFireButton |
								kFilterLeftFireAuto |
								kFilterRightFireButton |
								kFilterRightFireAuto,
	
	kFilterAllButtons =			kFilterLeftFireButton |
								kFilterLeftFireAuto |
								kFilterRightFireButton |
								kFilterRightFireAuto |
								kFilterOneButton |
								kFilterOneAuto |
								kFilterTwoButton |
								kFilterTwoAuto |
								kFilterThreeButton |
								kFilterThreeAuto |
								kFilterFourButton |
								kFilterFourAuto |
								kFilterMod1Button |
								kFilterMod1Auto |
								kFilterMod2Button |
								kFilterMod2Auto |
								kFilterMod3Button |
								kFilterMod3Auto,
	
	kFilterAllInputNoAuto =		kFilterUpButton |
								kFilterLeftButton |
								kFilterDownButton |
								kFilterRightButton |
								kFilterLeftFireButton |
								kFilterRightFireButton |
								kFilterOneButton |
								kFilterTwoButton |
								kFilterThreeButton |
								kFilterFourButton |
								kFilterMod1Button |
								kFilterMod2Button |
								kFilterMod3Button
};

/*

	Buttons are defined as:
		up, left, down, right		direction buttons.
		fireLeft, fireRight:		fire buttons.
		mod1, mod2, mod3:			modifier buttons, similar to shift, control, etc.
		a, b, c, d:					general purpose buttons.
	
	button state is held as bits in a long word, two bits per button.
	
	Filter bits:
		for each button, two bits are assigned for filtering. If bit 0 is set, the
		corresponding button is available for "button down" input. If bit 1 is set,
		the corresponding button is available for "auto down" input. Note that bit
		1 is meaningful only if bit 0 is set.
	
*/

class Input {
friend int operator==(const Input &, const Input &);
friend int operator!=(const Input &, const Input &);
friend class InputDevice;

public:
	Input() { clearInput(); }

	bool upButtonDown() const { return (_inputState & (kButtonStateBits << kUpButtonShift)) == (kButtonDown << kUpButtonShift); }
	bool upButtonAutoDown() const { return (_inputState & (kButtonStateBits << kUpButtonShift)) == (kButtonAutoDown << kUpButtonShift); }
	bool upButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kUpButtonShift)) != 0; }
	
	bool leftButtonDown() const { return (_inputState & (kButtonStateBits << kLeftButtonShift)) == (kButtonDown << kLeftButtonShift); }
	bool leftButtonAutoDown() const { return (_inputState & (kButtonStateBits << kLeftButtonShift)) == (kButtonAutoDown << kLeftButtonShift); }
	bool leftButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kLeftButtonShift)) != 0; }
	
	bool downButtonDown() const { return (_inputState & (kButtonStateBits << kDownButtonShift)) == (kButtonDown << kDownButtonShift); }
	bool downButtonAutoDown() const { return (_inputState & (kButtonStateBits << kDownButtonShift)) == (kButtonAutoDown << kDownButtonShift); }
	bool downButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kDownButtonShift)) != 0; }
	
	bool rightButtonDown() const { return (_inputState & (kButtonStateBits << kRightButtonShift)) == (kButtonDown << kRightButtonShift); }
	bool rightButtonAutoDown() const { return (_inputState & (kButtonStateBits << kRightButtonShift)) == (kButtonAutoDown << kRightButtonShift); }
	bool rightButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kRightButtonShift)) != 0; }
	
	bool leftFireButtonDown() const { return (_inputState & (kButtonStateBits << kLeftFireButtonShift)) == (kButtonDown << kLeftFireButtonShift); }
	bool leftFireButtonAutoDown() const { return (_inputState & (kButtonStateBits << kLeftFireButtonShift)) == (kButtonAutoDown << kLeftFireButtonShift); }
	bool leftFireButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kLeftFireButtonShift)) != 0; }
	
	bool rightFireButtonDown() const { return (_inputState & (kButtonStateBits << kRightFireButtonShift)) == (kButtonDown << kRightFireButtonShift); }
	bool rightFireButtonAutoDown() const { return (_inputState & (kButtonStateBits << kRightFireButtonShift)) == (kButtonAutoDown << kRightFireButtonShift); }
	bool rightFireButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kRightFireButtonShift)) != 0; }
	
	bool oneButtonDown() const { return	(_inputState & (kButtonStateBits << kOneButtonShift)) == (kButtonDown << kOneButtonShift); }
	bool oneButtonAutoDown() const { return (_inputState & (kButtonStateBits << kOneButtonShift)) == (kButtonAutoDown << kOneButtonShift); }
	bool oneButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kOneButtonShift)) != 0; }

	bool twoButtonDown() const { return (_inputState & (kButtonStateBits << kTwoButtonShift)) == (kButtonDown << kTwoButtonShift); }
	bool twoButtonAutoDown() const { return (_inputState & (kButtonStateBits << kTwoButtonShift)) == (kButtonAutoDown << kTwoButtonShift); }
	bool twoButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kTwoButtonShift)) != 0; }
	
	bool threeButtonDown() const { return (_inputState & (kButtonStateBits << kThreeButtonShift)) == (kButtonDown << kThreeButtonShift); }
	bool threeButtonAutoDown() const { return (_inputState & (kButtonStateBits << kThreeButtonShift)) == (kButtonAutoDown << kThreeButtonShift); }
	bool threeButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kThreeButtonShift)) != 0; }
	
	bool fourButtonDown() const { return (_inputState & (kButtonStateBits << kFourButtonShift)) == (kButtonDown << kFourButtonShift); }
	bool fourButtonAutoDown() const { return (_inputState & (kButtonStateBits << kFourButtonShift)) == (kButtonAutoDown << kFourButtonShift); }
	bool fourButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kFourButtonShift)) != 0; }
	
	bool mod1ButtonDown() const { return (_inputState & (kButtonStateBits << kMod1ButtonShift)) == (kButtonDown << kMod1ButtonShift); }
	bool mod1ButtonAutoDown() const { return (_inputState & (kButtonStateBits << kMod1ButtonShift)) == (kButtonAutoDown << kMod1ButtonShift); }
	bool mod1ButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kMod1ButtonShift)) != 0; }
	
	bool mod2ButtonDown() const { return (_inputState & (kButtonStateBits << kMod2ButtonShift)) == (kButtonDown << kMod2ButtonShift); }
	bool mod2ButtonAutoDown() const { return (_inputState & (kButtonStateBits << kMod2ButtonShift)) == (kButtonAutoDown << kMod2ButtonShift); }
	bool mod2ButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kMod2ButtonShift)) != 0; }
	
	bool mod3ButtonDown() const { return (_inputState & (kButtonStateBits << kMod3ButtonShift)) == (kButtonDown << kMod3ButtonShift); }
	bool mod3ButtonAutoDown() const { return (_inputState & (kButtonStateBits << kMod3ButtonShift)) == (kButtonAutoDown << kMod3ButtonShift); }
	bool mod3ButtonAnyDown() const { return (_inputState & (kButtonAutoDown << kMod3ButtonShift)) != 0; }
	
	bool allAutoInput() const { return (_inputState & kAllAutoBits) != 0; }
	bool anyDirectionInput() const { return (_inputState & kDirectionBits) != 0; }
	bool anyButtonInput() const { return (_inputState & kButtonBits) != 0; }
	bool anyInput() const { return _inputState != 0; }
	
	void getInputLocation(Common::Point &where) const { where = _inputLocation; }
	
	bool anyInputBitSet(const tInputBits bits) const { return (_inputState & bits) != 0; }
	
	void clearInput() {
		_inputState = kAllUpBits;
		_inputLocation.x = 0;
		_inputLocation.y = 0;
	}

protected:
	void setInputBits(const tInputBits state) { _inputState = state; }
	void setInputLocation(const Common::Point &where) { _inputLocation = where; }
	
	tInputBits _inputState;
	Common::Point _inputLocation;
};

} // End of namespace Pegasus

#endif
