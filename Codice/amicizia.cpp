#include "amicizia.h"

int id_a = 1;

Amicizia::Amicizia(Utente* _m, Utente* _d) {
    id_amicizia = id_a;
    mittente = _m;
    destinatario = _d;
    status = X;
}

Utente* Amicizia::get_mittente() {
    return mittente;
}

Utente* Amicizia::get_destinatario() {
    return destinatario;
}

stato Amicizia::get_status() const {
    return status;
}

void Amicizia::set_statusA() {
    status = A;
}

void Amicizia::set_statusR() {
    status = R;
}

