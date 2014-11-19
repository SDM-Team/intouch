#ifndef __UTENTE_H__
#define __UTENTE_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

class Utente {
    private:
       int id_utente;
       string nome;
       string cognome;
       string email;
       string password;
    public:
       Utente(string e, string p);
       Utente(string n, string c, string e, string p);
       bool check_login();
       bool utente_esiste();
       void aggiungi_utente();
       void stampa();
};


#endif
