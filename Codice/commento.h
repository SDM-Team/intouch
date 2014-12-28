#ifndef __COMMENTO_H__
#define __COMMENTO_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include "data.h"

using namespace std;

// Dichiarazione classe Commento
class Commento{
	private:
		int id_commento;
		Data tempo;
		string testo;
		string autore;
	public:
		Commento(int _id, string _t);
		Commento(int _id, string _autore, Data _tempo, string _testo);
		Data get_tempo() const;
		void visualizza_commento();
		
};

#endif

