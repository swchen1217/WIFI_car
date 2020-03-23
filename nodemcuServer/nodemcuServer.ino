#include <SPI.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D1,D2);  //建立軟體串列埠腳位 (RX, TX)

char ssid[] = "swchen1217";               // SSID of your home WiFi
char pass[] = "chen1217";               // password of your home WiFi
WiFiServer server(8888);                    

IPAddress ip(192, 168, 200, 13);            // IP address of the server
IPAddress gateway(192,168,100,4);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

void setup() {
  	Serial.begin(115200);                   // only for debug
 	Serial.println();
 	WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  	WiFi.begin(ssid, pass);                 // connects to the WiFi router
  	while (WiFi.status() != WL_CONNECTED) {
    	Serial.print(".");
    	delay(500);
  	}
  	server.begin();                         // starts the server
  	Serial.println("Connected to wifi");
  	Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  	Serial.print("IP: ");     Serial.println(WiFi.localIP());
  	Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  	Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  	Serial.print("SSID: "); Serial.println(WiFi.SSID());
  	Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  	Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
  	mySerial.begin(57600);
}

void loop () {
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.println(request);
      mySerial.println(request);
      client.flush();
    }
    client.stop();                // tarminates the connection with the client
  }
  delay(10);
}