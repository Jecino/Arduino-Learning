#define led 11
int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  while(Serial.available() > 0){
    value = Serial.parseInt();

    if (Serial.read() == '\n') {

    if (value > 255 || value < 0){
      Serial.write("The value must be in the range: (0 - 255)\n");
    }
    else{
      Serial.write("value do led setado: ");
      Serial.print(value, DEC);
      analogWrite(led, value);
    }
    }
  }  
}

