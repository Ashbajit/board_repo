#include <WiFi.h>
#include "ThingSpeak.h" // Download this library

const char* ssid = "Abhi";   // your network SSID (name) 
const char* password = "Sahoo528491636";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "X0NCVZGDJKO0AAB4"; // From ThingSpeak server

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000; // 20000 -> 20 s

void setup() {
  Serial.begin(115200);  //Initialize serial

  WiFi.mode(WIFI_STA);   

  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
    int randomNumberVoltageInt = random(0,365);
    float randomNumberVoltage = randomNumberVoltageInt/100;
    Serial.print("Value for voltage is: ");
    Serial.println(randomNumberVoltage);

    int randomNumberCurrentInt = random(-10000,10000);
    float randomNumberCurrent = randomNumberCurrentInt/100;
    Serial.print("Value for current is: ");
    Serial.println(randomNumberCurrent);

    int randomNumberTemperatureInt = random(2000,5000);
    float randomNumberTemperature = randomNumberTemperatureInt/100;
    Serial.print("Value for temperature is:  ");
    Serial.println(randomNumberTemperature);

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different pieces of information in a channel.  
    // Here, we write to field 1.

    // For a single channel
    //    int x = ThingSpeak.writeField(myChannelNumber, 1, randomNumberVoltage, myWriteAPIKey);  

    // For Multiple channel
    ThingSpeak.setField(1, randomNumberVoltage);
    ThingSpeak.setField(2, randomNumberCurrent);
    ThingSpeak.setField(3, randomNumberTemperature);
    ThingSpeak.setField(4, 10);
    ThingSpeak.setField(5, 20);
    ThingSpeak.setField(6, 30);
    ThingSpeak.setField(7, 40);
    ThingSpeak.setField(8, 50);

    int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(response == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(response) );
    }
    lastTime = millis();
  }
}
