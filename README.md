# moth.CO2.2

This projects provides instructions for building a CO₂ sensor from off the shelve electronic parts combined with 3D printed housing parts.

![CO₂-Sensor fully assembled](/images/sensor01_800.jpg?raw=true)

- measures
  - CO₂
  - temperature
  - humidity
  - pressure
  - altitude
  - battery

- can last ~6 weeks on a single battery charge, when operated at low power settings, this is the longest battery life of a SCD41 based sensor operated at regular interval as far as i know

- uses the [Sensirion SCD-41](https://www.adafruit.com/product/5190) Sensor, a small and high performance photoacoustic NDIR CO₂ sensor

- offers various ways to access the data measured
  - on the device display in table or chart mode
  - through an integrated [wifi-rest-api](/moth_client/README.md#wifi-rest-api)
  - over the standardized [MQTT protocol](/moth_core/README.md#mqttjson)

- is configurable in many ways
  - thresholds for CO₂, temperature and humidity
  - temperature display in °C or °F
  - sensor timezone
  - temperature offset
  - CO₂ calibration
  - WiFi, [MQTT](https://de.wikipedia.org/wiki/MQTT)

- stores unlimited history of data due to integrated SD-card

- hosts a web-UI on it's internal web-server, usable from mobile and desktop devices

- optionally provides
  - dark/inverted mode
  - acoustic alert

<!-- ![chart mode](/images/sensor03_800.jpg?raw=true)

![WiFi connection](/images/sensor04_800.jpg?raw=true) -->

---

## The project is structured as follows:

### [Core (moth_core)](moth_core/README.md)

This project is built with [PlatformIO](https://platformio.org/). Please refer to the instructions provided on the PlatformIO website. PlatformIO makes development with the ESP32 microcontroller easier and faster compared to the Arduino IDE. If you have not switched yet i advise you to do so, it will save you time after a very short period of time.
The PlatformIO project, and configuration files can be found here.

### [Building instructions (moth_parts)](moth_parts/README.md)

Building instructions, drawings and printable files for the device.

### [Client (moth_client)](moth_client/README.md)

A react UI for data retrieval and administration of the device.

![web-app client](/images/moth_client.gif)

---

## Device functionality:

### Device usage

- #### Buttons

- #### Table mode

- #### Chart Mode

- #### CO₂ sound alert

- #### Wifi

- #### Dark mode

- #### Altimeter

### Data access

- #### On display

The device display supports multiple display modes, "table", "chart" and "calibration".

  - In table mode the latest CO₂, temperature and  humidity values are shown numerically.
  - In chart mode one of CO₂, temperature, humidity or pressure are shown in a simple chart. The chart can show 1h, 3h, 6h, 12h or 24h data ranges.
  - In calibration mode, the most recent history of values is shown together with simple statistics. The device can then be calibrated either to a configurable value via button press, or through the wifi-rest-api and value that can be specified by the user.

- #### Over the wifi-rest-api

  The device provides various possibilities to access current and historic data over the wifi-rest-api.

- #### MQTT

  It is possible to configure a mqtt connection and upload the mqtt brokers certificate if needed. The device will make connections in configurable intervals und publish it's measurements.
  The sensor can easily be integrated into HomeAssistant.

### Calibration

- #### On display (no wifi required)

The device display can be switched to calibration display mode, then put outside into fresh air. After 10 minutes the recent measurement history standard deviation can be checked and, if within plausible tolerance, the device can be calibrated to a reference value previously configured. See [moth_core/disp.json](/moth_core/README.md#dispjson) and [moth_client/client_config](/moth_client/README.md#client-config) for more details.

- #### Over the wifi-rest-api

The rest-api of the device provides the "co2cal" endpoint. Here it is possible to calibrate the device to any value above 400pmm. This enables calibration to value other than outside air, if known from i.e. other devices (see: [moth_client/wifi-rest-api](/moth_client/README.md#wifi-rest-api)) for more detail.

---

## License

Please be aware that all software in this project is licensed under the [MIT license](license.txt), while the drawings and 3d-printed parts are licensed under the [Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/) license.

https://github.com/the-butcher/MOTH.CO2.2/assets/84620977/23303f60-04a6-4f3b-a14d-cb0d6dc5e2be


