// Biblioteca Wire.h para Acelerometro/Girsocopio MPU6050
#include<Wire.h>
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

// Endereço I2C do MPU6050
const int MPU=0x68;

// Variaveis para armazenamento de dados dos sensores de acelerometro e giroscopio
int acX,acY,acZ,grX,grY,grZ;

void setup() {
  Serial.begin(9600);
  // Inicializa o MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0);
  Wire.endTransmission(true); 

  /*
  // reset offsets
  accelgyro.setXAccelOffset(0);
  accelgyro.setYAccelOffset(0);
  accelgyro.setZAccelOffset(0);
  accelgyro.setXGyroOffset(0);
  accelgyro.setYGyroOffset(0);
  accelgyro.setZGyroOffset(0);

  */
  
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  // Solicita dados do sensor
  Wire.requestFrom(MPU,14,true);
  // Armazena dados nas variaveis
  acX = Wire.read()<<8|Wire.read();
  acY = Wire.read()<<8|Wire.read();
  acZ = Wire.read()<<8|Wire.read();
  grX = Wire.read()<<8|Wire.read();
  grY = Wire.read()<<8|Wire.read();
  grZ = Wire.read()<<8|Wire.read();

  // Display no serial monitor  
  Serial.print("Acel. X = "); Serial.print(acX);
  Serial.print("; Acel. Y = "); Serial.print(acY);
  Serial.print("; Acel. Z = "); Serial.println(acZ);
  Serial.print("Girosc. X = "); Serial.print(grX);
  Serial.print("; Girosc. Y = "); Serial.print(grY);
  Serial.print("; Girosc. Z = "); Serial.println(grZ);

  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);

  if(cmMsec <= 10.00){
    Serial.print(" - Próximo");
  }
  if(cmMsec >= 100.00){
    Serial.print(" - Distante");
  }
  if(cmMsec < 100.00 && cmMsec > 10.00){
    Serial.print(" - Média distância");
  }
  
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  
  /*
  if(acZ < 300){
    Serial.print("Capotado");
  } else if((acZ < 360) && (acY < 270)){
    Serial.println("Virado a esquerda");
  } else if((acZ < 360) && (acY > 380)){
    Serial.println("Virado a direita");
  } else if((acZ < 360) && (acX < 270)){
    Serial.println("Virado para frente");
  } else if((acZ < 360) && (acX > 380)){
    Serial.println("Virado para trás");
  } else {
    Serial.println("Normal");
  }
  */
  
  // Aguarda 1 segundo e repete o loop
  delay(1000);
  

}
