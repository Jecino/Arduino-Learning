#define Entrada1 12
#define Entrada2 13

#define Entrada3 2
#define Entrada4 4

#define UltraSonicECHO A0
#define UltraSonicTRIGGER 5
#define IRSensor 3

#define TIME_MIN 150

int ultimaalteracao = 0;
int time_atual = 0;

void setup(){
  pinMode(Entrada1, OUTPUT);
  pinMode(Entrada2, OUTPUT);
  pinMode(Entrada3, OUTPUT);
  pinMode(Entrada4, OUTPUT);
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
    digitalWrite(Entrada3, HIGH);
    digitalWrite(Entrada4, LOW);
  }
  else{
    digitalWrite(Entrada3, LOW);
    digitalWrite(Entrada4, HIGH);
  }
}

void girarEsquerda(int direcao){
  
  //1 para frente, 0 para trás
  if(direcao == 1){
    digitalWrite(Entrada1, LOW);
    digitalWrite(Entrada2, HIGH);
  }
  else{
    digitalWrite(Entrada1, HIGH);
    digitalWrite(Entrada2, LOW);
  }
}

void loop(){

  time_atual = millis();
  
    if(digitalRead(IRSensor) == 1){
    
      digitalWrite(UltraSonicTRIGGER, HIGH);
      delayMicroseconds(10);
      digitalWrite(UltraSonicTRIGGER, LOW);
    
      int duracao = pulseIn(UltraSonicECHO, HIGH);
    
      int distancia = duracao * 0.01715;
      
      Serial.write("Distancia:");
      Serial.print(distancia, DEC);
      Serial.write("\n");
      
      if(time_atual - ultimaalteracao >= TIME_MIN){
        if (distancia < 60){
          girarEsquerda(0);
          girarDireita(1);
          ultimaalteracao = time_atual;
        }
        else{
          girarEsquerda(1);
          girarDireita(1);
          ultimaalteracao = time_atual;
          
        }
      }
    }

    else{
      girarEsquerda(0);
      girarDireita(1);
      ultimaalteracao = time_atual;
    }  
}
