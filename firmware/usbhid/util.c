#include <sysinit.h>
#include <string.h>

#include "usbhid/usb.h"
#include "usbhid/usbcore.h"
#include "usbhid/usbhw.h"


void usbHIDInit() {
    uint32_t usbTimeout = 0; 
    USB_Init();
    USB_Connect(TRUE);
    while ( usbTimeout < CFG_USBCDC_INITTIMEOUT / 10 )
    {
      if (USB_Configuration) break;
      systickDelay(10);             // Wait 10ms
      usbTimeout++;
    }

}

void usbHIDOff(void) {
    USB_Connect(FALSE);
}
