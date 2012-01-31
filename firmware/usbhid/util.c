#include <sysinit.h>
#include <string.h>

#include "usbhid/usb.h"
#include "usbhid/usbcore.h"
#include "usbhid/usbhw.h"


void usbHIDInit() {
    USB_Init();
    USB_Connect(TRUE);
}

void usbHIDOff(void) {
    USB_Connect(FALSE);
}
