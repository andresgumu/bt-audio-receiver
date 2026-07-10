## A2DP

Bluetooth can be seen as an umbrella term; it's not really it's own, singular thing. It encapsulates profiles that have different jobs and Bluetooth itself is a protocol for these profiles. The core Bluetooth stack provides the physical radio links and basic data transport. Profiles are layered on top as specific job descriptions to two connecting devices know exactly what to expect from each other, rather than firing data at one another blindly.  

**A2DP** stands for Advanced Audio Distribution Profile. It strictly handles the heavy lifting of audio streaming, while **AVRCP** runs in "parallel" to handle the control signals (play, pause, skip, volume). 
## The Stack Underneath A2DP

**A2DP → AVDTP → L2CAP**
**|--------SBC codec-------|**

**A2DP** is dictating what is happening. AVDTP and L2CAP are protocols underneath that dictate how it happens. 

**AVDTP** (Audio/Video Distribution Transport Protocol) is responsible for establishing audio endpoints and handles codec negotiation. It asks the sink what it supports, cross-references it with the source, and verifies parameters so that both devices are speaking the same language with one another.  

**L2CAP** (Logical Link Control and Adaptation Protocol) handles the data transport mechanics. It takes the continuous stream of SBC-encoded audio (more on this in a bit), slices it up into specifically sized packets, and puts them on the radio to transmit. It can also act as a multiplexer to juggle multiple streams of data at once (receive dense audio packets and handle control commands simultaneously over the same wireless connection)

**SBC** (Subband Coding) is the universal codec (coder-decoder) for the A2DP profile. Every Bluetooth device is required to support it to guarantee there is a working fallback for any device trying to communicate with another. SBC relies on psychoacoustics to split the audio spectrum into several frequency "subbands" (hence the name). It dynamically assigns fewer bits in frequency bands where human ears struggle to hear differences and saves a lot of bandwidth doing so. As mentioned in a previous doc, SBC is lossy, meaning any data that is removed is *permanently* destroyed and cannot be recovered (via the ESP32's decoder).


