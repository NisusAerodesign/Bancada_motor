#include "FS.h"
#include "SD.h"
#include "SPI.h"
float volt, corrente, torque, empuxo, command = 0;
int rpm;
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



void setup(){
        Serial.begin(115200);
        setup_data();
        pinMode(2, OUTPUT);
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
    writeFile(SD, "/DataLogger.txt", "Tensao(V) |  Corrente(A) |  Comando(%)   |   Torque(N*m)  |  Empuxo(N) | RPM(rpm) |Sgundos(s)\n");
    
}

void loop(){
  loop_data();
  File file = SD.open("/DataLogger.txt", FILE_APPEND);
 
  if(file.print(volt)){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }
  file.print(" | ");
  file.print(corrente);
  file.print(" | ");
  file.print(command/1.8);
  file.print(" | ");
  file.print(torque);
  file.print(" | ");
  file.print(empuxo);
  file.print(" | ");
  file.print(rpm);
  file.print(" | ");
  file.println(millis()/1000.0);
  file.close();
}
