#ifndef __AMICIZIA_H__
#define __AMICIZIA_H__

// Definizione del tipo di dato Stato
typedef enum Stato {A,X,R};

// Definizione del tipo di dato Ruolo
typedef enum Ruolo {MITTENTE,DESTINATARIO};

// Forward declaration: evita inclusione circolare tra amicizia.h e utente.h
class Utente;

using namespace std;

// Dichiarazione classe Amicizia
class Amicizia {
  private:
    int id_amicizia;
    Utente* utente;
    Stato status;
    Ruolo ruolo;
  public:
    Amicizia(Utente* _u, Ruolo _r);
    Amicizia(int _id, Utente* _u, Stato _s, Ruolo _r);
    Amicizia(const Amicizia& a);
    int get_idamicizia() const;
    Utente* get_utente();
    Stato get_status() const;
    Ruolo get_ruolo() const;
    void set_statusA();
    void set_statusR();
};

#endif
