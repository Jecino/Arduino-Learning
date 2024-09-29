#define led 8
#define sensor 7

#define TMP_DETECT 5000

int vibracoes = 0;
float taxaVibracao = 0;
int initialTime = 0;
int currentTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  currentTime = millis();

  if(currentTime - initialTime < TMP_DETECT){
    if(digitalRead(sensor) == LOW){   
      vibracoes += 1; 
      Serial.print("Vibração detectada\n");
    } 
  }
  
  else{
    taxaVibracao = vibracoes / 5;

    Serial.print("Taxa de vibraçao: ");
    Serial.println(taxaVibracao);
    
    if(taxaVibracao >= 2){
      digitalWrite(led, HIGH);
      vibracoes = 0;
      taxaVibracao = 0;
      initialTime = currentTime;
    }
    
    else{
      digitalWrite(led, LOW);
      vibracoes = 0;
      taxaVibracao = 0;
      initialTime = currentTime;
    }
  }

}
