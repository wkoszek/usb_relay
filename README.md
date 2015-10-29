"usb_relay" - USB driver for JS284 relay from
=========

[![Build Status](https://travis-ci.org/wkoszek/usb_relay.svg)](https://travis-ci.org/wkoszek/usb_relay)

`usb_relay` is a driver for: http://www.j-works.com/jsb283.php It gives you
an ability to connect the JS284 to the USB port and use `usb_relay` to turn
the relay on and off from the UNIX-based system. I have used it both with
Ubuntu GNU/Linux and FreeBSD.

# How to build

To build `usb_relay` you must have `libusb` header files. On Ubuntu you can
install them with a following command:

	sudo apt-get install libusb-dev

To build `usb_relay`:

	make

# How to use

Usage of `usb_relay` is pretty simple:

	./usb_relay on

To turn it on. To turn the relay off, you do:

	./usb_relay off

You can also flash the LED:

	./usb_relay flash

In case you have to debug something on your system, the `-d` flag can be
passed to the program to get some debugging output.

# Author

- Wojciech Adam Koszek, [wojciech@koszek.com](mailto:wojciech@koszek.com)
- [http://www.koszek.com](http://www.koszek.com)
