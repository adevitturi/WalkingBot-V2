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

#pragma once

#include <Arduino.h>

namespace TowerPro {

class Servo {
	public:
		Servo(int pin_signal, int initial_pos);
		void go_to_pos(int pos);
		void loop();
	
	private:
		void do_loop();
		void set_pos_instant(int pos);
		int pin_signal_ = 0;
		int pos_setpoint_ = 0;
		int pos_ = 50;
		int ramp_speed_ = 1;
		unsigned long last_loop_time_ = 0;
};

} // namTowerPro
