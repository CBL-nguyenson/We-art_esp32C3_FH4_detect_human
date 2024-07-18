//Thư viện I2C cho LCD
#include "MKL_LiquidCrystal_I2C.h"
// Chọn chân Digital điều khiển Còi.
// Select the Digital pin to control Buzzer.
#define BUZZER_PIN 10
//Khởi tạo LCD
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // setup LCD
  lcd.init();
  lcd.backlight();
  // Cấu hình đây là chân Digital Output.
  // Config this is Digital Output.
  pinMode(BUZZER_PIN, OUTPUT);

  // Đảm bảo tắt Còi khi mới khởi động.
  // Make sure to turn off the Buzzer when starting.
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Bật Còi trong 0,5s.
  // Turn on Buzzer for 0,5 seconds.
  digitalWrite(BUZZER_PIN, HIGH);
  //xóa màn hình
  lcd.clear();
  //Vị trí chữ cái đầu sẽ ở hàng 1 cột 4 của LCD
  lcd.setCursor(3, 0);
  //In chữ ra màn hình LCD
  lcd.print("Buzzer On");
  delay(500);

  // Tắt Còi trong 0,5s.
  // Turn off Buzzer for 0,5 seconds.
  digitalWrite(BUZZER_PIN, LOW);
  //xóa màn hình
  lcd.clear();
  //Vị trí chữ cái đầu sẽ ở hàng 1 cột 4 của LCD
  lcd.setCursor(3, 0);
  //In chữ ra màn hình LCD
  lcd.print("Buzzer Off");
  delay(500);
}