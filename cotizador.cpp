// SYSTEM INCLUDES
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<sstream>
#include<windows.h>

// USER INCLUDES
#include "cotizador.h"

using namespace std;

// CONSTRUCTORES
Cotizador::Cotizador() {
    cotizacionAnterior = 0.0;
    cotizacionActual = 0.0;
    cantidad = 0;
    precio = 0.0;
}

Cotizador::Cotizador(float _cotizacionAnterior, float _cotizacionActual, int _cantidad) {
    cotizacionAnterior = _cotizacionAnterior;
    cotizacionActual = _cotizacionActual;
    cantidad = _cantidad;
    precio = cotizarCortes(cotizacionAnterior, cotizacionActual, cantidad);
}

// GETTERS
float Cotizador::getCotizacionAnterior() { return cotizacionAnterior; }
float Cotizador::getCotizacionActual() { return cotizacionActual; }
int Cotizador::getCantidad() { return cantidad; }
float Cotizador::getPrecio() { return precio; }

// SETTERS
void Cotizador::setCotizacionAnterior(float _cotizacionAnterior) { cotizacionAnterior = _cotizacionAnterior; }
void Cotizador::setCotizacionActual(float _cotizacionActual) { cotizacionActual = _cotizacionActual; }
void Cotizador::setCantidad(int _cantidad) { cantidad = _cantidad; }
void Cotizador::setPrecio(float _precio) { precio = _precio; }

// METODOS
float Cotizador::cotizarCortes(float _cotizacionAnterior, float _cotizacionActual, int _cantidad) {
    cotizacionAnterior = _cotizacionAnterior;
    cotizacionActual = _cotizacionActual;
    cantidad = _cantidad;
    float cotizacion = ((cotizacionActual / cotizacionAnterior) * 1.05) * 319;

    return round(cotizacion * _cantidad);
}

float Cotizador::cotizarSticker() {
    float precio = 0.0;

    Sticker _sticker = crearSticker();

    // FORMULA
    precio = round((_sticker.cantidad / _sticker.cantidadPlancha + 1) * _sticker.costoPlancha * 10);
    precio = round(precio / 10 + _sticker.costoInicio);

    // REDONDEO
    int unidad = static_cast<int>(precio);
    unidad = unidad % 10;

    if(unidad >= 5){
        precio -= unidad;
        precio += 10;
    }
    else
        precio -= unidad;

    return precio;
}

float Cotizador::cotizarStickerVinilo() {
    float precio = 0.0;
    float precioPapel = cotizarSticker();
    
    // FORMULA
    precio = (precioPapel * 1.5 * 10) / 10;

    return precio;
}

float Cotizador::cotizarStickerMetalizado() {
    float precio = 0.0;
    float precioPapel = cotizarSticker();
    
    // FORMULA
    precio = (precioPapel * 2 * 10) / 10;

    return precio;
}

// Seteamos los datos y devolvemos la estructura
Sticker Cotizador::crearSticker() {
    float costoPlancha, costoInicio, cantidad, cantidadPlancha;

    cout << "Ingrese el costo de la plancha: "; cin >> costoPlancha;
    cout << "Ingrese el costo de inicio: "; cin >> costoInicio;
    cout << "Ingrese la cantidad: "; cin >> cantidad;
    cout << "Ingrese la cantidad por plancha: "; cin >> cantidadPlancha;

    Sticker sticker = {costoPlancha, costoInicio, cantidad, cantidadPlancha};

    return sticker;
}

string Cotizador::obtenerPath() {
    // Obtenemos el path actual
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);

    return buffer;
}

long Cotizador::cotizarTarjetaPVC() {
    // Seteamos el path del archivo
    string path = obtenerPath() + string("\\INIT\\precios.ini");

    TarjetaPVC tarjeta = {0, 0.0, 0};

    int sobCantidad = 0;

    // Seteamos cantidad y doblefaz
    cout << "Ingrese la cantidad: "; cin >> tarjeta.cantidad;
    cout << "Ingrese si es doble faz (1 = Si, 0 = No): "; cin >> tarjeta.dobleFaz;

    // FILTROS (EN PROCESO)
    if(tarjeta.cantidad < 10)                                           // < 10
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad - 1);
    else if(tarjeta.cantidad < 100)                                     // < 100
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad % 10);
    else if(tarjeta.cantidad < 1000)                                    // < 1000
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad % 100);
    else if(tarjeta.cantidad < 100000)                                    // < 2000
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad % 10000);

    // DEBUG - Mostramos el sobrante de la cantidad y cantidad
    cout << "Restos de cantidad: " << sobCantidad << endl;
    cout << "Cantidad: " << tarjeta.cantidad << endl;

    string key = "U" + to_string(sobCantidad);

    if(tarjeta.dobleFaz)
        key += "DF";
    else
        key += "SF";

    // DEBUG - Mostramos la key
    cout << "Key: " << key << endl;
    
    // Cargamos el archivo, y creamos la estructura
    INIFile file(path);
    INIStructure precios;

    // Leemos el archivo
    file.read(precios);
    
    string value = precios["TarjetaPVC"].get(key);

    // DEBUG - Mostramos si obtuvo el valor
    cout << value << endl;

    istringstream(value) >> tarjeta.precio;

    // Calculamos el valor
    tarjeta.precio *= tarjeta.cantidad;

    // DEBUG - Mostramos el precio
    cout << tarjeta.precio << endl;

    tarjeta = {tarjeta.cantidad, tarjeta.precio, tarjeta.dobleFaz};

    return tarjeta.precio;
}

int main() {
    Cotizador cotizador = Cotizador(20.0, 21.0, 100);

    cotizador.cotizarTarjetaPVC();

    system("pause");
    return 0;
}
