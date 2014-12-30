#ifndef __COMMENTO_H__
#define __COMMENTO_H__
		
#include <string>		/* string */		

// Libreria personalizzata
#include "data.h"		/* classe Data e metodi relativi */

// Forward declaration
class Utente;			/* riferimento a Utente */

using namespace std;

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

