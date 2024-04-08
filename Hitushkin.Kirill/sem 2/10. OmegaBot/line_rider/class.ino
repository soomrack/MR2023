
LineRider::LineRider() {}


void LineRider::calibrate()
{   
    double sensor_diff_sum = 0;
    for (int idx = 0; idx < calib_arr_size; ++idx) {
        sensors_update();
        sensor_diff_sum += sensor_left_val_ - sensor_right_val_;
    }
    sensor_diff_ = (int) (sensor_diff_sum / calib_arr_size);

    Serial.print(sensor_diff_);
    Serial.print("\n");
}

void LineRider::init()
{   
    state_ = State::Search;
    disable_all_timers();
}


void LineRider::spin()
{
    sensors_update();
    
    switch (state_) {
        case State::Stop:
            //Serial.print("Stop\n");
            stop();
            break;
        case State::Search:
            //Serial.print("Search\n");
            search();
            break;
        case State::Follow:
            //Serial.print("Follow\n");
            follow();
            break;
        case State::Back:
            //Serial.print("Back\n");
            back();
            break;
    }
}


void LineRider::sensors_update()
{
    sensor_left_val_ = analogRead(sensor_left_pin_);
    sensor_right_val_ = analogRead(sensor_right_pin_);
    
    /*Serial.print(sensor_left_val_);
    Serial.print(" : ");
    Serial.print(sensor_right_val_);
    Serial.print("\n");*/
}


void LineRider::stop()
{
    set_motor(0, 0);
}


void LineRider::search()
{
    if (sensor_left_val_ > black_val_ || sensor_right_val_ > black_val_) {
        state_ = State::Follow;
        disable_all_timers();
        return;
    }

    if (get_timer(0)  > 6000) {
        state_ = State::Stop;
        return;
    }
    
    if (last_side == Side::Left) {
        set_motor(40, 255);
    } else {
        set_motor(255, 50);
    }
    
}


void LineRider::follow()
{
    if (sensor_left_val_ < black_val_ && sensor_right_val_ < black_val_) {
        if (get_timer(0) > 50) {
            disable_all_timers();
            state_ = State::Back;
            return;
        }
    } else {
        disable_timer(0);
        if (sensor_left_val_ < black_val_) last_side = Side::Right;
        else if (sensor_right_val_ < black_val_) last_side = Side::Left;
    }
    
    int diff = sensor_left_val_ - sensor_right_val_ - sensor_diff_;
    diff = (int) constrain((float) diff * diff_coef, -sensor_max_diff_, sensor_max_diff_);

    int motor_left_val = 255;
    int motor_right_val = 255;

    if (abs(diff) > 40) {
        motor_left_val = map(-diff, -sensor_max_diff_, abs(diff), -50, 255);
        motor_right_val = map(diff, -sensor_max_diff_, abs(diff), -50, 255);
    }

    /*int motor_left_val = constrain(255 - diff, 0, 255);
    int motor_right_val = constrain(255 + diff, 0, 255);*/
    
    /*constrain(abs(diff), 0, 10)
    Serial.print(diff);
    Serial.print("\n");

    int motor_left_val = 160;
    int motor_right_val = 160;
    
    if (abs(diff) < 100) {
        if (get_timer(1) > 300) {
            int motor_left_val = 255;
            int motor_right_val = 255;
        }
    } else {
        disable_timer(1);
        int motor_left_val = map(-diff, -sensor_max_diff_, sensor_max_diff_, 0, 255);
        int motor_right_val = map(diff, -sensor_max_diff_, sensor_max_diff_, 0, 255);
    }
    */
    set_motor(motor_left_val, motor_right_val);
}


void LineRider::back()
{
    if (sensor_left_val_ > black_val_ || sensor_right_val_ > black_val_) {
        if (get_timer(0) > 10) {
            state_ = State::Search;
            disable_all_timers();
            return;
        }
    } else {
        disable_timer(0);
    }

    if (get_timer(1) > 1000) {
        state_ = State::Search;
        return;
    }

    set_motor(-100, -100);
}


void LineRider::set_motor(int left_speed, int right_speed)
{
    digitalWrite(motor_dir_left_pin_, (left_speed >= 0) ? HIGH : LOW);
    digitalWrite(motor_dir_right_pin_, (right_speed >= 0) ? HIGH : LOW);

    analogWrite(motor_speed_left_pin_, constrain(abs(left_speed), 0, 250));
    analogWrite(motor_speed_right_pin_, constrain(abs(right_speed), 0, 250));

    Serial.print(left_speed);
    Serial.print(" : ");
    Serial.print(right_speed);
    Serial.print("\n");
}


void LineRider::enable_timer(const int idx)
{
    pref_time_[idx] = millis();
}

unsigned int LineRider::get_timer(const int idx)
{
    if (!pref_time_[idx]) enable_timer(idx);
    return millis() - pref_time_[idx];
}

void LineRider::disable_timer(const int idx)
{
    pref_time_[idx] = 0;
}

void LineRider::disable_all_timers()
{
    for (size_t idx = 0; idx < timers_count; idx++)
        disable_timer(idx);
}

