#include <Arduino.h>

#define RX_PIN 3 // Chọn số chân GPIO cho UART RX
#define TX_PIN 1 // Chọn số chân GPIO cho UART TX
#define BAUD_RATE 115200 // Tốc độ baud của UART

void setup() {
  Serial.begin(BAUD_RATE); // Khởi tạo Serial với tốc độ baud được chọn
  Serial1.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN); // Khởi tạo UART thứ hai với các cài đặt: baud rate, 8-bit data, no parity, 1 stop bit
}

void loop() {
  while (Serial1.available()) { // Loop để đọc toàn bộ dữ liệu có sẵn trong buffer của UART thứ hai
    char receivedChar = Serial1.read(); // Đọc ký tự được gửi đến
    Serial.print(receivedChar); // In ký tự nhận được ra Serial Monitor
  }

  if (Serial.available()) { // Kiểm tra xem có dữ liệu nào được gửi từ Serial Monitor không
    char sendChar = Serial.read(); // Đọc ký tự được gửi từ Serial Monitor
    Serial1.print(sendChar); // Gửi ký tự đó đi qua UART thứ hai
  }
}
