// Arduino Zero + DHT11 example sketch
//
// Wiring (typical DHT11 module):
// - DHT11 VCC -> 3.3V (Arduino Zero)
// - DHT11 GND -> GND
// - DHT11 DATA -> D2 (change DHT_PIN below if needed)
//
// If you use a bare DHT11 sensor (not a module), add a 10K pull-up
// resistor between DATA and VCC.

#include <DHT.h>

constexpr uint8_t DHT_PIN = 2;
constexpr uint8_t DHT_TYPE = DHT11;
constexpr unsigned long READ_INTERVAL_MS = 2000;

DHT dht(DHT_PIN, DHT_TYPE);
unsigned long lastReadMs = 0;

void printSensorValues(float temperatureC, float humidity) {
  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  const float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print("Temperature (F): ");
  Serial.println(temperatureF, 1);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial monitor on native USB boards like Arduino Zero.
  }

  Serial.println("Starting DHT11 sensor read on Arduino Zero...");
  dht.begin();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastReadMs < READ_INTERVAL_MS) {
    return;
  }
  lastReadMs = now;

  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from DHT11 sensor. Check wiring and try again.");
    return;
  }

  printSensorValues(temperatureC, humidity);
}
