/*********************************************************
* Voice Command Mini Robot (FINAL VERSION)
* ESP32 + TinyML Ready Code
*********************************************************/

#include <Arduino.h>

// ================= MOTOR DRIVER PINS =================
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12
#define ENA 25
#define ENB 33

// ================= SETTINGS =================
const float COMMAND_THRESHOLD = 0.80;
const unsigned long COMMAND_COOLDOWN = 1500;

unsigned long lastCommandTime = 0;

// ================= MOTOR FUNCTIONS =================
void stopRobot() {
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);

 analogWrite(ENA, 200);
 analogWrite(ENB, 200);

 Serial.println("ACTION: STOP");
}

void moveForward() {
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);

 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);

 analogWrite(ENA, 200);
 analogWrite(ENB, 200);

 Serial.println("ACTION: FORWARD");
}

void moveBack() {
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);

 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);

 analogWrite(ENA, 200);
 analogWrite(ENB, 200);

 Serial.println("ACTION: BACK");
}

void turnLeft() {
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);

 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);

 analogWrite(ENA, 200);
 analogWrite(ENB, 200);

 Serial.println("ACTION: LEFT");
}

void turnRight() {
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);

 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);

 analogWrite(ENA, 200);
 analogWrite(ENB, 200);

 Serial.println("ACTION: RIGHT");
}

// ================= EXECUTE COMMAND =================
void executeCommand(String cmd) {
 if (cmd == "forward") moveForward();
 else if (cmd == "back") moveBack();
 else if (cmd == "left") turnLeft();
 else if (cmd == "right") turnRight();
 else if (cmd == "stop") stopRobot();
}

// ================= TEMP (MANUAL TEST) =================
// ⚠️ পরে এটা ML function দিয়ে replace করবে
String getPredictedCommand(float &confidence) {

 if (Serial.available()) {
   String input = Serial.readStringUntil('\n');
   input.trim();

   if (input == "forward") {
     confidence = 0.95;
     return "forward";
   }
   else if (input == "back") {
     confidence = 0.94;
     return "back";
   }
   else if (input == "left") {
     confidence = 0.93;
     return "left";
   }
   else if (input == "right") {
     confidence = 0.92;
     return "right";
   }
   else if (input == "stop") {
     confidence = 0.99;
     return "stop";
   }
 }

 confidence = 0.0;
 return "none";
}

// ================= SETUP =================
void setup() {
 Serial.begin(115200);

 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);

 stopRobot();

 Serial.println("=================================");
 Serial.println("🤖 Voice Command Robot Ready!");
 Serial.println("Type:");
 Serial.println("forward / back / left / right / stop");
 Serial.println("=================================");
}

// ================= LOOP =================
void loop() {

 float confidence = 0.0;
 String command = getPredictedCommand(confidence);

 Serial.print("CMD: ");
 Serial.print(command);
 Serial.print(" | CONF: ");
 Serial.println(confidence);

 if (command != "none" &&
     confidence >= COMMAND_THRESHOLD &&
     millis() - lastCommandTime > COMMAND_COOLDOWN) {

   executeCommand(command);
   lastCommandTime = millis();
 }

 delay(100);
}
