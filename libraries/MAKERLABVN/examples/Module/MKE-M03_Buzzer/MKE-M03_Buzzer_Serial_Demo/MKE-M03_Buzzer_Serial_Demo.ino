// Chọn chân Digital điều khiển Còi.
// Select the Digital pin to control Buzzer.
#define BUZZER_PIN 10

void setup() {
  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
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
  Serial.println("Buzzer On");
  delay(500);

  // Tắt Còi trong 0,5s.
  // Turn off Buzzer for 0,5 seconds.
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("Buzzer Off");
  delay(500);
}