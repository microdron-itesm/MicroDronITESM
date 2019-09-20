#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define BUILTIN_LED2 13

const char *ssid = "microDrone3";
const char *password = "pass1234";

bool sent = true;
int i = 0;

char inByte;
String message = "\0";

WiFiServer telnetServer(23);
WiFiClient serverClient;

enum INIT_STATES {
  WAIT_FOR_CLIENT,
  NORMAL_OP
};
INIT_STATES initState = WAIT_FOR_CLIENT;
bool initDone = false;

void setup()
{
delay(1000);
Serial.begin(115200);
WiFi.softAP(ssid, password);
telnetServer.begin();
telnetServer.setNoDelay(true);
}

void clearSerial() {
  while(Serial.available())
    Serial.read();
}

void initFSM(){
  switch (initState) {
    case WAIT_FOR_CLIENT:
        if (telnetServer.hasClient()) {
          serverClient = telnetServer.available();
          serverClient.flush(); 
          initState = NORMAL_OP;
        }
        // Ignore every data sent by the microDrone controller
        clearSerial();
        break;
    case NORMAL_OP:
      initDone = true;
      break; 
    default:
      break;
  }
}

void loop()
{
  if (!initDone){
    initFSM();
    return;
  }
  if (!serverClient.connected()) {
    serverClient.stop();
    Serial.println("Telnet Client Stop");
    initDone = false;
    initState = WAIT_FOR_CLIENT;
  }
  
  if( Serial.available())
  {
    while(Serial.available())
    {
      inByte = Serial.read();
      message += inByte;
    }
    sent = false;
  }
  
  while(serverClient.available()) 
  {
    Serial.write(serverClient.read());
  }

  if (sent == false)
  {
    if (serverClient && serverClient.connected()) 
    {
        serverClient.println(message);        
        ESP.getFreeHeap();
        message = "\0";
        sent = true;
    }
  } 
  delay(10);
}
