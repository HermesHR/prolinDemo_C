#include "wifi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include "colors.h"
#include "gprs.h"
#include "buttons.h"

ST_WifiApInfo *Aps;
ST_WifiApSet ApSet;
char essid[MAX_ESSID_LEN], bssid[MAX_BSSID_LEN];
char ip_address[20];
char passwd[16] = { 0 };
char text[60] = { 0 };
int idx, times, rssi, netQuantity;
wifiname;
wifi_active = 1;

void WifiInit() {
	XuiClearArea(XuiStatusbarCanvas(), 0, 0, 240, 50);
	int ret;
	// Limpa a tela.
	XuiClearArea(XuiRootCanvas(), 0, 0, XuiRootCanvas()->width,
			XuiRootCanvas()->height);
	int titleHeight = 24;
	char *title = "WI-FI";

	XuiClearArea(XuiRootCanvas(), 0, 0, XuiRootCanvas()->width,
			XuiRootCanvas()->height);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 0, XuiRootCanvas()->width, 40,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 41, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 297, XuiRootCanvas()->width, 40,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 295, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);

	// title
	XuiCanvasDrawText(XuiRootCanvas(), 90, 8, titleHeight, font,
			XUI_TEXT_NORMAL, COLOR_WHITE, title);

	// loading status
	XuiCanvasDrawText(XuiRootCanvas(), 40, 58, 16, font, XUI_TEXT_NORMAL,
			COLOR_BLUE, "Buscando... ");

	ret = procuraWifi();
	if (ret != 0) {
		sprintf(text, "Falha %d", ret);
		XuiClearArea(XuiRootCanvas(), 0, 50, XuiRootCanvas()->width,
				(XuiRootCanvas()->height) - 50);
		XuiCanvasDrawText(XuiRootCanvas(), 40, 58, 16, font, XUI_TEXT_NORMAL,
				COLOR_RED, text);
		int key = XuiGetKey();
		if (key == XUI_KEYCANCEL) {
			closeWifi();
		}
	}
}

/**
 * Digitalize os SSIDs na área
 * @return 0 se a busca estiver correta.
 */
int procuraWifi() {
	int ret;

	OsLog(LOG_DEBUG, "(METODO) INICIA E PROCURA WIFI");
	/*
	 * Abra o módulo WIFI
	 * @return 0 se bem-sucedido
	 */
	ret = OsWifiOpen();
	if (ret != 0) {
		OsLog(LOG_DEBUG, "(FALHA) Falha na abertura do Wifi %s", ret);
		return ret;
	}

	/**
	 * Verificar a rede existente
	 * @parameter * Aps: Um ponteiro para a estrutura ST_WifiApInfo, armazenando as informações de rede escaneadas.
	 * @return> = 0 Número de AP que foi encontrado
	 */
	netQuantity = 0;
	netQuantity = OsWifiScan(&Aps);
	if (netQuantity <= 0) {
		return netQuantity;
	}

//Clear the key buffer.
	XuiClearKey();
	defineRede();
	return 0;
}

/*
 * Lista e seleciona uma rede para uma conexão.
 */
