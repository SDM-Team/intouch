#ifndef __COMMENTO_H__
#define __COMMENTO_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include "data.h"

using namespace std;

class Utente;

// Dichiarazione classe Commento
class Commento{
	private:
		int id_commento;
		Data tempo;
		string testo;
		Utente* autore;
	public:
		Commento(Utente* _autore, string _testo);
		Commento(int _id, Utente* _autore, Data _tempo, string _testo);
		Data get_tempo() const;
		void visualizza_commento();
		
};

#endif

