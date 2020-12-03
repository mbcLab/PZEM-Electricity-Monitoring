#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <PZEM004Tv30.h>

#define FIREBASE_HOST "smart-mosque-32bd7.firebaseio.com"
#define FIREBASE_AUTH "dArXCI74b8wFlAsZagm9h06TOAp9zrdBzu8Tl5NG"
#define WIFI_SSID "Smart Mosque"
#define WIFI_PASSWORD "13245768"
#define HardwareSerial Serial(2); //RX2 TX2

PZEM004Tv30 pzem(&Serial2);

void init() {
  //Menghubungkan ke WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Inisialisasi ke Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void setup() {
  Serial.begin(115200);
  init();
}

void loop() {  
    float voltage = pzem.voltage();
    if( !isnan(voltage) ) {
        Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
        Firebase.setString("Listrik/Appliances/tegangan", String(voltage));
    } else {
        Serial.println("Error reading voltage");
    }

    float current = pzem.current();
    if( !isnan(current) ){
        Serial.print("Current: "); Serial.print(current); Serial.println("A");
        Firebase.setString("Listrik/Appliances/arus", String(current));
    } else {
        Serial.println("Error reading current");
    }

    float power = pzem.power();
    if( !isnan(power) ){
        Serial.print("Power: "); Serial.print(power); Serial.println("W");
        Firebase.setString("Listrik/Appliances/daya", String(power));
    } else {
        Serial.println("Error reading power");
    }

    float energy = pzem.energy();
    float energyJoule = energy*pow(10,3)*3600; // p=(W/t)
    if( !isnan(energy) ){
        Serial.print("Energy: "); Serial.print(energyjoule/1000,3); Serial.println("kJoule");
        Firebase.setString("Listrik/Appliances/energi", String(energyJoule/1000));  //dibagi 1000 untuk konversi menjadi kJoule
    } else {
        Serial.println("Error reading energy");
    }

//In case you need it you can uncomment it
//    float frequency = pzem.frequency();
//    if( !isnan(frequency) ){
//        Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
//        Firebase.setFloat("Listrik/Appliances/Frequency", frequency);
//    } else {
//        Serial.println("Error reading frequency");
//    }
//
//    float pf = pzem.pf();
//    if( !isnan(pf) ){
//        Serial.print("PF: "); Serial.println(pf);
//        Firebase.setFloat("Listrik/Appliances/PowerFactor", pf);
//    } else {
//        Serial.println("Error reading power factor");
//    }

  delay(1000);
}
