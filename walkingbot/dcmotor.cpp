#include "dcmotor.h"

namespace L298N{

static const unsigned long LOOP_INTERVAL = 100;
static const int MAX_SPEED = 100;
static const int MIN_SPEED = 10;
static const int PWM_FREQ = 10000;

DcMotors::DcMotors(int pin_en_a, int pin_en_b, int pin_dir1, int pin_dir2, int pin_dir3, int pin_dir4) {
	pin_en_a_ = pin_en_a;
	pin_en_b_ = pin_en_b;
	pin_dir1_ = pin_dir1;
	pin_dir2_ = pin_dir2;
	pin_dir3_ = pin_dir3;
	pin_dir4_ = pin_dir4;
	pinMode(pin_en_a_, OUTPUT);
  pinMode(pin_en_b_, OUTPUT);
  pinMode(pin_dir1_, OUTPUT);
  pinMode(pin_dir2_, OUTPUT);
  pinMode(pin_dir3_, OUTPUT);
  pinMode(pin_dir4_, OUTPUT);

  analogWriteRange(MAX_SPEED);
  analogWriteFreq(PWM_FREQ);
}

void DcMotors::loop() {
	unsigned long current_time = millis();
	if (current_time - last_loop_time_ > LOOP_INTERVAL) {
		do_loop();
		last_loop_time_ = current_time;
	}	
}

void DcMotors::do_loop() {
	update_speed();
}

void DcMotors::update_speed() {
	set_left_speed_instant(left_speed_ + compute_speed_ramp_ratio(left_speed_setpoint_, left_speed_));
	set_right_speed_instant(right_speed_ + compute_speed_ramp_ratio(right_speed_setpoint_, right_speed_));
}

int DcMotors::compute_speed_ramp_ratio(int speed_setpoint, int current_speed) {
	int speed_error = speed_setpoint - current_speed;
	if (speed_error == 0) {
		return speed_error;
	}

	int ramp_ratio;
	if (abs(speed_error) >= ramp_speed_) {
		ramp_ratio = ramp_speed_;
	} else {
		ramp_ratio = abs(speed_error);
	}
	if (speed_error > 0) {
		return ramp_ratio;
	} else  {
		return ramp_ratio * (-1); 
	}
}

int DcMotors::compute_speed_setpoint(int speed) {
	if (abs(speed) > MAX_SPEED) {
		if (speed >= 0) {
			speed = MAX_SPEED;
		} else {
			speed = -1 * MAX_SPEED;
		}
	}
	if (abs(speed) < MIN_SPEED) {
		speed = 0;
	}
	return speed;	
}

int DcMotors::get_right_speed() {
	return right_speed_;
}

int DcMotors::get_left_speed() {
	return left_speed_;
}


void DcMotors::set_right_speed_instant(int speed) {
	if (right_speed_ == speed) {
		return;
	}

  if (speed > 0) {
		digitalWrite(pin_dir2_, LOW);
  	digitalWrite(pin_dir1_, HIGH);
	} else if (speed < 0) {
		digitalWrite(pin_dir2_, HIGH);
  	digitalWrite(pin_dir1_, LOW);
	} else {
		digitalWrite(pin_dir2_, LOW);
  	digitalWrite(pin_dir1_, LOW);	
	}
  analogWrite(pin_en_a_, abs(speed));
  right_speed_ = speed;
}

void DcMotors::set_left_speed_instant(int speed) {
	if (left_speed_ == speed) {
		return;
	}

	if (speed > 0) {
		digitalWrite(pin_dir3_, LOW);
  	digitalWrite(pin_dir4_, HIGH);
	} else if (speed < 0) {
		digitalWrite(pin_dir3_, HIGH);
  	digitalWrite(pin_dir4_, LOW);
	} else {
		digitalWrite(pin_dir3_, LOW);
  	digitalWrite(pin_dir4_, LOW);	
	}
  analogWrite(pin_en_b_, abs(speed));
  left_speed_ = speed;
}

// DIFF DRIVE ECUATIONS
// VL = (Vr + Vl) / 2 	
// W = (Vr - Vl) / d

// Vr = VL + W * d/2
// Vl = VL - W * d/2

// VL : linear speed
// W : angular speed
// d : distance between wheels / legs
// Vr : right wheel speed (tangent to the ground) 
// Vl : left wheel speed (tangent to the ground)

void DcMotors::set_diff_drive_speed(int linear, int angular) {
	right_speed_setpoint_ = compute_speed_setpoint(linear + angular);
	left_speed_setpoint_ = compute_speed_setpoint(linear - angular);
}

} // namespace L298N
