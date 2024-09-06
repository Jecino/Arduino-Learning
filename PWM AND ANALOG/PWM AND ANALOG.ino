#define led_vermelho 3
#define led_amarelo 5

#define maximo 32
#define minimo 0
#define tmp 100

void setup() {
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);

}

void loop() {
  for(int i = minimo; i <= maximo; i++){
    analogWrite(led_vermelho, i);
    analogWrite(led_amarelo, i);
    delay(tmp);
  }
  
  for(int i = maximo; i >= minimo; i--){
    analogWrite(led_vermelho, i);
    analogWrite(led_amarelo, i);
    delay(tmp);
  }
  
}
