#ifndef __AMICIZIA_H__
#define __AMICIZIA_H__

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

typedef enum stato {A,X,R};

// Forward declaration: evita inclusione circolare tra amicizia.h e utente.h
class Utente;

class Amicizia {
    private:
       int id_amicizia;
       Utente* mittente;
       Utente* destinatario;
       stato status;
    public:
       Amicizia(Utente* _m, Utente* _d);
       Utente* get_mittente();
       Utente* get_destinatario();
       stato get_status() const;
       void set_statusA();
       void set_statusR();
};

#endif

