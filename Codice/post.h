#ifndef __POST_H__
#define __POST_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "data.h"
#include "commento.h"
//#include "utente.h"

#define MAXPOST 250
#define MAXTITLE 30

using namespace std;

class Utente;

class Post{
	private:
		int id_post;
		Data tempo;
		string testo;
		string autore;
		list<Commento> lista_commenti;
		map<string,Utente*> lista_likes;
	public:
		//Post(string _autore, string _testo);
		Post(int _id, string _autore, string _testo);
		Post(int _id, string _autore, string _testo, Data _tempo);
		int get_idpost() const;
		Data get_tempo() const;
		string get_testo() const;
		string get_autore() const;
		list<Commento>* get_listacommenti();
		void visualizza_post_light();
		void visualizza_post();
		void commenta_post(string _email);
};

#endif

