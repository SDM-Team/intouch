#include "amicizia.h"

int id_a = 1;

Amicizia::Amicizia(Utente* _u, Ruolo _r) {
    id_amicizia = id_a;
    utente = _u;
    status = X;
    ruolo = _r;
}

Utente* Amicizia::get_utente() {
    return utente;
}

Stato Amicizia::get_status() const {
    return status;
}

Ruolo Amicizia::get_ruolo() const {
    return ruolo;
}

void Amicizia::set_statusA() {
    status = A;
}

void Amicizia::set_statusR() {
    status = R;
}

