#define FOWARD LOW
#define BACKWARD HIGH

#define MAX_HEAD_POS 80

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


/* got from https://gist.githubusercontent.com/nubiasouza/e211566607c3eed29c55/raw/musicmarioarduino */
//melodia do MARIO THEME
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
//duracao de cada nota
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};

void setup() {
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    Serial.begin(9600);
    reset_floppy();
    delay(1000);
    int dir = FOWARD;
}

void loop() {    
    //for para tocar as 156 notas comeÃ§ando no 0 ate 156 ++ incrementado
    for (int nota = 0; nota < 156; nota++) {
        int duracaodanota = duracaodasnotas[nota];
        floppy_tone(melodia[nota],duracaodanota);
        //pausa depois das notas
        int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
        delay(pausadepoisdasnotas[nota]);
    }
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
    long long delay_amount = (long long)(1000000 / frequency);             /* gap between the floppy ticks */
    long long loop_time = (long long)((time*1000)/(delay_amount*2));       /* times to tick */
    for (x = 0; x < loop_time; x++) { 
        if ((head_position <= 0 && dir == BACKWARD) ||(head_position >= MAX_HEAD_POS && dir == FOWARD)) 
            toggle_dir();
        floppy_tick(delay_amount);
    }
}

void floppy_tick(int delay_amount) {
    Serial.println(delay_amount);
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
