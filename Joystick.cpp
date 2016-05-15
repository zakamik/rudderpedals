/*
  Mouse.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Joystick.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptor[] PROGMEM = {

    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
   0x85, 0x04,                    // REPORT_ID (4) ???

    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x09, 0x33,                    //     USAGE (Rx)
    0x09, 0x34,                    //     USAGE (Ry)
    0x09, 0x35,                    //     USAGE (Rz)
    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
    0x16, 0x00, 0x80,              //     LOGICAL_MINIMUM (-32768)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0xc0                           // END_COLLECTION
  
};

//================================================================================
//================================================================================

Joystick_::Joystick_() {
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void Joystick_::move(int16_t x, int16_t y, int16_t z) {
    int16_t j[3];
    j[0] = x;
    j[1] = y;
    j[2] = z;
    //HID_SendReport(Report number, array of values in same order as HID descriptor, length)
    HID().SendReport(4, j, 6);
}
Joystick_ Joystick;

/*
Mouse_::Mouse_(void) : _buttons(0)
{
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void Mouse_::begin(void) 
{
}

void Mouse_::end(void) 
{
}

void Mouse_::click(uint8_t b)
{
	_buttons = b;
	move(0,0,0);
	_buttons = 0;
	move(0,0,0);
}

void Mouse_::move(signed char x, signed char y, signed char wheel)
{
	uint8_t m[4];
	m[0] = _buttons;
	m[1] = x;
	m[2] = y;
	m[3] = wheel;
	HID().SendReport(1,m,4);
}

void Mouse_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0,0,0);
	}
}

void Mouse_::press(uint8_t b) 
{
	buttons(_buttons | b);
}

void Mouse_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool Mouse_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0) 
		return true;
	return false;
}

Mouse_ Mouse;
*/
#endif
