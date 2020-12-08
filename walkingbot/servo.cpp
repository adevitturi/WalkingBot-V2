#include "servo.h"

namespace TowerPro {

static const unsigned long LOOP_INTERVAL = 20;
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
	int diff_pos = pos_setpoint_ - pos_;
	if (diff_pos == 0) {
		return;
	}

	int updating_ramp_speed;
	if (abs(diff_pos) >= ramp_speed_) {
		updating_ramp_speed = ramp_speed_;
	} else {
		updating_ramp_speed = ramp_speed_ - abs(diff_pos);
	}

	if (diff_pos > 0) {
		set_pos_instant(pos_ + updating_ramp_speed);
	} else {
		set_pos_instant(pos_ - updating_ramp_speed);
	}
}

void Servo::set_pos_instant(int pos) {
	analogWrite(pin_signal_, pos);
	pos_ = pos;
}

} // namespoace TowerPro