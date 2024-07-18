// Thêm bộ thư viện LCD.
// Add the LCD library.
#include <MKL_LiquidCrystal_I2C.h>
// Khởi tạo LCD
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <MKL_HCSR04.h>
// Chọn chân đọc cảm biến.
// Select the pin to read the sensor.
#define ECHO_PIN 12
#define TRIG_PIN 13
// Cấu hình chân kết nối tín hiệu cho cảm biến siêu âm.
// Configure the signal connection pins for the ultrasonic sensor.
MKL_HCSR04 ultra(TRIG_PIN, ECHO_PIN);

unsigned long now = 0;
void setup()
{
  // Setup LCD
  lcd.init();
  lcd.backlight();
}

void loop()
{
  //Xóa màn hình LCD mỗi 200ms
  if(millis() - now > 300){
    lcd.clear();
    now = millis();
  }
  //Gửi giá trị khoảng cách lên LCD
  lcd.setCursor(4,0);
  lcd.print("Distance");
  lcd.setCursor(4,1);
  lcd.print(ultra.dist());
  lcd.setCursor(10,1);
  lcd.print("cm");
  // Chờ 60ms mỗi lần đọc để tránh nhiễu tín hiệu.
  // Wait 60ms per read to avoid signal interference.
  delay(60);
}