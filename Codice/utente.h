#ifndef __UTENTE_H__
#define __UTENTE_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "profilo.h"

using namespace std;

class Utente {
    private:
       int id_utente;
       string nome;
       string cognome;
       string email;
       string password;
       Profilo profilo;
    public:
       Utente(string e, string p);
       Utente(string n, string c, string e, string p);
       int get_idutente() const;
       string get_nome() const;
       string get_cognome() const;
       string get_email() const;
       string get_password() const;
       void stampa();
       void schermata_iniziale();
       void logout();
       void visualizza_profilo();
       void modifica_profilo();
};

#endif

