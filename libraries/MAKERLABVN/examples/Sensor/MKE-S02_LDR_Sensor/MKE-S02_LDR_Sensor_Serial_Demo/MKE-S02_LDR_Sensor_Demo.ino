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
  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
}

void loop()
{
  // Đọc giá trị Analog.
  // Read Analog value.
  value = analogRead(LDR_PIN);

  // Chuyển đổi sang thang đo (%).
  // Convert to scale (%).
  percent = map(value, LDR_MIN_VALUE, LDR_MAX_VALUE, 100, 0);

  // Truyền giá trị đo được của cảm biến lên máy tính.
  // Transmit the measured value of the sensor to the computer.
  Serial.print("Giá trị thực: ");
  Serial.print(value);
  Serial.print("      ");
  Serial.print("Thang đo %: ");
  Serial.println(percent);

  // Chờ 0,5s mới đo lại.
  // Wait 0,5s to measure again.
  delay(500);
}