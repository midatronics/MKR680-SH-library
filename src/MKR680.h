

#ifndef MKR680_H_INCLUDED
#define MKR680_H_INCLUDED

#include <Wire.h>

#define MKR680_DEFAULT_I2C_ADDR 0x10

typedef struct {
  int64_t timestamp;
  float temperature;
  float rawTemperature;
  float humidity;
  float rawHumidity;
  float gasResistance;
  float pressure;
  float iaqEstimate;
  uint8_t iaqAccuracy;
} __attribute__((packed, aligned(1))) BME680_data;

class BME680Class {
  public:
    void begin(TwoWire &w = Wire, int addr = MKR680_DEFAULT_I2C_ADDR) {
      wire = &w;
      address = addr;
      lastTimestamp = 0;
    }

    // try to get new data from the sensor. Returns true if new valid data
    // is available for read()
    bool available() {
      Wire.requestFrom(address, sizeof(BME680_data));
      uint8_t *p = (uint8_t *)&last;
      unsigned int i;
      for (i = 0; Wire.available(); i++) {
        if (i < sizeof(BME680_data)) {
          p[i] = Wire.read();
        }
      }
      if (i != sizeof(BME680_data)) {
        return false;
      }
      if (lastTimestamp == last.timestamp) {
        return false;
      }
      lastTimestamp = last.timestamp;
      return true;
    }

    // returns new data to read
    BME680_data read() {
      return last;
    }

  private:
    BME680_data last;
    int64_t lastTimestamp;
    TwoWire *wire;
    int address;
};

BME680Class BME680;

#endif