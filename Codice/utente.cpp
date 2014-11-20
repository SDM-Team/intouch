#include "utente.h"

int id_u = 1;

// Costruttore specifico a due parametri per la procedura di login
Utente::Utente(string e, string p) {
    id_utente = 0;
    nome = "";
    cognome = "";
    email = e;
    password = p;
}

// Costruttore specifico a quattro parametri per la procedura di creazione utente
Utente::Utente(string n, string c, string e, string p) {
    id_utente = id_u;
    nome = n;
    cognome = c;
    email = e;
    password = p;
}

// Metodo che controlla se un utente esiste già o meno
bool Utente::utente_esiste(list<Utente>* p_lista_utenti) {
    list<Utente>::iterator iter;
    for (iter = p_lista_utenti->begin(); iter != p_lista_utenti->end(); iter++) {
       if (email == iter->email) return true;
    }
       
    return false;
}

// Metodo che aggiunge un nuovo utente nella lista degli utenti
void Utente::aggiungi_utente(list<Utente>* p_lista_utenti) {
    p_lista_utenti->push_back(*this);
    
    /*fstream utenti;
    utenti.open("utenti.txt");
    
    if(utenti == NULL) {
       perror("Errore in apertura del file");
       exit(1);
    }
    
    utenti << id_utente << endl;
    utenti << nome << endl;
    utenti << cognome << endl;
    utenti << email << endl;
    utenti << password << endl << endl;
    

    
    utenti.close();*/
    
    id_u++;
}

// Metodo che verifica la correttezza della password inserita in fase di login
bool Utente::check_login(list<Utente>* p_lista_utenti) {
    list<Utente>::iterator iter;
    for (iter = p_lista_utenti->begin(); iter != p_lista_utenti->end(); iter++) {
       if ((email == iter->email) && (password == iter->password)) return true;
    }
    return false;
}

// Metodo che stampa i dati di un utente
void Utente::stampa() {
    cout << id_utente << endl;
    cout << nome << endl;
    cout << cognome << endl;
    cout << email << endl;
    cout << password << endl << endl;
}

