#include "DHT.h" // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11 //DHT11
#include <ESP8266WiFi.h> 
#include "Adafruit_MQTT.h" 
#include "Adafruit_MQTT_Client.h" 
#include <Servo.h>

Servo servo;

#define Relay1 D0 
#define Relay2 D1 
#define Relay3 D2 
#define Relay4 D3 
#define Relay6 D5 
#define Relay7 D6
#define dht_dpin D8

#define WLAN_SSID "honor" // Your SSID
#define WLAN_PASS "deveshvishal6" // your password

 /************************* Adafruit.io Setup *********************************/

#define AIO_SERVER "io.adafruit.com" // Adafruit Server
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "deveshvishal607" // Username
#define AIO_KEY "775596eb6f9449829962b5b8adefc094" // Auth Key

//DHT PIN
DHT dht (dht_dpin, DHTTYPE); 
//WIFI CLIENT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT,AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe led3 = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME"/feeds/led3"); // Feeds name should be same everywhere
Adafruit_MQTT_Subscribe LIGHT2 = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME "/feeds/LIGHT2");
Adafruit_MQTT_Subscribe LIGHT3 = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME "/feeds/LIGHT3");
Adafruit_MQTT_Subscribe LIGHT4 = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME "/feeds/LIGHT4");
Adafruit_MQTT_Subscribe led1 = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME "/feeds/led1");
Adafruit_MQTT_Subscribe led2 = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME "/feeds/led2");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME "/feeds/led");
Adafruit_MQTT_Publish ROOM_TEM = Adafruit_MQTT_Publish(&mqtt,AIO_USERNAME "/feeds/ROOM_TEM");
Adafruit_MQTT_Publish OUT_TEMP = Adafruit_MQTT_Publish(&mqtt,AIO_USERNAME "/feeds/OUT_TEMP");


void MQTT_connect();

void setup() { 
	dht.begin(); Serial.begin(115200);
	pinMode(Relay1, OUTPUT);
	pinMode(Relay2, OUTPUT); pinMode(Relay3, OUTPUT); pinMode(Relay4, OUTPUT); //pinMode(Relay5, OUTPUT); pinMode(Relay6, OUTPUT); pinMode(Relay7, OUTPUT);
	servo.attach(2); //D4 servo.write(0);
	// Connect to WiFi access point. Serial.println(); Serial.println(); Serial.print("Connecting to "); Serial.println(WLAN_SSID);
	WiFi.begin(WLAN_SSID, WLAN_PASS); while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println();
	Serial.println("WiFi connected"); Serial.println("IP address: "); Serial.println(WiFi.localIP());
	mqtt.subscribe(&led3); mqtt.subscribe(&LIGHT2); mqtt.subscribe(&LIGHT3); mqtt.subscribe(&LIGHT4); 
	mqtt.subscribe(&led1);
	mqtt.subscribe(&led2);
	mqtt.subscribe(&led);
}

void loop() {
	MQTT_connect();
	float t = dht.readTemperature(); 
	float h = dht.readHumidity(); 
	Serial.print("HUMIDITY = "); 
	Serial.print(h);
	Serial.print("%"); 
	Serial.print("TEMPERATURE = "); Serial.print(t);
	Serial.println("C ");
	Serial.print("...");
	Adafruit_MQTT_Subscribe *subscription;

	while ((subscription = mqtt.readSubscription(20000))) {
		OUT_TEMP.publish(h); 
		delay(10);
		ROOM_TEM.publish(t);
		delay(10);
		if (subscription == &led3) {
			Serial.print(F("Got: "));
			Serial.println((char *)led3.lastread);
			int led3_State = atoi((char *)led3.lastread);
			digitalWrite(Relay1, !led3_State);
		}
		if (subscription == &LIGHT2) {
			Serial.print(F("Got: "));
			Serial.println((char *)LIGHT2.lastread);
			int LIGHT2_State = atoi((char *)LIGHT2.lastread);
			digitalWrite(Relay2, !LIGHT2_State);
		}
		if (subscription == &LIGHT3) {
			Serial.print(F("Got: "));
			Serial.println((char *)LIGHT3.lastread);
			int LIGHT3_State = atoi((char *)LIGHT3.lastread); 
			digitalWrite(Relay3, !LIGHT3_State);
		}
		if (subscription == &LIGHT4) {
			Serial.print(F("Got: "));
			Serial.println((char *)LIGHT4.lastread);
			int LIGHT4_State = atoi((char *)LIGHT4.lastread); 
			digitalWrite(Relay4, !LIGHT4_State);
		}
		if (subscription == &led) { 
			Serial.print(F("Got: ")); 
			Serial.println((char *)led.lastread);
			int led_State = atoi((char *)led.lastread); 
			if(led_State == 1) {
				servo.write(90); delay(1000);
			}
			if(led_State == 0) {
				servo.write(0); delay(1000);
			} 
		}
		if (subscription == &led1) { 
			Serial.print(F("Got: ")); 
			Serial.println((char *)led1.lastread);
			int led1_State = atoi((char *)led1.lastread); 
			digitalWrite(Relay6, !led1_State);
		}
		if (subscription == &led2) { 
			Serial.print(F("Got: ")); 
			Serial.println((char *)led.lastread);
			int led2_State = atoi((char *)led2.lastread); 
			digitalWrite(Relay7, !led2_State);
		}
	 }
	}

void MQTT_connect() { 
	int8_t ret;
	if (mqtt.connected()) { 
		return;
	}

	Serial.print("Connecting to MQTT... ");
	uint8_t retries = 3;
	while ((ret = mqtt.connect()) != 0) { 
		Serial.println(mqtt.connectErrorString(ret)); 
		Serial.println("Retrying MQTT connection in 5 seconds..."); 
		mqtt.disconnect();
		delay(5000);
		retries--;
		if (retries == 0) {
			while (1);
		} 
	}
	
	Serial.println("MQTT Connected!");
}













