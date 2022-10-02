#include "gprs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include "colors.h"

char stat[20] = { };

int GPRSConnect() {
	int ret;
	ret = OsWlLock();
	if (ret != 0) {
		OsLog(LOG_DEBUG, "FALHA GRPRS WLOCK: %d ", ret);
		return ret;
	}
	OsLog(LOG_DEBUG, "WLOCK: %d ", ret);

	// Status de carregamento
	XuiClearArea(XuiRootCanvas(), 169, 45, 64, 64);
	XuiCanvasDrawText(XuiRootCanvas(), 10, 135, 8, font, XUI_TEXT_NORMAL,
			COLOR_BLUE, "Iniciando...");

	/* Initialize wireless device.
	 * @parameter:
	 SimPin: um ponteiro para o PIN do cartão SIM. O comprimento de string válido é inferior a 50 bytes.
	 Pode ser NULL, o que significa que não precisa de senha.
	 * @return 0 se for bem-sucedido.
	 */

	OsWlInitEx(NULL, 100000, NULL, 0);
	if (ret != 0) {
		OsLog(LOG_DEBUG, "FALHA GRPRS WINIT: %d ", ret);
		return ret;
	}
	OsLog(LOG_DEBUG, "INIT: %d ", ret);
	//OsWlSwitchPower(1);

	// Status de carregamento
	XuiClearArea(XuiRootCanvas(), 20, 68, 200, 15);
	XuiCanvasDrawText(XuiRootCanvas(), 10, 152, 8, font, XUI_TEXT_NORMAL,
			COLOR_BLUE, "Obtendo sinal");

	/* Obtenha a força do sinal sem fio.
	 * @return 0 ~ 5: 0 significa nenhum sinal; 5 significa o sinal mais forte.
	 */;

	ret = OsWlGetSignal();
	OsLog(LOG_DEBUG, "GET SIGNAL %d", ret);

	if (ret >= 0) {
		// Status de carregamento
		XuiClearArea(XuiRootCanvas(), 20, 68, 200, 15);
		XuiCanvasDrawText(XuiRootCanvas(), 10, 168, 8, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, "Efetuando login");

		/* Login wireless network and set up a wireless link.
		 */

		ret = -1000;

		ret = OsWlLogin("zap.vivo.com.br", "vivo", "vivo", 0xFF, 20000, 10000,
				0);
		ret = OsWlLogin("claro.com.br", "claro", "claro", 0xFF, 20000, 10000,
				0);
		ret = OsWlLogin("gprs.oi.com.br", "oi", "oi", 0xFF, 20000, 10000, 0);
		ret = OsWlLogin("timbrasil.br", "tim", "tim", 0xFF, 20000, 10000, 0);
		OsLog(LOG_DEBUG, " ============== OsWlLogin [%d]", ret);

		XuiClearArea(XuiRootCanvas(), 8, 135, 65, 60);
		if (ret == 0) {
			OsLog(LOG_DEBUG, " ============== Conectado GPRS");
			XuiCanvasDrawText(XuiRootCanvas(), 11, 160, 9, font,
					XUI_TEXT_NORMAL, COLOR_BLUE, "CONECTADO");
		} else {
			OsLog(LOG_DEBUG, " ============== ERRO : %d", ret);
			memset(stat, 0, sizeof(stat));
			sprintf(stat, "ERRO [%d]", ret);
			XuiCanvasDrawText(XuiRootCanvas(), 11, 160, 8, font,
					XUI_TEXT_NORMAL, COLOR_BLUE, stat);
		}

	}

	return ret;
}

/*
 * GPRS disconnect.
 * @retorna 0 se a desconexão for bem-sucedida.
 */
int GPRSDesconnect() {

	int iRet;

	iRet = OsWlLock();
	XuiClearArea(XuiRootCanvas(), 8, 135, 60, 60);

	if (iRet != 0) {
		OsLog(LOG_DEBUG, "FALHA GRPRS WLOCK: %d ", iRet);
		return iRet;
	}
	// Faça logoff da rede sem fio e desconecte o link sem fio.
	iRet = OsWlLogout();
	OsLog(LOG_DEBUG, "Desconect GRPRS %d ", iRet);
	if (iRet == PPP_LOGOUTING) {
		iRet = OsWlLock();
		if (iRet == PPP_LOGOUTING) {
			iRet = PPP_LOGOUTING;
		} else {
			iRet = ERR_DEV_NOT_OPEN;
		}
	}

	return iRet;
}
