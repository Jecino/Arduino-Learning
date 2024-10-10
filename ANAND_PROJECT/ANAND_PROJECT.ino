#include <Wire.h>
#include <Servo.h>


#define led 8
#define sensor 7
#define Presenca 12
#define nivel_agua A1
#define servo 5

#define TMP_DETECT 5000

Servo meuServo;

int vibracoes = 0;
float taxaVibracao = 0;
int initialTime = 0;
int currentTime = 0;
int alguempresente = 0;

const int MPU=0x68;
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup() {

  //Inicializa o MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(Presenca, INPUT);
  pinMode(nivel_agua, INPUT);
  meuServo.attach(servo);
  meuServo.write(0);

}
//AAAAAAAAAAAAAAAAAAAAAAAAA
void loop() {
  delay(500);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);

  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Serial.print("Temperatura: ");
  Serial.println(Tmp/340.00+36.53);

  Serial.print("Acelerometro: ");
  Serial.println(AcX);
  
  Serial.println(digitalRead(Presenca));
  
  currentTime = millis();

  if(alguempresente != 1){
    alguempresente = digitalRead(Presenca);
  }
   
  //Se houve alguem presente
  if(alguempresente == 1){
    
    //Medindo a quantidade de vibração enquanto não acabar o tempo
    if(currentTime - initialTime < TMP_DETECT){
      if(digitalRead(sensor) == LOW){   
        vibracoes += 1; 
      } 
    }
  
    //Quando terminado o tempo, calcular a taxa e decidir
    else{ 
      taxaVibracao = vibracoes / 5;

      Serial.print("Taxa de vibraçao: ");
      Serial.println(taxaVibracao);
      
      int nivelagua = analogRead(nivel_agua);
      map(nivelagua, 0, 1023, 0, 255);

      Serial.print("Nivel agua: ");
      Serial.println(nivelagua);
    
      //Se a taxa de vibração for maior que x dar descarga
        if(nivelagua >= 128){
          if(taxaVibracao >= 2){
            digitalWrite(led, HIGH);
            
            meuServo.write(90);
            delay(5000);
            meuServo.write(0);
            
            vibracoes = 0;
            taxaVibracao = 0;
            alguempresente = 0;
            initialTime = currentTime;
          }
        }
      
        //Se não, atualiza as variáveis
        else{
          digitalWrite(led, LOW);
          vibracoes = 0;
          taxaVibracao = 0;
          alguempresente = 0;
          initialTime = currentTime;
        }
    }
  }
}
