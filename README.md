# LUMEN SENSOR

Caso de estudo sobre integração de comunicação entre protótipo Arduino UNO R3 (ou hardware compatível) e NodeJs.

![Protótipo utilizando um LED RGB](https://lh3.googleusercontent.com/mjkhKBrdhdE8V5m47sDzY0msHmHXvuRBDihl-1f6s343tfnGSf3sGwW73dsVQu1-z8h3irgaGTVCsc4efEEFQhDwDWf-A438YQSDyRa_SeqNMr9Uw1UcMSZ5ajnCZA6M1G8jSk49nh9HxHQtUesjEb3xer7usuoEYxXAjy8NiuZRxDJqVGuC8STdgtrG4eQ0DiB0NtPEwAB6GNSBBm8DE0H7Z-zSK6z35zFiyTKQw6QU1aOEkIaaUy40TI7sqFtHQEjIR0H0AvHA61Ms-Z5DouDiwrNyNYKQJTXTKywGgTLF6dzwXO4ePlvT9E1202XuMinqXLjlz9T_rp_HpOnMC5S-wPq-PCKwrmDUdNX15vhzVwavK_LvZVgUclG-uFSpUFNEjRwx4Z0Ct85bmfZWp5DYqoHT9f2eSzx1IYehhMgUNkLZgnOm_dBf2Bjuw7SFCU-uNUfQDGtiQa73Gk0lMuoNHL-IKH7CTllU-9_BEK7NBLiL9aP63JkRcbY8UIk0p811RDugmnfg8Rvj1Jbo9gv3Y_tFxzKmRwJncl5Mk7s76iUjXRpAIzBOB7MZUyZ7tb7L-NS5I1omBPGZTop6_oJX60T9bL44Ef-24V4klt90BxPa8hV4-U5fgiGTV74I3IpmlipjSiFaDHUAetZKsgtzrrGFC4Ml0XD2FUL1pA2BnldB98wfgPX4a42oU0LfcSlimuk-kEIYpNwTnvcH6WcnCP_WvoOTMxv9jEaPDiU4Vfo0zsuBL1Na4mtg9HEdZznfW2D5IblRputLf5bj9d2DOfmjOeaJrEkh7A=w1920-h864-no?authuser=0)

O projeto apresenta um sensor de luminosidade, com resposta visual no hardware com três LEDS representativos da intensidade de luz ambiente, classificados como forte, média ou fraca. Em paralelo, os dados capturados pelo sensor é enviado via porta serial (USB) e lidos por um servidor web [Express](https://expressjs.com/pt-br/), ouvindo a porta 3000 e estabelecendo uma conexão *event-based* e de baixa latência com a *library* [Socket.io](https://socket.io/).

![Hardware do protótipo Arduino](https://i.imgur.com/tnYXOCP.jpg)

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

## Hardware do protótipo Arduino

- 1 Placa Arduino UNO R3 (ou similar)
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

> *Consulte a [documentação](https://www.arduino.cc/en/Guide) do Arduino para carregar o código presente na pasta /arduino/sensor.ino em seu hardware, utilizando o **Arduino IDE**.

## Para rodar

Execute o comando `yarn start` + **PORTA** qual o protótipo está conectado.

Ex: `yarn start COM3`

## To do
- Migração de Arduino UNO R3 para ESP32, possibilitando comunicação via WiFi