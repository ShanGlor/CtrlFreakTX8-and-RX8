/*
NRF24L01 PA+ LNA as the transmitter 
Tested with 16MHz Nano, Duemilanove and Mega 
TMRH20 RF24 libs from  at github.  

nRF24 connections (left is nRF24, right is arduino):q  NOTE:  Edit the CE, CSN CONSTRUCTOR
  nrf24   Uno 
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

Thumbstick1 X and Y to A0 and A1 respectively.
Thumbstick1 Button to D3

Thumbstick2 X and Y to A2 and A3 respectively.
Thumbstick2 Button to D5.

10k potentiometers to A6, A7. 

PPM out from D4 and grnd to RF module or PC's mic input as game controller, add 80k-100k ohm resistor
*/

#include <SPI.h>
#include <RF24.h> 
#include <Wire.h>
#include "ppm.h"

#define SERIAL_DEBUG true  //true to see joystick values in serial mon but will require memory

#define thumbstick_sw1  3  //D3
#define thumbstick_sw2  5  //D5
boolean timeout;       
boolean hasHardware = true;  // Allows testing of radios and code without Joystick hardware. Set 'true' when joystick connected

const byte writingPipe[5] = {'F','r','E','A','K'};  //customizable pipe address must match the one in the receiver
//const uint64_t writingPipe = 0xE8E8F0F0E5LL; //can also be used as address

////CE, CSN CONSTRUCTOR////
//RF24 radio(8,10);  //For Uno 
RF24 radio(9,53);  //For Mega.  More pins to spare, Mega Version has OLED display, tx battery monitoring and buzzer/speaker,ETC.

struct packet {
  uint8_t throttle,pitch,roll,yaw,aux1,aux2,aux3,aux4;
} 
packet;  //data structure to broadcast

uint16_t pitch_mid = 537; // higher means more backward
uint16_t roll_mid = 492; // higher means more right

void setPPMValuesFromData()  //AETR sequence to PPM out D4 to other RF module or PC audio mic as game controller (Smartpropoplus with vjoy)
{
  ppm[0] = map(packet.roll, 0, 255, 1000, 2000);
  ppm[1] = map(packet.pitch,      0, 255, 1000, 2000);
  ppm[2] = map(packet.throttle,    0, 255, 1000, 2000);
  ppm[3] = map(packet.yaw,     0, 255, 1000, 2000);
  ppm[4] = map(packet.aux1,    0, 255, 1000, 2000);
  ppm[5] = map(packet.aux2,    0, 255, 1000, 2000);
  ppm[6] = map(packet.aux3,    0, 255, 1000, 2000);
  ppm[7] = map(packet.aux4,    0, 255, 1000, 2000);
  //ppm[8] = map(packet.aux5,    0, 255, 1000, 2000);
  //ppm[9] = map(packet.aux6,    0, 255, 1000, 2000); //future release as Tx batt monitor
} 

void setup() {
  
  if (SERIAL_DEBUG) Serial.begin(115200); //if true, initializes serial monitor but requires more memory
  
  setupPPM();  //initialize PPM OUT setup 
  
  pinMode(thumbstick_sw1, INPUT_PULLUP); // left thumbstick button
  pinMode(thumbstick_sw2, INPUT_PULLUP);  // right thumbstick button
  
  radio.begin(); 
  radio.openWritingPipe(writingPipe);  
  radio.setAutoAck(false) ;  //true false, will be used as telemetry channel from Rx in future releases
  radio.enableAckPayload();
  radio.setDataRate(RF24_250KBPS); //
  radio.setPALevel(RF24_PA_MAX);  //min, high, max
  radio.setChannel(108);

  radio.powerUp();  
}

/*
// Returns a corrected value for a joystick position that takes into account
// the values of the outer extents and the middle of the joystick range.
 
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}
*/

void readPots() {  //map joystick values to PWM
  
  packet.throttle = map(analogRead(0), 0, 1023, 255, 0); // 0, 255 to reverse  
  packet.yaw = map(analogRead(1), 0, 1023, 255, 0); 
  packet.pitch = map(analogRead(2), 0, 1023, 255, 0);  
  packet.roll = map(analogRead(3), 0, 1023, 255, 0);  

 //Thumbsticks Switches  //map digital values to PWM
  packet.aux1 = map(!digitalRead(thumbstick_sw1), 0, 1, 0, 255);  // Invert the pulldown switch  //D3
  packet.aux2 = map(!digitalRead(thumbstick_sw2), 0, 1, 0, 255);  // Invert the pulldown switch  //D5
  
  
  //add 10k potentiometers to make 10 channel
  packet.aux3 = constrain( map( analogRead(6), 968,   27, 0, 255 ), 0, 255);  //A6 
  packet.aux4 = constrain( map( analogRead(7),   1, 1022, 0, 255 ), 0, 255);  //A7    //pin also for tx battery monitor
  
  //packet.aux5 = constrain( map( analogRead(4), 968,   27, 0, 255 ), 0, 255);  //A4    //A4 and A5 reserved for I2c (wotking for OLED and/or other sensors for control i.e. gyro,flex,gesture,voice, etc.)
  //packet.aux6 = constrain( map( analogRead(5),   1, 1022, 0, 255 ), 0, 255);  //A5    //will disable this in future releases for I2c sensors

  //Alternate mapping
  //packet.throttle = mapJoystickValues( analogRead(0), 180, 497, 807, false );  //A0  false/true to reverse
  //packet.yaw = mapJoystickValues( analogRead(1), 109, 460, 848, false );  //A1
  //packet.pitch = mapJoystickValues( analogRead(2), 136, 462, 779, false );  //A2
  //packet.roll = mapJoystickValues( analogRead(3), 165, 564, 906, true );  //A3

}

void loop()  {

  readPots(); //read joystick 
  
  radio.write(&packet, sizeof(packet));  //broadcast packet data
  
  setPPMValuesFromData();  //enable PPM out

   if (SERIAL_DEBUG) {
    Serial.print(" Throttle@A0=");
    Serial.print(packet.throttle);
    Serial.print(" | Yaw@A1=");
    Serial.print(packet.yaw);
    Serial.print(" | Pitch@A2=");
    Serial.print(packet.pitch);
    Serial.print(" | Roll@A3=");
    Serial.print(packet.roll);
    Serial.print(" | Aux1@D3=");
    Serial.print(packet.aux1);
    Serial.print(" | Aux2@D5=");
    Serial.print(packet.aux2);
    Serial.print(" | Aux3@A6=");
    Serial.print(packet.aux3);
    Serial.print(" | Aux4@A7=");
    Serial.print(packet.aux4);
    //Serial.print(" | Aux5@A4=");
    //Serial.print(packet.aux5);
    //Serial.print(" | Aux6@A5=");
    //Serial.print(packet.aux6);
    Serial.println();
   }
}




