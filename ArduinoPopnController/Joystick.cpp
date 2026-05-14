#include "Joystick.h"
#include "DynamicHID.h"

#define JOYSTICK_REPORT_ID         0x04

Joystick_::Joystick_()
{
    int _buttonCount = 9;	
	int buttonPaddingBits = 7;
	
    uint8_t tempHidReportDescriptor[350];
    int hidReportDescriptorSize = 0;

    // USAGE_PAGE (Generic Desktop)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

    // USAGE (Joystick - 0x04; Gamepad - 0x05; Multi-axis Controller - 0x08)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05; // JOYSTICK_TYPE_GAMEPAD

    // COLLECTION (Application)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0xa1;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

    // REPORT_ID (Default: 3)
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x85;
    tempHidReportDescriptor[hidReportDescriptorSize++] = JOYSTICK_REPORT_ID;
	
	// USAGE_PAGE (Button)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;

	// USAGE_MINIMUM (Button 1)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x19;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

	// USAGE_MAXIMUM (Button 32)            
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x29;
	tempHidReportDescriptor[hidReportDescriptorSize++] = _buttonCount;

	// LOGICAL_MINIMUM (0)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

	// LOGICAL_MAXIMUM (1)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x25;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

	// REPORT_SIZE (1)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

	// REPORT_COUNT (# of buttons)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
	tempHidReportDescriptor[hidReportDescriptorSize++] = _buttonCount;

	// UNIT_EXPONENT (0)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x55;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

	// UNIT (None)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x65;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

	// INPUT (Data,Var,Abs)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;

	if (buttonPaddingBits > 0) {
		
		// REPORT_SIZE (1)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

		// REPORT_COUNT (# of padding bits)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
		tempHidReportDescriptor[hidReportDescriptorSize++] = buttonPaddingBits;
				
		// INPUT (Const,Var,Abs)
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
		tempHidReportDescriptor[hidReportDescriptorSize++] = 0x03;
		
	} // Padding Bits Needed

	// USAGE_PAGE (Generic Desktop)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;
		
	// USAGE (Pointer)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

	// LOGICAL_MINIMUM (0)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

	// LOGICAL_MAXIMUM (255)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x25;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0XFF;

	// REPORT_SIZE (8)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x08;

	// REPORT_COUNT (axisCount)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 2;
					
	// COLLECTION (Physical)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xA1;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

	// USAGE (X)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x30;

	// USAGE (Y)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x31;
	
	// INPUT (Data,Var,Abs)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x81;
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;
	
	// END_COLLECTION (Physical)
	tempHidReportDescriptor[hidReportDescriptorSize++] = 0xc0;
			
//    /*Lights */
//    0x85, 0x05,                    /*   REPORT_ID 5*/ 
//    0x15, 0x00,                    /*     LOGICAL_MINIMUM (0) */ 
//    0x25, 0x01,                    /*     LOGICAL_MAXIMUM (255) */ 
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x85;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;

    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x15;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x00;

    tempHidReportDescriptor[hidReportDescriptorSize++] = 0x25;
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0xFF;
//    /*Led 1 */ 
//    0x05, 0x0a,                    /*     USAGE_PAGE (Ordinals) */ 
//    0x09, 0x01,                    /*     USAGE (Instance 1) */ 
//    0xa1, 0x02,                    /*     COLLECTION (Logical) */ 
//    0x05, 0x08,                    /*       USAGE_PAGE (LEDs) */ 
//    0x09, 0x4b,                    /*       USAGE (Generic Indicator 1) */ 
//    0x79, 0x04,                    /*       STRING INDEX (4) */
//    0x75, 0x01,                    /*       REPORT_SIZE (8) */ 
//    0x95, 0x01,                    /*       REPORT_COUNT (1) */ 
//    0x91, 0x02,                    /*       OUTPUT (Data,Var,Abs) */ 
//    0xc0,                          /*     END_COLLECTION */ 
    for (int index = 0; index < 9; index++) {
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x0a;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
      tempHidReportDescriptor[hidReportDescriptorSize++] = index + 1;
      
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0xa1;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x05;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x08;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x09;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x4b;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x79;
      tempHidReportDescriptor[hidReportDescriptorSize++] = index + 4;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x75;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x08;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x95;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x01;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x91;
      tempHidReportDescriptor[hidReportDescriptorSize++] = 0x02;

      tempHidReportDescriptor[hidReportDescriptorSize++] = 0xc0;
    }

    // END_COLLECTION
    tempHidReportDescriptor[hidReportDescriptorSize++] = 0xc0;

	// Create a copy of the HID Report Descriptor template that is just the right size
	uint8_t *customHidReportDescriptor = new uint8_t[hidReportDescriptorSize];
	memcpy(customHidReportDescriptor, tempHidReportDescriptor, hidReportDescriptorSize);
	
	// Register HID Report Description
	DynamicHIDSubDescriptor *node = new DynamicHIDSubDescriptor(customHidReportDescriptor, hidReportDescriptorSize, false);
	DynamicHID().AppendDescriptor(node);
	
}

void Joystick_::setButton(uint8_t button, uint8_t value)
{
    int index = button / 8;
    int bit = button % 8;
	bitWrite(_buttonValues[index], bit, value);
}

void Joystick_::sendState()
{
	uint8_t data[4];
	data[0] = _buttonValues[0];
	data[1] = _buttonValues[1];
	data[2] = data[3] = 0;
	DynamicHID().SendReport(JOYSTICK_REPORT_ID, data, 4);
}
