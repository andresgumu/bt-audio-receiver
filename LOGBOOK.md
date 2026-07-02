### June 29 & 30 (updated; pulled from Obsidian notes)

Spent the entire day figuring out how to solder the header pins onto the DAC breakout so that I could connect it to the ESP32 (first time soldering). 


1st blunder: **Setting the soldering iron to it's maximum temperature**. Trust, I wached videos on how to solder properly and it didn't seem too bad, especially with the kit that i bought that came with several size tips. At first it seemed that the iron itself wasn't melting the solder fast enough so i incrementally raised the temperature until the desired speed and realized that I burnt a good amount of the solder on the tip.
This turned out to be the hardest thing to overcome because 1) the DAC pcb is TINY and 2) I had messed up the smallest tip that came with the tip. I used the sponge to try and take the residue off but it was a little too late for that. Thankfully, I came up with my own (temporary) technique to rotate the tip to find out which part of the iron wasn't completely covered with burnt solder.

2nd blunder: On the back of DAC were four jumpers, each with three pads. I was supposed to short the center to one of two sides (left or right) on each of the four jumpers but could not for the life of me figure out
where exactly I can find what pads corresponded to VIN or GND. My last resort was to look at the amazon listing page and actually found it (2nd pic):

<img width="463" height="313" alt="image" src="https://github.com/user-attachments/assets/7b9db30f-bf86-41ae-9f54-8b1630f20684" />

<img width="388" height="223" alt="image" src="https://github.com/user-attachments/assets/c5905d6e-faba-424c-8bd1-5fd9a337d35a" />

The blunder itself though was having to work with a burnt tip and getting JUST ENOUGH solder onto the center and have it short one of the two sides. For future reference: 

- TAKE YOUR TIME WITH SOLDERING

connections: (LOW is right, HIGH is left)

- H1L / FLT → LOW (center bridges right) → normal latency
- H2L / DEMP → LOW (center bridges right) → de-emphasis off
- H3L / XMST → HIGH (center bridges left) → soft un-mute
- H4L / FMT → LOW (center bridges right) → I²S


### July 1st

Rather than reinventing the wheel and spending unecessary time figuring out (line by line) the code that i had to flash the ESP32 with, I told claude to give me all of it so I can see if my soldering skills didn't fail me.

Aftwards, after everything (except the RCA cables) were connected, I flashed the ESP32 with the code and verified on the serial monitor that it displayed the correct message ("Sink Started..." etc. etc.) and remembered that the DAC had a headphone jack.
I used my old aux cable and Sony XM4's to verify that my contraption IN FACT DID work!

Now, a new problem:

<img width="459" height="341" alt="image" src="https://github.com/user-attachments/assets/ba004251-8496-4047-adda-ddb00c3cba48" />

Yes. What turned out to be the easiest item to buy on Amazon turned out to be such... SUCH a pain to work with. For starters, the exposed metal wire was too stubby and wide on the end to fit into the breadboard and successfully connect to.
I had to run to walmart and buy a wire stripper (which turned out to be dull and little to no help). Turns out, if you have some sharp scissors and hand strength it's very easy to make a slit through the rubber and expose some
more of the wire. I only used the wire stripper to yank the excess rubber out. The exposed copper wire itself was very brittle and had many copper "hairs" that kept getting smushed when i attempted to curl them together and form a skinny
tip. I even tried using a seperate male to female jumper cable but to no avail. I had two ideas:

- Put some solder and "shape" the tip while also strenghtening the integrity of the conductive part of the wire

This did not work out because of the burnt iron tip. 

- Cut the metal tip of an old jumper wire and somehow connect this (using solder mind you) to the copper hairs.

SOMEHOW this worked. The solder acted as a glue to stick the metal tip to the copper wire and since the metal tip was MEANT to fit inside a breaboard slot, it worked. 

Here are some photos of the working product!

<img width="609" height="804" alt="image" src="https://github.com/user-attachments/assets/8970e8f8-97e2-42b3-8dfd-cb5a1f3fe204" />

<img width="761" height="818" alt="image" src="https://github.com/user-attachments/assets/28afb933-f593-47bc-8fe6-a6701d282883" />

<img width="782" height="421" alt="image" src="https://github.com/user-attachments/assets/6b4510ec-3886-44d6-8cd4-0d37bdccd94d" />

FYI: the breakout was designed in such a way where it was physically impossible to directly connect to the breadboard via the header pins. It was arranged in an L-shape (shown below):

<img width="463" height="337" alt="image" src="https://github.com/user-attachments/assets/c132a9d4-1894-4dc9-b9c9-07aa09a80ab6" />

And so one of the two sides would not be able to completely fit into the available slots. I just resorted to using jumper cables (for now).


