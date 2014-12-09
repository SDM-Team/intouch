#include "amicizia.h"

// Variabile globale per ID univoco amicizia
int id_a = 1;

//Costruttore specifico amicizia (passati puntatore ad utente e ruolo)
Amicizia::Amicizia(Utente* _u, Ruolo _r) {
  id_amicizia = id_a;
  utente = _u;
  status = X;
  ruolo = _r;
}

// Restituisce il puntatore all'utente coinvolto
Utente* Amicizia::get_utente() {
  return utente;
}

// Restituisce lo stato dell'amicizia
Stato Amicizia::get_status() const {
  return status;
}

// Restituisce il ruolo che ha l'utente a cui appartiene la lista di amicizie
Ruolo Amicizia::get_ruolo() const {
  return ruolo;
}

// Imposta lo stato dell'amicizia su A(ccettata)
void Amicizia::set_statusA() {
  status = A;
}

// Imposta lo stato dell'amicizia su R(ifiutata)
void Amicizia::set_statusR() {
  status = R;
}
