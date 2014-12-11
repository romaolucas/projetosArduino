#define FOWARD LOW
#define BACKWARD HIGH

int step_pin = 2;    /*this pin used for steps*/
int dir_pin = 3;     /*this pin is used for direction*/
int dir;             /*BACKWARD or FOWARD*/
int head_position;   /*controls the position of the head of the floppy*/

/* Prototypes */
void toggle_dir();
void change_dir(int direct);
void reset_floppy();
void floppy_tone(int frequency, long time);

/* Debugging */
void find_max_head_pos();

void setup() {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  Serial.begin(9600);
  reset_floppy();
  int dir = FOWARD;
}

void loop() {    
  /*find_max_head_pos();*/
  delay(1000);
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
  floppy_tone(1000, 100);
}

/*
 * frequency is in Hz
 * time is in miliseconds
 */
void floppy_tone(int frequency, long time) {
  int x;
  long delayAmount = (long)(1000000 / frequency);             /*gap between the "clock ticks"*/
  long loopTime = (long)((time*1000)/(delayAmount*2));        /*time ticking*/
  Serial.println("passei :)");
  for (x = 0; x < loopTime; x++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(delayAmount);         
  }
}

/* Debugging */
void find_max_head_pos() {
  int pos = 0;
  int my_guess = 80; 
  int temp = dir;
  dir = FOWARD;
  reset_floppy();
  while (pos < my_guess) {
    digitalWrite(step_pin, HIGH);
    delay(1);
    digitalWrite(step_pin, LOW);
    delay(1);
    pos++;
  }
  dir = temp;
}

