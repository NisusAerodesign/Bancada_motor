#include "Adafruit_HX711.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h> 

// --- loadcell pins
#define DT1 PB8
#define DT2 PB4
#define DT3 PB9
#define CK PA11

// V and I pins
#define vPin PA3
#define iPin PA0

// SD CS pin
#define chipSelect PA4

// --- Pitot constants
#define PSI_TO_PASCAL 6894.76
#define AIR_DENSITY 1.225 // kg/m^3 (ao nível do mar)

// --- Pitot I2C address
#define MS4525_ADDRESS 0x28

// --- Pitot constants
#define Pmin -1.0
#define Pmax 1.0

// SD read LED
#define ledPin PC13

const float f_tracao = 432.1623978897209;
const float f_torq1 = 1015.5633090614887;
const float f_torq2 = 904.7828247803975;
const float f_volt = 167.80371035308198;
const float f_amp = 14.615;
const float f2_amp = 1898;
String fileName = "data.txt";
float pressure;
float temperature;

Adafruit_HX711 torq1(DT1, CK);
Adafruit_HX711 trac(DT2, CK);
Adafruit_HX711 torq2(DT3, CK);

// --- Loadcell setup ---
void tareAll(){
  Serial.println("Tareing....");
  for (uint8_t t=0; t<3; t++) {
    torq1.tareA(torq1.readChannelRaw(CHAN_A_GAIN_128));
    torq1.tareA(torq1.readChannelRaw(CHAN_A_GAIN_128));
    trac.tareA(trac.readChannelRaw(CHAN_A_GAIN_128));
    trac.tareA(trac.readChannelRaw(CHAN_A_GAIN_128));
    torq2.tareA(torq2.readChannelRaw(CHAN_A_GAIN_128));
    torq2.tareA(torq2.readChannelRaw(CHAN_A_GAIN_128));
  }
}

// --- SD functions begin ---
void startSD(){
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
}

void printlnSD(String text, String file){
  File myFile = SD.open(file, FILE_WRITE); // FILE_READ for reading
  if (myFile) {
    digitalWrite(ledPin, LOW); // Turn on the led
    myFile.println(text);
    myFile.close();
  } else {
    Serial.println("Error opening file.");
  }
  digitalWrite(ledPin, HIGH); // Turn off the led
}
// --- SD functions end ---

// --- Data collect functions begin ---
float tracao(){
  return trac.readChannelBlocking(CHAN_A_GAIN_128)/f_tracao;
}
float torque(){
  return ((torq1.readChannelBlocking(CHAN_A_GAIN_128)/f_torq1+torq2.readChannelBlocking(CHAN_A_GAIN_128)/f_torq2)*0.03/2);
}
float tensao(){
  return analogRead(vPin)/f_volt;
}
float corrente(){
  return (analogRead(iPin)-f2_amp)/f_amp;
}
void pitot(float * p,float * t){
  Wire.requestFrom(MS4525_ADDRESS, 4);
  if (Wire.available() == 4){
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    uint8_t temp_msb = Wire.read();
    uint8_t temp_lsb = Wire.read();

    uint8_t status = (msb & 0xC0) >> 6;

    uint16_t raw_pressure = ((msb & 0x3F) << 8) | lsb;

    uint16_t raw_temperature = ((temp_msb << 8) | temp_lsb) >> 5;

    *p = ((float)(raw_pressure - 1638) / (14745 - 1638)) * (Pmax - Pmin) + Pmin;

    *t = ((float)raw_temperature / 2047.0) * 200.0 - 50.0;
  }
}
// --- Data collect functions end ---

void setup() {
  //pin definitions
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, HIGH); //LED starts off. Note: PC13 has inverted logic.
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
  pinMode(DT1, INPUT_PULLDOWN);
  pinMode(DT2, INPUT_PULLDOWN);
  pinMode(DT3, INPUT_PULLDOWN);
  pinMode(vPin, INPUT);
  pinMode(iPin, INPUT);
  pinMode(PA11, OUTPUT);

  //Serial setup
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Serial ready");

  startSD();
  if (SD.exists(fileName))
  SD.remove(fileName);

  Wire.begin();

  torq1.begin();
  trac.begin();
  torq2.begin();

  tareAll();
  Serial.println("Tracao | Torque | Tensao | Corrente | Pressao | Temperatura");
  printlnSD("Tracao | Torque | Tensao | Corrente | Pressao | Temperatura", fileName);
}

void loop() {
  pitot(&pressure, &temperature);
  String dataLine = String(tracao(), 2) + " | " + String(torque(), 2) + " | " + String(tensao(), 2) + " | " + String(corrente(), 2) + " | " + String(pressure, 2) + " | " + String(temperature, 2);
  Serial.println(dataLine);
  printlnSD(dataLine, fileName);
}
