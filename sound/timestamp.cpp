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
 * $URL$
 * $Id$
 *
 */

#include "sound/timestamp.h"

namespace Audio {

static uint gcd(uint a, uint b) {
	while (a > 0) {
		int tmp = a;
		a = b % a;
		b = tmp;
	}
	return b;
}

Timestamp::Timestamp(uint32 ms, int fr) {
	assert(fr > 0);

	_secs = ms / 1000;
	_framerateFactor = 1000 / gcd(1000, fr);
	_framerate = fr * _framerateFactor;

	// Note that _framerate is always divisible by 1000.
	_numberOfFrames = (ms % 1000) * (_framerate / 1000);
}

Timestamp::Timestamp(uint s, int frames, int fr) {
	assert(fr > 0);

	_secs = s;
	_framerateFactor = 1000 / gcd(1000, fr);
	_framerate = fr * _framerateFactor;
	_numberOfFrames = 0;
	addFramesIntern(frames * _framerateFactor);
}

Timestamp Timestamp::convertToFramerate(int newFramerate) const {
	Timestamp ts(*this);

	if (ts.framerate() != newFramerate) {
		ts._framerateFactor = 1000 / gcd(1000, newFramerate);
		ts._framerate = newFramerate * ts._framerateFactor;

		const uint g = gcd(_framerate, ts._framerate);
		const uint p = _framerate / g;
		const uint q = ts._framerate / g;

		// Convert the frame offset to the new framerate.
		// We round to the nearest (as opposed to always
		// rounding down), to minimize rounding errors during
		// round trip conversions.
		ts._numberOfFrames = (ts._numberOfFrames * q + p/2) / p;

		ts._secs += (ts._numberOfFrames / ts._framerate);
		ts._numberOfFrames %= ts._framerate;
	}

	return ts;
}

bool Timestamp::operator==(const Timestamp &ts) const {
	return cmp(ts) == 0;
}

bool Timestamp::operator!=(const Timestamp &ts) const {
	return cmp(ts) != 0;
}

bool Timestamp::operator<(const Timestamp &ts) const {
	return cmp(ts) < 0;
}

bool Timestamp::operator<=(const Timestamp &ts) const {
	return cmp(ts) <= 0;
}

bool Timestamp::operator>(const Timestamp &ts) const {
	return cmp(ts) > 0;
}

bool Timestamp::operator>=(const Timestamp &ts) const {
	return cmp(ts) >= 0;
}

int Timestamp::cmp(const Timestamp &ts) const {
	int delta = _secs - ts._secs;
	if (!delta) {
		const uint g = gcd(_framerate, ts._framerate);
		const uint p = _framerate / g;
		const uint q = ts._framerate / g;

		delta = (_numberOfFrames * q - ts._numberOfFrames * p);
	}

	return delta;
}


Timestamp Timestamp::addFrames(int frames) const {
	Timestamp ts(*this);

	// The frames are given in the original framerate, so we have to
	// adjust by _framerateFactor accordingly.
	ts.addFramesIntern(frames * _framerateFactor);

	return ts;
}

void Timestamp::addFramesIntern(int frames) {
	_numberOfFrames += frames;

	if (_numberOfFrames < 0) {
		int secsub = 1 + (-_numberOfFrames / _framerate);

		_numberOfFrames += _framerate * secsub;
		_secs -= secsub;
	}

	// Wrap around if necessary
	_secs += (_numberOfFrames / _framerate);
	_numberOfFrames %= _framerate;
}

Timestamp Timestamp::addMsecs(int ms) const {
	assert(ms >= 0);
	Timestamp ts(*this);
	ts._secs += ms / 1000;
	// Add the remaining frames. Note that _framerate is always divisible by 1000.
	ts.addFramesIntern((ms % 1000) * (ts._framerate / 1000));
	return ts;
}

int Timestamp::frameDiff(const Timestamp &ts) const {

	int delta = 0;
	if (_secs != ts._secs)
		delta = (long(_secs) - long(ts._secs)) * _framerate;

	delta += _numberOfFrames;

	if (_framerate == ts._framerate) {
		delta -= ts._numberOfFrames;
	} else {
		// We need to multiply by the quotient of the two framerates.
		// We cancel the GCD in this fraction to reduce the risk of
		// overflows.
		const uint g = gcd(_framerate, ts._framerate);
		const uint p = _framerate / g;
		const uint q = ts._framerate / g;

		delta -= (ts._numberOfFrames * p + q/2) / q;
	}

	return delta / _framerateFactor;
}

int Timestamp::msecsDiff(const Timestamp &ts) const {
	return long(msecs()) - long(ts.msecs());
}

uint32 Timestamp::msecs() const {
	// Note that _framerate is always divisible by 1000.
	return _secs * 1000 + _numberOfFrames / (_framerate / 1000);
}


} // End of namespace Audio
