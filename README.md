# CtrlFreak Tx and FC/Rx




CtrlFreak FC/Rx - 

Use TMRH20 RF24 libs from Github.

Tested with 16MHz Nano, Uno or Duemilanove because of its 3.3v output to supply the NRF24 and the sensors. (Mega not yet supported).

ESCs/Motors use pins 9,6,5,3 instead of 9,10,11,3 because we allocated the hardware SPI pins for NRF24.

vbat voltage divider to A3

MPU6050 on I2c (A4/A5)

nRF24 connections (left is nRF24, right is arduino)

CE- D7

CSN-D8

MOSI-D11

MISO-D12

SCK-D13

IMPORTANT: Add capacitor (104 ceramic or 47uF 25v) between VCC(3.3v) and Ground pins of NRF24l01


Fritzing Diagram:  To do...
