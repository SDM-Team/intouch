#ifndef __UTENTE_H__
#define __UTENTE_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "profilo.h"
#include "bacheca.h"
#include "amicizia.h"

using namespace std;

class Utente {
    private:
       int id_utente;
       string nome;
       string cognome;
       string email;
       string password;
       Bacheca bacheca;
       Profilo profilo;
       map<int,Amicizia> lista_amicizie;
    public:
       Utente(string e, string p);
       Utente(string n, string c, string e, string p);
       int get_idutente() const;
       string get_nome() const;
       string get_cognome() const;
       string get_email() const;
       string get_password() const;
       Bacheca* get_bacheca();
       void stampa();
       void schermata_iniziale();
       void logout();
       void visualizza_profilo();
       void modifica_profilo();
       void visualizza_bacheca();
       void modifica_bacheca();
       void visualizza_amici();
       void gestisci_amicizie();
};

#endif

