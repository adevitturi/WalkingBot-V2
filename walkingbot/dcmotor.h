#pragma once

#include <Arduino.h>

namespace L298N{

class DcMotors {
	public:
		DcMotors(int pin_en_a, int pin_en_b, int pin_dir1, int pin_dir2, int pin_dir3, int pin_dir4);

		void set_left_speed(int speed);
		void set_right_speed(int speed);
		int get_left_speed();
		int get_right_speed();
		void set_diff_drive_speed(int linear, int angular);

		void loop();

	private:
		void do_loop();
		void set_left_speed_instant(int speed);
		void set_right_speed_instant(int speed);
		void update_speed();
		void update_left_speed();
		void update_right_speed();

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
