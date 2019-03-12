/* Copyright (c) 2019 Jaymin Suthar. All rights reserved.
 *
 * This file is part of "Advanced Charging Switch (ACSwitch)".
 *
 * ACSwitch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, only version 3 of the License.
 *
 * ACSwitch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ACSwitch.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "exception.h"
#include "sanity.h"

const int Sanity::LEVEL_MIN = 0;
const int Sanity::LEVEL_MAX = 100;

const int Sanity::SLEEP_DELAY = 60;

int Sanity::toLevel(const string &lvlStr) {
	int level = stoi(lvlStr);

	if (level < LEVEL_MIN || level > LEVEL_MAX) {
		throw("Out of range level: " + lvlStr);
	}
	return level;
}