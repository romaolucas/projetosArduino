
void testaLeds(int tempo);
void ascendeLed(int x, int y);
void apagaLed(int x, int y);
void zeraTabuleiro();
void toogle(int x, int y);
void desenhaTabuleiro(int tempo, int  posX, int posY);
boolean estaCompleto();
void sorteiaTabuleiro();

int cont = 0;
boolean state = true;
int posicaox = 0;
int posicaoy = 0; 
int tabuleiro[6][6];
boolean apertado = false;

void setup() {

  for(int i = 0; i <= 11; i++)
    pinMode(i,OUTPUT);
  for(int i = 0; i <= 5; i++)
    digitalWrite(i,LOW);
  for(int i = 6; i <= 11; i++)
    digitalWrite(i,HIGH);
  zeraTabuleiro();
  testaLeds(200);
  sorteiaTabuleiro();
}

void loop(){
  if (!estaCompleto()) {
    int direita = analogRead(A0);
    int esquerda = analogRead(A1);
    int cima = analogRead(A2); 
    int baixo = analogRead(A3);
    int toogleIt = analogRead(A4);
    
    if(!apertado && direita >= 600) {
      posicaox = posicaox + 1; 
      apertado = true; 
    }
    if(posicaox > 5)
      posicaox = 0;
    
  
    if(!apertado && esquerda > 600) {
      posicaox = posicaox - 1; 
      apertado = true;
    
    }
    if(posicaox < 0){
      posicaox = 5;
    }
  
    if(!apertado && cima > 600) {
      posicaoy = posicaoy + 1; 
      apertado = true;
    }
    if(posicaoy > 5){
      posicaoy = 0;
    }
  
    if(!apertado && baixo > 600) {
      posicaoy = posicaoy - 1; 
      apertado = true;
    }
     
    
    if(posicaoy < 0){
      posicaoy = 5;
    }
    
      if(!apertado && toogleIt > 600) {
      toogle(posicaox,posicaoy); 
      apertado = true;
    }
    if(baixo < 600 && cima < 600 && esquerda < 600 && direita < 600 && toogleIt < 600)
        apertado = false;
        
    desenhaTabuleiro(3,posicaox,posicaoy);
  }
}



void ascendeLed(int x, int y) {
  digitalWrite(x,HIGH);
  digitalWrite(y + 6,LOW);
}

void apagaLed(int x, int y) {
  digitalWrite(x,LOW);
  digitalWrite(y + 6,HIGH);
}

void testaLeds(int tempo) {
  for(int x = 0; x <=5; x++)
    for(int y = 0; y <=5; y++) {
      ascendeLed(x,y);
      delay(tempo);
      apagaLed(x,y);
    }
}

void zeraTabuleiro() {
  for(int i = 0; i <= 5; i++)
    for(int j = 0; j <= 5; j++)
      tabuleiro[i][j] = 0;
}

void toogle(int x, int y) {
    if(tabuleiro[x][y] == 0)
        tabuleiro[x][y] = 1;
    else
        tabuleiro[x][y] = 0;    

    if(x + 1 <= 5) {
        if (tabuleiro[x + 1][y] == 1)
          tabuleiro[x + 1][y] = 0;
        else
        tabuleiro[x + 1][y] = 1;
    }
    if(x - 1 >= 0){
        if(tabuleiro[x - 1][y] == 1)
          tabuleiro[x - 1][y] = 0;
        else
          tabuleiro[x - 1][y] = 1;
    }  
    if(y + 1 <= 5) {
        if(tabuleiro[x][y + 1] == 1)
          tabuleiro[x][y + 1] = 0;
        else
          tabuleiro[x][y + 1] = 1;
    }
    if(y - 1 >= 0){
        if(tabuleiro[x][y - 1] == 1)
          tabuleiro[x][y - 1] = 0;
        else
          tabuleiro[x][y - 1] = 1;
    }
}

void desenhaTabuleiro(int tempo, int posX, int posY) {
  for(int i = 0; i <= 5; i++) {
     digitalWrite(i,HIGH);
   for(int j = 0; j <= 5; j++) {
       if(tabuleiro[i][j] == 1)
             digitalWrite(j + 6,LOW);
         else
            digitalWrite(j + 6,HIGH);    
        if( i == posX && j == posY) {  
          if(state) {
                digitalWrite(posY + 6,LOW);
             } 
            else {
                digitalWrite(posY + 6,HIGH);
            }
            if (cont >= 125) {
                cont = 0;
                state = state ? false : true;
            }
                
          }
        
    }
      delay(tempo);    
      digitalWrite(i,LOW);
      cont++;    
   }  
}

boolean estaCompleto() {
  for (int i = 0; i < 6; i++)
     for (int j = 0; j < 6; j++)
        if (tabuleiro[i][j]) return false;
  return true; 
}

void sorteiaTabuleiro() {
  randomSeed(analogRead(A5));
  long nLuzes = random(0.55*36, 0.85*36); 
  for (; nLuzes > 0; nLuzes--)
    toogle(random(0, 6), random(0, 6));
}
