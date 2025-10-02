// === ESP32 Scanner ===

#include <WiFi.h>
#include <esp_now.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

// === Capteur R307 sur RX2/TX2 ===
HardwareSerial mySerial(2); // RX2 = GPIO16, TX2 = GPIO17
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// === Adresse MAC de l'ESP Serveur ===
uint8_t serverAddress[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC}; // À adapter

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Capteur R307 détecté !");
  } else {
    Serial.println("Erreur capteur !");
    while (true);
  }

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, serverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erreur ajout du pair");
    return;
  }
}

void loop() {
  if (finger.getImage() == FINGERPRINT_OK) {
    if (finger.image2Tz() == FINGERPRINT_OK) {
      if (finger.fingerSearch() == FINGERPRINT_OK) {
        Serial.print("ID reconnu : ");
        Serial.println(finger.fingerID);
        uint16_t id = finger.fingerID;
        esp_now_send(serverAddress, (uint8_t *)&id, sizeof(id));
        delay(3000); // Anti-repétition
      } else {
        Serial.println("Empreinte non reconnue");
      }
    }
  }
  delay(500);
}
