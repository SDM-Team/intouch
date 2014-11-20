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
       bool check_login(list<Utente>* p_lista_utenti);
       bool utente_esiste(list<Utente>* p_lista_utenti);
       void aggiungi_utente(list<Utente>* p_lista_utenti);
       void stampa();
       void schermata_iniziale();
       void logout();
};


#endif
