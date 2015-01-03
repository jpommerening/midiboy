# Using AVRDUDE to program the ATtiny2313a

Once you've connected your programmer and the programmer to the ISP headers of
your board, you're almost ready to write the _MIDIboy_ firmware to the flash.

## Reading and writing fuse bits

Out of the box, the ATtiny2313a microcontroller usually has all the right
fuse bits set. The fuse bits are system-wide settings, usually related to
the hardware and capabilities of the microcontroller. For example, if you want
to use an external clock source, like a crystal oscillator, you would have to
set the CKSEL bits. To be sure they have the correct values, you can read and
write their contents with AVRDUDE.

The fuses are written byte-wise. We're mostly concerned with the "low" byte,
which is used to specify the kind of clock the chip is using. The "low" fuse
should read `0x64`; the "high" fuse should read `0xdf`.

To decode the output, or to easily turn the the information from the datasheet
into the hexadecimal notation AVRDUDE understands, you can use the online
[fuse calculator](http://www.engbedded.com/fusecalc/) from _engbedded_.

To read the fuse bits use the following command (subsitute the `usbasp` with
the device you're using, and make sure it is connected):

```console
midiboy:~ $ avrdude -c usbasp -p t2313 -U lfuse:r:-:m -U hfuse:r:-:m

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.02s

...

avrdude done.  Thank you.
```

If the output does not match the listing above (if the fuse values do not match)
use the following command to write the correct values:

```console
midiboy:~ $ avrdude -c usbasp -p t2313 -U lfuse:w:0x64:m -U hfuse:w:0xdf:m

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.02s

...

avrdude done.  Thank you.
```

## Uploading the firmware

Once you are sure the fuse bits are correctly set, you can upload the firmware to
the connected microcontroller using the following command:

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
