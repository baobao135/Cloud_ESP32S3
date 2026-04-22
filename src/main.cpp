#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>

// 1. Điền thông tin WiFi của bạn
const char* ssid = "quocbao";
const char* password = "tamsomot";

// 2. Điền URL từ Azure Blob (nhớ đổi tên file thành firmware.bin)
const char* firmware_url = "https://esp32s3.blob.core.windows.net/human-dectec-firmware/firmware.bin";

// Hàm thực hiện cập nhật OTA
void performOTAUpdate() {
  Serial.println("Bắt đầu tiến trình cập nhật OTA...");
  
  WiFiClientSecure client;
  // Bỏ qua kiểm tra chứng chỉ SSL (chỉ dùng cho mục đích test để tránh phức tạp)
  client.setInsecure(); 

  // Gọi hàm update từ đường link
  t_httpUpdate_return ret = httpUpdate.update(client, firmware_url);

  // Xử lý kết quả trả về
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("Cập nhật thất bại. Lỗi (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("Không có bản cập nhật mới.");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("Cập nhật thành công! ESP32-S3 sẽ tự khởi động lại.");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối WiFi!");

  Serial.println("Đang chạy Firmware Version 2.0 ");

  delay(5000); 
  performOTAUpdate();
}

void loop() {
  // Code chạy model Edge Impulse của bạn sẽ nằm ở đây
}