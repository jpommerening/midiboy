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

```console
midiboy:~ $ avrdude -c usbasp -p t2313 -U lfuse:w:0xce:m

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.02s

avrdude: Device signature = 0x1e910a
avrdude: reading input file "0xce"
avrdude: writing lfuse (1 bytes):

...

avrdude done.  Thank you.
```

After that we can upload the firmware to the connected microcontroller using
the following command:

```console
midiboy:~ $ avrdude -c usbasp -p t2313 -U midiboy.elf

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.02s

avrdude: Device signature = 0x1e910a
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "midiboy.elf"
avrdude: input file midiboy.elf auto detected as ELF
avrdude: writing flash (216 bytes):

...

avrdude done.  Thank you.
```

![CC BY-SA 4.0](cc-by-sa-80x15.png "Creative Commons Attribution-ShareAlike 4.0 International")
