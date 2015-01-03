#ifndef __UTENTE_H__
#define __UTENTE_H__

#include <map>			/* map									*/
#include <string>		/* string 								*/

// Librerie personalizzate
#include "amicizia.h"	/* classe Amicizia e metodi relativi 	*/
#include "bacheca.h"	/* classe Bacheca e metodi relativi 	*/
#include "profilo.h"	/* classe Profilo e metodi relativi 	*/

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
    Utente(const Utente& u);      
    int get_idutente() const;
    string get_nome() const;
    string get_cognome() const;
    string get_email() const;
    string get_password() const;
    Bacheca* get_bacheca();
    Profilo* get_profilo();
    map<int,Amicizia>* get_listaamicizie();
    void schermata_iniziale(map<string,Utente>* lista_utenti_p);
    void logout();
    void visualizza_profilo();
    void modifica_profilo();
    void visualizza_bacheca();
    void visualizza_contenuto_amici();
    void visualizza_bacheca_amico();
    void visualizza_profilo_amico();       
    void visualizza_bacheca_generale();
    void visualizza_amici();
    void gestisci_amicizie(map<string,Utente>* lista_utenti_p);
    void richiedi_amicizia(map<string,Utente>* lista_utenti_p);
    void accetta_rifiuta_amicizia();
    void cancella_amicizia();
    int num_richieste_pendenti();
};

#endif
