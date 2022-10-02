#include <osal.h>
#include <xui.h>
#include "printer.h"
#include "colors.h"
#include "buttons.h"
#include "menuPrinter.h"

void PrinterScreen() {
	CoresInit();
	XuiImg *imgBg;
	XuiColor colorTitleFg;
	XuiColor colorTitleBg;
	int titleWidth;
	int titleHeight = 24;
	int titleX;
	int titleY;
	int key;
	char buf[128];
	char *title = "Menu Printer";
	char *bgfilename;

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

	printerButtonsInit();

	while (1) {
		key = XuiGetKey();

		if (key == XUI_KEY1) {
			PrinterText();

		} else if (key == XUI_KEY2) {
			PrinterBitmap();

		} else if (key == XUI_KEYCANCEL) {
			clearPrinterButtons();
			ProjectHR();
		}
	}
}

