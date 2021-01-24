/*
Copyright (c) 2017, Agustin Devitturi (agustin.devitturi@gmail.com)
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "servo.h"

namespace TowerPro {

static const unsigned long LOOP_INTERVAL = 50;
static const int MAX_POS = 100;

Servo::Servo(int pin_signal, int initial_pos) {
	pin_signal_ = pin_signal;
	pos_ = initial_pos;
	analogWriteRange(MAX_POS);
}

void Servo::go_to_pos(int pos) {
	if (pos < 0) {
		return;
	}

	if (pos > MAX_POS) {
		pos = MAX_POS;
	}

	pos_setpoint_ = pos;
}

void Servo::loop() {
	unsigned long current_time = millis();
	if (current_time - last_loop_time_ > LOOP_INTERVAL) {
		do_loop();
		last_loop_time_ = current_time;
	}
}

void Servo::do_loop() {
	int error_pos = pos_setpoint_ - pos_;
	if (error_pos == 0) {
		return;
	}

	int ramp_ratio;
	if (abs(error_pos) >= ramp_speed_) {
		ramp_ratio = ramp_speed_;
	} else {
		ramp_ratio = abs(error_pos);
	}

	if (error_pos > 0) {
		set_pos_instant(pos_ + ramp_ratio);
	} else {
		set_pos_instant(pos_ - ramp_ratio);
	}
}

void Servo::set_pos_instant(int pos) {
  if (pos == pos_) {
    return;
  }
	analogWrite(pin_signal_, pos);
	pos_ = pos;
}

} // namespoace TowerPro
