# Using AVRDUDE to program the ATtiny2313a

Once you've connected your programmer and the programmer to the ISP headers of
your board, you're almost ready to write the _MIDIboy_ firmware to the flash.

But first, to make sure your controller is driven by the external clock and
uses its pins the way it's supposed to, we have to set the so-called fuse-bits.

These are written byte-wise. We're mostly concerned with the "low" byte, which
is used to specify the kind of clock the chip is using. To use an external
crystal oscillator with 8MHz or more we need to set the CKSEL bits to `1110`.
To turn this information into the hexadecimal notation AVRDUDE understands,
we can use the online [fuse calculator](http://www.engbedded.com/fusecalc/)
from _engbedded_.

To write the fuse bits use the following command (subsitute the `usbasp` with
the device you're using):

```command
~/midiboy $ avrdude -c usbasp -pt2313 -U lfuse:w:0xce:m
```

After that we can upload the firmware to the connected microcontroller using
the following command:

```command
~/midiboy $ avrdude -c usbasp -pt2313 -U midiboy.elf
```
