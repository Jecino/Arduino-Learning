#define c 2
#define d 3
#define e 4
#define f 5
#define g 6
#define a 7
#define transposer A0
#define speaker 8

#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 349
#define T_G 392
#define T_A 440
#define T_B 493

void setup() {
  pinMode(c, INPUT);
  pinMode(d, INPUT);
  pinMode(e, INPUT);
  pinMode(f, INPUT);
  pinMode(g, INPUT);
  pinMode(a, INPUT);
  pinMode(transposer, INPUT);
  pinMode(speaker, OUTPUT);

  Serial.begin(9600);

}

void loop(){
  int transposerValue = analogRead(transposer);
  transposerValue = map(transposerValue, 0, 1023, -127, 128);
  transposerValue = calculateTranspo(transposerValue);
  Serial.println(transposerValue);

  if(digitalRead(c)){
    tone(speaker, T_C * pow(2, transposerValue));
  }

  if(digitalRead(d)){
    tone(speaker, T_D * pow(2, transposerValue));
  }

  if(digitalRead(e)){
    tone(speaker, T_E * pow(2, transposerValue));
  }

  if(digitalRead(f)){
    tone(speaker, T_F * pow(2, transposerValue));
  }

  if(digitalRead(g)){
    tone(speaker, T_G * pow(2, transposerValue));
  }

  if(digitalRead(a)){
    tone(speaker, T_A * pow(2, transposerValue));
  }

  noTone(speaker);

}

int calculateTranspo(int value){
  if(value < 51 && value > -51){
    return 0;
  }

  else if(value > 51 && value < 102){
    return 1;
  }

  else if(value > 102 && value <= 128){
    return 2;
  }

  else if(value < -51 && value > -102){
    return -1;
  }

  else if(value < -102 && value >= -127){
    return -2;
  }
}
