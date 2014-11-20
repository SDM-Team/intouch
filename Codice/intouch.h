#ifndef __INTOUCH_H__
#define __INTOUCH_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

#include "utente.h"

using namespace std;

class InTouch {
    private:
       list<Utente> lista_utenti;
    public:
       void schermata_autenticazione();
       void schermata_iniziale();
       void login();
       void logout();
       void registrazione();
};

#endif
