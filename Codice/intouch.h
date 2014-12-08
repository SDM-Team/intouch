#ifndef __INTOUCH_H__
#define __INTOUCH_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <map>

#include "utente.h"

using namespace std;

class InTouch {
    private:
       map<string,Utente> lista_utenti;
    public:
       InTouch();
       void schermata_autenticazione();
       void login();
       void registrazione();
       bool check_login(const Utente& u);
       bool utente_esiste(const Utente& u);
       void aggiungi_utente(const Utente& u);
       void importa_utenti();
       void importa_post();
};

#endif

