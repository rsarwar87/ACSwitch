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

#include <string>
#include <vector>

#include "battery.h"
#include "config.h"
#include "daemon.h"
#include "database.h"
#include "exception.h"
#include "setup.h"
#include "shared.h"

using namespace std;

static const string DUMMY_VALUE = "dummyValue";

static void setSwitch(const Database::Switch& switch_) {
	Config::setTrigger(switch_.trigger);
	Config::setPosVal(switch_.posVal);
	Config::setNegVal(switch_.negVal);
}

bool Setup::configGood() {
	return Shared::fileExists(Config::getTrigger());
}

void Setup::checkOrDie() {
	if (!configGood()) {
		throw("Setup is incomplete, please initialize first");
	}
	if (!Daemon::isRunning()) {
		throw("The daemon is not running, launch it first");
	}
}

void Setup::initializeSwitch(const vector<string>& args) {
	for (const Database::Switch& switch_ : Database::getSwitches()) {
		setSwitch(switch_);

		if (Battery::isCharging()) {
			Battery::stopCharging();
			if (Battery::isCharging()) {
				Battery::startCharging();
			} else {
				Battery::startCharging();
				if (Battery::isCharging()) {
					return;
				}
			}
		}
	}
	setSwitch({
		DUMMY_VALUE,
		DUMMY_VALUE,
		DUMMY_VALUE
	});
	throw("Your device is unfortunately not supported :(");
}
