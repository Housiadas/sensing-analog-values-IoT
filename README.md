# sensing-analog-values-IoT

Development of an embedded system using IoT principles to measure analog values of physical quantities such as temperature, humidity, soil moisture, etc. We are building our system using MQTT, which is a lightweight, publish-subscribe network protocol that transports messages between devices.

### Electronics and devices.
* Raspberry pi 3 model B.
* Arduino mega 2560.
* Barometric sensor arduino BMP180. 
* Wireless serial transceiver module HC12.

### Raspberry pi configuration.
The raspberry pi was setted up as a MQTT broker. Eclipse Mosquitto message broker was used, which is lightweight and is suitable for use on all devices from low power single board computers to full servers.  

* Raspberry pi connected to a pc via putty. 

### HC12 module and connection.
HC-12 wireless serial communication module is a new-generation multichannel embedded wireless data transmission module. Its wireless working frequency band is 433.4-473.0MHz, multiple channels can be set, with the stepping of 400 KHz, and there are 100 channels in total. The maximum transmitting power of the module is 100mW (20dBm).

* Supply voltage: 3.2V to 5.5VDC.
* Communication distance: 1,000m in the open space.
* Serial baud rate: 1.2Kbps to 115.2Kbps (default 9.6Kbps).
* Receiving sensitivity: -117dBm to -100dBm.
* Transmit power: -1dBm to 20dBm.
* Interface protocol: UART/TTL.
* Operating temperature: -40℃ to +85℃.

#### Connection with Arduino.
![alt text](https://raw.githubusercontent.com/Housiadas/sensing-analog-values-IoT/master/images/arduino_hc12.png)

#### Connection with raspberry pi.
* VIN – Connect to RPi 5V (PIN 4)
* GND – Connect to RPi GND (PIN 6)
* RX – Connect to RPi GPIO14 (PIN 8, UART0_TXD)
* TX – Connect to RPi GPIO15 (PIN 10, UART0_RXD)

It is recommended to use a decoupling capacitor (0.1 to 10uF) and an external power supply.



