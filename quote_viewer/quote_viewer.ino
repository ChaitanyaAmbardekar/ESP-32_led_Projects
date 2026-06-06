#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Energy 0.2";
const char* password = "wififiber";

WebServer server(80);

String quotes[] = {
  "Prioritize health first.",
  "Time is your most valuable asset.",
  "Save a little every month.",
  "Surround yourself with doers.",
  "Give more than you take.",
  "Speak less, listen more.",
  "Take responsibility, not excuses.",
  "Break big goals into steps.",
  "Invest in skills, not just degrees.",
  "Unlearn to relearn better.",
  "Learn from criticism, not blame.",
  "Focus long-term, act short-term.",
  "Be patient with progress.",
  "Work quietly, let results speak.",
  "Maintain curiosity as practice.",
  "Rest is part of work.",
  "Create systems, not just goals.",
  "Replace perfectionism with iteration.",
  "Be kind; it costs nothing.",
  "Write down your priorities.",
  "Track progress, not outcomes.",
  "Start your day with a win.",
  "Say 'I can learn' instead of 'I cant'.",
  "Remove one bad habit this month.",
  "Mentor someone when you can.",
  "Practice gratitude daily.",
  "Limit comparison; focus on self-growth.",
  "Use setbacks as course correction.",
  "Be adaptable, stay resilient.",
  "Make decisions with clarity, not fear.",
  "Keep moving forward, even slowly."
};

int numQuotes = sizeof(quotes) / sizeof(quotes[0]);

void handleRoot() {

  int n = random(0, numQuotes);

  String page =
    "<html>"
    "<head>"
    "<title>Quote Viewer</title>"
    "<style>"
    "body{font-family:Arial;text-align:center;padding-top:50px;background:#f0f0f0;}"
    "h2{color:#333;}"
    "pre{font-size:24px;background:white;padding:20px;border-radius:10px;display:inline-block;max-width:80%;}"
    "</style>"
    "</head>"
    "<body>"
    "<h2>Quote Viewer</h2>"
    "<pre>" + quotes[n] + "</pre>"
    "<br><br>"
    "<button onclick='location.reload()'>New Quote</button>"
    "</body>"
    "</html>";

  server.send(200, "text/html", page);
}

void setup() {

  Serial.begin(115200);

  randomSeed(micros());

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();

  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}