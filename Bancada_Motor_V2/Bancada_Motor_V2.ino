/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */
#include "FS.h"
#include "SD.h"
#include "SPI.h"
float torq, empuxo, volt, corrente, ttl, rpm, power;


void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}



void setup_sd(){
        Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    digitalWrite(12, HIGH);
    writeFile(SD, "/DataLogger.txt", "Torque(N*mm) |  Empuxo(N) |  Comando(%)  |   RPM   |   Tensao(V)  |  Corrente(A) |  Potencia(W)  | Sgundos(s)\n");
    
}

void loop_sd(){
  File file = SD.open("/DataLogger.txt", FILE_APPEND);
 
  file.print(torq);
  file.print(" | ");
  file.print(empuxo);
  file.print(" | ");
  file.print(ttl);
  file.print(" | ");
  file.print(rpm);
  file.print(" | ");
  file.print(volt);
  file.print(" | ");
  file.print(corrente);
  file.print(" | ");
  file.print(power);
  file.print(" | ");
  file.println(millis()/1000.0);
  file.close();
}
