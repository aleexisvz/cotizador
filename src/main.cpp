// SYSTEM INCLUDES
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<Windows.h>
//#include<WinUser.h>
#include<sstream>

// USER INCLUDES
#include "cotizador.h"

// NAMESPACES
using namespace std;

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0

// Copia un texto al portapapeles y devuelve true si se pudo copiar
bool CopyToClipboard(const std::wstring &text) {
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, (text.length() + 1) * sizeof(wchar_t));
        if (clipbuffer) {
            wchar_t *buffer = static_cast<wchar_t*>(GlobalLock(clipbuffer));
            if (buffer) {
                wcscpy(buffer, text.c_str());
                GlobalUnlock(clipbuffer);
                SetClipboardData(CF_UNICODETEXT, clipbuffer);
                CloseClipboard();
                return true;
            }
        }
        CloseClipboard();
    }
    return false;
}

// Genera un menu con un arreglo de opciones
int createMenu(string* _opciones, int _size, bool& _showMenu) {
    int opt = 0;

    while(_showMenu) {
        system("cls");

        // Mostramos el menu
        for(int i = 0; i < _size; i++) {
            cout << i + 1 << ". " << _opciones[i] << endl;
        }

        cout << "\nIngrese una opcion: "; cin >> opt;

        return opt;
    }
}

// Convierte un string a wstring
wstring stringToWstring(string _string) {
    wstring ws;
    ws.assign(_string.begin(), _string.end());

    return ws;
}

// Genera el texto a copiar al portapapeles
string createText(TarjetaPVC _tarjeta) {
    Cotizador cotizador;
    string textToCopy = to_string(_tarjeta.cantidad) + "u. Tarjetas PVC ";
    
    if(_tarjeta.dobleFaz) {
        textToCopy += "DOBLE FAZ ";
    } else {
        textToCopy += "SIMPLE FAZ ";
    }

    if(_tarjeta.campoVariable != 0)
        textToCopy += " + " + to_string(_tarjeta.campoVariable) + " Campos Variables";

    if(_tarjeta.fotoVariable != 0)
        textToCopy += " + " + to_string(_tarjeta.fotoVariable) + " Fotos Variables";

    if(_tarjeta.brilloSectorizado != 0)
        textToCopy += " + Brillo Sectorizado";

    if(_tarjeta.relieve != 0)
        textToCopy += " + Relieve";

    if(_tarjeta.sectorFirmable != 0)
        textToCopy += " + Sector Firmable";

    textToCopy += " $" + cotizador.formatear(_tarjeta.precio);
    
    return textToCopy;
}

int main() {
    // DECLARACIONES MENU
    string opciones[] = {"Cotizar Tarjetas PVC", "Cotizar sticker (EN DESARROLLO)", "Salir"};
    string opcionesSticker[] = {"Cotizar Sticker", "Cotizar Sticker Vinilo", "Cotizar Sticker Metalizado", "Salir"};
    Cotizador cotizador = Cotizador();
    TarjetaPVC tarjeta;

    int size = sizeof(opciones) / sizeof(opciones[0]);
    bool showMenu = true;
    int opt = createMenu(opciones, size, showMenu);
    
    // DECLARACIONES CopyToClipboard
    string textToCopy;

    while(showMenu) {
        switch(opt) {
            case 1:
                showMenu = false;
                system("cls");

                tarjeta = cotizador.cotizarTarjetaPVC();

                // Crear texto a copiar
                CopyToClipboard(stringToWstring(createText(tarjeta)));
                
                system("pause");
                break;
            case 2:
                cout << "Se cotizaran las etiquetas (EN DESARROLLO)" << endl;
                showMenu = true;
                size = sizeof(opcionesSticker) / sizeof(opcionesSticker[0]);

                // Mostramos el menu de stickers
                opt = createMenu(opcionesSticker, size, showMenu);
                
                switch(opt) {
                    case 1:
                        cout << "Se cotizaran los stickers" << endl;
                        cotizador.cotizarSticker();
                        break;
                    case 2:
                        cout << "Se cotizaran los stickers vinilo" << endl;
                        cotizador.cotizarStickerVinilo();
                        break;
                    case 3:
                        cout << "Se cotizaran los stickers metalizado" << endl;
                        cotizador.cotizarStickerMetalizado();
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                        system("pause");
                        opt = createMenu(opcionesSticker, size, showMenu);
                        break;
                }

                system("pause");
                break;
            case 3:
                cout << "Saliendo..." << endl;
                showMenu = false;
                break;
            default:
                cout << "Opcion no valida" << endl;
                system("pause");
                opt = createMenu(opciones, size, showMenu);
                break;
        }
    }

    return 0;
}
