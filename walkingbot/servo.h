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
		int pos_ = 0;
		int ramp_speed_ = 1;
		unsigned long last_loop_time_ = 0;
};

} // namTowerPro