void defineRede() {
	int i, key;
	// Variáveis usadas na seleção de rede
	char selectBuf[2] = { 0 };
	unsigned char mode = 0x24;
	XuiGetStrAttr strattr;
	strattr.fg = COLOR_WHITE;
	strattr.font = font;
	strattr.parent = XuiRootCanvas();
	strattr.size = 13;
	strattr.x = 130;
	strattr.y = 50;

	// Clear loading status
	XuiClearArea(XuiRootCanvas(), 0, 50, XuiRootCanvas()->width,
			(XuiRootCanvas()->height) - 100);

	/* Lista de redes encontradas .
	 */
	for (i = 0; i < netQuantity; i++) {
		if (i < 13) {
			// Primeira coluna.
			sprintf(text, " %d: %s", i + 1, Aps[i].Essid);
			XuiCanvasDrawText(XuiRootCanvas(), 10, (80 + (15 * i)), 13, font,
					XUI_TEXT_NORMAL, COLOR_WHITE, text);
		} else if (i == 13) {
			// Final da primeira coluna.
			XuiClearArea(XuiRootCanvas(), ((XuiRootCanvas()->width) / 2) - 5,
					75, (XuiRootCanvas()->width) / 2,
					(XuiRootCanvas()->height) - 100);
			XuiCanvasDrawRect(XuiRootCanvas(), ((XuiRootCanvas()->width) / 2),
					80, 1, 200, colorTitleBg, 0, 1);
			sprintf(text, " %d: %s", i + 1, Aps[i].Essid);
			XuiCanvasDrawText(XuiRootCanvas(),
					((XuiRootCanvas()->width) / 2) + 2, (15 * i) - 115, 13,
					font, XUI_TEXT_NORMAL, COLOR_WHITE, text);
		} else {
			// Segunda coluna.
			sprintf(text, " %d: %s", i + 1, Aps[i].Essid);
			XuiCanvasDrawText(XuiRootCanvas(),
					((XuiRootCanvas()->width) / 2) + 2, (15 * i) - 115, 13,
					font, XUI_TEXT_NORMAL, COLOR_WHITE, text);
		}
	}

	/** Selecione a rede
	 */
	while (1) {
		XuiClearArea(XuiRootCanvas(), 10, 50, 300, 14);
		XuiCanvasDrawText(XuiRootCanvas(), 10, 50, 13, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, "Selecione a Rede: ");
		selectBuf[0] = '\0';
		XuiGetString(strattr, selectBuf, mode, 1, 2);
		idx = atoi(selectBuf) - 1;
		if (idx <= netQuantity + 1) {
			sprintf(text, "Confirmar Rede %s ?", Aps[idx].Essid);
			XuiClearArea(XuiRootCanvas(), 10, 50, 300, 14);
			XuiCanvasDrawText(XuiRootCanvas(), 10, 50, 13, font,
					XUI_TEXT_NORMAL, COLOR_BLUE, text);
			key = XuiGetKey();
			if (key == XUI_KEYENTER) {
				idx = atoi(selectBuf) - 1;
				if (idx <= netQuantity + 1) {
					LoginWifi();
					break;
				}
			} else if (key == XUI_KEYCANCEL) {
				OsLog(LOG_DEBUG, "CANCELA?");
				XuiClearArea(XuiRootCanvas(), 10, 50, 300, 14);
				XuiCanvasDrawText(XuiRootCanvas(), 10, 50, 13, font,
						XUI_TEXT_NORMAL, COLOR_BLUE, "Selecione a Rede: ");
				key = XuiGetKey();
				if (key == XUI_KEYCANCEL) {
					closeWifi();
					break;
				}
			}
		} else {
			sprintf(text, "Escolha invalida");
			XuiClearArea(XuiRootCanvas(), 10, 50, 300, 14);
			XuiCanvasDrawText(XuiRootCanvas(), 10, 50, 13, font,
					XUI_TEXT_NORMAL, COLOR_BLUE, text);
			key = XuiGetKey();
			if (key == XUI_KEYCANCEL) {
				XuiClearArea(XuiRootCanvas(), 10, 50, 300, 14);
				XuiCanvasDrawText(XuiRootCanvas(), 10, 50, 13, font,
						XUI_TEXT_NORMAL, COLOR_BLUE, "Deseja sair? (Confirma)");
				key = XuiGetKey();
				if (key == XUI_KEYENTER) {
					closeWifi();
					break;
				}
			}
		}
	}
}

/*
 * Fazer Login na rede
 */
void LoginWifi() {
	int key;
//	unsigned char mode = 0x2c; for the pass type
	unsigned char mode = 0x14; //String type
	XuiGetStrAttr strattr;
	OsLog(LOG_DEBUG, "(METODO) LOGIN WIFI");

	XuiClearArea(XuiRootCanvas(), 0, 50, XuiRootCanvas()->width,
			(XuiRootCanvas()->height) - 50);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 97, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 297, XuiRootCanvas()->width, 40,
			colorTitleBg, 0, 1);
	XuiCanvasDrawRect(XuiRootCanvas(), 0, 295, XuiRootCanvas()->width, 1,
			colorTitleBg, 0, 1);

	XuiCanvasDrawText(XuiRootCanvas(), 30, 61, 18, font, XUI_TEXT_NORMAL,
			COLOR_WHITE, Aps[idx].Essid);

	strattr.fg = COLOR_WHITE;
	strattr.font = font;
	strattr.parent = XuiRootCanvas();
	strattr.size = 16;
	strattr.x = 80;
	strattr.y = 111;

	// entrada da senha
	if (Aps[idx].AuthMode != 1) {
		XuiCanvasDrawText(XuiRootCanvas(), 15, 111, 18, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, "Senha: ");
		XuiCanvasDrawText(XuiRootCanvas(), 30, 150, 16, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, "Insira a Senha");

		XuiGetString(strattr, passwd, mode, 4, 16);
		XuiClearArea(XuiRootCanvas(), 10, 150, XuiRootCanvas()->width, 100);
		XuiCanvasDrawText(XuiRootCanvas(), 30, 150, 16, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, "Confirmar Senha?");
		key = XuiGetKey();
		if (key == XUI_KEYCANCEL) {
			XuiClearArea(XuiRootCanvas(), 10, 150, 300, 100);
			XuiCanvasDrawText(XuiRootCanvas(), 30, 150, 16, font,
					XUI_TEXT_NORMAL, COLOR_BLUE, "Insira a Senha");
			key = XuiGetKey();
			if (key == XUI_KEYCANCEL) {
				defineRede();
			}
		} else {
			completaLogin();
		}
	} else {
		completaLogin();
	}
}

