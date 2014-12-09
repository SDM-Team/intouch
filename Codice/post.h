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
		string autore;
		list<Commento> lista_commenti;
	public:
		Post(string _testo);
		Post(int _id, string _autore, string _testo);
		int get_post() const;
		int get_idpost() const;
		string get_testo() const;
		string get_autore() const;
		void visualizza_post();
		void commenta_post();
};

#endif

