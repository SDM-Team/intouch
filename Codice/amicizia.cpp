#include "amicizia.h"

Amicizia::Amicizia(Utente* _m, Utente* _d) {
    mittente = _m;
    destinatario = _d;
    status = X;
}

Utente Amicizia::get_mittente() const {
    return *mittente;
}

Utente Amicizia::get_destinatario() const {
    return *destinatario;
}

stato Amicizia::get_status() const {
    return status;
}

void Amicizia::approva_amicizia() {
    status = A;
}

void Amicizia::rifiuta_amicizia() {
    status = R;
}
