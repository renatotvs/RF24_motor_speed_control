# RF24_motor_speed_control
Programa para controle de velocidade de motor DC com uso de radio frequencia (nRF24L01)


O uso de radio frequencia com o módulo nRF24L01 possibilita controlar dispositivos com um maior alcance sem fio.

O Módulo Wireless NRF24L01 opera na frequência de 2.4GHz, este possuí duas versões: uma com antena intregrada e outra com antena externa. O que possuí antena integrada o alcance é em torno de 100 metros e com antena externa possuí alcance de 1.000 metros e em alguns casos chega até mais de 1.000 metros. 

## Esquema de ligação (pinagem)

Á definir

## Laboratório:

Nesse laboratório foi utilizado os dois modelos de radio frequencia:

**nRF24L01 com antena integrada para o Receptor:**

![NRF24L01_antena_integrada](https://github.com/renatotvs/RF24_motor_speed_control/blob/main/images/NRF24L01_antena_integrada.png)

**nRF24L01 + PA + LNA com antena externa para o Transmissor:**

![NRF24L01_antena_externa](https://github.com/renatotvs/RF24_motor_speed_control/blob/main/images/NRF24L01_PA_LNA_antena_externa.png)

Print dos valores no Serial Monitor (Arduino IDE):

![Serial monitor](https://github.com/renatotvs/RF24_motor_speed_control/blob/main/images/Serial_monitor_received_transmitter.png)

#### Resultado Comunicação - Transmissor X Receptor

https://github.com/renatotvs/RF24_motor_speed_control/assets/42357180/683e3b23-e950-4746-ad81-fa72067dbd30

#### Observações

Nesse primeiro momento foi testado em minha residência em torno de uns 30 metros de distancia do receptor e transmissor e mesmo com obstáculos e paredes a comunicação funcionou perfeitamente.
Pretendo ainda testar em maiores distâncias e com outras configurações.

#### Lista de materiais utilizados:

**Transmissor:**

+ Placa Arduino nano
+ NRF24L01+ PA + N com antena externa
+ adptador nRF24L01 - esse adaptador já possuí o regulador de Tensão 3.3V (Ams1117) regula a voltagem de 5 volts para 3.3 volts - o nRF24L01 deve operar nessa voltagem para evitar que danifique a módulo RF. Com esse adaptador fica mais fácil a ligação dos pinos.
+ botao on/off - para ligar e desligar o circuito do transmissor.
+ botao push button - para ligar LED
+ 1 resistor (conectado ao pino negativo do push button)
+ 1 case com 3 pilhas AA 1.5 volts = 4.5 volts - voltagem necessária para alimentar a placa arduino nano

**Receptor:**

+ Placa ESP32 - (resolvi utilizar a placa esp32 que possuí maior robustez, maior armazenamento e um maior poder de processamento para projetos de robótica em geral, mas para este Lab poderíamos utilizar o arduino nano conforme usado no transmissor.
+ Motor DC (tensão de operação 3-6V)
+ Roda 68mm
+ Ponte-H dupla (L298N) - módulo para ligar, desligar e controlar a velocidade e rotação dos motores
+ botao on/off - para ligar e desligar o circuito do receptor.
+ LED 3mm
+ 1 resistor (conectado aos pino negativo do Led)
+ 1 case com 2 baterias lipo 18650 4.2 volts = 8.4 volts total (essa voltagem é alimentado a ponte-h para os motores e a saída de 5 volts é alimentado a placa esp32).

### Links de referência:


