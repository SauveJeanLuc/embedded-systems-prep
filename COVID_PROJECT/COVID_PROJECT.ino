//Libraries
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

// Needed variables
#define REDPIN 12
#define GREENPIN 13
#define BUZZERPIN 15
#define TEMPVOUT A0

int lcdColumns = 16;
int lcdRows = 2;
WiFiClient wifiClient;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {

    Serial.begin(9600);

    Serial.println("================================");
    Serial.println("===== DOBY's TEMPO LIMITED =====");
    Serial.println("================================");
    
    // LEDs
    pinMode(REDPIN, OUTPUT);
    pinMode(GREENPIN, OUTPUT);
    pinMode(BUZZERPIN, OUTPUT);

    // LCD
    lcd.begin(5,4);
    lcd.init();
    lcd.backlight();    

    // SETUP WiFi
     WiFi.begin("RCA-WiFi", "rca@2019");
}

void loop() {

  // Read Temperature Meter
  int analogValue = analogRead(TEMPVOUT);
  float millivolts = (analogValue/1024.0) * 5; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts*100;

  Serial.print("Degrees READ=   ");
  Serial.println(celsius);

  String mData="";
  String dummy_device = "sauve";
  mData = "device="+dummy_device+"&distance="+(String)celsius;
    
  if(celsius < 35 ){
    // Turn on GREEN LED
    digitalWrite(GREENPIN, HIGH);
    // Turn off GREEN LED
    digitalWrite(REDPIN, LOW);
    // Turn off BUZZER
    digitalWrite(BUZZERPIN, LOW);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print((String)celsius + " celsius");   

    
  }else{
    // Turn on GREEN LED
    digitalWrite(GREENPIN, LOW);
    // Turn off GREEN LED
    digitalWrite(REDPIN, HIGH);
    // Turn off BUZZER
    digitalWrite(BUZZERPIN, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print((String)celsius + " celsius");  

    sendData(80, "insecure.benax.rw", "/iot/" , mData); 
  }

  delay(2000);

}


void sendData(const int httpPort, const char* host,const char* filepath , String data){
  
  wifiClient.connect(host, httpPort); 

  wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
  wifiClient.println("Host: " + (String)host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("Content-Type: application/x-www-form-urlencoded");
  wifiClient.println("Content-Length: " +(String)data.length());
  wifiClient.println();
  wifiClient.print(data);

  Serial.println("Response: " + wifiClient.readStringUntil('\n'));

}
