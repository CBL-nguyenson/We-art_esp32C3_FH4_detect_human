//Thư viện I2C cho LCD
#include "MKL_LiquidCrystal_I2C.h"
//Khởi tạo LCD
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Chọn chân Digital điều khiển LED.
// Select the Digital pin to control LED.
#define LED_PIN 11

void setup() {
  // setup LCD
  lcd.init();
  lcd.backlight();
  // Cấu hình đây là chân Digital Output.
  // Config this is Digital Output.
  pinMode(LED_PIN, OUTPUT);

  // Đảm bảo tắt LED khi mới khởi động.
  // Make sure to turn off the LED when starting.
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Bật LED trong 1s.
  // Turn on LED for 1 seconds.
  digitalWrite(LED_PIN, HIGH);
  //xóa màn hình
  lcd.clear();
  //Vị trí chữ cái đầu sẽ ở hàng 1 cột 6 của LCD
  lcd.setCursor(5, 0);
  //In chữ ra màn hình LCD
  lcd.print("Led On");
  delay(1000);

  // Tắt LED trong 1s.
  // Turn off LED for 1 seconds.
  digitalWrite(LED_PIN, LOW);
  //xóa màn hình
  lcd.clear();
  //Vị trí chữ cái đầu sẽ ở hàng 1 cột 6 của LCD
  lcd.setCursor(5, 0);
  //In chữ ra màn hình LCD
  lcd.print("Led Off");
  delay(1000);
}