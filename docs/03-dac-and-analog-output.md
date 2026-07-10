## What the DAC Does

- fs stands for sampling frequency/rate: represents how many times per second the analog audio signal is measured and converted into a digital number. for CD quality (44.1 kHz), the system processes 44,100 samples every single second to reconstruct the waveform.
	- Importantly, it defines the rate at which data must arrive over your I2S bus
	- If the system doesn't move data at this exact rate, the DAC will produce glitches and gaps in silence because it runs out of data or gets it too fast

**Simply put, the DAC takes in a sequence of discrete, time spaced values and transforms them into a smooth, continuous waveform that matches the audio being streamed.**  

Now more technical: The DAC takes in discrete pulse code modulation (PCM) samples at a $f_s$ (sampling frequency)— 44.1 kHz since we're dealing with CD quality— and turns this into a continuous analog voltage. 

Why voltage? 

Voltage helps tremendously when bridging the digital world to the physical one. Speakers, for example, don't have any digital input. They are fundamentally electromagnetic devices— coils that move in a magnetic field. Using Ohm's law, you can infer that the necessary current going into the speaker is only possible because of a corresponding voltage. 
## Delta-Sigma At a Conceptual Level

Once the DAC takes in these PCM samples that are coming from the ESP32, as stated above briefly, it needs to convert these digital signals into voltage values. Getting 16 bit, high-fidelity audio accuracy from a R-2R/resistor-ladder approach (hardware architecture for building a DAC) is unrealistic (demands hyper-precise analog manufacturing), so Delta-sigma sidesteps this complexity by trading amplitude resolution for time resolution (fast digital switching and oversampling)

It would be naive to simply take each digital sample and hold the corresponding voltage (until the next sample comes) because this would create a staircase waveform. In this context, the sharp edges would contain the original audio signal + a large amount of image noise. As a result, you'd have to apply an aggressive analog filter to cut everything above a certain frequency, which is 1) very hard to build and 2) introduces phase distortion.

the Delta-Sigma architecture is used instead and works by **oversampling** the input data to smoothen the sharp edged staircase waveform (spreads the same amount of information over more time chunks) and using fast, pre-built quantizer along with a feedback loop to remove the resulting quantization noise out of the audible frequency range for humans and into the ultrasonic range. 

No need for a complex filter now. since the audio and "noise" are separated, you can use a simple, low-pass filter to smooth out the remaining high-frequency noise.
## The Clock

 A typical $I^{2}S$ DAC needs a fast master clock to run its internal oversampling. Normally, the source (ESP32) has to generate and route this as a 4th wire. By tying the SCK pin to GND, I told the chip to run its internal phase-locked loop (PLL) instead. A PLL compares its own internally generated clock against an external reference clock. It takes note of if there is clock lag/drift and adjusts a voltage-controlled oscillator (VCO) to speed up/slow down the internal clock to match the reference again.

The payoff is wiring 3 lines instead of 4, which is a pretty big deal for this smaller-scale project.
