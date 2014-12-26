#include "post.h"

#include <fstream>
#include <sstream>

using namespace std;

// File di configurazione
extern string path_files_p;
extern string nome_file_commenti;

int id_p = 1;

//costruttore specifico per creazione post senza titolo con timestamp corrente
/*Post::Post(string _autore, string _testo){
	id_post = id_p;
	id_p++;
	
	Data temp;
	temp.imposta_dataOra();
	tempo = temp;
	
	autore = _autore;

	testo = _testo;
}*/

Post::Post(int _id, string _autore, string _testo) {
  id_post = _id;
  autore = _autore;
    
  Data temp;
	temp.imposta_dataOra();
	tempo = temp;
	
  testo = _testo;
}

Post::Post(int _id, string _autore, string _testo, Data _tempo) {
  id_post = _id;
  autore = _autore;
    
  tempo = _tempo;
	
  testo = _testo;
}

int Post::get_idpost () const {
      return id_post; 
}

Data Post::get_tempo() const {
  return tempo;
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
	
	// Scrittura su file
	stringstream convert;
	convert << id_post;
	
  string path = path_files_p + convert.str() + "/" + nome_file_commenti;
	ofstream file;
	file.open(path.c_str(), ios::out);
	
	file << id_post << ";"
	     << autore << ";"
	     << tempo << ";"
	     << testo << endl;
	     
  file.close();
		
}
