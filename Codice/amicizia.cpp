// Libreria personalizzata
#include "amicizia.h"		/* Libreria di riferimento 				*/

// Variabile globale per ID univoco amicizia
int id_a = 1;

//Costruttore specifico amicizia (passati puntatore ad utente e ruolo)
Amicizia::Amicizia(Utente* _u, Ruolo _r) {
  id_amicizia = id_a;
  utente = _u;
  status = X;
  ruolo = _r;
}

Amicizia::Amicizia(int _id, Utente* _u, Stato _s, Ruolo _r) {
  id_amicizia = _id;
  utente = _u;
  status = _s;
  ruolo = _r;
}

// Costruttore di copia
Amicizia::Amicizia(const Amicizia& a){
  id_amicizia= a.id_amicizia;
  utente= a.utente;
  status= a.status;
  ruolo= a.ruolo;                            
}

int Amicizia::get_idamicizia() const {
  return id_amicizia;
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
