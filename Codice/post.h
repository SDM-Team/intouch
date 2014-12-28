#ifndef __POST_H__
#define __POST_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "data.h"
#include "commento.h"


#define MAXPOST 250
#define MAXTITLE 30

using namespace std;

class Utente;
class Bacheca;

class Post{
	private:
		int id_post;
		Data tempo;
		string testo;
		//string autore;
		Utente* author;
		list<Commento> lista_commenti;
		map<string,Utente*> lista_likes;
	public:
		//Post(string _autore, string _testo);
		//Post(int _id, string _autore, string _testo);
		Post(int _id, Utente* _autore, string _testo, Data _tempo);
		Post(Utente* _u, string _testo);
		int get_idpost() const;
		Data get_tempo() const;
		string get_testo() const;
		Utente* get_autore();
		list<Commento>* get_listacommenti();
		void visualizza_post_light();
		void visualizza_post();
		void commenta_post(Utente* autore);
};

#endif

