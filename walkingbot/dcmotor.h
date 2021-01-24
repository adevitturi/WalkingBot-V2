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
*/s

#pragma once

#include <Arduino.h>

namespace L298N{

class DcMotors {
	public:
		DcMotors(int pin_en_a, int pin_en_b, int pin_dir1, int pin_dir2, int pin_dir3, int pin_dir4);
		int get_left_speed();
		int get_right_speed();
		void set_diff_drive_speed(int linear, int angular);

		void loop();

	private:
		void do_loop();
		void set_left_speed_instant(int speed);
		void set_right_speed_instant(int speed);
		void update_speed();
		int compute_speed_ramp_ratio(int speed_setpoint, int current_speed);
		int compute_speed_setpoint(int speed);

		int pin_en_a_ = 0;
		int pin_en_b_ = 0;
		int pin_dir1_ = 0;
		int pin_dir2_ = 0;
		int pin_dir3_ = 0;
		int pin_dir4_ = 0;

		int left_speed_ = 0;
		int right_speed_ = 0;
		int left_speed_setpoint_ = 0;
		int right_speed_setpoint_ = 0;

		int ramp_speed_ = 10;
		unsigned long last_loop_time_ = 0;
};
} // namespace L298N
