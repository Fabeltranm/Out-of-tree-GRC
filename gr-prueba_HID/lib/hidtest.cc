/*******************************************************
 Windows HID simplification
 
 Alan Ott
 Signal 11 Software
 
 8/22/2009
 
 Copyright 2009, All Rights Reserved.
 
 This contents of this file may be used by anyone
 for any reason without any conditions and may be
 used as a starting point for your own applications
 which use HIDAPI.
********************************************************/
 
#include <hidtest.h>
 
void main_hidtest(void)
{
    
    int res;
    unsigned char buf[9];// 1 extra byte for the report ID
    #define MAX_STR 255
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    int i;

 
    struct hid_device_info *devs, *cur_dev;
    printf("inicializando HID\n");


    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs; 
    while (cur_dev) {
        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("  Release:      %hx\n", cur_dev->release_number);
        printf("  Interface:    %d\n",  cur_dev->interface_number);
        printf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);
 
    // Set up the command buffer.
    memset(buf,0x00,sizeof(buf));
    buf[0] = 0x01;
    buf[1] = 0x81;
    
 
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    ////handle = hid_open(0x4d8, 0x3f, L"12345");
    //print
    handle = hid_open(0x03eb, 0x2402, NULL);
    if (!handle) {
        printf("unable to open device\n");
       // return 1;
    }
 
    // Read the Manufacturer String
    wstr[0] = 0x0000;
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read manufacturer string\n");
    printf("Manufacturer String: %ls\n", wstr);
 
    // Read the Product String
    wstr[0] = 0x0000;
    res = hid_get_product_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read product string\n");
    printf("Product String: %ls\n", wstr);
 
    // Read the Serial Number String
    wstr[0] = 0x0000;
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read serial number string\n");
    printf("Serial Number String: (%d) %ls", wstr[0], wstr);
    printf("\n");
 
    // Read Indexed String 1
    wstr[0] = 0x0000;
    res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read indexed string 1\n");
    printf("Indexed String 1: %ls\n", wstr);
 
    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);
 
    // send and receive 20 reports
    for (int r = 0; r < 20; r++) {
        // send some dummy data
        buf[0] = 0x0; //report number
//        for (i = 1; i < sizeof(buf); i++) {
//            buf[i] = r + i;
//        }
 
//        res = hid_write(handle, buf, sizeof(buf));
//        if (res < 0) {
//            printf("Unable to write()\n");
//            printf("Error: %ls\n", hid_error(handle));
//        }S
 
        // Read requested state. hid_read() has been set to be
        // non-blocking by the call to hid_set_nonblocking() above.
        // This loop demonstrates the non-blocking nature of hid_read().
        res = 0;
        while (res == 0) {
            res = hid_read(handle, buf, sizeof(buf));
            if (res == 0)
                printf("waiting...\n");
            if (res < 0)
                printf("Unable to read()\n");
            #ifdef WIN32
            Sleep(500);
            #else
            usleep(500*1000);
            #endif
        }
 
        printf("Data read:\n   ");
        // Print out the returned buffer.
        for (i = 0; i < res; i++)
            printf("%02hhx ", buf[i]);
        printf("\n");
    }//end 20 reports
 
    //close HID device
    hid_close(handle);
 
    /* Free static HIDAPI objects. */
    hid_exit();
 
#ifdef WIN32
    system("pause");
#endif
 
  //  return 0;
}
