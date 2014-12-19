CFLAGS+=	-Wall -std=c99

usb_relay: usb_relay.c
	$(CC) $(CFLAGS) $< -o $@ -lusb

usb_relay.static: usb_relay.c
	$(CC) $(CFLAGS) -static $< -o $@ -lusb

clean:
	rm -rf usb_relay
