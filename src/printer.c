#include <osal.h>
#include <xui.h>
#include "printer.h"
#include "colors.h"
#include "imgBmp.h"

void PrinterText() {
	// Clear area for the a new message
	XuiClearArea(XuiRootCanvas(), 20, 168, 200, 20);
	XuiSetStatusbarIcon(6, "./res/print.png");

	//Variable responsible to check functions returns
	int iRet;
	iRet = OsPrnOpen(PRN_REAL, NULL );
	OsLog(LOG_DEBUG, " Open  [%d] ", iRet);

	iRet = OsInstallFile(NULL, "./res/robo.tar.gz", FILE_TYPE_SYS_LIB);
	if(iRet != RET_OK) {
		iRet = OsInstallFile(NULL, "./res/robo_sign.tar.gz", FILE_TYPE_SYS_LIB);
	}

	// Select print font
	OsPrnSetFont("RobotoMono-Regular.ttf");

	// Select print font size
	OsPrnSelectFontSize(20, 20, 20, 20);
	// Format and output string to print buffer

	// Set Gray
	OsPrnSetGray(4);

	OsPrnPrintf("\n \n");
	OsPrnPrintf("*******************\n");
	OsPrnPrintf("Teste de Impressão ");
	OsPrnPrintf("Teste de Acentuação");
	OsPrnPrintf("*******************\n");
	OsPrnPrintf("\n \n \n \n \n \n \n ");

	OsPrnStart();

	// Check the current status of printer. It only applies to physical printer
	iRet = OsPrnCheck();
	//OsLog(LOG_DEBUG, "PrnCheck == %d", iRet);

	OsLogSetTag("LOG_TESTE");
	OsPmGetEvent(0);
	OsLog(LOG_DEBUG, " ValidaFont  [%d] ", DEFAULTFONT );

	// Clear buffer
	OsPrnClrBuf();
	// Clear icon in status bar
	XuiSetStatusbarIcon(6, "./res");
	OsPrnClose();

}

void PrinterBitmap() {
	// Clear area for the a new message
	XuiClearArea(XuiRootCanvas(), 20, 168, 200, 20);
	XuiSetStatusbarIcon(6, "./res/print.png");

	//Variable responsible to check functions returns
	int iRet;
	iRet = OsPrnOpen(PRN_REAL, NULL );
	OsLog(LOG_DEBUG, " Open  [%d] ", iRet);

	OsPrnPrintf("\n \n");

	OsPrnPutImage(img_bmp);

	OsPrnPrintf("\n \n \n \n \n");

	OsPrnStart();

	// Check the current status of printer. It only applies to physical printer
	iRet = OsPrnCheck();
	OsLog(LOG_DEBUG, "PrnCheck == %d", iRet);

	// Clear buffer
	OsPrnClrBuf();
	// Clear icon in status bar
	XuiSetStatusbarIcon(6, "./res");
	OsPrnClose();

}
