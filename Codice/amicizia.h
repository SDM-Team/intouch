#ifndef __AMICIZIA_H__
#define __AMICIZIA_H__

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Definizione del tipo di dato Stato
typedef enum Stato {A,X,R};

// Definizione del tipo di dato Ruolo
typedef enum Ruolo {MITTENTE,DESTINATARIO};

// Forward declaration: evita inclusione circolare tra amicizia.h e utente.h
class Utente;

// Dichiarazione classe Amicizia
class Amicizia {
  private:
    int id_amicizia;
    Utente* utente;
    Stato status;
    Ruolo ruolo;
  public:
    Amicizia(Utente* _u, Ruolo _r);
    Utente* get_utente();
    Stato get_status() const;
    Ruolo get_ruolo() const;
    void set_statusA();
    void set_statusR();
};

#endif
