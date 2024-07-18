// Thêm bộ thư viện LCD.
// Add the LCD library.
#include <MKL_LiquidCrystal_I2C.h>

// Khởi tạo "LiquidCrystal_I2C" cho màn hình LCD với cấu hình sau.
// Initialize "LiquidCrystal_I2C" for the monitor LCD with the following config.
MKL_LiquidCrystal_I2C lcd(
    0x27, // Cài đặt địa chỉ I2C là 0x27.
    16,   // With 16 columns.
    2     // With 2 rows.
);

// Lưu số đếm.
// Save the count.
int count = 0;

void setup()
{
  // Khởi động thư viện.
  // Start up the library.
  lcd.init();

  // Xóa màn hình, đảm bảo không còn nội dung cũ trước đó.
  // Clear the screen, making sure there is no old content left before.
  lcd.clear();

  // Bật đèn nền màn hình.
  // Turn on the screen backlight.
  lcd.backlight();

  // Tại vị trí cột 1 dòng 1, cho in nội dung...
  // At column 1, row 1, print the content...
  lcd.setCursor(0, 0);
  lcd.print("   LCD1602 I2C  ");

  // Tại vị trí cột 1 dòng 2, cho in nội dung...
  // At column 1, row 2, print the content...
  lcd.setCursor(0, 1);
  lcd.print("   MakerLab.vn  ");

  // Chờ 5s.
  // Wait 5s.
  delay(5000);

  // Xóa màn hình.
  // Clear the screen.
  lcd.clear();

  // Tại vị trí cột 1 dòng 1, cho in nội dung...
  // At column 1, row 1, print the content...
  lcd.setCursor(0, 0);
  lcd.print("Count:");
}

void loop()
{
  // Tăng số đếm lên 1 đơn vị.
  // Increase the count by 1 unit.
  count++;

  // Tại vị trí cột 8 dòng 1, cho in nội dung...
  // At column 8, row 1, print the content...
  lcd.setCursor(7, 0);
  lcd.print(count);

  // Đợi 1s để đếm tiếp.
  // Wait for 1s to count continue.
  delay(1000);
}