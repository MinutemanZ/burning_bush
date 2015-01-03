burning_bush
============

Heat control system for Trinity Covenant Church

This software is designed to be run on a Raspberry Pi model B.  The model B+
should work as well.

The interface for the heating system is controlled through ACCESS's I/O USB
driver library, [AIOUSB](https://github.com/accesio/AIOUSB)

Several components of the system are designed to work together:
1. Crontab handles the scheduling.  Most crontab entries
are short commands to the AIOUSB to turn specific zones on at specific times.
1. ddclient publishes the church's IP address so that it can be reached at
`burning-bush.dynu.com`.

# Install instructions

Backups of a stable version of the pi's SD card should exist, but in case they
don't, here is how to build the system from a fresh Rasperian install.

1. `sudo apt-get install ddclient`
  1. I'm using https://www.dynu.com to map `burning-bush.dynu.com` to the
  raspberry pi's current IP address.
  1. Configure ddclient using configuration info from https://www.dynu.com
1. Install [RVM](http://rvm.io/rvm/install)
  1. Follow Multi-User install instructions
1. `mkdir ~/tcc`
1. `cd ~/tcc`
1. `git clone https://github.com/accesio/AIOUSB`
1. `cd AIOUSB`
1. Follow Ubuntu/Debian install directions in https://github.com/accesio/AIOUSB
to build C/C++ libraries and the ruby wrappers.
1. `cd ~/tcc`
1. `git clone https://github.com/MinutemanZ/burning_bush`
1. `cd burning_bush`
1. `gem install bundler`
1. `bundle install`
1. Create `/etc/ld.so.conf.d/aiousb.conf` with the values of LD_LIBRARY_PATH in AIOUSB/AIOUSB/sourceme.sh
1. Reboot

Further install instructions will be added as the system gets built.
