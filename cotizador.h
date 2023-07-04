// Cotizador de cortes AJI S.A en base a cotizacones del dolar

#ifndef COTIZADOR_H
#define COTIZADOR_H

#include "date.h"

struct PrecioDolar {
    Date fecha;
    float precio;
};

struct Sticker {
    float costoPlancha, costoInicio, cantidad, cantidadPlancha;
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
        float cotizarCortes(float, float, int);
        float cotizarSticker();
        float cotizarStickerVinilo();
        float cotizarStickerMetalizado();
};

#endif
