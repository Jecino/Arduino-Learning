#define btn 9
#define led 8

void setup() {
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  if (digitalRead(btn) == HIGH){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }

}
