burning_bush
============

Heat control system for Trinity Covenant Church

This software is designed to be run on a Raspberry Pi model B.  The model B+
should work as well.

The interface for the heating system is controlled through ACCESS's I/O USB
driver library, [AIOUSB](https://github.com/accesio/AIOUSB)

Several components of the system are designed to work together:
1. Crontab handles the scheduling on a daily basis.  Most crontab entries
are short commands to the AIOUSB to turn specific zones on at specific times.
1. A web server is hosted that provides a front end to the heating system.
The web server updated the crontab entries on demand.
1. Crontab can't handle all of the scheduling demands of the system.  For
example, it can't do one-time events.  At best it can set it up as annual.
To account for this, one crontab entry runs daily a program to refresh the
crontab file for the day.

# Install instructions

Backups of a stable version of the pi's SD card should exist, but in case they
don't, here is how to build the system from a fresh Rasperian install.

1. `mkdir ~/tcc`
1. `cd ~/tcc`
1. `git clone https://github.com/accesio/AIOUSB`
1. `cd AIOUSB`
1. Follow Ubuntu/Debian install directions in https://github.com/accesio/AIOUSB
to build C/C++ libraries and the ruby wrappers.
  1. In my initial install, I had to add `-I/usr/include/libusb-1.0` to
  the INCPATH in `AIOUSB/samples/USB-IDIO-16/Makefile` in order to compile the
  samples.  This may have been corrected by now.
1. `cd ~/tcc`
1. `git clone https://github.com/MinutemanZ/burning_bush`

Further install instructions will be added as the system gets built.
