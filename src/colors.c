#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include "menu.h"

void CoresInit() {
	COLOR_GREEN.b = 0;
	COLOR_GREEN.g = 0xcc;
	COLOR_GREEN.r = 0;
	COLOR_GREEN.a = 0xff;

	COLOR_BLUE.b = 0xff;
	COLOR_BLUE.g = 0;
	COLOR_BLUE.r = 0;
	COLOR_BLUE.a = 0xff;

	COLOR_BLACK.b = 0;
	COLOR_BLACK.g = 0;
	COLOR_BLACK.r = 0;
	COLOR_BLACK.a = 0xff;

	COLOR_TRANSPARENT.b = 0;
	COLOR_TRANSPARENT.g = 0;
	COLOR_TRANSPARENT.r = 0;
	COLOR_TRANSPARENT.a = 0;

	COLOR_WHITE.b = 0xff;
	COLOR_WHITE.g = 0xff;
	COLOR_WHITE.r = 0xff;
	COLOR_WHITE.a = 0xff;

	COLOR_YELLOW.b = 0;
	COLOR_YELLOW.g = 0xff;
	COLOR_YELLOW.r = 0xff;
	COLOR_YELLOW.a = 0xff;

	COLOR_YELLOW_ALPHA.b = 0;
	COLOR_YELLOW_ALPHA.g = 0xff;
	COLOR_YELLOW_ALPHA.r = 0xff;
	COLOR_YELLOW_ALPHA.a = 0x7f;

	COLOR_YELLOW_ALPHA2.b = 0;
	COLOR_YELLOW_ALPHA2.g = 0xff;
	COLOR_YELLOW_ALPHA2.r = 0xff;
	COLOR_YELLOW_ALPHA2.a = 0x00;

	COLOR_GRAY.b = 0xF0;
	COLOR_GRAY.g = 0xF0;
	COLOR_GRAY.r = 0xF0;
	COLOR_GRAY.a = 0xff;

	COLOR_GRAY_ALPHA.b = 0xF0;
	COLOR_GRAY_ALPHA.g = 0xF0;
	COLOR_GRAY_ALPHA.r = 0xF0;
	COLOR_GRAY_ALPHA.a = 0x00;

	COLOR_TESTE.r = 0;
	COLOR_TESTE.g = 191;
	COLOR_TESTE.b = 255;
	COLOR_TESTE.a = 50;

	COLOR_GREEN_LIGHT.b = 0x7f;
	COLOR_GREEN_LIGHT.g = 0xff;
	COLOR_GREEN_LIGHT.r = 0x00;
	COLOR_GREEN_LIGHT.a = 0xff;

	COLOR_RED.b = 0;
	COLOR_RED.g = 0;
	COLOR_RED.r = 0xff;
	COLOR_RED.a = 0xff;

	COLOR_GRAY_LOW.b = 124;
	COLOR_GRAY_LOW.g = 124;
	COLOR_GRAY_LOW.r = 124;
	COLOR_GRAY_LOW.a = 0xff;

	COLOR_GRAY_BORDER.b = 124;
	COLOR_GRAY_BORDER.g = 124;
	COLOR_GRAY_BORDER.r = 124;
	COLOR_GRAY_BORDER.a = 0x7f;

	font = XuiCreateFont("/usr/font/paxfont.ttf", 0, 0);
	fontClock = XuiCreateFont("/usr/font/paxfont.ttf", 0, 0);
}
