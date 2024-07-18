// Chọn chân Analog đọc Biến trở.
// Select the Analog pin to read the Potentiometer.
#define POTEN_PIN A2

// Số lần lấy mẫu.
// Number of sampling times.
#define SAMPLES 25

// Lưu giá trị Analog đọc từ Biến trở.
// Stores the Analog value read from the Potentiometer.
int valuePot;

// Lưu giá trị Analog lớn nhất đọc được từ Biến trở.
// Store the maximum Analog value read from the Potentiometer.
int maxPot = 691;

// Lưu giá trị (%) đổi từ giá trị Analog tương ứng.
// Store the value (%) converted from the corresponding Analog value.
int percentPot;

// Chọn chân Digital điều khiển LED.
// Select the Digital pin to control LED.
#define LED_PIN 11

// Lưu giá trị (~PWM) điều khiển LED.
// Save value (~PWM) control LED.
int lightLED;

void setup()
{
  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
}

void loop()
{
  /**
   * Các bước tính giá trị trung bình của cảm biến
   * 1. Xóa giá trị trong biến về 0
   * 2. Cộng tổng các mẫu đo lại
   * 3. Chia số mẫu để lấy giá trị trung bình
   */
  valuePot = 0;
  for (int i = 0; i < SAMPLES; i++)
  {
    valuePot += analogRead(POTEN_PIN);

    // Chờ 0,001s mới đo lại.
    // Wait 0,001s to measure again.
    delay(1);
  }
  valuePot = valuePot / SAMPLES;

  // Lưu nếu giá trị lớn nhất hiện tại được phát hiện.
  // Save if the current maximum value is detected.
  if (maxPot < valuePot)
  {
    maxPot = valuePot;
  }

  // Chuyển đổi sang thang đo (%).
  // Convert to scale (%).
  percentPot = map(valuePot, 0, maxPot, 0, 100);

  // Chuyển đổi sang thang đo (~PWM).
  // Conver to scale (~PWM).
  lightLED = map(percentPot, 0, 100, 0, 255);

  // Điều khiển độ sáng LED theo Biến trở.
  // Control LED brightness according to the Potentiometer.
  analogWrite(LED_PIN, lightLED);

  // Truyền giá trị đo được của cảm biến lên máy tính.
  // Transmit the measured value of the sensor to the computer.
  Serial.print("Giá trị thực: ");
  Serial.print(valuePot);
  Serial.print("       ");
  Serial.print("Giá trị thang đo %: ");
  Serial.print(percentPot);
  Serial.println("%");

  // Chờ 0,025s.
  // Wait 0,025s.
  delay(25);
}