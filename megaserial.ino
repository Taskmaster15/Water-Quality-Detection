#include <DHT.h>
#include <SoftwareSerial.h>
#define DHTPIN 2
#define DHTTYPE DHT11 // DHT 11
SoftwareSerial espSerial(5, 6);
DHT dht(DHTPIN, DHTTYPE);

String str;
String str1;
String str2;
String str3;

float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;

int sensorPin = A1;
float volt;
float ntu;

void setup(){
Serial.begin(115200);//baud rate
espSerial.begin(115200);
dht.begin();
delay(2000);
}

void loop()
{
  dht11();
  pH();
  Tur();
  Serial.println();
}



void dht11()
{
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
Serial.print("H: ");
Serial.print(h);
Serial.print("% ");
Serial.print(" T: ");
Serial.print(t);
Serial.println("C");
str =String("DHT-11 ")+String("H= ")+String(h)+String(" T= ")+String(t);
espSerial.println(str);
delay(1000);
}

void pH()
{
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
 ph_act = -5.70 * volt + calibration_value;

 Serial.print("pH Val: ");
 Serial.print(ph_act);
 str1 = String("pH value = ") + String(ph_act);
 espSerial.println(str1);
 delay(1000);
}  

void Tur()
{
    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += (((float)analogRead(sensorPin)/1023)*5) + 1.8;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
    Serial.println();
    Serial.print(volt);
    Serial.println(" V");
 
    Serial.print(ntu);
    Serial.println(" NTU");
    delay(1000);
    str2 = String("Voltage = ") + String(volt) + String(" NTU = ") + String(ntu);
    espSerial.println(str2);
    espSerial.println();
}
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}




  