void completaLogin() {

	XuiClearArea(XuiRootCanvas(), 10, 150, 300, 100);
	XuiCanvasDrawText(XuiRootCanvas(), 10, 150, 14, font, XUI_TEXT_NORMAL,
			COLOR_BLUE, "Efetuando conexao ...");

	int retCon = ConectaWifi();
	if (retCon == ERR_NET_PASSWD || retCon == -1003) {
		XuiClearArea(XuiRootCanvas(), 10, 150, 300, 100);
		XuiCanvasDrawText(XuiRootCanvas(), 30, 150, 16, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, "Senha invalida");
		XuiGetKey();
		LoginWifi();
	} else if (retCon == 0) {
		wifiname = Aps[idx].Essid;
		GPRSDesconnect();
		sprintf(text, "Conectado a %s", wifiname);
		XuiClearArea(XuiRootCanvas(), 10, 150, 300, 100);
		XuiCanvasDrawText(XuiRootCanvas(), 30, 150, 15, font, XUI_TEXT_NORMAL,
				COLOR_GREEN, text);
		XuiCanvasDrawText(XuiRootCanvas(), 10, 170, 13, font, XUI_TEXT_NORMAL,
				COLOR_BLUE, " Pressione um botao para Voltar");
		XuiGetKey();
		closeWifi();
	} else {
		sprintf(text, "Falha %d", retCon);
		XuiClearArea(XuiRootCanvas(), 10, 150, 300, 100);
		XuiCanvasDrawText(XuiRootCanvas(), 30, 150, 16, font, XUI_TEXT_NORMAL,
				COLOR_RED, text);
		XuiGetKey();
		defineRede();
	}
}

/*
 *	Conexão na rede selecionada.
 * @return 0 se a conexão for bem-sucedida.
 */
int ConectaWifi() {
	int ret;
	OsLog(LOG_DEBUG, "(METODO) CONECTA WIFI");
	// Put the selected network information in ApSet
	strcpy(ApSet.Essid, Aps[idx].Essid);
	strcpy(ApSet.Bssid, Aps[idx].Bssid);
	ApSet.Channel = Aps[idx].Channel;
	ApSet.Mode = Aps[idx].Mode;
	ApSet.SecMode = Aps[idx].SecMode;

	// Doing the authentication
	if (Aps[idx].AuthMode == AUTH_NONE_WEP) {
		ApSet.AuthMode = AUTH_NONE_WEP_SHARED; //AUTH_NONE_WEP
		ApSet.KeyUnion.WepKey.Idx = 0;
		strcpy(ApSet.KeyUnion.WepKey.Key[0], passwd);
		ApSet.KeyUnion.WepKey.KeyLen = strlen(ApSet.KeyUnion.WepKey.Key[0]);
	} else {
		ApSet.AuthMode = Aps[idx].AuthMode;
		strcpy(ApSet.KeyUnion.PskKey.Key, passwd);
		ApSet.KeyUnion.PskKey.KeyLen = strlen(ApSet.KeyUnion.PskKey.Key);
	}

	/*
	 * Conecte-se a uma rede sem fio especificada.
	 * @parameters:
	 ApSet: Um ponteiro para a estrutura ST_WifiApSet, armazenando os atributos da rede sem fio especificada
	 Tempo limite: 0 a 3600000
	 * @return 0 se a conexão for bem-sucedida.
	 */
	ret = OsWifiConnect(&ApSet, 5000);
	OsLog(LOG_DEBUG, "CONEXAO WIFI === %d ===", ret);
	// Clear the password utilized.
	passwd[0] = '\0';

	//	ret = OsWlGetSignal();

	/* Usado para enviar dados por WiFi, se necessário.
	 */
	OsNetStartDhcp(NET_LINK_WIFI);
	return ret;
}

/*
 * Desconecte a conexão WIFI.
 * @return 0 se estiver desconectado.
 */

int DesconectaWifi() {
	int ret;

	OsLog(LOG_DEBUG, "(METODO) DESCONECTA WIFI");
	// Desconectar da rede atual.
	ret = OsWifiDisconnect();
	if (ret != 0) {
		return ret;
	}
	// Encerrar o uso do mudulo WIfi.
	OsWifiClose();

	return 0;
}

void closeWifi() {
	XuiClearArea(XuiRootCanvas(), 10, 150, 300, 100);
	ProjectHR();
	OsLog(LOG_DEBUG, "CLOSE WIFI");
}

