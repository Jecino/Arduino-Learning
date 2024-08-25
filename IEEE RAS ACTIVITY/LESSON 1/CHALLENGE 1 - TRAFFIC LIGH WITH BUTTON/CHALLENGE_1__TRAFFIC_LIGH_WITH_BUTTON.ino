#define redLED 10
#define yellowLED 9
#define btn 11

int prevRed = 0; 
int prevYellow = 0;
int btnState = 0;


void setup()
{
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(btn, INPUT);
}

void loop()
{  
  btnState = digitalRead(btn);
  int currentTime = millis();
  
  //Caso o botão não esteja apertado
  if(btnState == LOW){
    if(currentTime - prevRed >= 500){
      if (digitalRead(redLED)== LOW){
        digitalWrite(redLED, HIGH);
        prevRed = currentTime;
      }
      else{
        digitalWrite(redLED, LOW);
        prevRed = currentTime;
      }

    }

    if(currentTime - prevYellow >= 1000){
      if (digitalRead(yellowLED)== LOW){
        digitalWrite(yellowLED, HIGH);
        prevYellow = currentTime;
      }
      else{
        digitalWrite(yellowLED, LOW);
        prevYellow = currentTime;
      }

    }
  }
  
  if(btnState == HIGH){
    if(currentTime - prevRed >= 1000){
      if (digitalRead(redLED)== LOW){
        digitalWrite(redLED, HIGH);
        prevRed = currentTime;
      }
      else{
        digitalWrite(redLED, LOW);
        prevRed = currentTime;
      }

    }

    if(currentTime - prevYellow >= 500){
      if (digitalRead(yellowLED)== LOW){
        digitalWrite(yellowLED, HIGH);
        prevYellow = currentTime;
      }
      else{
        digitalWrite(yellowLED, LOW);
        prevYellow = currentTime;
      }

    }
  }
}