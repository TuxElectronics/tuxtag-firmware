# TuxTag Firmware

ESP32-C3 firmware for the TuxTag tracker. The device starts a Wi-Fi Access Point and hosts a simple web UI that lets any browser on the same network trigger the on-board vibrator and buzzer.

## Features

- **Wi-Fi Access Point** – no router required; the ESP32-C3 creates its own network.
- **HTTP web interface** – served at `http://192.168.4.1` with one-tap buttons for each actuator.
- **Vibrator & buzzer control** – mutual exclusion enforced in firmware (only one actuator runs at a time).
- **USB Serial monitor** – status messages at 115 200 baud via USB CDC.

## Hardware

| Pin | Function |
|-----|----------|
| GPIO 1 | Vibrator motor |
| GPIO 10 | Passive buzzer |

Board: **ESP32-C3-DevKitM-1**

## Build & Flash

Install [PlatformIO](https://platformio.org/) (VS Code extension or CLI), then:

```bash
# Build
pio run

# Upload
pio run --target upload

# Open serial monitor
pio device monitor
```

The `platformio.ini` is pre-configured for the ESP32-C3-DevKitM-1 with the Arduino framework, DIO flash mode, and USB CDC enabled.

## Usage

1. Power the device.
2. On your phone or laptop, connect to the Wi-Fi network **`ESP32_Tag_Network`** (password: `password123`).
3. **Android users:** open the **TuxTag app** — it connects directly after joining the access point, no browser needed.
4. **Other devices:** open a browser and navigate to **`http://192.168.4.1`**.
5. Use the on-screen buttons to turn the vibrator or buzzer on/off.

## License

GNU General Public License v3.0 — see [LICENSE](LICENSE) for details.
