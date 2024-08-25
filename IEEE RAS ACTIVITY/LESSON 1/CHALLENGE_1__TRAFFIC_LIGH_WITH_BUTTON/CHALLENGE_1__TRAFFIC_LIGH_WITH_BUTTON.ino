#define redLED 10
#define yellowLED 9
#define greenLED 8
#define btn 11
int btnState = 0;

void setup()
{
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(btn, INPUT);
}

void ligar(int pin, int tmp){
 digitalWrite(pin, HIGH);
 delay(tmp);
}

void desligar(int pin){
 digitalWrite(pin, LOW);
}

void loop()
{
  btnState = digitalRead(btn);
  
  if(btnState == HIGH){
  ligar(yellowLED, 1000);
  
  desligar(yellowLED);
    
  ligar(redLED, 3000);
  
  desligar(redLED);
  }
  
  else{
  ligar(redLED, 3000);

  desligar(redLED);
  
  ligar(greenLED, 5000);
  
  desligar(greenLED);
  
  ligar(yellowLED, 1000);
  
  desligar(yellowLED);
  } 
}