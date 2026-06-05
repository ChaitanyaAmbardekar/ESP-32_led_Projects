#include <WiFi.h>
#include <WebServer.h>
const char* ssid="Energy 0.2";
const char* password="wififiber";
WebServer server(80);
#define FLASH_LED 4

void handleRoot() {
  unsigned long seconds=millis()/1000;
  long rssi=WiFi.RSSI();
  String page =
    "<html><body>"
    "<h1>ESP32 LED Control</h1>"
    "<h2>Uptime: "+String(seconds)+"sec</h2>"
    "<h2>Signal Streangth: "+String(rssi) +"dBm</h2>"
    "<a href='/on'><button>LED ON</button></a><br><br>"
    "<a href='/off'><button>LED OFF</button></a>"
    "<button onclick='startVoice()'>Voice Control</button>"

"<script>"

"function startVoice(){"

"var recognition = new webkitSpeechRecognition();"

"recognition.onstart = function(){"
"alert(\"Microphone started\");"
"};"

"recognition.onresult = function(event){"
"var command = event.results[0][0].transcript.toLowerCase();"
"alert(\"You said: \" + command);"
"};"

"recognition.onerror = function(event){"
"alert(\"Error type: \" + event.error);"
"};"

"recognition.start();"

"}"

"</script>"

"</body></html>";

  server.send(200, "text/html", page);
}
void ledOn(){
  digitalWrite(FLASH_LED,HIGH);
  server.sendHeader("Location","/");
  server.send(303);
}
void ledOff(){
  digitalWrite(FLASH_LED,LOW);
  server.sendHeader("Location","/");
  server.send(303);
}
void setup(){
  Serial.begin(115200);
  pinMode(FLASH_LED, OUTPUT);
  digitalWrite(FLASH_LED,LOW);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/",handleRoot);
    server.on("/on",ledOn);
    server.on("/off",ledOff);

    server.begin();

  }
  void loop(){
    server.handleClient();
  }
