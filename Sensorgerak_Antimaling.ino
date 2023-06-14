#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6e0uuoW0E"
#define BLYNK_TEMPLATE_NAME "Sensor Anti Maling"
#define BLYNK_AUTH_TOKEN "llRPoYQewrVZwdoAk7-ZNhwZiJngQIdl"
#define buzzer 22
#define sensor 21

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "INDIJETIS";
char pass[] = "kosatas123";
bool isOn = false;

String gerak = "Mendeteksi gerakan!";
String tdk_gerak = "Tidak ada pergerakan!";

BLYNK_WRITE(V1)
{ 
  int value1 = param.asInt();
  digitalWrite(sensor, value1);
  isOn = (value1 == 1);
}

void setup() {
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.begin(115200);
}

void loop() {
  Blynk.run();
  long kondisi = digitalRead(sensor);
  Blynk.virtualWrite(V0, tdk_gerak);
  if (isOn) {
    if (kondisi==HIGH) {
      Serial.println("Mendeteksi Gerakan!");
      Blynk.virtualWrite(V0, gerak);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    else {
      Serial.println("Tidak ada pergerakan!");
      delay(2000);
    }
  }
  
}