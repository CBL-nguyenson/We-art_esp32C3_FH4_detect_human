// Chọn chân Digital điều khiển LED.
// Select the Digital pin to control LED.
#define LED_PIN 11

void setup() {
  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
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
  Serial.println("Led On");
  delay(1000);

  // Tắt LED trong 1s.
  // Turn off LED for 1 seconds.
  digitalWrite(LED_PIN, LOW);
  Serial.println("Led Off");
  delay(1000);
}