#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "freebox_chaouki";
const char* password = "sepP6R5NzH";
const char* mqtt_server = "io.adafruit.com";

#define IO_USERNAME  "medChaouki"
#define IO_KEY       "a2eced6abafd42f7ab4431e59c5f07a2"
#define SERVERPORT      1883
#define PREAMBLE          "/feeds/"
#define RANDOM_DATA      "randomData"

// create WIFI object
WiFiClient WiFiClient;

// create MQTT object
PubSubClient client(WiFiClient);

int counter =0;
String sc="";
char counterStr[5]; 

void reconnect()
{
	while (!client.connected())
	{
		Serial.println("Attempting MQTT connection...");

		if (client.connect("", IO_USERNAME, IO_KEY))
		{
			//connection to the broker is estableshed
			Serial.println("connected to the MQTT broker");


		}
		else
		{
			Serial.println("failed to connect to the MQTT broker");
			Serial.println("retrying in 5s");
			delay(5000);		
		}		
	}


}


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

	//setting the connection to the MQTT broker
	client.setServer(mqtt_server, SERVERPORT);

	reconnect();

}


void loop()
{

	//checking if the ESP is connected to the broker
	//if it isn't connected , try to reconnect
	if (!client.connected())
	{
		reconnect();
		delay(1000);
	}

	//sending test data to the MQTT broker
	if (client.connected())
	{
		counter ++;
		sc = (String)counter;
		sc.toCharArray(counterStr,5);

		Serial.println("Publish test value");
		client.publish(IO_USERNAME PREAMBLE RANDOM_DATA, counterStr);
		delay(2000);
	}

	yield();
	

}