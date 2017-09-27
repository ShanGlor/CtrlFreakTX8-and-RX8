# CtrlFreak Tx8 and QuadX FCRx
CtrlFreak Tx8 - Transmitter tested with Uno, Nano, Duemilanove, and Mega.  Not tested on 5v Promini but will work.

TX PINOUT: Check the Tx sketch for pinout to NRF24l01, thumbsticks and pots.  

nRF24 connections (left is nRF24, right is arduino)

  nrf24   Uno/Duemilanove/Promini
  
  CE      9
  
  CSN     10
  
  MOSI   11
  
  MISO   12
  
  SCK    13
  

  nrf24   Mega
  
  CE      9
  
  CSN     53
  
  MOSI    51
  
  MISO     50
  
  SCK      52
  


CtrlFreak QuadX Flight Controller/Receiver -  Only supports QuadX type drone with MPU6050 only as IMU. Tested on 16MHz 328 Nano. Nano is preferred because of its size and the 3.3v output to supply the NRF24l01 and the sensors. Mega not yet supported.  PPM sequence is THROTTLE,PITCH,ROLL,YAW,AUX1,AUX2,AUX3,AUX4 

Compatible with FlyWiiGUIs from Synerflight (See Clifford's posts). 


CAUTION!:  Upload only to a Nano.  Upload the CtrlFreak8-QuadX-MPU6050-Nano.hex via XLoader. Select Duemilanove/Nano(ATmega328) as board.  See downloaded image.  Be mindful of board type or brick it. 

RX PINOUT: 

ESCs/Motors use digital pins 9,6,5,3 instead of 9,10,11,3 because we allocated the hardware SPI pins for NRF24.

MPU6050 on I2c (A4/A5)

nRF24 connections (left is nRF24, right is arduino):

  CE- D7

  CSN-D8

  MOSI-D11

  MISO-D12

  SCK-D13


IMPORTANT: Add capacitor (104 ceramic or 47uF 25v electrolytic) between VCC and Ground pins of NRF24l01

Fritzing Diagram:  To do...

No guarantees.  No warranties.  Use at your own risk.  Fly safely and have fun!
