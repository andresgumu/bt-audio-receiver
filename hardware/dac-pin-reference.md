### Charge pump and negative supply:

- Pin 1: CPVDD (input) - Charge pump power supply, 3.3V
- Pin 2: CAPP (output) - Charge pump flying capacitor terminal for positive rail
- Pin 3: CPGND (n/a) - Charge pump ground
- Pin 4: CAPM (output) - Charge pump flying capacitor terminal for negative rail
- Pin 5: VNEG (output) - Negative charge pump rail terminal for decoupling, -3.3V

Charge Pumps: little DC/DC converters that use a capacitor to store energy instead of an inductor; comprise of no more than two diodes and two capacitors usually. Good for output currents in 10mA range, lack in <250mA. Less efficient than inductor based DC/DC converters. "Flying capacitor" term usually meant to symbolize the capacitors' lack of fixed voltage source (float might be a better term honestly)
- Can generate negative voltage by rearranging the diodes (switches) and capacitors (source)


Ground centered output? https://www.ti.com/lit/an/slaa723/slaa723.pdf?ts=1784690077790&ref_url=https%253A%252F%252Fwww.google.com%252F


### Analog output and analog power:

- Pin 6: OUTL (output)  - Analog output from DAC left channel
- Pin 7: OUTR (output) - Analog output from DAC right channel
- Pin 8: AVDD (power) - Analog power supply, 3.3V
- Pin 9: AGND (n/a) - Analog ground

### Hardware config straps:

- Pin 10: DEMP (input) - De-emphasis control for 44.1 kHz sampling rate; off(low), on(high)
- Pin 11: FLT (input) - Filter select : Normal latency (low) / low latency (high)
- Pin 16: FMT (input) - Audio format selection: I^2S (low) / left-justified(high)
- Pin 17: XSMT (input) - Soft mute control: soft moute (low)/ soft un-mute (high)

### Digital audio interface:

- Pin 12: SCK (input) - System clock input
- Pin 13: BCK (input) - Audio data bit clock input
- Pin 14: DIN (input) - Audio data input
- Pin 15: LRCK (input) - Audio data word clock input

### Digital supply and internal LDO:

- Pin 18: LDOO (power) - internal logic supply rail terminal for decoupling, or external 1.8V supply terminal
- Pin 19: DGND - Digital ground
- Pin 20: DVDD (power) - Digital power supply, 1.8V or 3.3V
