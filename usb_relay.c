#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <getopt.h>
#endif

#include "usb.h"

static int	g_debug = 0;

#define	DBG(...)	do {				\
	if (g_debug == 0) {				\
		break;					\
	}						\
	printf("%s(%d): ", __func__, __LINE__);		\
	printf(__VA_ARGS__);				\
	printf("\n");					\
} while (0)

enum {
	CMD_QUERY,
	CMD_ON,
	CMD_FLASH,
	CMD_OFF
};

static void
usage(void)
{

	printf("./usb_relay <on|off>\n");
	exit(1);
}

static struct usb_device *
usb_dev_find(uint32_t look_vid, uint32_t look_pid)
{
	struct usb_bus *busses;
	struct usb_bus *bus;
	struct usb_device *dev;
	struct usb_device_descriptor *desc;
	uint32_t	vid, pid;

	usb_init();
	usb_find_busses();
	usb_find_devices();
	busses = usb_get_busses();
	for (bus = busses; bus; bus = bus->next) {
		for (dev = bus->devices; dev; dev = dev->next) {
			desc = &dev->descriptor;
			vid = desc->idVendor;
			pid = desc->idProduct;
			if ((vid == look_vid) && (pid == look_pid)) {
				return (dev);
			}
    		}
    	}
	return (NULL);
}

int
main(int argc, char **argv)
{
	struct usb_device *dev;
	struct usb_dev_handle *hptr;
	int		o, ret, state, ac, cmd;
	uint32_t	data[2];
	char		**av;

	while ((o = getopt(argc, argv, "dh")) != -1) {
		switch (o) {
		case 'd':
			g_debug++;
			break;
		case 'h':
			usage();
			break;
		default:
			usage();
			break;
		}
	}
	ac = argc - optind;
	av = argv + optind;

	cmd = CMD_QUERY;
	if (ac > 0) {
		if (strcmp(av[0], "on") == 0) {
			cmd = CMD_ON;
		} else if (strcmp(av[0], "off") == 0) {
			cmd = CMD_OFF;
		} else if (strcmp(av[0], "flash") == 0) {
			cmd = CMD_FLASH;
		} else {
			abort();
		}
	}

	dev = usb_dev_find(0x07c3, 0x1283);
	if (dev == NULL) {
		printf("J283 not found!\n");
		exit(1);
	}
	hptr = usb_open(dev);
	DBG("usb_open returned %p", hptr);
	ret = usb_set_configuration(hptr, 1);
	DBG("usb_set_configuration return %d", ret);
	ret = usb_claim_interface(hptr, 0);
	DBG("usb_claim_interface returned %d", ret);

	data[0] = -1;
	data[1] = -1;
	ret = usb_control_msg(hptr, 0xc2, 176, 0x0, 0, (char *)data, 8, 400);
	DBG("usb_control_msg = %d %08x,%08x", ret, data[0], data[1]);
	ret = usb_control_msg(hptr, 0xc2, 184, 0x0, 0, (char *)data, 8, 400);
	DBG("usb_control_msg = %d %08x,%08x", ret, data[0], data[1]);

	if (cmd == CMD_QUERY) {
		state = data[0] & 1;
		printf("%s\n", state ? "on" : "off");
	} else if (cmd == CMD_ON) {
		ret = usb_control_msg(hptr, 0xc2, 183, 0x0, 0, (char *)data, 8, 400);
	} else if (cmd == CMD_OFF) {
		ret = usb_control_msg(hptr, 0xc2, 182, 0x0, 0, (char *)data, 8, 400);
	} else if (cmd == CMD_FLASH) {
		ret = usb_control_msg(hptr, 0xc2, 177, 0x0, 0, (char *)data, 8, 400);
	} else {
		abort();
	}

	exit(0);
} 
