#include <Wire.h>
#include <MKR680.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  BME680.begin();
}

void loop() {
  delay(500);
  if (BME680.available()) {
    BME680_data data = BME680.read();
    Serial.print("Timestamp         : ");
    Serial.print((float) data.timestamp / 1000.0);
    Serial.println(" sec");

    Serial.print("Temperature (RAW) : ");
    Serial.print(data.temperature);
    Serial.print("°C (");
    Serial.print(data.rawTemperature);
    Serial.println("°C)");

    Serial.print("Pressure          : ");
    Serial.print(data.pressure);
    Serial.println(" hPa");

    Serial.print("Humidity (RAW)    : ");
    Serial.print(data.humidity);
    Serial.print("% (");
    Serial.print(data.rawHumidity);
    Serial.println("%)");

    Serial.print("Gas resistance    : ");
    Serial.print(data.gasResistance);
    Serial.println(" Ohm");

    Serial.print("IAQ (accuracy)    : ");
    Serial.print(data.iaqEstimate);
    Serial.print(" (");
    Serial.print(data.iaqAccuracy);
    Serial.println(")");

    Serial.println();
  }
}