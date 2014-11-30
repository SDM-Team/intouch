#ifndef __AMICIZIA_H__
#define __AMICIZIA_H__

#include <cstdlib>
#include <iostream>
#include <string>

#include "utente.h"

using namespace std;

typedef enum stato {A,X,R};

class Amicizia {
    private:
       Utente* mittente;
       Utente* destinatario;
       stato status;
    public:
       Amicizia(Utente* _m, Utente* _d);
       void approva_amicizia();
       void rifiuta_amicizia();
};

#endif

