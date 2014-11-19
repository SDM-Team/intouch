#ifndef __INTOUCH_H__
#define __INTOUCH_H__

#include <cstdlib>
#include <iostream>
#include <string>

#include "utente.h"

using namespace std;

extern list<Utente> lista_utenti;

class InTouch {
    public:
       void schermata_autenticazione();
       void schermata_iniziale();
       void login();
       void logout();
       void registrazione();
};

#endif
