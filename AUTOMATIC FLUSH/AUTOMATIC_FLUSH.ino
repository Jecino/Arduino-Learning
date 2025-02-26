#include <MPU6050.h>
#include <Wire.h>
#include <Servo.h>

#define PIR 12
#define nivel_agua A1
#define VCC_nivel_agua 11
#define servo 5

#define TMP_LAST 10000 //Tempo de espera após detecção de presença e vibração
#define limiar 1000 //Limiar para vibrações
#define VIBRATION_AMOUNT 500 //Quantidade de vibrações para registrar

//Instancia do acelerometro e servo
MPU6050 mpu;
Servo meuServo;

int ax, ay, az; // Variáveis para armazenar os valores do acelerômetro
int last_ax, last_ay, last_az; // Para armazenar a última leitura

bool presenceDetected = false;
bool firstVibration = true;
bool VibrationOk = false;
int lastPresenceTime = 0;
int initialTime = 0;
long currentTime = 0;
int firstVibrationTime = 0;
int lastVibrationTime = 0;
float taxaVibracao = 0;

void setup() {
  //Inicializa o MPU-6050
  Wire.begin();
  mpu.initialize();

  mpu.getAcceleration(&last_ax, &last_ay, &last_az);
    
  pinMode(PIR, INPUT);
  pinMode(VCC_nivel_agua, OUTPUT);
  pinMode(nivel_agua, INPUT);

  meuServo.attach(servo);
  meuServo.write(180);
}

void loop() {
  currentTime = millis();
  
  //Detecta apenas uma vez para não sobreescrever o valor
  if(presenceDetected == false){
    presenceDetected = digitalRead(PIR) == HIGH;

    //Guarda o tempo em que ocorreu a detecção
    if(presenceDetected == true){
      lastPresenceTime = currentTime;
    }
  }
     
  //Se não houve alguem presente
  if(!presenceDetected){
    return;
  }

  //Medindo a taxa de vibrações
  taxaVibracao = VibrationRate();

  //Armazena se em algum momento a taxa de vibração foi maior ou igual a 10
  if(taxaVibracao >= 10){
    VibrationOk = true;     
  }

  //Se o nível da água tiver baixado, a descarga foi ativada manualmente
  if(waterLevel() < 128){
    EndCycle();
    return;
  }

  //Verifica se a ultima detecção de presença e de vibração aconteceram a mais tempo que TMP_LAST e se houve vibração em algum momento
  if(currentTime - lastPresenceTime > TMP_LAST && currentTime - lastVibrationTime > TMP_LAST && VibrationOk == true){
    
    //Ativa o servo motor para efetivamente dar descarga
    meuServo.write(90);
    delay(10000);
    meuServo.write(180);
    
    EndCycle();
  }
}

void EndCycle(){
  presenceDetected = false;
  firstVibration = true;
  VibrationOk = false;
  lastPresenceTime = 0;
  initialTime = currentTime;
  firstVibrationTime = 0;
  lastVibrationTime = 0;
  taxaVibracao = 0;
}

int waterLevel(){
  int waterlevel_value = 0;

  //Analisando o nível da água
  digitalWrite(VCC_nivel_agua, HIGH);
  delay(10);
  waterlevel_value = analogRead(nivel_agua);
  digitalWrite(VCC_nivel_agua, LOW);
  
  waterlevel_value = map(waterlevel_value, 0, 1023, 0, 255);

  return waterlevel_value;
}

float VibrationRate(){
  int vibracoes = 0;

  for(int i = 0; i < VIBRATION_AMOUNT; i++){
    //Lê os valores atuais do acelerômetro
      mpu.getAcceleration(&ax, &ay, &az);
    
      // Calcula a diferença em relação à última leitura
      int delta_x = abs(ax - last_ax);
      int delta_y = abs(ay - last_ay);
      int delta_z = abs(az - last_az);
    
      // Verifica se a diferença excede o limiar, indicando vibração
      if (delta_x > limiar) {
        lastVibrationTime = currentTime - initialTime;
        
        vibracoes += 1;
      }
      if(delta_y > limiar){
        lastVibrationTime = currentTime - initialTime;
        
        vibracoes += 1;
      }
      if(delta_z > limiar){
        lastVibrationTime = currentTime - initialTime;
        
        vibracoes += 1;
      }
    
      // Atualiza os valores para a próxima iteração
      last_ax = ax;
      last_ay = ay;
      last_az = az;

      delay(10);
    }

  // Calcula a média das diferenças
  float taxa = vibracoes / 5;

  return taxa;
}
