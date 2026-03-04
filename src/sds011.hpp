/**
 * SDS011 Nova Fitness PM2.5 / PM10 dust sensor driver
 * Protocol: UART 9600 8N1, active reporting mode
 * Data frame: 10 bytes  AA C0 PM25L PM25H PM10L PM10H ID1 ID2 CRC AB
 *
 * Uses HardwareSerial (UART1) on SDS011_RX_PIN / SDS011_TX_PIN
 */

HardwareSerial sdsSerial(1); // UART1

#define SDS011_TIMEOUT_MS 10000 // 10 seconds without data → show "--"

class SDS011Sensor {
public:
  void init();
  void read();
  float getPM25() { return _pm25; }
  float getPM10() { return _pm10; }
  bool isDetected() { return _detected; }

private:
  float _pm25 = -1.0;
  float _pm10 = -1.0;
  bool _detected = false;
  uint8_t _buf[10];
  uint8_t _bufIdx = 0;
  uint32_t _lastDataMs = 0; // timestamp of last valid frame
};

/**
 * Initialize SDS011 sensor on Serial1 (UART1)
 */
void SDS011Sensor::init() {
  sdsSerial.begin(9600, SERIAL_8N1, SDS011_RX_PIN, SDS011_TX_PIN);
  Serial.println("SDS011:    Initialized on UART1");
  // Flush any stale data
  while (sdsSerial.available())
    sdsSerial.read();
  _lastDataMs = millis();
}

/**
 * Try to read a complete 10-byte frame from SDS011.
 * Call this frequently (e.g. every sensor read cycle).
 * The sensor sends a frame roughly once per second in active mode.
 * If no valid data received for SDS011_TIMEOUT_MS, values reset to -1 ("--").
 */
void SDS011Sensor::read() {
  bool gotFrame = false;

  while (sdsSerial.available()) {
    uint8_t b = sdsSerial.read();

    if (_bufIdx == 0 && b != 0xAA)
      continue; // wait for start byte
    _buf[_bufIdx++] = b;

    if (_bufIdx == 10) {
      _bufIdx = 0;

      // Validate: byte 0 = 0xAA, byte 1 = 0xC0, byte 9 = 0xAB
      if (_buf[0] != 0xAA || _buf[1] != 0xC0 || _buf[9] != 0xAB)
        continue;

      // Checksum: sum of bytes 2..7 & 0xFF == byte 8
      uint8_t chk = 0;
      for (uint8_t i = 2; i <= 7; i++)
        chk += _buf[i];
      if (chk != _buf[8])
        continue;

      // Parse PM values (unit: µg/m³, factor 10)
      _pm25 = ((_buf[3] << 8) | _buf[2]) / 10.0f;
      _pm10 = ((_buf[5] << 8) | _buf[4]) / 10.0f;
      _detected = true;
      _lastDataMs = millis();
      gotFrame = true;

      // Update global values
      global.sds011_pm25 = _pm25;
      global.sds011_pm10 = _pm10;
    }
  }

  // Timeout: if no valid data for SDS011_TIMEOUT_MS, reset to "no data"
  if (!gotFrame && (millis() - _lastDataMs > SDS011_TIMEOUT_MS)) {
    _pm25 = -1.0;
    _pm10 = -1.0;
    _detected = false;
    global.sds011_pm25 = -1.0;
    global.sds011_pm10 = -1.0;
  }
}
