#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_SSD1306.h> // Подключение библиотеки для OLED дисплея

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Инициализация объектов датчика BMP280 и OLED дисплея
Adafruit_BMP280 bmp;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Используем I2C интерфейс

// Подключение MQ-2 к аналоговому пину A0
const int MQ2_PIN = A0;

void setup() {
  Serial.begin(9600);

  // Инициализация OLED дисплея
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.setTextSize(1); // Устанавливаем размер букв в один раз больше
  display.setTextColor(SSD1306_YELLOW);
  display.display(); // Отображаем приветствие на дисплее
  delay(2000);
  display.clearDisplay();
   // Устанавливаем уровень яркости (0-255)
  
  // Подключение датчика BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  Serial.println(F("BMP280 test"));
}

void loop() {
  // Чтение данных с датчика BMP280
  float temperature = bmp.readTemperature();
  float pressure_pa = bmp.readPressure(); // Давление в паскалях
  float pressure_mmHg = pressure_pa * 0.00750062; // Преобразование к мм рт. ст.

  // Чтение данных с датчика MQ-2
  int mq2Value = analogRead(MQ2_PIN);

  // Очистка и вывод данных на OLED дисплей
  display.clearDisplay();
  display.setTextSize(1); // Устанавливаем размер букв в один раз больше
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(temperature, 1);
  display.print(" C");

  display.setCursor(0, 16);
  display.print("Pressure: ");
  display.print(pressure_mmHg, 2);
  display.print(" mmHg");

  display.setCursor(0, 32);
  display.print("MQ-2 Value: ");
  display.print(mq2Value);

  display.display();

  // Вывод данных в Serial Monitor
  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_mmHg);
  Serial.println(" mmHg");

  Serial.print("MQ-2 Value = ");
  Serial.println(mq2Value);

  delay(1000);
}
