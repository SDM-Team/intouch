#include "post.h"

#include <fstream>

using namespace std;

int id_p = 1;

//costruttore specifico per creazione post senza titolo con timestamp corrente
Post::Post(string _testo){
	id_post = id_p;
	id_p++;
	
	data temp;
	temp.imposta_dataOra();
	tempo = temp;
	
	testo = _testo;
}

Post::Post(int _id, string _autore, string _testo) {
    id_post = _id;
    autore = _autore;
    testo = _testo;
}

int Post::get_post() const {
    return id_post;
}

int Post::get_idpost()const{
      return id_p; 
}    

string Post::get_testo() const {
    return testo;
}

string Post::get_autore() const {
    return autore;
}

//metodo che stampa a video il post e tutta la lista dei commenti relativi ad esso
void Post::visualizza_post(){
	cout << "POST #" << id_post << " ####################" << endl;
	cout << "Autore: " << "Cognome" << " " << "Nome" <<endl;			//TO DO ##############################
	cout << "Data: " << tempo <<endl;
	cout << endl << '"' << testo << '"' << endl << endl;
	
	//stampa commenti
	int i=0;
	list<Commento>::iterator iter; 
	for(iter = lista_commenti.begin(); iter != lista_commenti.end(); iter++){
	cout << "Commento #" << ++i << endl;
	iter->visualizza_commento();
	}
	cout << endl;
	
}

//aggiunge un commento al post
void Post::commenta_post(){
	cout << "Inserisci testo:" << endl;
	string temp;
	fflush(stdin); //?
	//controllo input MAXPOST
	cin >> temp;
	lista_commenti.push_back( Commento(temp) );
	
	/*
	//scrivo su csv id_post del commento
	ofstream outfile("commenti.csv", ios::app);
	//controllare!
     outfile << id_post << ';';	
     outfile.close();
	lista_commenti.push_back( Commento(temp) );
	*/
		
}
