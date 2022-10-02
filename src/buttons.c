#include <stdio.h>
#include <stdlib.h>
#include <osal.h>
#include <xui.h>
#include <colors.h>

XuiWindow *btnPrinter;
XuiWindow *btnBitmap;
XuiWindow *btnGPRS_1;
XuiWindow *btnGPRS_2;
XuiWindow *btnWifi;
XuiWindow *btnConfig;

XuiButtonStat statNormal;
XuiButtonStat statPressed;

XuiImg *imgPrinter;
XuiImg *imgBmp;
XuiImg *imgWifi;
XuiImg *imgCgprs;
XuiImg *imgDgprs;
XuiImg *imgConfig;

void buttonsInit() {
	// load image
	imgPrinter = XuiImgLoadFromFile("./res/print02.png");
	imgBmp = XuiImgLoadFromFile("./res/bmp.png");
	imgWifi = XuiImgLoadFromFile("./res/wifi.png");
	imgCgprs = XuiImgLoadFromFile("./res/gprs.png");
	imgDgprs = XuiImgLoadFromFile("./res/gprs.png");
	imgConfig = XuiImgLoadFromFile("./res/config.png");

	//Create buttons
	btnPrinter = XuiCreateButton(XuiRootCanvas(), 8, 45, 64, 64);
	btnBitmap = XuiCreateButton(XuiRootCanvas(), 89, 45, 64, 64);
	btnGPRS_1 = XuiCreateButton(XuiRootCanvas(), 9, 130, 64, 64);
	btnGPRS_2 = XuiCreateButton(XuiRootCanvas(), 89, 130, 64, 64);
	btnWifi = XuiCreateButton(XuiRootCanvas(), 170, 45, 64, 64);
	btnConfig = XuiCreateButton(XuiRootCanvas(), 8, 215, 64, 64);

	memset(&statNormal, 0, sizeof(statNormal));

	statNormal.btn_bg.r = 0;
	statNormal.btn_bg.g = 191;
	statNormal.btn_bg.b = 255;
	statNormal.btn_bg.a = 50;
	statNormal.btn_round = 0;
	statPressed = statNormal;
	statPressed.btn_bg.r = 0;
	statPressed.btn_bg.g = 191;
	statPressed.btn_bg.b = 255;
	statPressed.btn_bg.a = 80;

	/* Print Button */
	XuiButtonSetStat(btnPrinter, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnPrinter, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgPrinter;
	//Action Button
	XuiButtonSetKey(btnPrinter, XUI_KEY1);
	//Show button in screen
	XuiShowWindow(btnPrinter, 1, 0);

	/* Bitmap Button */
	XuiButtonSetStat(btnBitmap, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnBitmap, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgBmp;
	//Action Button
	XuiButtonSetKey(btnBitmap, XUI_KEY2);
	//Show button in screen
	XuiShowWindow(btnBitmap, 1, 0);

	/* GPRS ON */
	XuiButtonSetStat(btnGPRS_1, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnGPRS_1, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgCgprs;
	//Action Button
	XuiButtonSetKey(btnGPRS_1, XUI_KEY4);
	//Show button in screen
	XuiShowWindow(btnGPRS_1, 1, 0);

	/* GPRS OFF */
	XuiButtonSetStat(btnGPRS_2, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnGPRS_2, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgDgprs;
	//Action Button
	XuiButtonSetKey(btnGPRS_2, XUI_KEY5);
	//Show button in screen
	XuiShowWindow(btnGPRS_2, 1, 0);

	/* WIFI */
	XuiButtonSetStat(btnWifi, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnWifi, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgWifi;
	//Action Button
	XuiButtonSetKey(btnWifi, XUI_KEY3);
	//Show button in screen
	XuiShowWindow(btnWifi, 1, 0);

	/* Config */
	XuiButtonSetStat(btnConfig, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnConfig, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgConfig;
	//Action Button
	XuiButtonSetKey(btnConfig, XUI_KEY7);
	//Show button in screen
	XuiShowWindow(btnConfig, 1, 0);

}

void printerButtonsInit() {
	btnPrinter = XuiCreateButton(XuiRootCanvas(), 8, 45, 64, 64);
	btnBitmap = XuiCreateButton(XuiRootCanvas(), 89, 45, 64, 64);

	memset(&statNormal, 0, sizeof(statNormal));

	statNormal.btn_bg.r = 0;
	statNormal.btn_bg.g = 191;
	statNormal.btn_bg.b = 255;
	statNormal.btn_bg.a = 50;
	statNormal.btn_round = 0;
	statPressed = statNormal;
	statPressed.btn_bg.r = 0;
	statPressed.btn_bg.g = 191;
	statPressed.btn_bg.b = 255;
	statPressed.btn_bg.a = 80;

	/* Print Button */
	XuiButtonSetStat(btnPrinter, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnPrinter, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgPrinter;
	//Action Button
	XuiButtonSetKey(btnPrinter, XUI_KEY1);
	//Show button in screen
	XuiShowWindow(btnPrinter, 1, 0);

	/* Bitmap Button */
	XuiButtonSetStat(btnBitmap, XUI_BTN_NORMAL, &statNormal);
	XuiButtonSetStat(btnBitmap, XUI_BTN_PRESSED, &statPressed);
	statNormal.img = imgBmp;
	//Action Button
	XuiButtonSetKey(btnBitmap, XUI_KEY2);
	//Show button in screen
	XuiShowWindow(btnBitmap, 1, 0);
}

void clearButtons() {
	XuiDestroyWindow(btnPrinter);
	XuiDestroyWindow(btnBitmap);
	XuiDestroyWindow(btnGPRS_1);
	XuiDestroyWindow(btnGPRS_2);
	XuiDestroyWindow(btnWifi);
	XuiDestroyWindow(btnConfig);
}

void clearPrinterButtons() {
	XuiDestroyWindow(btnPrinter);
	XuiDestroyWindow(btnBitmap);
}
