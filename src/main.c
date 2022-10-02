#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include "colors.h"
#include "menu.h"

char *KeyToStr(int key) {
	static char buf[24];
	switch (key) {
	case XUI_KEY0:
		return "0";
	case XUI_KEY1:
		return "1";
	case XUI_KEY2:
		return "2";
	case XUI_KEY3:
		return "3";
	case XUI_KEY4:
		return "4";
	case XUI_KEY5:
		return "5";
	case XUI_KEY6:
		return "6";
	case XUI_KEY7:
		return "7";
	case XUI_KEY8:
		return "8";
	case XUI_KEY9:
		return "9";
	case XUI_KEYCANCEL:
		return "CANCEL";
	case XUI_KEYCLEAR:
		return "CLEAR";
	case XUI_KEYENTER:
		return "ENTER";
	case XUI_KEYALPHA:
		return "Alpha";
	case XUI_KEYSHARP:
		return "#";
	case XUI_KEYF1:
		return "F1";
	case XUI_KEYF2:
		return "F2";
	case XUI_KEYF3:
		return "F3";
	case XUI_KEYF4:
		return "F4";
	case XUI_KEYFUNC:
		return "FUNC";
	case XUI_KEYUP:
		return "UP";
	case XUI_KEYDOWN:
		return "DOWN";
	case XUI_KEYMENU:
		return "MENU";
	default:
		snprintf(buf, sizeof(buf), "value %u", key);
		return buf;
	}
	return "";
}

static int GuiInit(int statusbar_height) {
	char value[24];
	char rotate_str[32];
	char statusbar_str[32];
	int ret;
	char *xui_argv[10];
	int xui_argc;

	ret = OsRegGetValue("ro.fac.lcd.rotate", value);
	if (ret > 0) {
		snprintf(rotate_str, sizeof(rotate_str), "ROTATE=%s", value);
	} else {
		strcpy(rotate_str, "ROTATE=0");
	}

	if (statusbar_height > 0) {
		snprintf(statusbar_str, sizeof(statusbar_str), "STATUSBAR=%d",
				statusbar_height);
	} else {
		strcpy(statusbar_str, "STATUSBAR=0");
	}

	xui_argv[0] = rotate_str;
	xui_argv[1] = statusbar_str;
	xui_argv[2] = NULL;
	xui_argc = 2;

	ret = XuiOpen(xui_argc, xui_argv);
	if (ret == XUI_RET_OK) {
		return RET_OK;
	} else {
		return -1;
	}
}

static void GuiDeinit(void) {
	XuiClose();
}

static void CrashReportInit(void) {
	signal(SIGILL, OsSaveCrashReport);
	signal(SIGABRT, OsSaveCrashReport);
	signal(SIGBUS, OsSaveCrashReport);
	signal(SIGFPE, OsSaveCrashReport);
	signal(SIGSEGV, OsSaveCrashReport);
	signal(SIGSTKFLT, OsSaveCrashReport);
	signal(SIGPIPE, OsSaveCrashReport);
}

void UpdateStatusbar(XuiFont *font) {
	CoresInit();
	static ST_TIME oldTime = { 0 };
	ST_TIME newTime;
	int clockX;
	int clockY;
	int clockWidth;
	int clockHeight;
	char buf[16];
	OsGetTime(&newTime);
	if (memcmp(&oldTime, &newTime, sizeof(oldTime)) != 0) {
		oldTime = newTime;
		snprintf(buf, sizeof(buf), "%02d:%02d:%02d", newTime.Hour,
				newTime.Minute, newTime.Second);
		clockHeight = 13;
		clockWidth = XuiTextWidth(font, clockHeight, "88:88:88");
		clockX = XUI_CENTER_X(0, XuiStatusbarCanvas()->width, clockWidth);
		clockY = XUI_CENTER_Y(0, XuiStatusbarCanvas()->height, clockHeight);
		XuiClearArea(XuiStatusbarCanvas(), clockX, 0, clockWidth,
				clockHeight + 2);
		XuiCanvasDrawText(XuiStatusbarCanvas(), clockX, clockY, clockHeight,
				font, XUI_TEXT_NORMAL, COLOR_WHITE, buf);

		OsLog(LOG_DEBUG, "BATTERY UPDATE");
		BatteryCheck();
	}
}

int main(int argc, char **argv) {
	CrashReportInit();
	OsLogSetTag("LOG S920");
	GuiInit(18);
	CoresInit();
	login();
	GuiDeinit();
	return 0;
}
