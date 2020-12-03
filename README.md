# Monitoring Konsumsi Daya dengan PZEM dan ESP32
### Sistem ini menggunakan mikrokontroler ESP32 __bukan ESP8266__
Semua library yang diperlukan sudah ada di repository ini, untuk firebase nya menggunakan email MBC, jadi silahkan menghubungi Asisten Lab MBC untuk mendapatkan aksesnya, atau edit di codingan arduino nya.
### Schematic rangkaian kontroler:
| esp32 | PZEM | Relay |
|-------|------|-------|
|3v3    |5v    |VCC    |
|GND    |GND   |GND    |
|D4     |NC    |NC     |
|RX2    |TX    |NC     |
|TX2    |RX    |NC     |
- [x] Monitoring komsumsi daya
- [x] Kirim data ke firebase
- [ ] Kontrol relay via firebase
