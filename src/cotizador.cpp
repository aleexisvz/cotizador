// SYSTEM INCLUDES
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<sstream>
#include<windows.h>
#include<locale>

// USER INCLUDES
#include "cotizador.h"

using namespace std;

// CONSTRUCTORES
Cotizador::Cotizador() {

}

// COTIZADORES
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

long Cotizador::cotizarTarjetaPVC() {
    // DECLARACIONES
    TarjetaPVC tarjeta;
    int sobCantidad = 0;
    long cvUnidad, cvTotal;
    float costoInicio;
    bool adicionales;

    system("cls");

    // Seteamos cantidad y doblefaz
    cout << "Ingrese la cantidad: "; cin >> tarjeta.cantidad;
    cout << "Ingrese si es doble faz (1 = Si, 0 = No): "; cin >> tarjeta.dobleFaz;
    cout << "Tiene adicionales? (1 = Si, 0 = No): "; cin >> adicionales;

    if(adicionales) {
        cout << "Cuantos campos variables tiene: "; cin >> tarjeta.campoVariable;
        cout << "Cuantas fotos variables tiene: "; cin >> tarjeta.fotoVariable;
        cout << "Tiene brillo sectorizado (1 = Si, 0 = No): "; cin >> tarjeta.brilloSectorizado;
        cout << "Tiene sector firmable (1 = Si, 0 = No): "; cin >> tarjeta.sectorFirmable;
        cout << "Tiene relieve (1 = Si, 0 = No): "; cin >> tarjeta.relieve;
    } else {
        tarjeta.campoVariable = 0;
        tarjeta.fotoVariable = 0;
        tarjeta.brilloSectorizado = 0;
        tarjeta.sectorFirmable = 0;
        tarjeta.relieve = 0;
    }

    // FILTROS
    if(tarjeta.cantidad < 10)                                           // < 10
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad - 1);
    else if(tarjeta.cantidad < 100)                                     // < 100
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad % 10);
    else if(tarjeta.cantidad < 1000)                                    // < 1000
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad % 100);
    else if(tarjeta.cantidad > 1000)                                  // < 100000
        sobCantidad = tarjeta.cantidad - (tarjeta.cantidad % 1000);

    string key = "U" + to_string(sobCantidad);

    if(tarjeta.dobleFaz)
        key += "DF";
    else
        key += "SF";

    cout << "Key: " << key << endl;
    
    string value = cargar("TarjetaPVC", key);
    istringstream(value) >> tarjeta.precio;

    // Calculamos el valor
    tarjeta.precio *= tarjeta.cantidad;

    // Agregamos el precio de los campos variables
    if(tarjeta.campoVariable > 0) {
        key = "U" + to_string(sobCantidad);

        value = cargar("CampoVariable", key);
        istringstream(value) >> cvUnidad;
        value = cargar("CostoInicio", "CampoVariable");
        istringstream(value) >> costoInicio;

        tarjeta.precio += (cvUnidad * tarjeta.campoVariable * tarjeta.cantidad) + costoInicio;
    }

    // Agregamos el precio de las fotos variables
    if(tarjeta.fotoVariable > 0) {
        key = "U" + to_string(sobCantidad);

        value = cargar("FotoVariable", key);
        istringstream(value) >> cvUnidad;
        value = cargar("CostoInicio", "FotoVariable");
        istringstream(value) >> costoInicio;

        tarjeta.precio += (cvUnidad * tarjeta.fotoVariable * tarjeta.cantidad) + costoInicio;
    }

    // Agregamos el precio del relieve
    if(tarjeta.relieve > 0) {
        key = "U" + to_string(sobCantidad);

        value = cargar("Relieve", key);
        istringstream(value) >> cvUnidad;
        value = cargar("CostoInicio", "Relieve");
        istringstream(value) >> costoInicio;

        tarjeta.precio += (cvUnidad * tarjeta.cantidad) + costoInicio;
    }

    // Agregamos el precio del brillo sectorizado
    if(tarjeta.brilloSectorizado > 0) {
        key = "U" + to_string(sobCantidad);

        value = cargar("BrilloSectorizado", key);
        istringstream(value) >> cvUnidad;
        value = cargar("CostoInicio", "BrilloSectorizado");
        istringstream(value) >> costoInicio;

        tarjeta.precio += (cvUnidad * tarjeta.cantidad) + costoInicio;
    }

    // Agregamos el precio del sector firmable
    if(tarjeta.sectorFirmable > 0) {
        key = "U" + to_string(sobCantidad);

        value = cargar("SectorFirmable", key);
        istringstream(value) >> cvUnidad;
        value = cargar("CostoInicio", "SectorFirmable");
        istringstream(value) >> costoInicio;

        tarjeta.precio += (cvUnidad * tarjeta.sectorFirmable * tarjeta.cantidad) + costoInicio;
    }

    // Separador de miles
    long long int precio_long = tarjeta.precio;
    locale loc("");
    const numpunct<char>& punct = use_facet<numpunct<char>>(loc);
    char separador = punct.thousands_sep();
    string formatted = to_string(precio_long);

    for (int i = formatted.size() - 3; i > 0; i -= 3) {
        formatted.insert(i, 1, separador);
    }

    // DEBUG - Mostramos el precio
    cout << "TOTAL: $" << formatted << endl;

    tarjeta = {tarjeta.cantidad, tarjeta.precio, tarjeta.dobleFaz};

    return tarjeta.precio;
}

// UTILES

// Seteamos los datos y devolvemos la estructura
Sticker Cotizador::crearSticker() {
    float costoPlancha, costoInicio, cantidad, cantidadPlancha;

    costoPlancha = stof(cargar("Sticker", "CostoPlancha"));
    costoInicio = stof(cargar("Sticker", "CostoInicio"));

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

string Cotizador::cargar(string _campo, string _key) {
    // Seteamos el path del archivo
    string path_actual = obtenerPath();
    size_t separador = path_actual.find_last_of("\\");
    string path = path_actual.substr(0, separador) + "\\INIT\\precios.ini";

    // Cargamos el archivo, y creamos la estructura
    INIFile file(path);
    INIStructure precios;

    // Leemos el archivo
    file.read(precios);
    
    return precios[_campo].get(_key);
}
