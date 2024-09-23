#define Entrada1 2
#define Entrada2 4
#define Motor1 3

#define Entrada3 7
#define Entrada4 5
#define Motor2 6

#define potenc A0

void setup(){
  pinMode(Entrada1, OUTPUT);
  pinMode(Entrada2, OUTPUT);
  pinMode(Motor1, OUTPUT);
  pinMode(potenc, INPUT);
}

void pararEsquerda(){
  digitalWrite(Entrada1, LOW);
  digitalWrite(Entrada2, LOW);  
}

void pararDireita(){
  digitalWrite(Entrada3, LOW);
  digitalWrite(Entrada4, LOW);  
}

void girarDireita(int velocidade, int direcao){
  analogWrite(Motor1, velocidade);
  
  //1 para frente, 0 para trás
  if(direcao == 1){
    digitalWrite(Entrada1, HIGH);
    digitalWrite(Entrada2, LOW);
  }
  else{
    digitalWrite(Entrada1, LOW);
    digitalWrite(Entrada2, HIGH);
  }
}

void girarEsquerda(int velocidade, int direcao){
  analogWrite(Motor2, velocidade);
  
  //1 para frente, 0 para trás
  if(direcao == 1){
    digitalWrite(Entrada3, LOW);
    digitalWrite(Entrada4, HIGH);
  }
  else{
    digitalWrite(Entrada3, HIGH);
    digitalWrite(Entrada4, LOW);
  }
}

void loop(){
  int potencValue = analogRead(potenc)/4;
  
  if(potencValue <= 128){
    girarDireita(250, 1);
    girarEsquerda(250, 0);
  }
  else{
  	girarDireita(250, 0);
  	girarEsquerda(250, 1);  
  }
}