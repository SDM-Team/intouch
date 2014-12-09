#include "commento.h"

#include <fstream>

// Variabile globale per ID univoco amicizia
int id_c = 1;

// Costruttore specifico per creare commento con timestamp corrente
Commento::Commento(string _t){
	id_commento = id_c;
	id_c++;
	
	testo = _t;
	
	Data temp;
	temp.imposta_dataOra();
	tempo = temp;
}

void Commento::visualizza_commento(){
	cout << "Autore: " << "Cognome" << " " << "Nome" <<endl; //TO DO ##############################
	cout << "Data: " << tempo <<endl;
	cout << '"' << testo << '"' << endl << endl;
}
