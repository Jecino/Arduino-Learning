#include <Servo.h>

#define led 8
#define sensor 7
#define Presenca 4
#define nivel_agua A0
#define servo 4

#define TMP_DETECT 5000

Servo meuServo;

int vibracoes = 0;
float taxaVibracao = 0;
int initialTime = 0;
int currentTime = 0;
int alguempresente = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(Presenca, INPUT);
  pinMode(nivel_agua, INPUT);
  meuServo.attach(servo);

}

void loop() {
  currentTime = millis();
  alguempresente = digitalRead(Presenca);
  
  //Se houve alguem presente
  if(alguempresente == 1){
    
    //Medindo a quantidade de vibração enquanto não acabar o tempo
    if(currentTime - initialTime < TMP_DETECT){
      if(digitalRead(sensor) == LOW){   
        vibracoes += 1; 
        Serial.print("Vibração detectada\n");
      } 
    }
  
    //Quando terminado o tempo, calcular a taxa e decidir
    else{ 
      taxaVibracao = vibracoes / 5;

      Serial.print("Taxa de vibraçao: ");
      Serial.println(taxaVibracao);
      
      int nivelagua = analogRead(nivel_agua);
      map(nivelagua, 0, 1023, 0, 255);
    
      //Se a taxa de vibração for maior que x dar descarga
        if(nivelagua >= 128){
          if(taxaVibracao >= 2){
            digitalWrite(led, HIGH);
            meuServo.write(90);
            delay(10000);
            vibracoes = 0;
            taxaVibracao = 0;
            initialTime = currentTime;
          }
        }
      
        //Se não, atualiza as variáveis
        else{
          digitalWrite(led, LOW);
          vibracoes = 0;
          taxaVibracao = 0;
          initialTime = currentTime;
        }
    }
  }
}
