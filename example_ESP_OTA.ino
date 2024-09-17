#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "WiFi_ismi";      // WiFi ismini kiriting
const char* password = "WiFi_paroli"; // WiFi parolini kiriting
const char* ota_password = "OTA_parol"; // OTA uchun parol kiriting

void setup() {
  Serial.begin(115200);

  // WiFi ga ulanish
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi ga ulanishga urinyapti...");
  }
  Serial.println("WiFi ulanish muvaffaqiyatli!");

  // OTA ni sozlash
  ArduinoOTA.setPassword(ota_password); // OTA parolini sozlash

  ArduinoOTA.onStart([]() {
    Serial.println("OTA yangilanishi boshlandi");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("OTA yangilanishi tugadi!");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Yangilanish: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Xato [%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Tasdiqlash xatosi");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Boshlash xatosi");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Ulanish xatosi");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Ma'lumot olish xatosi");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Tamomlash xatosi");
    }
  });

  ArduinoOTA.begin(); // OTA ni ishga tushirish
}

void loop() {
  ArduinoOTA.handle(); // OTA ishlashini kuzatib boradi
  Serial.println("eski kod");
  //Serial println("yangi kod");
}
