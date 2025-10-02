// === ESP32 Serveur ===

#include <WiFi.h>
#include <esp_now.h>

// === Liste des IDs autorisés ===
const uint16_t validIDs[] = {1, 3, 5}; // À adapter
const int relayPin = 5; // GPIO pour relais

void onReceive(const uint8_t *mac, const uint8_t *data, int len) {
  if (len != sizeof(uint16_t)) return;

  uint16_t receivedID;
  memcpy(&receivedID, data, sizeof(receivedID));
  Serial.print("ID reçu : ");
  Serial.println(receivedID);

  for (int i = 0; i < sizeof(validIDs) / sizeof(validIDs[0]); i++) {
    if (receivedID == validIDs[i]) {
      Serial.println("Accès autorisé !");
      digitalWrite(relayPin, HIGH);
      delay(3000); // Ouverture 3s
      digitalWrite(relayPin, LOW);
      return;
    }
  }

  Serial.println("Accès refusé !");
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}
