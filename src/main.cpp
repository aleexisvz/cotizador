// SYSTEM INCLUDES
#include<iostream>
#include<stdlib.h>
#include<string>

// USER INCLUDES
#include "cotizador.h"

// NAMESPACES
using namespace std;

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

int main() {
    string opciones[] = {"Cotizar Tarjetas PVC", "Cotizar sticker", "Salir"};
    string opcionesSticker[] = {"Cotizar Sticker", "Cotizar Sticker Vinilo", "Cotizar Sticker Metalizado", "Salir"};
    Cotizador cotizador = Cotizador();
    int size = sizeof(opciones) / sizeof(opciones[0]);
    bool showMenu = true;
    int opt = createMenu(opciones, size, showMenu);
    
    while(showMenu) {
        switch(opt) {
            case 1:
                cout << "Se cotizaran las tarjetas" << endl;
                showMenu = false;
                cotizador.cotizarTarjetaPVC();
                system("pause");
                break;
            case 2:
                cout << "Se cotizaran las etiquetas" << endl;
                showMenu = true;
                size = sizeof(opcionesSticker) / sizeof(opcionesSticker[0]);
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
