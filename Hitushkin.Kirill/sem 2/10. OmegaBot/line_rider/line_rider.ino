// Definition
#define PIN_BUTTON 11

// Global variables

enum State { Stop, Search, Follow, Back};
enum Side { Left, Right, Unknown};

class LineRider 
{
private:

    int sensor_left_pin_ = A1;
    int sensor_right_pin_ = A0;
    int motor_speed_left_pin_ = 6;
    int motor_speed_right_pin_ = 5;
    int motor_dir_left_pin_ = 7;
    int motor_dir_right_pin_ = 4;

    State state_ = State::Stop;
    Side last_side = Side::Unknown;
    int sensor_diff_;
    int calib_arr_size = 50;
    int sensor_max_diff_ = 200;
    float diff_coef = 12;
    int black_val_ = 750;
    int miss_line_count_ = 0;

    int sensor_left_val_;
    int sensor_right_val_;

    const static size_t timers_count = 10;
    unsigned long pref_time_[timers_count];

public:

    LineRider();

    void calibrate();
    void init();

    void spin();

    void sensors_update();

    void stop();
    void search();
    void follow();
    void back();

    void set_motor(int left_speed, int right_speed);

    void enable_timer(const int idx);
    unsigned int get_timer(const int idx);
    void disable_timer(const int idx);
    void disable_all_timers();

} Planner;


void wait_button(int button_pin)
{
    while (digitalRead(button_pin) == LOW) {}
    delay(200);
    while (digitalRead(button_pin) == HIGH) {}
    delay(200);
}


void setup() {

    Serial.begin(9600);

    pinMode(PIN_BUTTON, INPUT);
    
}

void loop() {

    Serial.print("Wait\n");
    wait_button(PIN_BUTTON);

    Serial.print("Calib\n");
    Planner.calibrate();

    wait_button(PIN_BUTTON);

    Serial.print("Spin\n");
    Planner.init();

    while (digitalRead(PIN_BUTTON) == LOW) 
    {
        Planner.spin();
    }

    Planner.stop();
    wait_button(PIN_BUTTON);

}
