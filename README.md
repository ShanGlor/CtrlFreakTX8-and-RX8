# CtrlFreak Tx and FC/Rx




CtrlFreak FC/Rx - 

Tested with 16MHz Nano/Uno and TMRH20 RF24 libs(Github) 

Motors use pins 9,6,5,3 instead of 9,10,11,3 because we allocated the hardware SPI pins for NRF24

vbat voltage divider to A3

MPU6050 on I2c (A4 A5)

nRF24 connections (left is nRF24, right is arduino):q

  CE      7
  CSN     8
  MOSI   11
  MISO   12
  SCK    13

IMPORTANT: Add capacitor (104 ceramic or 47uF 25v) between VCC(3.3v) and Ground pins of NRF24l01


Fritzing Diagram:  To do...
