#define Entrada1 2
#define Entrada2 4

#define Entrada3 12
#define Entrada4 13

#define UltraSonicECHO A0
#define UltraSonicTRIGGER 5
#define IRSensor 3


void setup(){
  pinMode(Entrada1, OUTPUT);
  pinMode(Entrada2, OUTPUT);
  pinMode(UltraSonicECHO, INPUT);
  pinMode(UltraSonicTRIGGER, OUTPUT);
  pinMode(IRSensor, INPUT);
  Serial.begin(9600);
}

void pararEsquerda(){
  digitalWrite(Entrada1, LOW);
  digitalWrite(Entrada2, LOW);  
}

void pararDireita(){
  digitalWrite(Entrada3, LOW);
  digitalWrite(Entrada4, LOW);  
}

void girarDireita(int direcao){
  
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

void girarEsquerda(int direcao){
  
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
  
  if(digitalRead(IRSensor) == 1){
    
    digitalWrite(UltraSonicTRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(UltraSonicTRIGGER, LOW);
  
    int duracao = pulseIn(UltraSonicECHO, HIGH);
  
    int distancia = duracao * 0.01715;
    
    Serial.write("Distancia:");
    Serial.print(distancia, DEC);
    Serial.write("\n");
  
    if (distancia < 60){
      girarEsquerda(1);
      girarDireita(1);
    }
    else{
      girarEsquerda(0);
      girarDireita(1);
    }
  }

  else{
    girarEsquerda(0);
    girarDireita(1);
    delay(500);
  }
}
