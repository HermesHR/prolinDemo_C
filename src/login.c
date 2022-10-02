#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "login.h"
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include "main.h"
#include "colors.h"

void login() {
	CoresInit();
	XuiClearArea(XuiStatusbarCanvas(), 60, 0, 240, 50);
	int titleHeight = 24;
	char *title = "LOGIN";
	// Variáveis usadas nas credenciais de entrada.
	char text[30] = { 0 };
	int key;
	unsigned char mode;
	unsigned char modePass;
	XuiGetStrAttr strattr;
	char Logbuf[15] = { 0 };
	char Passbuf[15] = { 0 };
	char LogbufCompar[10] = { 'H', 'E', 'R', 'M', 'E', 'S' };
	char PassbufCompar[10] = { '1', '5', '0', '1' };
	int posLogon = XUI_CENTER_Y(0, 40, 24);
	XuiWindow *rootCanvas;
	rootCanvas = XuiRootCanvas();

	mode = 0x14; // Alfanum�rico
	modePass = 0x2c; // Num�rico apenas
	strattr.fg = COLOR_WHITE;
	strattr.font = font;
	strattr.parent = XuiRootCanvas();
	strattr.size = 18;
	strattr.x = 80;
	strattr.y = posLogon + 53;

	// Limpar tela
	XuiClearArea(XuiRootCanvas(), 0, 0, XuiRootCanvas()->width,
			XuiRootCanvas()->height);
	// Desenhe o retângulo do título e as linhas horizontais.
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 0, XuiRootCanvas()->width, 38,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 39, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 97, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 297, XuiRootCanvas()->width, 40,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 295, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);
	// title
	XuiCanvasDrawText(XuiRootCanvas(), 80, 8, titleHeight, font,
			XUI_TEXT_NORMAL, COLOR_WHITE, title);
	// credentials label.
	XuiCanvasDrawText(XuiRootCanvas(), 15, 61, 18, font, XUI_TEXT_NORMAL,
			COLOR_BLUE, "Login: ");
	XuiCanvasDrawText(XuiRootCanvas(), 15, 111, 18, font, XUI_TEXT_NORMAL,
			COLOR_BLUE, "Senha: ");

	while (1) {
		XuiClearArea(rootCanvas, 30, 150, rootCanvas->width, 100);
		memset(Logbuf, 0, sizeof Logbuf);
		XuiGetString(strattr, Logbuf, mode, 3, 10);
		sprintf(text, "Confirme para a Senha");
		XuiCanvasDrawText(rootCanvas, 30, 150, 16, font, 0, COLOR_BLUE, text);

		// get key input
		key = XuiGetKey();
		if (key == XUI_KEYENTER) {
			XuiClearArea(rootCanvas, 30, 150, rootCanvas->width, 100);
			strattr.y = posLogon + 103;
			memset(Passbuf, 0, sizeof Passbuf);
			XuiGetString(strattr, Passbuf, modePass, 3, 10);

			sprintf(text, "Confirmar Logon?");
			XuiCanvasDrawText(rootCanvas, 30, 150, 16, font, 0, COLOR_BLUE,
					text);
			key = XuiGetKey();

			if (key == XUI_KEYENTER) {
				int r;
				int logVerify = 0;
				int passVerify = 0;
				for (r = 0; r < sizeof(LogbufCompar); r++) {
					if (Logbuf[r] == LogbufCompar[r]) {
						logVerify++;
					}
				}

				for (r = 0; r < sizeof(PassbufCompar); r++) {
					if (Passbuf[r] == PassbufCompar[r]) {
						passVerify++;
					}
				}

				if ((logVerify == 10) && (passVerify == 10)) {
					OsLog(LOG_DEBUG, " OPEN CONFIG ");
					XuiClearArea(rootCanvas, 30, 150, rootCanvas->width, 100);
					sprintf(text, "Conectado com Sucesso");
					XuiCanvasDrawText(rootCanvas, 30, 150, 16, font, 0,
							COLOR_BLUE, text);
					OsSleep(150);
					ProjectHR();
					break;
				} else {
					XuiClearArea(rootCanvas, 30, 150, rootCanvas->width, 100);
					sprintf(text, "Acesso Negado");
					XuiCanvasDrawText(rootCanvas, 30, 150, 16, font, 0,
							COLOR_BLUE, text);
					XuiGetKey();
					OsLog(LOG_DEBUG, " CLOSE LOGIN ");
					login();
					break;
				}
			}

		} else if (key == XUI_KEYCANCEL) {
			OsLog(LOG_DEBUG, " ==== CLOSE LOGIN ==== ");
			login();
			break;
		}
	}
}
