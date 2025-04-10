#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Galaxy M33";         // Replace with your WiFi SSID
const char* password = "omui1727";       // Replace with your WiFi password

// IR sensors
#define IR1 14  // D5
#define IR2 12  // D6
#define IR3 13  // D7

// LEDs
#define LED1 5   // D1
#define LED2 4   // D2
#define LED3 0   // D3

bool led1_manual = false;
bool led2_manual = false;
bool led3_manual = false;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: ");
  Serial.println(WiFi.localIP());

  // Root web page
  server.on("/", []() {
    String html = "<h2>3-Street Light IR + Web Control System</h2>";

    html += "<p>LED1: " + String(digitalRead(LED1) ? "ON" : "OFF") + "</p>";
    html += "<a href='/led1/on'><button>Turn ON LED1</button></a> ";
    html += "<a href='/led1/off'><button>Turn OFF LED1</button></a><br><br>";

    html += "<p>LED2: " + String(digitalRead(LED2) ? "ON" : "OFF") + "</p>";
    html += "<a href='/led2/on'><button>Turn ON LED2</button></a> ";
    html += "<a href='/led2/off'><button>Turn OFF LED2</button></a><br><br>";

    html += "<p>LED3: " + String(digitalRead(LED3) ? "ON" : "OFF") + "</p>";
    html += "<a href='/led3/on'><button>Turn ON LED3</button></a> ";
    html += "<a href='/led3/off'><button>Turn OFF LED3</button></a><br>";

    server.send(200, "text/html", html);
  });

  // LED1 controls
  server.on("/led1/on", []() {
    led1_manual = true;
    digitalWrite(LED1, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/led1/off", []() {
    led1_manual = false;
    digitalWrite(LED1, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  // LED2 controls
  server.on("/led2/on", []() {
    led2_manual = true;
    digitalWrite(LED2, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/led2/off", []() {
    led2_manual = false;
    digitalWrite(LED2, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  // LED3 controls
  server.on("/led3/on", []() {
    led3_manual = true;
    digitalWrite(LED3, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/led3/off", []() {
    led3_manual = false;
    digitalWrite(LED3, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();

  // IR1 automatic control (only if not manually ON)
  if (!led1_manual) {
    digitalWrite(LED1, digitalRead(IR1) == LOW ? HIGH : LOW);
  }

  // IR2 automatic control (only if not manually ON)
  if (!led2_manual) {
    digitalWrite(LED2, digitalRead(IR2) == LOW ? HIGH : LOW);
  }

  // IR3 automatic control (only if not manually ON)
  if (!led3_manual) {
    digitalWrite(LED3, digitalRead(IR3) == LOW ? HIGH : LOW);
  }
}