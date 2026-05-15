#include "Joystick.h"
#include "DynamicHID.h"

#define JOYSTICK_REPORT_ID         0x04
#define LED_DEFINITION(idx) 0x05, 0x0a, 0x09, (idx), 0xa1, 0x02, 0x05, 0x08, 0x09, 0x4b, 0x79, 0x03 + (idx), 0x75, 0x08, 0x95, 0x01, 0x91, 0x02, 0xc0
const uint8_t hidReportDescriptor[] = {
	0x05, 0x01,                 // USAGE_PAGE (Generic Desktop)
	0x09, 0x05,                 // USAGE (Gamepad)
	0xa1, 0x01,                 // COLLECTION (Application)
	0x85, JOYSTICK_REPORT_ID,   // REPORT_ID
	0x05, 0x09,                 // USAGE_PAGE (Button)
	0x19, 0x01,                 // USAGE_MINIMUM (Button 1)
	0x29, 0x09,                 // USAGE_MAXIMUM (Button 9)
	0x15, 0x00,                 // LOGICAL_MINIMUM (0)
	0x25, 0x01,                 // LOGICAL_MAXIMUM (1)
	0x75, 0x01,                 // REPORT_SIZE (1)
	0x95, 0x09,                 // REPORT_COUNT (# of buttons)
	0x55, 0x00,                 // UNIT_EXPONENT (0)
	0x65, 0x00,                 // UNIT (None)
	0x81, 0x02,                 // INPUT (Data,Var,Abs)
	0x75, 0x01,                 // REPORT_SIZE (1) - PADDING: 7 bits to next byte boundary
	0x95, 0x07,                 // REPORT_COUNT (# of padding bits)
	0x81, 0x03,                 // INPUT (Const,Var,Abs)
	0x05, 0x01,                 // USAGE_PAGE (Generic Desktop)
	0x09, 0x01,                 // USAGE (Pointer)
	0x15, 0x00,                 // LOGICAL_MINIMUM (0)
	0x26, 0xFF, 0x00,           // LOGICAL_MAXIMUM (255)
	0x75, 0x08,                 // REPORT_SIZE (8)
	0x95, 0x02,                 // REPORT_COUNT (2)
	0xA1, 0x00,                 // COLLECTION (Physical)
	0x09, 0x30,                 // USAGE (X)
	0x09, 0x31,                 // USAGE (Y)
	0x81, 0x02,                 // INPUT (Data,Var,Abs)
	0xc0,                       // END_COLLECTION (Physical)
	// Lights - REPORT_ID 5 
	0x85, 0x05,                 // REPORT_ID 5
	0x15, 0x00,                 // LOGICAL_MINIMUM (0)
	0x26, 0xFF, 0x00,           // LOGICAL_MAXIMUM (255)
	LED_DEFINITION(1),
	LED_DEFINITION(2),
	LED_DEFINITION(3),
	LED_DEFINITION(4),
	LED_DEFINITION(5),
	LED_DEFINITION(6),
	LED_DEFINITION(7),
	LED_DEFINITION(8),
	LED_DEFINITION(9),
	0xc0                        // END_COLLECTION
};

Joystick_::Joystick_() {
	DynamicHIDSubDescriptor *node = new DynamicHIDSubDescriptor(hidReportDescriptor, sizeof(hidReportDescriptor), true);
	DynamicHID().AppendDescriptor(node);
	report[0] = 0; // Buttons
	report[1] = 0; // Buttons
	report[2] = 0x80; // X
	report[3] = 0x80; // Y
}

void Joystick_::setButton(uint8_t button, uint8_t value) {
	int index = button / 8;
	int bit = button % 8;
	if (bitRead(report[index], bit) != value) reportChanged = true;
	bitWrite(report[index], bit, value);
}

void Joystick_::sendState() {
	if (!reportChanged) return;
	DynamicHID().SendReport(JOYSTICK_REPORT_ID, report, sizeof(report));
	reportChanged = false;
}
