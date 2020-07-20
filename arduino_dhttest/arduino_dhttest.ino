//Libraries
#include <DHT.h>

//Constants
#define DHT11_PIN 2   
#define DHTTYPE DHT11

#define RELAIS_PIN 3

DHT dht(DHT11_PIN, DHTTYPE);
//Variables
float peter;  //Stores humidity value
float temp; //Stores temperature value
float relaisSwitchOnThreshhold=13.00;

void setup()
{
    Serial.begin(9600);
    dht.begin();
    pinMode(RELAIS_PIN, OUTPUT);
    digitalWrite(RELAIS_PIN, HIGH);
}

void loop()
{
    //Read data and store it to variables hum and temp
    peter = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(peter);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius"); 
    switchRelaisBasedOnSensorHumidity(peter);  
    delay(2000); //Delay 2 sec.
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



