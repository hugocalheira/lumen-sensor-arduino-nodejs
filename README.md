# LUMEN SENSOR

Caso de estudo sobre integração de comunicação entre protótipos ESP32*, Arduino UNO R3 (ou hardware compatível) e NodeJs.

![Protótipo utilizando LED RGB](https://i.imgur.com/BBvfBvv.png)

O projeto apresenta um sensor de luminosidade, com resposta visual no hardware com três LEDS representativos da intensidade de luz ambiente, classificados como forte, média ou fraca. Em paralelo, os dados capturados pelo sensor é enviado via porta serial (USB) e lidos por um servidor web [Express](https://expressjs.com/pt-br/), ouvindo a porta 3000 e estabelecendo uma conexão *event-based* e de baixa latência com a *library* [Socket.io](https://socket.io/).

Em resumo, podemos ler os dados de luminosidade através de qualquer aparelho na mesma rede, além de interagir dinamicamente como um interruptor ao enviar comando para o protótipo, interferir na luminosidade de forma artificial, acendendo um led branco junto ao sensor.

<div align="center">

![Gif do protótipo e aplicação](https://s8.gifyu.com/images/WhatsApp-Video-2022-05-10-at-16.08.03.gif)
</div>

### Payload
```
{
    "lumens": number,
    "status": number,
    "light": boolean
}
```
### Modelo com ESP32*
![Hardware do protótipo com ESP32*](https://i.imgur.com/obwEFyt.png) */iot/esp32/esp32_censor.cpp*

### Modelo com UNO R3
![Hardware do protótipo com Arduino UNO R3](https://i.imgur.com/tnYXOCP.jpg) */iot/unoR3/unoR3_censor.cpp*

## Componentes

- 1 ESP32* / Arduino UNO R3 (ou similar)
- 1 Sensor LDR
- 1 LED RGB cátodo comum
- 4 Resistores 220 Ohms 5%
- 1 Resistor 10 kOhms 5%
- 8 jumpers (macho-macho)
- 1 protoboard

## Diagrama UNO R3

![Diagrama](https://i.imgur.com/rWzb9GZ.jpeg)
![Esquema elétrico](https://i.imgur.com/juitD82.jpeg)

## Pré-requisitos

- [NodeJs](https://nodejs.org/en/)
- [Arduino IDE](https://www.arduino.cc/en/software)

## Instalação

Execute o comando `npm install` ou `yarn install` para instalar as dependências listadas no arquivo *package.json*.

> *Consulte a [documentação](https://www.arduino.cc/en/Guide) do Arduino para carregar o código presente na pasta */iot/unoR3/unoR3_sensor.cpp* ou */iot/esp32/esp32_sensor.cpp* em seu hardware, utilizando o **Arduino IDE** conforme o caso.

## Para rodar

Execute o comando `yarn start` + **PORTA** qual o protótipo está conectado.

Ex: `yarn start COM3`

## To do
- Conectar modelo ESP32 à rede local

## Notas
*Devkit com 38 pinos