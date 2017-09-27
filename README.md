# CtrlFreak Tx8 and QuadX FCRx
CtrlFreak Tx8 - Transmitter tested with Uno, Nano, Duemilanove, and Mega.  (Will also work on 16Mhz promini)

You can use the FlyWiiGUI versions from Synerflight. 


TX PINOUT: Check the Tx sketch for pinout to NRF24l01, thumbsticks and pots.



CtrlFreak FC/Rx -  Tested on 16MHz 328 Nano.  Nano is preferred because of its size and the 3.3v output to supply the NRF24l01 and the sensors. Mega not yet supported.

Upload the CtrlFreak8-QuadX-MPU6050-Nano.hex via XLoader to Nano (be mindful of board type or brick it) - at Device select Duemilanove/Nano(AtMEga328). See downloaded image.

CAUTION!:  Upload to Nano only! 

RX PINOUT: 

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

No guarantees.  No warranties.  Use at your own risk.
