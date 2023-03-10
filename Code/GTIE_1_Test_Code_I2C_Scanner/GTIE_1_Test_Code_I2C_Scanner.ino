/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  GTIE Grid Tie Inverter Extender v1.0
  Features include ESP8266 CT Clamp Battery Voltage Detector I2C OLED Opto-In GPIO
  PCA v1.2211-104 - Test Code Firmware v1 - 19th January 2023

  Simplified Board Bring Up Test - I2C Bus Scanner (Output sent to the Serial Print)
  
  Remember!
  - Set the BOARD to ESP8266 DEV Module (Any Wemos D1 or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  
  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.
  
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and github.com/DitroniX
*/

// Libraries
#include <Wire.h>

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1;  // Loop Delay in Seconds

// **************** OUTPUTS ****************
#define LED_Blue 2  // Red LED

// Define I2C (Expansion Port)
#define I2C_SDA 4
#define I2C_SCL 5

// **************** FUNCTIONS AND ROUTINES ****************

void ScanI2CBus() {  // I2C Bus Scanner

  byte error, address;
  int nDevices;

  Serial.println("\nScanning I2C Bus for Devices ...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.print(address, HEX);
      if (address == 72) Serial.print(" ADC Present");
      if (address == 50) Serial.print(" EEPROM Present");
      Serial.println();

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found. Possible Hardware Issue?");
  } else {
    Serial.println("I2C Bus Scan Complete");
  }
}

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;
  Serial.println("");

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // LEDs
  pinMode(LED_Blue, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Blue, HIGH);

}

// **************** LOOP ****************
void loop() {

  
  // Hardware Tests
  ScanI2CBus();

  // Heatbeat LED
  digitalWrite(LED_Blue, LOW);
  delay(50);
  digitalWrite(LED_Blue, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);
}
