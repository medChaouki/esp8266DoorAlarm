#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "freebox_chaouki";
const char* password = "sepP6R5NzH";
const char* mqtt_server = "io.adafruit.com";

#define IO_USERNAME  "medChaouki"
#define IO_KEY       "a2eced6abafd42f7ab4431e59c5f07a2"
#define SERVERPORT      1883

// create WIFI object
WiFiClient WiFiClient;

// create MQTT object
PubSubClient client(WiFiClient);

void setup() 
{
	//starting serial communication
	Serial.begin(115200);

	Serial.print("Connecting to ");
	Serial.println(ssid);
	//connecting to wifi
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) 
	{
    	delay(500);
    	Serial.print(".");
	}

	//printing wifi infos
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	WiFi.printDiag(Serial);

}


void loop()
{
	//just a place holder
	Serial.println("hello");
	yield();
	delay(1000);

}