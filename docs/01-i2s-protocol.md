Here's the situation: the ESP32 has already decoded PCM sitting in memory. It needs to get this data to the DAC. Why not use the SPI peripheral which moves data (bits) between two devices instead of I2S?
## The Nature of the Data

When you use SPI to read a sensor or write to flash, timing becomes a constraint. Instead of the continuous/real-time timing I2S offers, you are given "bursty" samples. This is because SPI is **transaction-oriented** by design. It's great for handling general-purpose data in registers and files because it's architected around discrete "start/transfer x bytes/stop" operations, but leads to audible clicking/popping in the audio itself because gaps in the audio get created. 

This is why I2S is necessary: it's specifically used for audio streaming and uses a clock that runs continuously at a fixed rate set by the audio— unlike SPI's clock which is not fixed and reliant on the software's pacing.

## A Stereo Problem

Additionally, when working with stereo speakers, the left and right channels need to arrive perfectly sequential. SPI uses the specific channel-selector GPIO pin on the ESP32, but I cannot just tell the SPI peripheral that X bits from the pin are for the left speaker and the next X bits are for the right speaker. The reason is because SPI uses **spatial selection**: it is able to select which device is on the bus— such as an SD card, a display, or a sensor— but cannot tell what parts of the data stream correspond to specific channels.

Since I2S is specifically for audio streaming, it selects which part of the audio (instead of which device) you are talking to.  Adding a WS/LCK line, you can categorize `LOW` as the left channel and `HIGH` as the right channel to be able to correctly map the stereo audio for the speakers. 

**How often does the WS line toggle relative to the audio?** 

WS completes on full cycle per stereo sample pair. since the sample rate is fixed (44.1 kHz), `sample rate = WS frequency`. Then, the bit clock (BCK) has to be fast enough to shift all the bits in that time `BCK = sample_rate × bits_per_sample × channels` which is `44,100 x 16 x 2 = 1,411,200` bits per second. 

In short: the bit clock runs at `sample_rate × bits × channels` because it must clock out every audio bit in real time; for 16-bit stereo at 44.1 kHz that's ~1.41 MHz, exactly 32x the word-select clock.
