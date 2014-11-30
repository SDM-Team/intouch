#ifndef __POST_H__
#define __POST_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "data.h"
#include "commento.h"

#define MAXPOST 250
#define MAXTITLE 30

using namespace std;

class Post{
	private:
		int id_post;
		data tempo;
		string testo;
		string titolo;
		list<Commento> lista_commenti;
	public:
		Post(string _testo);
		Post(string _titolo, string _testo);
		void visualizza_post();
		void commenta_post();

};












#endif

