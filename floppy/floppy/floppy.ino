#define FOWARD LOW
#define BACKWARD HIGH

#define MAX_HEAD_POS 160

int step_pin = 2;    /* this pin used for steps */
int dir_pin = 3;     /* this pin is used for direction */
int dir;             /* BACKWARD or FOWARD */
int head_position;   /* controls the position of the head of the floppy */

void toggle_dir();
void change_dir(int direct);
void reset_floppy();
void floppy_tone(int frequency, long time);
void floppy_tick(int delay_amount);
/* For debugging */
void find_max_head_pos();

void setup() {
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    Serial.begin(9600);
    reset_floppy();
    delay(1000);
    int dir = FOWARD;
}

void loop() {    
    //floppy_tone(1000, 100);
    delay(100);
}

void toggle_dir() {
    dir = 1 - dir;
    digitalWrite(dir_pin, dir);
}

void change_dir(int direct) {
    dir = direct;
    digitalWrite(dir_pin, dir);
}

void reset_floppy() {
    change_dir(BACKWARD);
    head_position = MAX_HEAD_POS;
    while (head_position > 0) {
        floppy_tick(1);
        delay(1);
    }
    change_dir(FOWARD);
}

/*
 * frequency is in Hz
 * time is in miliseconds
 */
void floppy_tone(int frequency, long time) {
    int x;
    long delay_amount = (long)(1000000 / frequency);             /* gap between the floppy ticks */
    long loop_time = (long)((time*1000)/(delay_amount*2));       /* times to tick */
    for (x = 0; x < loop_time; x++) { 
        Serial.println(head_position);
        if (head_position >= MAX_HEAD_POS || head_position <= 0) 
            toggle_dir();
        floppy_tick(delay_amount);
    }
}

void floppy_tick(int delay_amount) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(delay_amount);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(delay_amount);
    if (dir == FOWARD)
        head_position++;
    else
        head_position--;
}

/* Debugging */
void find_max_head_pos() {
    int my_guess = 80;
    int temp = dir;
    reset_floppy();
    while (head_position  < my_guess) {
        digitalWrite(step_pin, HIGH);
        delay(1);
        digitalWrite(step_pin, LOW);
        delay(1);
        head_position++;
    }
    dir = temp;
}
