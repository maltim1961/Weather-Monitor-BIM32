# 🌦️ BIM32 — Weather Monitor based on ESP32

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=flat-square&logo=espressif" alt="ESP32"/>
  <img src="https://img.shields.io/badge/IDE-Arduino%201.8.19-teal?style=flat-square&logo=arduino" alt="Arduino"/>
  <img src="https://img.shields.io/badge/RTOS-FreeRTOS-green?style=flat-square" alt="FreeRTOS"/>
  <img src="https://img.shields.io/badge/License-Open%20Source-orange?style=flat-square" alt="License"/>
  <img src="https://img.shields.io/github/v/release/himikat123/Weather-monitor-BIM32?style=flat-square&label=Version" alt="Release"/>
  <img src="https://img.shields.io/github/stars/himikat123/Weather-monitor-BIM32?style=flat-square" alt="Stars"/>
</p>

<p align="center">
  <b>A feature-rich home weather monitor with color touchscreen display, wireless sensors, voice notifications, and a flexible web-based configuration interface.</b>
</p>

---

## 📖 Table of Contents

- [About the Project](#-about-the-project)
- [Key Features](#-key-features)
- [Supported Hardware](#-supported-hardware)
- [Wiring Diagrams](#-wiring-diagrams)
- [Software & Dependencies](#-software--dependencies)
- [Flashing the Device](#-flashing-the-device)
- [Uploading Files to LittleFS](#-uploading-files-to-littlefs)
- [Initial Setup](#-initial-setup)
- [Web Interface](#-web-interface)
- [Project Structure](#-project-structure)
- [External Service Integrations](#-external-service-integrations)
- [3D Printed Enclosure](#-3d-printed-enclosure)
- [FAQ](#-faq)
- [Acknowledgments](#-acknowledgments)
- [License](#-license)

---

## 🌍 About the Project

**BIM32** is an open-source home weather monitor project based on the ESP32 microcontroller. The device combines a home weather station, clock, alarm, air quality monitoring system, and home climate controller into a single versatile unit.

The project was created by **himikat123** (Nuremberg, Germany) and has been actively developed since 2020. As of now, the project has **26 releases**, with the latest being **v5.5** (January 2025).

> **Core idea:** Build an affordable yet highly functional device for monitoring outdoor weather and indoor climate, suitable for DIY assembly.

---

## ✨ Key Features

### 🌤️ Weather & Forecast
- Display **current weather** and **3-day forecast**
- **Hourly weather forecast** for up to 5 days
- **Weather history** (hourly) for the previous day
- **Chart building**: temperature, humidity, pressure, and precipitation probability
- Support for **3 weather providers**: OpenWeatherMap, Weatherbit.io, Open-Meteo

### 🏠 Indoor Climate Monitoring
- Display **temperature, humidity, CO₂**, and **Indoor Air Quality index (IAQ)**
- **Dust monitoring** (PM2.5 and PM10) via SDS011 sensor
- **Automatic climate control**: humidifier, dehumidifier, heater, cooler, and air purifier
- **Sound alerts** when climate parameters exceed comfort thresholds

### ⏰ Clock & Calendar
- Clock formats: small / large / with seconds / analog
- **NTP synchronization** with configurable update period
- **DS3231 RTC** support for autonomous timekeeping
- **Calendar** with infinite scrolling
- **12/24-hour format**, automatic daylight saving time (DST) adjustment

### 📡 Wireless Sensors
- Up to **2 wireless sensors** (via HC-12 radio module)
- Measured parameters: temperature, pressure, humidity, CO₂, ambient light, voltage, current, power, energy
- Support for **PZEM-004t** (power meter) and **SenseAir S8** (CO₂) through wireless sensors

### 🔊 Sound
- **Talking clock** — voice time announcements
- **Alarm clock** playing MP3 files (up to 12 alarms)
- **Hourly chime** (configurable by time or sunrise/sunset)
- **DF-Player Mini** module for audio playback

### 🖥️ Displays
- **ILI9341** touchscreen display (3.2 inch, 320×240)
- **Nextion** NX4832K035 (enhanced) / NX4832T035 (basic) (3.5 inch)
- **WS2812B** — 7-segment LED display for large and extra-large clocks
- Automatic brightness adjustment: by light sensor, by time of day, by sunrise/sunset

### 🌐 Networking
- Connect to home **WiFi 2.4 GHz** networks
- **Access Point** mode for initial configuration
- Support for **static IP** or **DHCP**
- **OTA** (Over-the-Air) firmware updates
- Device discovery via **SSDP**

### 🌍 Multilingual Support
- **6 languages**: English, German, Russian, Polish, Ukrainian, Bulgarian

---

## 🔧 Supported Hardware

### Microcontroller
| Component | Description |
|-----------|-------------|
| **ESP32 Dev Module** | Main device controller |

### Displays
| Display | Type | Size |
|---------|------|------|
| **ILI9341** | TFT LCD with touch (XPT2046) | 3.2" (320×240) |
| **Nextion NX4832K035** | Enhanced model | 3.5" |
| **Nextion NX4832T035** | Basic model | 3.5" |
| **WS2812B** | LED panel for 7-segment clock | — |

### Wired Sensors
| Sensor | Measured Parameters |
|--------|-------------------|
| **BME280** | Temperature, humidity, pressure |
| **BME680** | Temperature, humidity, pressure, Indoor Air Quality (IAQ) |
| **BMP180** | Temperature, pressure |
| **SHT21** | Temperature, humidity |
| **DHT22** | Temperature, humidity |
| **DS18B20** | Temperature |
| **MAX44009** | Ambient light |
| **BH1750** | Ambient light |
| **Photoresistor** | Ambient light (analog) |
| **SDS011** | Particulate matter PM2.5 & PM10 |

### Additional Modules
| Module | Purpose |
|--------|---------|
| **DS3231** | Real-Time Clock (RTC) |
| **HC-12** | Radio module for wireless sensor communication |
| **DF-Player Mini** | MP3 player for alarms and talking clock |
| **PCF8574** | I/O expander for climate control devices |
| **XPT2046** | Touchscreen controller (for ILI9341) |

---

## 📐 Wiring Diagrams

### Base Modules
To start the weather monitor, you only need to connect a **display** to the ESP32. All other modules are optional.

### Wired Sensors
You can connect any one, several, or all of the supported sensors simultaneously. Sensors use the **I²C bus** (BME280, BME680, BMP180, SHT21, MAX44009, BH1750, PCF8574, DS3231) and **one-wire bus** (DS18B20, DHT22).

### HC-12 Radio Module
To connect [wireless sensors](https://github.com/himikat123/Radio-sensor), add the HC-12 radio module.

### Sound Module
The **DF-Player Mini** module enables alarm and talking clock functionality. Copy the contents of the `SDcard` folder to a micro-SD card formatted as **FAT32**.

> ⚠️ **Important:** If you choose not to install buttons (display on/off and alarm off), the pull-up resistors for these buttons must still be installed.

> 💡 **Tip:** If the sound module is not used, connect GPIO18 of the ESP32 to ground.

> 🔧 **DF-Player noise fix:** The DF-Player Mini may produce constant low noise. To fix this, re-solder the resistor from position A to position B on the module board. This switches the amplifier's MUTE input to the BUSY output.

---

## 💻 Software & Dependencies

### Development Environment
- **Arduino IDE** v1.8.19
- **ESP32 Board** by Espressif Systems v2.0.14
- **Partition Scheme:** No OTA (2MB APP / 2MB SPIFFS)

### Required Libraries

| Library | Version | Purpose |
|---------|---------|---------|
| [ArduinoJson](https://arduinojson.org/) | v7.0.3 | JSON parsing (configuration, API responses) |
| [AsyncTCP](https://github.com/dvarrel/AsyncTCP) | v1.1.4 | Asynchronous TCP for the web server |
| [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) | v1.2.3 | Asynchronous web server |
| [TimeLib](https://playground.arduino.cc/Code/Time/) | v1.6.1 | Time management library |
| [ESP32SSDP](https://github.com/luc-github/ESP32SSDP) | v1.2.0 | SSDP device discovery |
| [Adafruit BME280](https://github.com/adafruit/Adafruit_BME280_Library) | v2.2.4 | BME280 sensor driver |
| [Adafruit BMP085](https://github.com/adafruit/Adafruit-BMP085-Library) | v1.2.4 | BMP180 sensor driver |
| [SHT21](https://github.com/markbeee/SHT21) | — | SHT21 sensor driver |
| [DHTesp](http://desire.giesecke.tk/index.php/2018/01/30/esp32-dht11/) | v1.19.0 | DHT22 sensor driver |
| [MAX44009](https://github.com/dantudose/MAX44009) | v1.2.3 | MAX44009 ambient light sensor driver |
| [BH1750](https://github.com/claws/BH1750) | v1.3.0 | BH1750 ambient light sensor driver |
| [OneWire](https://github.com/PaulStoffregen/OneWire) | v2.3.7 | 1-Wire protocol library |
| [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library) | v3.9.0 | DS18B20 temperature sensor driver |
| [BSEC](https://www.bosch-sensortec.com/software-tools/software/bsec/) | v1.8.1492 | BME680 environmental sensor library (IAQ) |
| [Adafruit PCF8574](https://github.com/adafruit/Adafruit_PCF8574) | v1.1.1 | PCF8574 I/O expander driver |
| [DS3232](https://github.com/RobTillaart/DS3232) | v0.4.1 | DS3231 RTC driver |

---

## 🔥 Flashing the Device

### Flashing the Nextion Display
1. Copy the display firmware file (`.tft` file with your display model name) from the `bin` folder to a micro-SD card (FAT32)
2. Insert the card into the display's micro-SD slot
3. Power the display — it will flash itself automatically from the card

### Flashing the ESP32
1. Download [flash_download_tools](https://www.google.ru/search?q=flash_download_tools)
2. Run the tool and select **ESP32 DownloadTool**
3. Select the firmware binaries from the `bin` folder and set the corresponding addresses
4. Select your COM port
5. Press **Start** in the flashing tool and simultaneously hold the **BOOT** button on the ESP32 module
6. Keep the button pressed until the flashing process begins

---

## 📂 Uploading Files to LittleFS

In addition to flashing the main firmware, you need to upload data files (web interface, configuration, images) to the **LittleFS** file system on the ESP32. Without this step, the web interface and display icons will not work.

### Prerequisites

1. **Download and install the `esp32littlefs.jar` plugin:**
   - Download the file directly: **[esp32littlefs.jar](https://github.com/lorol/arduino-esp32littlefs-plugin/raw/master/src/bin/esp32littlefs.jar)**
   - In your Arduino IDE (or Sketchbook) directory, create the path: `tools/ESP32LittleFS/tool/`
   - Copy the downloaded `esp32littlefs.jar` into that folder
   - The final path should look like:
     ```
     <Arduino IDE>/tools/ESP32LittleFS/tool/esp32littlefs.jar
     ```

2. **Download and install the `mklittlefs` tool:**
   - Download the appropriate version from the releases page: **[mklittlefs releases](https://github.com/earlephilhower/mklittlefs/releases)**
   - For Windows, download the file named `x86_64-w64-mingw32-mklittlefs-...zip`
   - Extract and copy `mklittlefs.exe` to the ESP32 platform `tools` folder, where `esptool.exe` and `espota.exe` are located
   - Typical path:
     ```
     <Arduino IDE>/hardware/espressif/esp32/tools/mklittlefs.exe
     ```
   > 💡 **Tip:** For a portable Arduino IDE installation, the path may be: `<Arduino>/portable/packages/esp32/tools/`

3. **Restart Arduino IDE** — the **ESP32 LittleFS Data Upload** option should appear under the **Tools** menu

4. **Ensure** that **Tools → Partition Scheme** is set to: **No OTA (2MB APP / 2MB SPIFFS)**

### `data/` Folder Structure

All files to be uploaded to LittleFS must be located in the `data/` folder inside the project:

```
data/
├── config.json          # Device configuration
├── defaultConfig.json   # Default configuration (for factory reset)
├── alarm.json           # Alarm settings
├── bme680.json          # BME680 sensor calibration data
├── icon48.png           # Device icon (for SSDP discovery)
├── index.html.gz        # Compressed web interface (gzip)
└── img/                 # Images for ILI9341 display
    ├── logo.jpg          # Boot logo
    ├── ant/              # Antenna/access point icons (6 files)
    ├── bat/              # Battery level icons (4 files)
    ├── digits/           # Clock digit images (10 files)
    ├── icons/
    │   ├── big/          # Large weather icons (12 files)
    │   └── small/        # Small weather icons (9 files)
    ├── symb/             # Symbols (home, humidity, pressure, temperature, wind)
    └── wind/             # Wind direction icons (8 files)
```

### Upload Procedure

1. **Open the project** `BIM32_Arduino40.ino` in Arduino IDE
2. **Close Serial Monitor** (if open) — it blocks the COM port
3. Go to **Tools → ESP32 LittleFS Data Upload**
4. Wait for the upload to complete (progress is shown in the console at the bottom of the IDE)
5. Upon success, the console will display `LittleFS Image Uploaded`

> ⚠️ **Important:** Uploading files **completely erases** the current LittleFS partition contents on the ESP32. If you have already configured the device, your settings (`config.json`) will be reset.

> 💡 **Tip:** Before uploading files to LittleFS, you can edit `data/config.json` to pre-fill your WiFi credentials, so you don't need to configure the device via the access point.

> 🔄 **Full flashing sequence:**
> 1. First, upload the **main firmware** (Sketch → Upload)
> 2. Then, upload the **data files to LittleFS** (Tools → ESP32 LittleFS Data Upload)

---

## ⚙️ Initial Setup

1. After flashing, the device creates a Wi-Fi access point:
   - **SSID:** `BIM32`
   - **Password:** `1234567890`
2. Connect to this network from your smartphone or laptop
3. Open a browser and navigate to: **[http://192.168.4.1](http://192.168.4.1)**
4. Enter login: `admin`, password: `1111`
5. Configure WiFi, weather provider, sensors, and displays

> 🔐 **Security note:** Change the default login and password after the initial setup!

Once connected to your home network, access the settings by entering the device's IP address in your browser. To find out the IP address, tap the antenna icon on the weather monitor screen.

---

## 🖥️ Web Interface

Device configuration is done through a rich web interface accessible from any browser.

🔗 **Web Interface Demo:** [https://himikat123.github.io/Web-Interface-BIM/](https://himikat123.github.io/Web-Interface-BIM/)

The web interface allows you to configure:
- **WiFi** network parameters (up to 3 networks)
- **Weather provider** and location settings
- **Displays** — type, brightness, animations, timeslots
- **Sensors** — reading corrections, data sources
- **Clock** — NTP server, timezone, format
- **Sound** — volume, equalizer, hourly chime
- **Alarms** — up to 12 alarms with melody and weekday selection
- **Integrations** — ThingSpeak, Narodmon
- **Comfort** — threshold values for temperature, humidity, CO₂, IAQ
- **Account** — web interface login and password

---

## 📁 Project Structure

```
BIM32_Arduino40/
├── BIM32_Arduino40.ino      # Main Arduino project file
├── taskdisplay.hpp          # FreeRTOS task for display management
├── tasksensors.hpp          # FreeRTOS task for sensor polling
├── web.ino                  # Web interface request handlers
├── src/
│   ├── globals.hpp          # Global variables, configuration, pin definitions
│   ├── sensors.hpp          # Wired sensor initialization & reading
│   ├── wirelessSensor.hpp   # Wireless sensor communication (HC-12)
│   ├── weather.hpp          # Weather data fetching from providers
│   ├── network.hpp          # Network connection management
│   ├── ili9341.hpp          # ILI9341 display driver
│   ├── nextion.hpp          # Nextion display driver
│   ├── ws2812b.hpp          # WS2812B LED driver
│   ├── lcdDisplay.hpp       # Common LCD display logic
│   ├── sound.hpp            # Sound management (DF-Player, alerts)
│   ├── sds011.hpp           # SDS011 dust sensor driver
│   ├── comfort.hpp          # Comfort level calculation
│   ├── agregateData.hpp     # Sensor data aggregation
│   ├── thingspeak.hpp       # ThingSpeak integration
│   ├── narodmon.hpp         # Narodmon integration
│   ├── languages.hpp        # Multilingual support (6 languages)
│   ├── fonts.hpp            # Fonts for ILI9341 display
│   └── validate.hpp         # Input data validation
└── data/                    # LittleFS files (web interface, config)
```

---

## 🔗 External Service Integrations

### ThingSpeak
- **Send data** (up to 8 fields) at a configurable interval
- **Receive data** from a specified channel
- Support for **Write API Key** and **Read API Key**

### Narodmon
- **Send data** (up to 12 fields) to the Narodmon monitoring service
- Configure metrics, coordinates, and sensor names

### Weather Forecast Providers
| Provider | API Key |
|----------|---------|
| [OpenWeatherMap](https://openweathermap.org/) | Required (free tier available) |
| [Weatherbit.io](https://www.weatherbit.io/) | Required (free tier available) |
| [Open-Meteo](https://open-meteo.com/) | Not required |

---

## 🏗️ 3D Printed Enclosure

STL files for 3D printing the weather monitor enclosure are available in the `enclosure/STL/` folder of the original repository. The enclosure can be printed on a standard **FDM 3D printer**.

---

## ❓ FAQ

**Q: Which display should I choose?**
A: The ILI9341 is a more affordable and flexible option with touch control. The Nextion NX4832K035 is more expensive but has a built-in processor and graphics engine.

**Q: Do I need to connect all sensors?**
A: No. The device works with just the ESP32 and a display. Sensors are entirely optional.

**Q: How can I add support for a new sensor or display?**
A: There are three options:
1. Do it yourself — the source code is open
2. Send the sensor/display to the author
3. Commission the development (paid)

**Q: The device won't connect to WiFi. What should I do?**
A: Press and hold the **Settings** button until the access point symbol appears on screen, then connect to the BIM32 network and reconfigure WiFi.

**Q: The DF-Player Mini produces constant noise. How do I fix it?**
A: Re-solder the resistor on the DF-Player Mini board from position A to position B. This switches the amplifier's MUTE input to the BUSY output, so it only produces sound during playback.

---

## 🙏 Acknowledgments

### Project Author
A huge thank you to **himikat123** (📧 himikat123@gmail.com) for creating and continuously developing this outstanding open-source project. Development has been ongoing since 2020 from Nuremberg, Germany, and the project now boasts **26 releases** — a truly impressive commitment!

### Library Authors & Contributors
This project was made possible by the incredible work of the authors and contributors of many open-source libraries:

- **Benoît Blanchon** — [ArduinoJson](https://arduinojson.org/) — the backbone of configuration and API handling
- **Hristo Gochkov**, **Me-No-Dev** — [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) & [AsyncTCP](https://github.com/dvarrel/AsyncTCP) — asynchronous web server framework
- **Paul Stoffregen** — [OneWire](https://github.com/PaulStoffregen/OneWire) — 1-Wire protocol for DS18B20
- **Miles Burton** — [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library) — DS18B20 driver
- **Adafruit Industries** — libraries for [BME280](https://github.com/adafruit/Adafruit_BME280_Library), [BMP085](https://github.com/adafruit/Adafruit-BMP085-Library), [PCF8574](https://github.com/adafruit/Adafruit_PCF8574), and many more
- **Rob Tillaart** — [DS3232](https://github.com/RobTillaart/DS3232) — real-time clock driver
- **Dan Tudose** — [MAX44009](https://github.com/dantudose/MAX44009) — ambient light sensor driver
- **Christopher Laws** — [BH1750](https://github.com/claws/BH1750) — ambient light sensor driver
- **Mark Bee** — [SHT21](https://github.com/markbeee/SHT21) — temperature & humidity sensor driver
- **Luc** — [ESP32SSDP](https://github.com/luc-github/ESP32SSDP) — network device discovery
- **Bosch Sensortec** — [BSEC](https://www.bosch-sensortec.com/software-tools/software/bsec/) — software library for BME680 air quality sensing
- **Michael Miller** — [NeoPixelBus](https://github.com/Makuna/NeoPixelBus) — WS2812B LED control
- **Espressif Systems** — for the [ESP32](https://www.espressif.com/) platform and Arduino core

### Community
- All users who report bugs and suggest improvements
- The **Arduino** and **ESP32** communities for invaluable documentation and examples
- **FreeRTOS** authors and contributors for a robust real-time operating system
- Weather data providers: **OpenWeatherMap**, **Weatherbit.io**, **Open-Meteo**
- Data sharing services: **ThingSpeak** and **Narodmon** for their free APIs

---

## 📄 License

This is an open-source project. See the original repository for details:

🔗 **GitHub:** [https://github.com/himikat123/Weather-monitor-BIM32](https://github.com/himikat123/Weather-monitor-BIM32)

---

<p align="center">
  <i>© himikat123@gmail.com, Nuremberg, Germany, 2020–2025</i>
</p>
