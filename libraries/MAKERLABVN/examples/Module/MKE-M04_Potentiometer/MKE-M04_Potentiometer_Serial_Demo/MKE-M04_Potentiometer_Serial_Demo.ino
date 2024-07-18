// Chọn chân Analog đọc Biến trở.
// Select the Analog pin to read the Potentiometer.
#define POTEN_PIN A2

// Lưu giá trị Analog đọc từ Biến trở.
// Stores the Analog value read from the Potentiometer.
int valuePot;

void setup()
{
  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
}

void loop()
{
  valuePot = analogRead(POTEN_PIN);

  // Truyền giá trị đo được của cảm biến lên máy tính.
  // Transmit the measured value of the sensor to the computer.
  Serial.print("Potentiometer value: ");
  Serial.println(valuePot);

  // Chờ 0,025s.
  // Wait 0,025s.
  delay(25);
}