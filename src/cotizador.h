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
    public:
        // CONSTRUCTORES
        Cotizador();

        // METODOS
        Sticker crearSticker();
        string obtenerPath();
        string cargar(string, string);
        string formatear(long);

        // COTIZAR STICKERS
        float cotizarSticker();
        float cotizarStickerVinilo();
        float cotizarStickerMetalizado();

        // COTIZAR TARJETAS
        TarjetaPVC cotizarTarjetaPVC();
        long cotizarTarjetaPVC(bool);
};

#endif
