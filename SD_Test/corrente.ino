#define VIN 2 // define the Arduino pin A0 as voltage input (V in)
#define VCC  3.3// supply voltage 5V or 3.3V. If using PCB, set to 5V only.
#define model  0  // enter the model (see below)

#define cutOffLimit 1.00;// reading cutt off current. 1.00 is 1 Amper

float c1 = 0;
float c2 = 0;
float c3 = 0;
float c4 = 0;
float c5 = 0;

/*
          "ACS758LCB-050B",// for model use 0
          "ACS758LCB-050U",// for model use 1
          "ACS758LCB-100B",// for model use 2
          "ACS758LCB-100U",// for model use 3
          "ACS758KCB-150B",// for model use 4
          "ACS758KCB-150U",// for model use 5
          "ACS758ECB-200B",// for model use 6
          "ACS758ECB-200U"// for model use  7   
sensitivity array is holding the sensitivy of the  ACS758
current sensors. Do not change.          
*/
float sensitivity[] ={
          40,// for ACS758LCB-050B
          60.0,// for ACS758LCB-050U
          20.0,// for ACS758LCB-100B
          40.0,// for ACS758LCB-100U
          13.3,// for ACS758KCB-150B
          16.7,// for ACS758KCB-150U
          10.0,// for ACS758ECB-200B
          20.0,// for ACS758ECB-200U     
         }; 

/*         
 *   quiescent Output voltage is factor for VCC that appears at output       
 *   when the current is zero. 
 *   for Bidirectional sensor it is 0.5 x VCC
 *   for Unidirectional sensor it is 0.12 x VCC
 *   for model ACS758LCB-050B, the B at the end represents Bidirectional (polarity doesn't matter)
 *   for model ACS758LCB-100U, the U at the end represents Unidirectional (polarity must match)
 *    Do not change.
 */
float quiescent_Output_voltage [] ={
          0.5,// for ACS758LCB-050B
          0.12,// for ACS758LCB-050U
          0.5,// for ACS758LCB-100B
          0.12,// for ACS758LCB-100U
          0.5,// for ACS758KCB-150B
          0.12,// for ACS758KCB-150U
          0.5,// for ACS758ECB-200B
          0.12,// for ACS758ECB-200U            
          };
const float FACTOR = sensitivity[model]/1000;// set sensitivity for selected model
const float QOV =   quiescent_Output_voltage [model] * VCC;// set quiescent Output voltage for selected model
//float voltage;// internal variable for voltage
float cutOff = FACTOR/cutOffLimit;// convert current cut off to mV
int voltagetot = 0;
int i;
 //************ END of ACS785 Settings
 
//******************** Start of LCD1602
// Jan 21, 2018 14:25
// original source https://www.arduino.cc/en/Tutorial/HelloWorld


void setup_corrente() {
  // Robojax.com ACS758 Current Sensor with LCD1602 
    Serial.begin(115200);// initialize serial monitor
    //Serial.println("ACS758 Current Sensor");
    delay(100);
    float pres_1 = 0;

}

void loop_corrente() {
  // Robojax.com ACS758 Current Sensor with LCD1602 
  for(i=0;i<32;i++){
    voltagetot= voltagetot+analogRead(VIN);
  }
  c5 = c4;
  c4 = c3;
  c3 = c2;
  c2 = c1;
  float voltage_raw =   (3.3 / 1023.0)* (voltagetot/32);// Read the voltage from sensor
  voltage =  voltage_raw - QOV + 0.007 ;// 0.007 is a value to make voltage zero when there is no current
  c1 = (((voltage / FACTOR)*2.76124)-302)/2.761;
  corrente = abs((c1 +  c2 + c3 + c4 + c5)/5);
  voltagetot=0;
  // Robojax.com ACS758 Current Sensor with LCD1602 
} 