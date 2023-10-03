/* 
  Programa de Recebimento para controlar motor DC com a placa ESP32 e antena de radio frequencia (nRF24L01+) 
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//#define PRINT_DEBUG   //Uncomment this line if you want to print on serial monitor

//Lights
#define light_FR 15 //21 - deixei o 15 para teste pois o 15 inicia Ligado

//motor lado A - Left
int enableLeftMotor=22; //GP022 //GPIO23 - pino especifico para MOSI (RF)
int Motor1pin1 = 21; //GPIO21
int Motor1pin2 = 2; //GPIO2 //LED internal esp32 - only test
//int Motor1pin2 = 25; //GPI25

//config PWM
const int PWMFreq = 1000; //1Mhz
const int PWMResolution = 8; // 8bits

//const int rightMotorPWMSpeedChannel = 4; //canal pwm - controla o motor em diferentes canais (ex. lado A)
const int leftMotorPWMSpeedChannel = 5; //canal pwm - "-"

RF24 radio(4, 5); //CE, CSN
const byte address[6] = "00001";

boolean radio_connection = false;

int set_speed_forward;
int set_speed_backward;

unsigned long data[6];

void rotateMotor(int X, int Y){

  set_speed_forward = map(Y,550,1020,10,255);

  set_speed_backward = map(Y,470,0,10,255);


  if(Y > 550){
    digitalWrite(Motor1pin1,LOW);
    digitalWrite(Motor1pin2,HIGH);

    #ifdef PRINT_DEBUG
      Serial.println("Forward...");
    #endif

    ledcWrite(leftMotorPWMSpeedChannel, abs(set_speed_forward));
  }

  if(Y > 0 && Y < 470){
    digitalWrite(Motor1pin1,HIGH);
    digitalWrite(Motor1pin2,LOW);

    #ifdef PRINT_DEBUG
      Serial.println("Backward...");
    #endif

    ledcWrite(leftMotorPWMSpeedChannel, abs(set_speed_backward));
  }

  if(Y > 470 && Y < 550){
    digitalWrite(Motor1pin1,LOW);
    digitalWrite(Motor1pin2,LOW);

    #ifdef PRINT_DEBUG
      Serial.println("Stop...");
    #endif
  }
  
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  #ifdef PRINT_DEBUG
    Serial.println("RF24 Received - Test");
  #endif

  pinMode(light_FR, OUTPUT); //Led

  //----------------------------------------------------------------------
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(Motor1pin1, OUTPUT);
  pinMode(Motor1pin2, OUTPUT);

  //Set up PWM for motor speed
  //configura o PWM com a função ledcSetup , que recebe como entrada o canal PWM, a frequência e a resolução do ciclo de trabalho.
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  
  //função ledcAttachPin. Este recebe como entrada o GPIO e o canal.
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel);
  //------------------------------------------------------------------------

  radio.begin();
  //radio.setChannel(5); //radio.setChannel(108); // os canais mais altos tendem a ser mais "abertos"

  // Define o endereço do receptor (data pipe 0) - o data pipe pode ser configurado de 0 a 5. 
  // Cada “data pipe” pode ter um endereço (ID) de recebimento separado;
  // Ou seja, um mesmo dispositivo pode ser configurado para ouvir outros 6 dispositivos (1 endereço em cada data pipe) considerando que estejam todos na mesma frequência.
  radio.openReadingPipe(0, address); 

  radio.setPALevel(RF24_PA_MIN); //"configuração de curto alcance" - aumente se quiser mais alcance E tiver uma boa fonte de alimentação
  //radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  #ifdef PRINT_DEBUG
    Serial.println("INICIANDO TRANSMISSÃO - NRF24 - TEST");
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:

  if (radio.available()) {   // If the NRF240L01 module received data

    radio.read(&data, sizeof(data));

    #ifdef PRINT_DEBUG

      Serial.print("button_1: ");
      Serial.print(data[0]);

      Serial.print(" xValue: ");
      Serial.print(data[1]);
      Serial.print(" yValue: ");
      Serial.println(data[2]);
    #endif

    delay(10);
    
    radio_connection = true;

    #ifdef PRINT_DEBUG
      Serial.println("Conectado...");
    #endif
  }else{
    #ifdef PRINT_DEBUG
      Serial.println("Desconectado...");
    #endif

    radio_connection = false;
  }

  //liga LED
  if(data[0] == 1){
    digitalWrite(light_FR, HIGH);
  }else{
    digitalWrite(light_FR, LOW);
  }

  //control motor
  rotateMotor(data[1], data[2]);
}
