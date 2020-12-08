// https://www.arduino.cc/reference/en/libraries/pubsubclient/
// https://arduinojson.org/v6/assistant/ to compute the static json size.

#include "dcmotor.h"
#include "servo.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HCSR04.h>

#define MOTOR_EN_A  4
#define MOTOR_EN_B  0
#define MOTOR_DIR_IN1  16
#define MOTOR_DIR_IN2  5
#define MOTOR_DIR_IN3  13
#define MOTOR_DIR_IN4  15
#define SERVO_HEAD 2
#define ULTRASOUND_TRIG 14
#define ULTRASOUND_ECHO 12

#define MSG_BUFFER_SIZE  (50)

L298N::DcMotors dcmotors(MOTOR_EN_A, MOTOR_EN_B, MOTOR_DIR_IN1, MOTOR_DIR_IN2, MOTOR_DIR_IN3, MOTOR_DIR_IN4);
TowerPro::Servo servo_head(SERVO_HEAD, 50);
HCSR04 hc(ULTRASOUND_TRIG, ULTRASOUND_ECHO);//initialisation class HCSR04 (trig pin , echo pin)

StaticJsonDocument<200> json;

const char* ssid = "YourSSID";
const char* password = "YourSSIDPassword";
const char* mqtt_server = "YourIpAddr";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

char payload_buffer[64];
void callback(char* topic, byte* payload, unsigned int length) {
  String topic_str(topic);

  // Form a C-string from the payload
  memcpy(payload_buffer, payload, length);
  payload_buffer[length] = '\0';
  
  String payload_str(payload_buffer);
  payload[length] = '\0';
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.print(payload_str);
  Serial.println();  

  if (topic_str.equals("diff_speed")) {
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(json, (char *)payload);
  
    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
  
    int linear = json["linear"];
    int angular = json["angular"];
    dcmotors.set_diff_drive_speed(linear, angular);
    Serial.print("linear: ");
    Serial.println(linear);
    Serial.print("angular: ");
    Serial.println(angular);
  }

  if (topic_str.equals("head_dir")) {
    int value = payload_str.toInt();
    servo_head.go_to_pos(value);
  }  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("connection", "connected");
      // ... and resubscribe
      client.subscribe("diff_speed");
      client.subscribe("head_dir");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(SERVO_HEAD, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
}

unsigned long last_loop_time = 0;
unsigned long current_time = 0;
char ultrasound_buff[10];
void loop() {
  dcmotors.loop();
  servo_head.loop();

  current_time = millis();
  if (current_time - last_loop_time > 100) {
    dtostrf(hc.dist(), 10, 2, ultrasound_buff);
    Serial.println(ultrasound_buff);
    client.publish("ultrasound", ultrasound_buff);
    last_loop_time = current_time;
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
