/* Arduino ControlPilot Observer

   Purpose: Measure the control pilot voltage of electrical cars charge port, and show
   the result with LEDs. Print the results on serial port.
*/


#define LED1_pin 6 /* LED1 shows that the high-voltage of the CP is in valid range (6V to 12V) */
#define LED2_pin 7 /* LED2 shows that the low-voltage of the CP is in valid range (-12V) */

void setup() {
  Serial.begin(115200);
  pinMode(LED1_pin, OUTPUT);
  pinMode(LED2_pin, OUTPUT);
}

/* we have a voltage divider between the CP and the controller port. */
#define R1 100000.0 /* 100k upper resistor */
#define R2 (33000.0/2) /* two 33k are the lower divider resistor. One to ground, one to 5V */

float uMin, uMax;

void loop() {
  uint16_t analogValueCP;
  float voltageCP_V;
  uint16_t i;
  uMin=100;
  uMax=-uMin;
  for (i=0; i<200; i++) { /* take 200 samples of the analog input and calculate the min and max voltage */
    analogValueCP = analogRead(A2);
    voltageCP_V = 2.5 + ((float)analogValueCP - 512.0) * 5.0 / 1023 * (R1+R2)/R2;
    if (voltageCP_V<uMin) uMin = voltageCP_V;
    if (voltageCP_V>uMax) uMax = voltageCP_V;
  }
  //Serial.print(analogValueCP);
  Serial.println(String(uMin) + " " + String(uMax));
  /* control the LEDs depending on the min and max voltage */
  if ((uMax>4) && (uMax<14)) { /* nominal 6V, 9V or 12V. We give 2V tolerance. */
    digitalWrite(LED1_pin, HIGH);
  } else {
    digitalWrite(LED1_pin, LOW);
  }
  if ((uMin>-14) && (uMin<-10)) { /* nominal -12V. We give 2V tolerance. */
    digitalWrite(LED2_pin, HIGH);
  } else {
    digitalWrite(LED2_pin, LOW);
  }
}
