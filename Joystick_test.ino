/*
 Joystick input with serial output

 Reads the analogue input pins from the x and y axis on a joystick along
 with the button pres state and echos this to the serial monitor.

 The circuit:
 * Joystick with x and y connected to A0 and A1
   Gnd and 5V connected to Joystick supply and
   Joysticj button connected to Digital input 2

 Created  22 January 2013
 Modified 22 January 2013
 by Tim Russell (@timr1972)

 This example code is in the public domain.

 */

// Modify pins accordingly
const int analogue0 = A0;  // Analog input pin X
const int analogue1 = A1;  // Analog input pin Y
const int jbutton   = 3;   // Digital input pin Button

int a0Value = 0;        // value read from the x-axis
int a1Value = 0;        // value read from the y-axis
int jbValue = 0;        // value read from the joystick button

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  pinMode(jbutton, INPUT);     // Set button as input
  digitalWrite(jbutton, HIGH); // Pullup resisitor
}

void loop() {
  // read the analogue values, and the button state
  a0Value = analogRead(analogue0);
  a1Value = analogRead(analogue1);
  if (digitalRead(jbutton) == HIGH) {
    jbValue=0;
  }else {
    jbValue=1;
  }

  // Erint the results to the serial monitor:
  Serial.print("a0 = " );
  Serial.print(a0Value);
  Serial.print("\t a1 = ");
  Serial.print(a1Value);
  Serial.print("\t jb = ");
  Serial.println(jbValue);
  // Wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  delay(10);
}
