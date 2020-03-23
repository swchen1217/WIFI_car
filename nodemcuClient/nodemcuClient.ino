#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PS2X_lib.h>

PS2X ps2x;

char ssid[] = "swchen1217";               // SSID of your home WiFi
char pass[] = "chen1217";               // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,100,13);       // the fix IP address of the server
WiFiClient client;

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup() {
  delay(300);
  error = ps2x.config_gamepad(D1,D3,D2,D4, true, true);

  if(error == 1)
	return; 

  Serial.begin(115200);               // only for debug
  Serial.println();
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
}

void loop () {
  if(error == 1)
	return; 
  ps2x.read_gamepad(false, vibrate);
  //String pkg=ps2x.Analog(PSS_LY)+","+ps2x.Analog(PSS_LX)+","+ps2x.Analog(PSS_RY)+","+ps2x.Analog(PSS_RX)+","+ps2x.Button(PSB_L2);
  Serial.print(ps2x.Analog(PSS_LY));
  Serial.print(",");
  Serial.print(ps2x.Analog(PSS_LX));
  Serial.print(",");
  Serial.print(ps2x.Analog(PSS_RY));
  Serial.print(",");
  Serial.print(ps2x.Analog(PSS_RX));
  Serial.print(",");
  Serial.println(ps2x.Button(PSB_L2));
  client.connect(server, 8888);
  client.print(ps2x.Analog(PSS_LY));
  client.print(",");
  client.print(ps2x.Analog(PSS_LX));
  client.print(",");
  client.print(ps2x.Analog(PSS_RY));
  client.print(",");
  client.print(ps2x.Analog(PSS_RX));
  client.print(",");
  client.println(ps2x.Button(PSB_L2));
  client.flush();          // client will trigger the communication after two seconds
}