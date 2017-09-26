# CtrlFreak Tx and FC/Rx
CtrlFreak Tx - Tested with Uno, Nano, Duemilanove, and Mega.  (Will also work on 16Mhz promini)

Default 6 channels to match the receiver.  Uncomment lines to make it 10 channels.

Check the Tx code for pinout to NRF24l01, thumbsticks and pots.


CtrlFreak FC/Rx -  Tested with 16MHz Nano, Uno and Duemilanove.  Nano is preferred because of its size, weight and the 3.3v output to supply the NRF24l01 and the sensors. Mega not yet supported.

Upload the CtrlFreak6-QuadX-MPU6050-Nano Hex file via XLoader.

ESCs/Motors use digital pins 9,6,5,3 instead of 9,10,11,3 because we allocated the hardware SPI pins for NRF24.

voltage divider to A3 (vBat)

MPU6050 on I2c (A4/A5)


nRF24 connections (left is nRF24, right is arduino):

CE- D7

CSN-D8

MOSI-D11

MISO-D12

SCK-D13

IMPORTANT: Add capacitor (104 ceramic or 47uF 25v electrolytic) between VCC and Ground pins of NRF24l01


Fritzing Diagram:  To do...
