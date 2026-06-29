/*
 * ESP32 Bluetooth A2DP Audio Receiver
 * -----------------------------------
 * Bluetooth A2DP sink: receives audio from a phone (the source),
 * decodes SBC to PCM in software, and streams the PCM out over I2S
 * to an external PCM5102A DAC, which produces line-level analog audio.
 *
 * Signal chain:
 *   Phone --BT/A2DP--> ESP32 --I2S--> PCM5102A --analog--> Amp --> Speakers
 *
 * Hardware: ESP32-WROOM-32 + GY-PCM5102 breakout.
 * See ../README.md and ../docs/ for the protocol details.
 *
 * NOTE: The ESP32-A2DP library moved its audio output to the
 * arduino-audio-tools backend. The exact constructor/pin-config API
 * can vary by installed version. This sketch uses the classic
 * set_pin_config() form, which remains the clearest and is widely
 * supported. Reconcile against the example that compiled in your
 * IDE during Phase 2 bring-up if the API differs.
 */

#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;

void setup() {
  Serial.begin(115200);

  // I2S pin mapping (ESP32 GPIO -> PCM5102 pin).
  //   bck_io_num   = BCK  -> bit clock      (GPIO 26)
  //   ws_io_num    = LCK  -> word select    (GPIO 25)
  //   data_out_num = DIN  -> serial data    (GPIO 22)
  // The PCM5102's SCK (master clock) pin is tied to GND in hardware,
  // which enables the chip's internal PLL to regenerate MCLK from BCK.
  // There is therefore NO master-clock line configured here.
  i2s_pin_config_t pin_config = {
    .bck_io_num   = 26,
    .ws_io_num    = 25,
    .data_out_num = 22,
    .data_in_num  = I2S_PIN_NO_CHANGE
  };
  a2dp_sink.set_pin_config(pin_config);

  // Bring up the entire Bluetooth stack (radio, L2CAP, AVDTP, SBC
  // decoder) and advertise this device name to phones.
  a2dp_sink.start("BoseBT");

  Serial.println("A2DP sink started. Pair with \"BoseBT\".");
}

void loop() {
  // Nothing to do here — the library runs the audio pipeline on its
  // own FreeRTOS tasks. The main loop stays empty.
}
