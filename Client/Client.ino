#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Replace with your network credentials (STATION)
const char* ssid = "ESP8266 Thing 99C2";
const char* password = "sparkfun";
const String serverPath = "http://10.10.10.22/boloKiKhobor";


unsigned long previousMillis = 0;
unsigned long interval = 30000;

// set the LCD number of columns and rows
const int lcdColumns = 16;
const int lcdRows = 2;
const int PushButton = 15;  // will set to D15

bool first = true;
int Push_button_state;
String jsonBuffer;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(115200);
  lcd.init();
  initWiFi();
  // turn on LCD backlight                      
  lcd.backlight();
  pinMode(PushButton, INPUT);
}

void loop(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    printString("Reconnecting..", 0, true);
    WiFi.disconnect();
    delay(5000);
    WiFi.reconnect();
    delay(5000);
  }else{
    // call in every 10 second
    delay(10000);
    Serial.println("Connected to WiFi...");
    HTTPClient http;

      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode == 200) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        
        StaticJsonDocument<200> doc;
        auto error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(error.c_str());
            return;
        }
        float upper = doc["test1"]; //Get sensor type value
        float lower = doc["test2"];                    //Get value of sensor measurement
       
        Serial.print("Upper: ");
        Serial.println(upper);
        Serial.print("lower value: ");
        Serial.println(lower);
        
        jsonBuffer = "Upper: ";
        jsonBuffer.concat(upper);
        printString(jsonBuffer, 0, true);
        
        jsonBuffer = "Lower: ";
        jsonBuffer.concat(lower);
        printString(jsonBuffer, 1, false);
      }
      else {
        Serial.print("Error code: ");
        printString("Error on", 0, true);
        printString("      server", 1, false);
      }
   
    /* Push */
    Push_button_state= digitalRead(PushButton);
    if ( Push_button_state == HIGH ){ 
      Serial.println("Button pushed.");
      printString("Push Catched", 0, true);
      delay(5000);
      lcd.clear();
    }
    
  }
  

}

void printString(String st, int index, bool clean_previous){
  int row_size = 16;
  if(clean_previous)lcd.clear();
  if(index < 2 && -1 < index && st.length() <= row_size){
    lcd.setCursor(0, index);
    lcd.print(st);
  }else{
    lcd.setCursor(0, 0);
    lcd.print("Invalid length!");
  }
  //delay(5000);
  //lcd.clear();
}
