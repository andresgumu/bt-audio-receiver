# Bill of Materials

Split by build phase. Phase 1/2 parts are the breadboard prototype (have in hand). Phase 3–5 parts are for the custom PCB and are finalized only after layout.

## Phase 1–2 — Breadboard prototype (in hand)

| Qty | Part | Purpose | Notes |
|-----|------|---------|-------|
| 2 | ESP32-WROOM-32 dev board | MCU + Bluetooth Classic + I²S master | 2× for a spare. Must be classic ESP32, **not** S2/S3/C3 (those lack BT Classic). |
| 2 | GY-PCM5102 (PCM5102A) breakout | I²S → analog line-level DAC | Headers ship loose → first soldering task. Includes output coupling caps. |
| 1–2 | RCA male → bare-wire pigtail | DAC analog out → amp input | Need **2** RCA males (L + R). |
| 1 | Half-size solderless breadboard | Prototyping | |
| 1 | Jumper wire assortment (M-M, M-F) | Wiring | |
| 1 | USB data cable (match board port) | Power + flashing | Must be a **data** cable, not charge-only. |

## Tools (one-time)

| Qty | Item | Notes |
|-----|------|-------|
| 1 | Temperature-adjustable soldering iron + tips | YIHUA adjustable kit. |
| 1 | Solder, 63/37 leaded, rosin-core, 0.8 mm | Learning-friendly; eutectic. |
| 1 | Flux, solder wick, brass tip cleaner | Bundled in kit / supplement. |
| 1 | Fine ESD tweezers, flush cutters | For SMD later + lead trimming. |
| 1 | Multimeter | Continuity + power-rail debugging during bring-up. |

## Phase 3–5 — Custom PCB (finalize after layout)

| Qty | Part | Purpose | Notes |
|-----|------|---------|-------|
| 2–3 | ESP32-WROOM-32 **module** (bare) | The part that goes on the board | Spares — hand-soldering a module, first attempt may not survive. |
| 3–5 | PCM5102A IC (TSSOP) | DAC | SMD; spares matter. |
| 2–3 | NE5532 op-amp (optional buffer) | Output impedance buffer | SOIC; may be omitted on v1. |
| 3–5 | LDO regulator (e.g. AMS1117-3.3 or quieter) | 5 V → 3.3 V | |
| 1 kit | 0805 resistor + capacitor assortment | Decoupling (100 nF), bulk (10 µF), coupling caps | 0805 = hand-solderable; don't go to 0402 on a first board. |
| 2 | RCA jacks (PCB-mount) | Analog output | Or 1 dual/stereo jack. |
| 1–2 | USB or barrel jack (PCB-mount) | 5 V input | |
| few | Tactile button, status LED | Optional (reset/boot/status) | |
| 5 | PCB fabrication | The board | JLCPCB/PCBWay ~5-board minimum. Budget 2 spins. |

> Exact passive values (coupling cap size, LDO support caps, decoupling) are pinned down during schematic capture against the PCM5102A and LDO datasheets — not guessed here. See [`../docs/04-pcb-design-notes.md`](../docs/04-pcb-design-notes.md).
