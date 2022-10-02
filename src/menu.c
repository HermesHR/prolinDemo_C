#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include "printer.h"
#include "buttons.h"
#include "colors.h"
#include "login.h"
#include "main.h"

int BatteryCheck() {
	static int i = 0;
	char *batterys[] = { "./res/battery0c.png", "./res/battery25c.png",
			"./res/battery50c.png", "./res/battery75c.png",
			"./res/battery100c.png", };

	int ret = OsCheckBattery();
	if (ret >= 1 && ret <= 4) {
		XuiSetStatusbarIcon(7, batterys[ret]);
	} else if (ret == 6) {
		XuiSetStatusbarIcon(7, batterys[4]);
	} else if (ret == 5) {
		XuiSetStatusbarIcon(7, batterys[i]);
	}

	i++;
	if (i >= sizeof(batterys) / sizeof(batterys[0])) {
		i = 0;
	}
}

int ProjectHR(void) {
	CoresInit();
	UpdateStatusbar();
	XuiImg *imgBg;
	XuiColor colorTitleFg;
	XuiColor colorTitleBg;
	XuiColor colorMsgFg;
	int titleWidth;
	int titleHeight = 24;
	int titleX;
	int titleY;
	int key;
	char *title = "ProjectHR";
	char *bgfilename;
	char buf[128];

	if (XuiRootCanvas()->width >= 320) {
		bgfilename = "./res/bg_320x240.png";
	} else {
		bgfilename = "./res/bg_240x320.png";
	}

	/* load image background */
	imgBg = XuiImgLoadFromFile(bgfilename);

	XuiClearArea(XuiRootCanvas(), 0, 0, 300, 100);
	/* set background */
	colorTitleBg = COLOR_WHITE;
	XuiCanvasSetBackground(XuiRootCanvas(), XUI_BG_CENTER, imgBg, colorTitleBg);
	/* after SetBackground, the imgBg can free it */
	XuiImgFree(imgBg);
	imgBg = NULL;

	//set background title
	colorTitleBg.r = 0;
	colorTitleBg.g = 191;
	colorTitleBg.b = 255;
	colorTitleBg.a = 50;
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 0, XuiRootCanvas()->width, 40,
			colorTitleBg, 0, 1);
	titleWidth = XuiTextWidth(font, titleHeight, title);
	titleX = XUI_CENTER_X(0, XuiRootCanvas()->width, titleWidth);
	titleY = XUI_CENTER_Y(0, 40, titleHeight);

	//set background text
	colorTitleFg.r = 0xef;
	colorTitleFg.g = 0xef;
	colorTitleFg.b = 0xef;
	colorTitleFg.a = 0xff;
	XuiCanvasDrawText(XuiRootCanvas(), titleX, titleY, titleHeight, font,
			XUI_TEXT_NORMAL, colorTitleFg, title);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 295, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 297, XuiRootCanvas()->width, 40,
			colorTitleBg, 0, 1);

	XuiCanvasDrawText(XuiRootCanvas(), 13, 112, 10, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, "1. Printer");
	XuiCanvasDrawText(XuiRootCanvas(), 93, 112, 10, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, "2. Bitmap  ");
	XuiCanvasDrawText(XuiRootCanvas(), 175, 112, 10, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, "3. Wifi");
	XuiCanvasDrawText(XuiRootCanvas(), 13, 197, 10, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, "4. Gprs On");
	XuiCanvasDrawText(XuiRootCanvas(), 93, 197, 10, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, "5. Gprs Off");
	XuiCanvasDrawText(XuiRootCanvas(), 13, 282, 10, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, "7. Install");

	buttonsInit();

	/* loop & wait for keys */
	while (1) {
//		UpdateStatusbar();
//		if (!XuiHasKey()) {
//			continue;
//		}
		key = XuiGetKey();

		if (key == XUI_KEY1) {
			clearButtons();
			PrinterScreen();

		} else if (key == XUI_KEY2) {
			PrinterBitmap();

		} else if (key == XUI_KEY3) {
			clearButtons();
			WifiInit();

		} else if (key == XUI_KEY4) {
			GPRSConnect();

		} else if (key == XUI_KEY5) {
			GPRSDesconnect();

		} else if (key == XUI_KEY7) {
			clearButtons();
			login();

		} else if (key == XUI_KEYCANCEL) {
			ShutDown();
		}
	}

	/* third, free fonts */
	XuiDestroyFont(font);
	XuiDestroyFont(fontClock);

	return 0;

}

int ShutDown() {
	int ret;
	int ret2;
	int key;

	OsPmGetEvent(0); /*just connect app to os*/

	ret = OsRegSetValue("persist.sys.delayshutdown", "5");

	ret2 = OsRegSetValue("persist.sys.confirmshutdown", "1");

	key = XuiGetKey();
	if (key == XUI_KEYENTER) {
		ret = OsPmRequest(PM_FORBID_POWEROFF);
		OsPowerOff();  //let pos goto shutdown.
	}

	return 0;
}
