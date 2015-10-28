CFLAGS+=	-Wall -std=c99

usb_relay: usb_relay.c
	$(CC) $(CFLAGS) $< -o $@ -lusb

usb_relay.static: usb_relay.c
	$(CC) $(CFLAGS) -static $< -o $@ -lusb

setup_osx:
	#brew update
	wget https://gist.githubusercontent.com/chambbj/2229071/raw/6b73bf8fe32d34f67de213fc91f9e830a3fc1ddd/libusb-devel.rb
	brew install libusb-devel.rb

clean:
	rm -rf usb_relay
