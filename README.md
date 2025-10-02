# EspBiometricDoor

**Système d’accès biométrique basé sur ESP32 (R307 + ESP-NOW)**

---

## 🧠 Architecture

- **ESP32 Scanner (extérieur)** : lit l’empreinte digitale et transmet l’ID via ESP-NOW  
- **ESP32 Serveur (intérieur)** : stocke les empreintes, valide l’ID, et commande l’ouverture de la porte

---

## 🔒 Sécurité

- Aucune donnée biométrique stockée côté scanner  
- Validation centralisée derrière la porte  
- Communication ESP-NOW chiffrée (optionnelle)  
- Résistance aux attaques physiques sur le capteur

---

## 📦 Matériel requis

- 2 × ESP32-WROOM-32 Dev Kit  
- 1 × Capteur d’empreintes R307  
- 1 × Module relais ou servo moteur  
- Alimentation 5V  
- Câblage et boîtier

---

## 🛠️ Fonctionnalités

- Lecture d’empreinte avec le capteur R307  
- Transmission sécurisée via ESP-NOW  
- Validation locale des empreintes  
- Ouverture automatique de porte si l’ID est reconnu  
- Extensible : journalisation, écran OLED, badge RFID, etc.

---

## 📁 Structure du dépôt

- `/scanner/` : code pour l’ESP32 extérieur avec capteur R307  
- `/server/` : code pour l’ESP32 intérieur avec validation et relais  
- `/docs/` : schémas, câblage, instructions de montage  
- `/examples/` : enregistrement d’empreintes, test de communication

---

## ⚠️ Licence

Ce projet est protégé par le **droit d’auteur**.  
**Toute réutilisation, modification ou redistribution est strictement interdite sans autorisation explicite.**  
> © Ludovic Viguier – Tous droits réservés.

---

## ✉️ Contact

Pour toute demande ou collaboration : [via GitHub Issues](https://github.com/Ludovic-py/EspBiometricDoor/issues)

