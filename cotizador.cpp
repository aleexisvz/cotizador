// SYSTEM INCLUDES
#include<iostream>
#include<stdlib.h>
#include<cmath>

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

int main() {
    Cotizador cotizador = Cotizador(20.0, 21.0, 100);

    cout << cotizador.cotizarStickerMetalizado() << endl;

    system("pause");
    return 0;
}
