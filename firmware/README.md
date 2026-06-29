# Firmware

ESP32 Arduino firmware for the A2DP sink. Receives Bluetooth audio, decodes SBC to PCM, streams it out over I²S to the PCM5102A.

## Dependencies

| Library | Source | Role |
|---------|--------|------|
| ESP32 board core | "esp32 by Espressif Systems" (Boards Manager) | ESP-IDF + Arduino layer, Bluetooth stack |
| `ESP32-A2DP` | https://github.com/pschatzmann/ESP32-A2DP | A2DP sink + SBC decode |
| `arduino-audio-tools` | https://github.com/pschatzmann/arduino-audio-tools | I²S output backend (required dependency) |

Install both libraries by cloning into your Arduino `libraries/` folder, or via Sketch → Include Library → Add .ZIP Library.

## Build configuration (Arduino IDE)

| Setting | Value | Why |
|---------|-------|-----|
| Board | **ESP32 Dev Module** | Targets the classic ESP32 (BT Classic). Not S2/S3/C3. |
| Partition Scheme | **Huge APP (3 MB No OTA / 1 MB SPIFFS)** | The BT stack overflows the default 1.2 MB app partition. |
| Upload Speed | 921600 (or drop to 115200 if uploads fail) | |
| Port | (the board's COM port, once plugged in) | Needs the CP2102/CH340 USB driver. |

## Wiring (breadboard)

| ESP32 GPIO | I²S signal | PCM5102 pin |
|------------|-----------|-------------|
| 26 | BCK (bit clock) | BCK |
| 25 | WS / LRCLK | LCK |
| 22 | DIN (data) | DIN |
| — | (no MCLK) | **SCK → GND** ← critical, enables internal PLL |
| 5V (or 3V3) | power | VIN |
| GND | ground | GND |
| | analog out | L / R / GND → RCA → amp |

> GPIO assignments are the library defaults — confirm against the installed library version during bring-up. See [`../docs/01-i2s-protocol.md`](../docs/01-i2s-protocol.md) for why SCK ties to ground.

## Bring-up checklist (Phase 2)

1. [ ] Headers soldered to both boards.
2. [ ] Wiring matches the table above; **SCK tied to GND** double-checked.
3. [ ] Board enumerates on a COM port (driver installed).
4. [ ] Sketch uploads (Upload, not just Verify).
5. [ ] "BoseBT" appears in the phone's Bluetooth list.
6. [ ] Pair, play audio, confirm clean output from the amp.
7. [ ] If silence: check SCK→GND, check XSMT not held low, scope BCK:WS for the 32:1 ratio.

See [`bt_receiver/bt_receiver.ino`](bt_receiver/bt_receiver.ino) for the sketch.
