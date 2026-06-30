## The Device

A2DP. 
Sink. 

A2DP is a Bluetooth profile that enables wireless devices to stream high quality, stereo-channel audio. The term "sink" here is used as a visual term to show that what I am building is *capturing* the data transmitted from the device (phone) as a sink would with water (data) from a faucet (phone), and using this transformed data to ultimately play audio from a speaker.
## The full Path From Phone to Speaker

Phone -> ESP32 -> DAC -> Amp. -> Speakers

1. Inside of the phone is a radio chip that sends data over ultra-high radio frequencies. 
	- The operating system in your phone decides protocols, profiles, and audio codecs. The actual protocol used is a black box because the implementation in the OS is hidden. In this case it isn't a mystery because the source (phone) and the sink (ESP32) need to agree on a specific profile/codec and since the `BluetoothA2DPSINK` library is used, that's the only profile that would be handled by the sink.
	- In this case, the audio compression codec chosen is "low-complexity subband coding" (SBC). "SB" implies the codec will split the audio into various different frequency bands (and not so implied: will compress each separately). "Low-complexity" meaning it's fast and cheap to run on your phone's CPU and draws little power on the ESP32. Ultimately, this is the format of the data your phone is trying to send to the ESP32. 
2. The ESP32 at this point is flashed with code that uses ESP-IDF + Pschatzmann's library (~15 lines: config, routing/glue, optional callbacks) and when it receives the SBC over Bluetooth, it decodes it to PCM and streams PCM over $I^{2}S$  (a serial bus specifically designed for transferring digital audio data) to the DAC.
3. the DAC transforms this data into analog audio and sends it to the amplifier via the RCA pigtail.
4. The amplifier takes this signal, shapes it into a higher-power replica of the input signal, and sends it to the speakers.
## The Digital/Analog Boundary

 The digital-to-audio converter (DAC) is the boundary between digital and analog signals, though the quality ceiling is determined upstream from the component itself. The compression that occurs (lossy SBC) permanently removes information from the audio being transmitted. A good DAC does it's best to keep the ceiling set by the compression.
 
  The ESP32 contains it's own DAC for small use-cases, but for this specific project I went with an external DAC to ensure that the analog signal being sent to the amplifier is not as affected by electrical noise. Unlike digital signals, analog signals are continuous. They directly measure and mirror real-world, physical phenomena. In turn, the signal can take on any infinite, fractional value within its given range which gives rise to the issue of noise. To ensure the quality of the audio is at it's best, an external DAC is necessary. 

## Part Justifications

- **ESP32**: An ESP32 is best to use in this case since it supports Bluetooth classic which is designed for high -throughput and continuous streams. Classic A2DP cannot run on BLE-only ESP32 variants.
- **PCM5102A Breakout (DAC)**: The internal DAC on the ESP32 board is 8-bit and sits on tons of electrical noise. The PCM5102A gives 16-bit resolution and is more physically isolated from the electrical noise going on.

## Abstracted Complexity Worth Knowing

Pschatzmann's library that wraps Espressif's ESP-IDF using C++ is what makes the code on the Arduino IDE so simple. Instead of reinventing the wheel, I get to complete this project in a shorter amount of time while also digging deeper into the abstractions for sheer curiosity. Hopefully in the future I will be skilled enough to attempt to handle RF design.

Everything else though, the hardware, $I^{2}S$ integration, analog output, and PCB is mine.
