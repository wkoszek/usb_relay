usb_relay: usb_relay.c
	gcc -Wall -std=c99 usb_relay.c -o usb_relay -lusb
clean:
	rm -rf usb_relay
