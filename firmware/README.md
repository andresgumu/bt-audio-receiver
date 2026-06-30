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

## Some troubleshooting Tips

- **Keep the wires short and the ground solid.** The bit clock runs at ~1.41 MHz and the PLL is regenerating an ~11 MHz master clock internally, so these aren't slow signals. Over long, loose jumper wires (6"+), the lines start acting like antennas — the signals degrade and the PLL can't lock, even when everything is wired correctly. The nasty part is that the waveforms can still look right on a scope while the chip refuses to work. So if I get correct signals but no audio, the first move isn't to chase the waveforms — it's to shorten the wires. Seat the ESP32 and the DAC right next to each other and run a short, direct ground between them.
- **Check the jumpers before powering on.** The four solder jumpers on the back set the chip's mode. Stock settings aren't guaranteed to be correct, so I verify them first: FLT, DEMP, and FMT short to GND, and XSMT shorts to 3.3V. XSMT is the one to watch — it's the soft-mute control, and if it's pulled low the chip is muted. That produces total silence with everything else looking perfectly fine, which is a miserable bug to chase. FMT matters too: it has to be set to I²S, not left-justified, or the audio comes out wrong.
- **SCK has to be tied to GND.** Grounding SCK tells the chip to generate its own master clock through the internal PLL, which is what lets the whole thing run on 3 wires. Leave it floating and the clock config is undefined — you get silence or noise. This one's confirmed both in the datasheet and by people who learned it the hard way, so it's not optional.
- **If there's a background hiss, twist the output wires.** If audio plays but there's a static hiss underneath it, twist the L, R, and ground wires together on the run from the DAC to the amp. Twisting the signal lines with their ground makes any noise picked up along the way cancel out. Quick fix, and it points at a real layout principle for the PCB later — keep signals and their return paths tightly coupled.

See [`bt_receiver/bt_receiver.ino`](bt_receiver/bt_receiver.ino) for the sketch.
