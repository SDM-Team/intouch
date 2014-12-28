#include "commento.h"

#include <fstream>

// Variabile globale per ID univoco commento
int id_c = 1;

// Costruttore specifico per creare commento con timestamp corrente
Commento::Commento(int _id, string _t){
	testo = _t;
	
	Data temp;
	temp.imposta_dataOra();
	tempo = temp;
}

Commento::Commento(int _id, string _autore, Data _tempo, string _testo) {
  id_commento = _id;
  autore = _autore;
  tempo = _tempo;
  testo = _testo;
}

Data Commento::get_tempo() const{
	return tempo;	
}

void Commento::visualizza_commento(){
	cout << "Autore: " << "Cognome" << " " << "Nome" <<endl; //TO DO ############################## InTouch applicazione.lista_utenti.find?
	cout << "Data: " << tempo <<endl;
	cout << '"' << testo << '"' << endl << endl;
}
