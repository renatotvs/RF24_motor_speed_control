/* 
  Programa transmissor para controle de velocidade do motor DC com uso de radio frequencia (nRF24L01) 
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//#define PRINT_DEBUG   //Uncomment this line if you want to print on serial monitor

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001";

int X, Y;

const byte pinButton1 = 2;
const byte pinJoystick1 = 0; //A0
const byte pinJoystick2 = 1; //A1

byte valorBotaoAnterior;
boolean ledLigado = false;

unsigned long data[6];

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  #ifdef PRINT_DEBUG
    Serial.println("RF24 Transmitter - Test");
  #endif

  radio.begin();
  //radio.setChannel(5);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  //radio.setPALevel(RF24_PA_MAX);
  radio.stopListening(); //inicia comunicação de rádio para o Transmissor

  pinMode(pinButton1, INPUT); //entrada INPUT é para quando utilizamos resistor no negativo e utilzamos o positivo ao lado
  //pinMode(pinButton1, INPUT_PULLUP); //utiliza o resistor interno
}

void loop() {
  // put your main code here, to run repeatedly:

  int pinValueButton1 = digitalRead(pinButton1);

  if(pinValueButton1 != valorBotaoAnterior){

    if(pinValueButton1){
      ledLigado = !ledLigado;

      if(ledLigado){
        #ifdef PRINT_DEBUG
          Serial.println("LED LIGADO");
          Serial.println(1);
        #endif

        data[0] = 1;
      }
      else{
        #ifdef PRINT_DEBUG
          Serial.println("LED DESLIGADO");
          Serial.println(0);
        #endif

        data[0] = 0;
      }
      
    }
    
  }

  valorBotaoAnterior = pinValueButton1;

  X = analogRead(pinJoystick1); //Read Joystick X-axis
  Y = analogRead(pinJoystick2); //Read Joystick Y-axis

  data[1] = X; //map(X, 0, 1023, 0, 255); 
  data[2] = Y; //map(Y, 0, 1023, 0, 255);

  data[3] = 20; 
  data[4] = 30;
  
  radio.write(&data, sizeof(data));

  #ifdef PRINT_DEBUG
    Serial.print("button_1: ");
    Serial.print(data[0]);

    Serial.print(" xValue: ");
    Serial.print(data[1]);
    Serial.print(" yValue: ");
    Serial.println(data[2]);
  #endif

  delay(10);

}
