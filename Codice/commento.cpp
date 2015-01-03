#include <iostream>		/* cout, endl							*/
#include <string>		/* string								*/

// Librerie personalizzate
#include "commento.h"	/* Libreria di riferimento				*/
#include "data.h"		/* classe Data e relativi metodi 		*/
#include "utente.h"		/* classe Utente e relativi metodi 		*/

// Variabile globale per ID univoco commento
int id_c = 1;

// Namespace
using namespace std;

// Costruttore usato per creare commento passando utente e testo, autotimestamp corrente
Commento::Commento(Utente* _autore, string _testo){
  id_commento = id_c;
  autore = _autore;
  Data temp;
  temp.imposta_dataOra();
  tempo = temp;
  testo = _testo;
}

// Costruttore specifico per creazione commenti fittizi
Commento::Commento(int _id, Utente* _autore, Data _tempo, string _testo){
  id_commento = _id;
  autore = _autore;
  tempo = _tempo;
  testo = _testo;
}

// Costruttore di copia
Commento::Commento(const Commento& c){
  id_commento= c.id_commento;
  tempo= c.tempo;
  testo= c.testo;
  autore= c.autore;                         
}

// Metodo che ritorna data e ora di pubblicazione
Data Commento::get_tempo() const{
	return tempo;	
}

// Metodo che permette di visualizzare l'elenco di commenti di un determinato post
void Commento::visualizza_commento(){
	cout << "Autore: ";
	
	// Stampa l'autore
	if(autore != NULL) {
    cout << autore->get_cognome() << " " << autore->get_nome() << " (" << autore->get_email() << ")" << endl;
  }
  
  // Stampa data e ora di pubblicazione del commento
	cout << "Data: " << tempo <<endl;
	
	// Stampa il testo del commento
	cout << '"' << testo << '"' << endl << endl;
}
