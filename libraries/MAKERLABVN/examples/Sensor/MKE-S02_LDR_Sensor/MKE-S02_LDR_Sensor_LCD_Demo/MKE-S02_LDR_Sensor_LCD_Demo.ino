//Thư viện I2C cho LCD
#include "MKL_LiquidCrystal_I2C.h"
//Khởi tạo LCD
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);
// Chọn chân Analog đọc cảm biến.
// Select the Analog pin to read the sensor.
#define LDR_PIN A1
//Giá trị max và min của cảm biến
#define LDR_MIN_VALUE 0
#define LDR_MAX_VALUE 691
// Lưu giá trị Analog đọc từ cảm biến.
// Stores the Analog value read from the sensor.
int value;

// Lưu giá trị (%) đổi từ giá trị Analog tương ứng.
// Store the value (%) converted from the corresponding Analog value.
int percent;

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  // Đọc giá trị Analog.
  // Read Analog value.
  value = analogRead(LDR_PIN);

  // Chuyển đổi sang thang đo (%).
  // Convert to scale (%).
  percent = map(value, LDR_MIN_VALUE, LDR_MAX_VALUE, 100, 0);

  //Gửi giá trị lên LCD
  lcd.setCursor(0, 0);
  lcd.print("Value: ");
  lcd.setCursor(7, 0);
  if (value / 10 == 0) {             // value la so co 1 chu so
    lcd.print(value);
    lcd.print("  ");
  } else if (value / 100 == 0) {     // value la so co 2 chu so
    lcd.print(value); 
    lcd.print(" ");
  } else {                              // value la so co 3 chu so
    lcd.print(value);
  }
  lcd.setCursor(12, 0);
  if (percent < 10) {
    lcd.print("  ");
  } else if (percent < 100) {
    lcd.print(" ");
  }
  lcd.print(percent);
  lcd.print("%");

  // Chờ 0,5s mới đo lại.
  // Wait 0,5s to measure again.
  delay(500);
}