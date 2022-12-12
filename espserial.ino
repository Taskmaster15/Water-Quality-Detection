#include <ESP8266WiFi.h>
 
String apiKey = "H38TEGNC0XKW43BB";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Kishaan";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Kishaan1843807692";
const char* server = "api.thingspeak.com";

const int updateThingSpeakInterval = 20 * 1000;  // 20 second interval at which to update ThingSpeak
void setup() {
// Open serial communications and wait for port to open:

Serial.begin(115200);
connectToWiFi();
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over

if (Serial.available()) {
Serial.write(Serial.read());
}

}
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  Serial.println("...");
  WiFi.begin(ssid, pass);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 20)) {
   retries++;
   delay(500);
   Serial.print(".");
  }
  if (retries > 19) {
    Serial.println(F("WiFi connection FAILED"));
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected!"));
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.SSID());
  }
    Serial.println(F("Setup ready"));
}


