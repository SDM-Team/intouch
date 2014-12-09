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
	public:
		Commento(string _t);
		void visualizza_commento();
};

#endif
