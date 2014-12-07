# MIDIboy

> Open source MIDI sync box for LSDJ and nanoloop

## About

_MIDIboy_ aims to be a dead-simple way to synchronize your Gameboy to a MIDI clock.
Based on the [LSDJ-MC](http://www.firestarter-music.de/lsdj/) it is designed around
the affordable [ATtiny2313(a)][attiny2313a] microcontroller (µC).

## Features

- Starts in Omni-Mode, learns MIDI channel at the press of a button.
- Clock jitter correction
- Standalone clock
- Sysex programmable

## Requirements

To compile the code in this repository, you need a proper C compiler. Luckily, the
open source compiler suite GCC ships with great AVR support. If you're using a Mac,
you can use my [Homebrew tap](/jpommerening/homebrew-avr). Windows users can use the
ready-to-use [WinAVR][]. Everyone else probably doesn't need my help to get up and
running.
If you are not ready to go hardware with it and just want to give it a try, you can
use [SimulAVR][].
To transfer the compiled binary to the microcontroller you need a hardware programmer
and software. I'm using [USBasp][] connected to a breadboard and [AVRDUDE][].
Finally, besides the microcontroller, you need some electric components, maybe a case
and a power supply. Also, a soldering iron and something to etch and drill your PCB.

## Next

- [About the ATtiny2313a](docs/attiny2313a.md)
- [Bill of materials](docs/bom.md)
- [PCB layout](docs/pcb.md)
- [Using SimulAVR for simulation](docs/simulavr.md)
- [Using AVRDUDE to program the µC](docs/avrdude.md)

[winavr]: http://www.mikrocontroller.net/articles/WinAVR
[usbasp]: http://www.fischl.de/usbasp/
[avrdude]: http://www.nongnu.org/avrdude/
[simulavr]: http://www.nongnu.org/simulavr/
[attiny2313a]: http://www.atmel.com/devices/attiny2313a.aspx

## [License](LICENSE-BSD) (BSD)

Copyright &copy; 2014, Jonas Pommerening <jonas.pommerening@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
