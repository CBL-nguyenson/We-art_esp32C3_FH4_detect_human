// Chọn chân Digital điều khiển Còi.
// Select the Digital pin to control Buzzer.
#define BUZ_PIN 10

void setup()
{
  // Cấu hình đây là chân Digital Output.
  // Config this is Digital Output.
  pinMode(BUZ_PIN, OUTPUT);

  // Đảm bảo tắt Còi khi mới khởi động.
  // Make sure to turn off the Buzzer when starting.
  digitalWrite(BUZ_PIN, LOW);
}

void loop()
{
  // Bật Còi trong 0,5s.
  // Turn on Buzzer for 0,5 seconds.
  digitalWrite(BUZ_PIN, HIGH);
  delay(500);

  // Tắt Còi trong 0,5s.
  // Turn off Buzzer for 0,5 seconds.
  digitalWrite(BUZ_PIN, LOW);
  delay(500);
}