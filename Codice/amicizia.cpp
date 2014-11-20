#include "amicizia.h"

Amicizia::Amicizia(Utente* _m, Utente* _d) {
    mittente = _m;
    destinatario = _d;
    status = X;
}

void Amicizia::approva_amicizia() {
}

void Amicizia::rifiuta_amicizia() {
}
