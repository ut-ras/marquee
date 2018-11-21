/* ESP8266 WiFi Serial Tool
 * based on https://github.com/ut-ras/ESP8266_Arduino_Examples
 *
 *  Sets up the ESP8266 as a WiFi Access Point or connects to one
 *  Launches a Web Server with a form to output text over Serial
 *
 *  AP Mode: Launches the web server at http://192.168.4.1:80/
 *  STA Mode: Connects to an existing WiFi network
 *
 * Web Server
 * https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/examples/HelloServer
 * https://links2004.github.io/Arduino/d3/d58/class_e_s_p8266_web_server.html
 * https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/src/ESP8266WebServer.h
 * Examples > ESP8266WebServer
 *
 * Soft Access Point
 * https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "clock.h"


/* WiFi Mode
 * STA = connect to a WiFi network with name ssid
 * AP = create a WiFi access point with  name ssid
 */
#define WIFI_MODE "AP"
const char * ssid = "RAS_Signboard";
const char * pass = "esp";



//Web Server at port 80
int port = 80;
IPAddress ip;
String webServerPath = "http://";
ESP8266WebServer server(port);


//Marquee Default Message
String default_mssg = "Welcome to IEEE RAS!";


//Marquee Current Info
String current_mssg = default_mssg;
boolean clock_display = false;      //turn the clock on, only do this if connected to WiFi and time sync
int last_t = 0;         //for timing each minute to update display



/* Setup Functions */

/* setupWiFi
 * STA = connect to a WiFi network with name ssid
 * AP = create a WiFi access point with  name ssid
 */
void setupWiFi(String mode, const char * _ssid, const char * _pass) {
  if (mode.equals("AP")) {
    //Turn on Access Point
    WiFi.softAP(_ssid, _pass);
    ip = WiFi.softAPIP();
  }
  else {
    //Connect to a WiFi network
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      yield();
      //Serial.print(".");
    }
    ip = WiFi.localIP();
  }
}

void setupWebServer() {
  //Turn on a web server at port 80
  //Map paths to hander functions, can also specify HTTP methods
  server.on("/", handleRoot);
  server.on("/serial", HTTP_POST, handleSerial);
  server.on("/serial", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);    //404 Not Found
  server.begin();

  webServerPath += ip.toString() + ":" + String(port) + "/";
}

void setup() {
  Serial.begin(115200);

  setupWiFi(WIFI_MODE, ssid, pass);
  setupWebServer();
  
  //Serial.println("WiFi mode=" + String(WIFI_MODE) + ", ssid = " + String(ssid) + ", pass = " + String(pass));
  //Serial.println("Web server at " + webServerPath);

  //only set clock_display on if in station mode
  clock_display = String(WIFI_MODE).equals("STA");
  if (clock_display) {
    //Serial.println("Setting up time sync");
    setupTime();

    last_t = millis() - (1000 * getSecond() ) + 1000;    //so the minutes are updated 1 s after minute changes
  }

  //send default message
  serialMarquee(default_mssg);
}





/* Main Loop - Handle a client connection */
void loop() {
  
  //check the clock if its on
  checkClock();
  
  //handle web server
  server.handleClient();
  
}


//marquee serial output format
void serialMarquee(String mssg) {
  //Check clock
  if (clock_display && isTimeSync()) {
    mssg = getClock() + " " + mssg;
  }
  
  //Marquee must receive 25 characters for scrolling
  while(mssg.length() < 26) {
    mssg = mssg + " ";
  }
  mssg += "\n";
  Serial.print(mssg);
}

//check if clock needs to be updated and resend current message
void checkClock() {
  if ((clock_display) && (millis() - last_t >= 1000 * 60)) {
    last_t = millis();
    serialMarquee(current_mssg);    
    //String test_datetime = getClock() + " " + getDate(false, true);
    //Serial.println(test_datetime);
  }
}




/* Request Handlers */

//main page
void handleRoot() {
  server.send(200, "text/html", indexHTML());
}

//serial posts
void handleSerial() {
  //hasArg() checks if the last HTTP request in the server has an argument
  //arg() gets the value of the arg by name

  if(server.hasArg("serial_input")) {
    String serial_input = server.arg("serial_input");
    //Serial.println(serial_input);
    current_mssg = serial_input;
    serialMarquee(current_mssg);
  }
  handleRoot();
}




/* HTML */

//index and /serial
String indexHTML() {
  String htmlPage =
            String("<body>") +
              "<h1>RAS Marquee</h1>" +
              "<h2>ESP8266 Serial Tool</h2>" +
              "<form action=\"/serial\" method=\"post\">" +
                "<input type=\"text\" name=\"serial_input\" placeholder=\"Output to ESP8266 Serial\"><br>" +
                "<input type=\"submit\" value=\"Output Serial\"><br>" +
              "</form>" +
            "</body>";
  return htmlPage;
}

//404 Not Found
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
