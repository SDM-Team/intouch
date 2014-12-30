#ifndef __INTOUCH_H__
#define __INTOUCH_H__

#include <cstdlib>
#include <iostream>
#include <string> /* string, */
#include <list>
#include <map> /* map, */

#include "utente.h" /* utente, */

using namespace std;

class InTouch {
    private:
       map<string,Utente> lista_utenti;
    public:
       InTouch();
       map<string,Utente> get_listautenti();
       void schermata_autenticazione();
       void login();
       void registrazione();
       bool check_login(const Utente& u);
       bool utente_esiste(const Utente& u);
       void aggiungi_utente(const Utente& u);
       void reset();
       void importa_utenti();
       void importa_post();
       void importa_commenti(string _autore, int id_post);
       void importa_likes(string _autore, int id_post);
       void importa_profilo();
       void importa_amicizie();
};

#endif

