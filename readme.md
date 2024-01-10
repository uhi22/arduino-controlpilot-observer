# Arduino ControlPilot Observer

Purpose: Measure the control pilot voltage of electrical cars charge port, and show the result with LEDs. Print the results on serial port.

Hardware:
- Arduino Pro Mini
- CP via 100k to analog input A2
- A2 pulled to 2.5V by a voltage divider 33k and 33k between 5V and ground
- LED1 with serial resistor between digital pin 6 and ground
- LED2 with serial resistor between digital pin 7 and ground
