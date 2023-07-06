#ifndef COTIZADOR_H
#define COTIZADOR_H

// USER INCLUDES
#include "date.h"
#include "ini.h"

// SYSTEM INCLUDES

// NAMESPACES
using namespace std;
using namespace mINI;

struct PrecioDolar {
    Date fecha;
    float precio;
};

struct Sticker {
    float costoPlancha, costoInicio, cantidad, cantidadPlancha;
};

struct TarjetaPVC {
    int cantidad, campoVariable, fotoVariable, relieve, brilloSectorizado, sectorFirmable;
    long precio;
    bool dobleFaz;
};

class Cotizador {
    private:
        float cotizacionAnterior;
        float cotizacionActual;
        int cantidad;
        float precio;
    public:
        // CONSTRUCTORES
        Cotizador();
        Cotizador(float, float, int);

        // GETTERS
        float getCotizacionAnterior();
        float getCotizacionActual();
        int getCantidad();
        float getPrecio();

        // SETTERS
        void setCotizacionAnterior(float);
        void setCotizacionActual(float);
        void setCantidad(int);
        void setPrecio(float);

        // METODOS
        Sticker crearSticker();
        string obtenerPath();
        float cotizarCortes(float, float, int);
        string cargar(string, string);

        // COTIZAR STICKERS
        float cotizarSticker();
        float cotizarStickerVinilo();
        float cotizarStickerMetalizado();

        // COTIZAR TARJETAS
        long cotizarTarjetaPVC();
        long cotizarTarjetaPVC(bool);
};

#endif
