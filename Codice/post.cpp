#include "post.h"
#include "input.h"
#include "config.h"
#include "utente.h"

#include <fstream>
#include <sstream>
#include <cstring> /* strtok */

using namespace std;


int id_p = 1;
extern int id_c;

Post::Post(int _id, Utente* _autore, string _testo, Data _tempo) {
  id_post = _id;
  author = _autore;
    
  tempo = _tempo;
	
  testo = _testo;
}

Post::Post(Utente* _u, string _testo){
	id_post = id_p;
	
	Data temp;
	temp.imposta_dataOra();
	tempo = temp;
	
	author = _u;
	
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

Utente* Post::get_autore(){
    return author;
}

list<Commento>* Post::get_listacommenti() {
    return (&lista_commenti);
}

void Post::visualizza_post_light() {
  cout << "POST #" << id_post << endl;
	cout << "Autore: "; 
	if(author != NULL) { cout << author->get_cognome() << " " << author->get_nome() << " (" << author->get_email() << ")" << endl; }
	cout << "Data: " << tempo <<endl;
	cout << endl << '"' << testo << '"' << endl << endl;
  
  if (lista_commenti.size() == 0) {
    cout << "Nessun commento" << endl;
  } else if (lista_commenti.size() == 1) {
    cout << "1 commento" << endl;
  } else {
    cout << lista_commenti.size() << " commenti" << endl;
  }
  
  
  if (lista_likes.size() == 0) {
    cout << "Nessun \"mi piace\"" << endl;
  } else if (lista_likes.size() == 1) {
    cout << "1 \"mi piace\"" << endl;
  } else {
    cout << lista_likes.size() << " \"mi piace\"" << endl;
  }
  cout << endl;  
}

//metodo che stampa a video il post e tutta la lista dei commenti relativi ad esso
void Post::visualizza_post(){
	cout << "POST #" << id_post << " ####################" << endl;
	cout << "Autore: ";
	if(author != NULL) { cout << author->get_cognome() << " " << author->get_nome() << " (" << author->get_email() << ")" << endl; }
	cout << "Data: " << tempo <<endl;
	cout << endl << '"' << testo << '"' << endl << endl;
	
	if (lista_commenti.size() == 0) {
    cout << "Nessun commento" << endl;
  } else {
  
    //stampa commenti
	  int i=0;
	  list<Commento>::iterator iter; 
	  for(iter = lista_commenti.begin(); iter != lista_commenti.end(); iter++){
	  cout << "Commento #" << ++i << endl;
	  iter->visualizza_commento();
	  }
	  cout << endl;
  }
	
	//stampa likes
	if (lista_likes.size() == 0) {
    cout << "Ancora nessun \"mi piace\"" << endl;
  } else {
    map<string,Utente*>::iterator iter_listalike;
    cout << "Utenti a cui piace questo post:" << endl;
	  for (iter_listalike = lista_likes.begin(); iter_listalike != lista_likes.end(); iter_listalike++) {
      cout << "\t" << iter_listalike->second->get_cognome() << " " << iter_listalike->second->get_nome() << endl;
    }
  }
	cout << endl;
}

//aggiunge un commento al post
void Post::commenta_post(Utente* autore){
	int s = 0;
	string testo_commento;
	do{
	  cout << "Inserisci testo:" << endl;
	  //controllo input MAXPOST
	  testo_commento = inputString(MAXPOST);
	  
	  cout << "Per confermare ed aggiungere il commento al post premi 2" << endl;
	  cout << "Per modificare il testo del commento premi 1" << endl;
	  cout << "Per tornare alla schermata iniziale premi 0" << endl;
	  
      s = inputInt(0,2);
	}while(s == 1);
	
	switch(s){
	case 0: system("CLS"); return;
	case 2:	break;
	}
	
	Commento c(autore,testo_commento);
	lista_commenti.push_back( c );
	
	// Scrittura su file
	stringstream convert;
	convert << id_post;
	
    string path = path_files_p + convert.str() + "/" + nome_file_commenti;
    
	ofstream file;
	file.open(path.c_str(), ios::app);
	//controllo apertura corretta file
	if(!file){ cerr<< "Errore apertura file!"; return;}
	file << id_c << ";";
    file << autore->get_email() << ";"; 
	file << c.get_tempo() << ";";
	file << testo_commento << endl;
	     
  file.close();
  
  id_c++;
}

void Post::aggiungi_like(Utente* autore){
	
	//controllo se piace già
	map<string,Utente*>::iterator iter;
	iter = lista_likes.find( autore->get_email() );
	
	if( iter == lista_likes.end() ){ //aggiungo like perché non trovato
	lista_likes.insert( pair<string,Utente*> (autore->get_email(), autore) );
	
	// Scrittura su file
	stringstream convert;
	convert << id_post;
	
    string path = path_files_p + convert.str() + "/" + nome_file_likes;
    
	ofstream file;
	file.open(path.c_str(), ios::app);
	//controllo apertura corretta file
	if(!file){ cerr<< "Errore apertura file!"; return;}
	file << autore->get_email() << endl;  
    file.close();
    
    system("CLS"); 
	cout<<"Liked!" << endl << endl; 
	}else{
	  rimuovi_like(autore);	
	}
	
}

void Post::rimuovi_like(Utente* autore){

	//controllo eseguito in aggiungi_like
	lista_likes.erase( autore->get_email() );
	
	//riscrittura su nuovo file
	stringstream convert;
	convert << id_post;
	
    string path = path_files_p + convert.str() + "/" + nome_file_likes;	
    string path_copia = path_files_p + convert.str() + "/" + nome_file_likes + "_copia";
    
	ofstream file_copia;
	file_copia.open(path_copia.c_str(), ios::out);
	//controllo apertura corretta file
	if(!file_copia){ cerr<< "Errore apertura file!"; return;}
	
	ifstream file;
	file.open(path.c_str(), ios::in);
	//controllo apertura file
	if(!file){ cerr << "Errore apertura file!"; return;}
	
	char linea[150];
	while (!file.getline(linea,150).eof()) {
        //token mail
        string _email = strtok (linea,";");
        if(_email != autore->get_email() ){
          file_copia << _email << endl;
      	}
	  }	
 
    file.close();
    file_copia.close();
    
    //elimino il precedente file
    if(remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }
    //rinomino
    if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }
    
	system("CLS"); 
	cout<<"Non ti piace piu'!" << endl << endl; 
}

void Post::popola_lista_likes( pair<string, Utente* > pair ){
	lista_likes.insert( pair );	
}
