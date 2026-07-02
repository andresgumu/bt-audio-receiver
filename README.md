# ESP32 Bluetooth Audio Receiver

A from-scratch **Bluetooth A2DP audio receiver** that turns a phone into a wireless source for a passive stereo amplifier. Built as a hardware-engineering learning project: breadboard prototype first, then a custom 2-layer PCB designed in Altium.

---

I inherited a set of older Bose passive bookshelf speakers driven by an amplifier with L/R RCA inputs. The only way to play audio was a wired RCA-to-USB-C dongle tethering my phone to the amp. I wanted that connection to be wireless; and rather than buy a $15 RCA-to-Bluetooth adapter, I wanted to design and build...

A **Bluetooth A2DP sink**. The phone is the *source* (transmitter); this device is the *sink* (receiver). Accepts a compressed audio stream over Bluetooth Classic, decodes it to PCM, converts that to a line-level analog signal, and feeds the amplifier over RCA.

```
 Phone  ──BT/A2DP──>  ESP32  ──I²S──>  PCM5102A  ──analog──>  Amp  ──>  Speakers
(source)  (SBC enc)  (decode)  (3-wire)   (DAC)    (line-level) (RCA)
```

Full walk-through of each stage: [`docs/00-architecture.md`](docs/00-architecture.md)

## Hardware

| Block        | Part                | Why                                                        |
|--------------|---------------------|------------------------------------------------------------|
| MCU + radio  | ESP32-WROOM-32      | Onboard **Bluetooth Classic** (A2DP needs BR/EDR, not BLE) |
| DAC          | PCM5102A (GY-PCM5102 breakout) | Clean line-level I²S DAC; ESP32 internal DAC is 8-bit and unusable for audio |
| Output       | RCA jacks + coupling caps | Block DC offset into the amp                         |
| Power        | 5 V USB → 3.3 V LDO | Single rail for MCU + DAC                                   |

Full bill of materials: [`hardware/BOM.md`](hardware/BOM.md)

## Firmware (tentative)

ESP32 Arduino + Phil Schatzmann's [`ESP32-A2DP`](https://github.com/pschatzmann/ESP32-A2DP) library (with `arduino-audio-tools` as the output backend). The A2DP sink decodes SBC in software on the ESP32; the decoded PCM is streamed out over I²S to the external DAC.

Sketch + build notes: [`firmware/`](firmware/)

## Learning Points

| Topic | Deep-dive |
|-------|-----------|
| System architecture & the digital/analog boundary | [`docs/00-architecture.md`](docs/00-architecture.md) |
| **I²S** — clocks, framing, and why SCK ties to ground | [`docs/01-i2s-protocol.md`](docs/01-i2s-protocol.md) |
| **Bluetooth A2DP & the SBC codec** — the protocol stack and the quality ceiling | [`docs/02-bluetooth-a2dp-sbc.md`](docs/02-bluetooth-a2dp-sbc.md) |
| **DACs & analog output** — delta-sigma conversion, line level, coupling | [`docs/03-dac-and-analog-output.md`](docs/03-dac-and-analog-output.md) |
| **Mixed-signal PCB design** — ground planes, decoupling, Altium workflow | [`docs/04-pcb-design-notes.md`](docs/04-pcb-design-notes.md) |

Day-by-day build journal: [`LOGBOOK.md`](LOGBOOK.md)

## Build phases

- [x] **Phase 1 — Setup.** Parts ordered, toolchain installed, firmware compiles clean against the target.
- [x] **Phase 2 — Breadboard validation.** Wire ESP32 + PCM5102A, flash, pair, get audio out. *(The empirical "does the concept work" gate.)*
- [ ] **Phase 3 — Schematic capture.** Translate the validated circuit into a clean Altium schematic.
- [ ] **Phase 4 — PCB layout.** 2-layer board, ground plane, analog/digital separation, DRC, Gerber export, fab.
- [ ] **Phase 5 — Assembly & bring-up.** Hand-solder the board (TSSOP DAC, 0805 passives), validate the custom hardware.

## Repository layout

```
bt-audio-receiver/
├── README.md            ← you are here
├── LOGBOOK.md           ← engineering journal, dated entries
├── docs/                ← protocol & design deep-dives (the learning)
├── hardware/            ← BOM now; schematic, layout, Gerbers later
└── firmware/            ← Arduino sketch + build configuration notes
```

## License

MIT — see [`LICENSE`](LICENSE).
