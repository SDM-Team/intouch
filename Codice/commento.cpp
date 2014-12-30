#include <iostream>		/* cout, endl							*/
#include <string>		/* string								*/

// Librerie personalizzate
#include "commento.h"	/* Libreria di riferimento				*/
#include "data.h"		/* classe Data e relativi metodi 		*/
#include "utente.h"		/* classe Utente e relativi metodi 		*/

// Variabile globale per ID univoco commento
int id_c = 1;

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

// Metodo che ritorna il tempo
Data Commento::get_tempo() const{
	return tempo;	
}

void Commento::visualizza_commento(){
	cout << "Autore: ";
	if(autore != NULL) { cout << autore->get_cognome() << " " << autore->get_nome() << " (" << autore->get_email() << ")" << endl; }
	cout << "Data: " << tempo <<endl;
	cout << '"' << testo << '"' << endl << endl;
}
