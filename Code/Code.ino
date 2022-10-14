#include <Arduino.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST "traffic-control-30f4f-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "54jnWJgyJUyaYuiSLgAaPpsQtw97QClA8cVoU6gK"

char ssid[] = "SAHIL";
char pass[] = "SAHIL1745";

FirebaseData object;
String path = "/light/light";

void setup()
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.print("You're connected to the ");
  Serial.println(ssid);
  Serial.print("WiFi localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Firebase.getString(object, path))
  {
    if (object.stringData() == "Red")
    {
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      Serial.println("RED");
    }
    else if (object.stringData() == "Yellow")
    {
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      Serial.println("YELLOW");
    }
    else if (object.stringData() == "Green")
    {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      Serial.println("GREEN");
    }
  }
  else
  {
    Serial.println("Error");
  }
}
