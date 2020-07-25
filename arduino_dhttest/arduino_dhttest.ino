 //Used LCD Pins
 //2, 3, 4, 5, 6, 11, 12, 3xGND, 2x5V  
 //
 //Open pins
 //9, 10
 //
 //DHT11 Pins
 //8, 1xGND, 1x5V
 //
 //RELAY Pins
 //7, 1x GND, 1x5V
 //
 //LED Pins
 //13, 1xGND

#include <LiquidCrystal.h> 
#include <DHT.h>

#define DHT11_PIN 8   
#define DHTTYPE DHT12
#define RELAIS_PIN 7
#define LED 13


DHT dht(DHT11_PIN, DHTTYPE);
int Contrast=100;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
int led = 13;

float hum;  
float temp; 
float relaisSwitchOnThreshhold=20.00;

 void setup()
 {
    //LCD
    analogWrite(6,Contrast);
     lcd.begin(16, 2);

    //DHT11
    Serial.begin(9600);
    dht.begin();

    //RELAY
    pinMode(RELAIS_PIN, OUTPUT);
    digitalWrite(RELAIS_PIN, HIGH);

    //LED
    pinMode(led, OUTPUT);
  } 




  
     void loop()
 { 
     lcd.setCursor(0, 0);
     lcd.print("Hum:  " + String(hum) + "%");
     lcd.setCursor(0, 1);
     lcd.print("Temp: " + String(temp) + (char)223 + "C");
   
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius"); 
    delay(2000);
    switchRelaisBasedOnSensorHumidity(hum);
    
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
 }


 void switchRelaisBasedOnSensorHumidity(float hum){
       if (isHumidityAboveThreshhold(hum)){
        digitalWrite(RELAIS_PIN, LOW);
        Serial.println(" Switching Relay");       
    } else {
        digitalWrite(RELAIS_PIN, HIGH);
        Serial.println(" Switching Relay Off");
    }
}

bool isHumidityAboveThreshhold(float hum){
    if (hum>relaisSwitchOnThreshhold){
    return true;
    }
    return false;
}
