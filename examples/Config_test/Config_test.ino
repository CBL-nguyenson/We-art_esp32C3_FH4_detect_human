#include <Arduino.h>

#define Fan_BT_Start_Stop 0
#define Fan_BT_1 10
#define Fan_BT_2 7
#define Fan_BT_3 6

#define test_gpio_1 5
#define test_gpio_2 4
#define test_gpio_3 3


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Fan_BT_1, INPUT_PULLUP);
  pinMode(Fan_BT_2, INPUT_PULLUP);
  pinMode(Fan_BT_3, INPUT_PULLUP);
  pinMode(Fan_BT_Start_Stop, INPUT_PULLUP);


  pinMode(test_gpio_1, OUTPUT);
  pinMode(test_gpio_2, OUTPUT);
  pinMode(test_gpio_3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(Fan_BT_Start_Stop));
  Serial.print("||");
  Serial.print(digitalRead(Fan_BT_1));
  Serial.print("||");
  Serial.print(digitalRead(Fan_BT_2));
  Serial.print("||");
  Serial.println(digitalRead(Fan_BT_3));

  digitalWrite(test_gpio_1, digitalRead(Fan_BT_1));
  digitalWrite(test_gpio_2, digitalRead(Fan_BT_2));
  digitalWrite(test_gpio_3, digitalRead(Fan_BT_3));
}