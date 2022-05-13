# LUMEN SENSOR

Caso de estudo sobre integração de comunicação entre protótipo Arduino UNO R3 (ou hardware compatível) e NodeJs.

![Hardware do protótipo Arduino](https://i.imgur.com/tnYXOCP.jpg)

O projeto apresenta um sensor de luminosidade, com resposta visual no hardware com três LEDS representativos da intensidade de luz ambiente, classificados como forte, média ou fraca. Em paralelo, os dados capturados pelo sensor é enviado via porta serial (USB) e lidos por um servidor web [Express](https://expressjs.com/pt-br/), ouvindo a porta 3000 e estabelecendo uma conexão *event-based* e de baixa latência com a *library* [Socket.io](https://socket.io/).

<div align="center">

![Gif do protótipo e aplicação](https://s8.gifyu.com/images/WhatsApp-Video-2022-05-10-at-16.08.03.gif)
</div>

Em resumo, podemos ler os dados de luminosidade através de qualquer aparelho na mesma rede, além de interagir dinamicamente como um interruptor ao enviar comando para o protótipo, interferir na luminosidade de forma artificial, acendendo um led branco junto ao sensor.

### Payload
```
{
    "lumens": number,
    "status": number,
    "light": boolean
}
```

## Hardware do protótipo Arduino

- 1 Placa Arduino UNO R3 (ou similar)
- 1 Sensor LDR
- 4 LEDs (Vermelho, Amarelo, Verde e Branco)
- 4 Resistores 220 Ohms 5%
- 1 Resistor 10 kOhms 5%
- 8 jumpers (macho-macho)
- 1 protoboard

## Diagrama

![Diagrama](https://i.imgur.com/3eBH7C0.jpeg)

## Pré-requisitos

- [NodeJs](https://nodejs.org/en/)
- [Arduino IDE](https://www.arduino.cc/en/software)

## Instalação

Execute o comando `npm install` ou `yarn install` para instalar as dependências listadas no arquivo *package.json*.

> *Consulte a [documentação](https://www.arduino.cc/en/Guide) do Arduino para carregar o código presente na pasta /arduino/sensor.ino em seu hardware, utilizando o **Arduino IDE**.

## Para rodar

Execute o comando `yarn start` + **PORTA** qual o protótipo está conectado.

Ex: `yarn start COM3`

## To do
- Migração de Arduino UNO R3 para ESP32, possibilitando comunicação via WiFi