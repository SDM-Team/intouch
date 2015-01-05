#include <cstdlib>		/* system								*/
#include <cstring>  	/* strtok								*/
#include <fstream>		/* ofstream, ifstream 					*/
#include <iostream>		/* cout, endl, remove, rename			*/
#include <list>			/* list, list::iterator					*/
#include <map>			/* map, map::iterator					*/
#include <sstream>		/* stringstream							*/
#include <string>		/* string								*/

// Librerie personalizzate
#include "post.h"		/* Libreria di riferimento 				*/
#include "commento.h"	/* classe Commento e relativi metodi 	*/
#include "config.h"		/* Definizione variabili globali		*/
#include "data.h"		/* classe Data e relativi metodi 		*/
#include "input.h"		/* inputInt, inputString				*/
#include "utente.h"		/* classe Utente e relativi metodi 		*/

// Namespace
using namespace std;

// Costruttore a quattro parametri, per l'importazione
Post::Post(int _id, Utente* _autore, string _testo, Data _tempo) {
  id_post = _id;
  author = _autore;
  tempo = _tempo;
  testo = _testo;
}

// Costruttore a due parametri, per la creazione di post fittizi da inserire in bacheca
Post::Post(Utente* _u, string _testo){
  id_post = id_p;
  Data temp;
  temp.imposta_dataOra();
  tempo = temp;
  author = _u;
  testo = _testo;
}

// Costruttore di copia
Post::Post(const Post& p){
  id_post= p.id_post;
  tempo= p.tempo;
  testo= p.testo;
  author= p.author;
  lista_commenti = p.lista_commenti;
  lista_likes= p.lista_likes;          
}

// Restituisce l'id del post
int Post::get_idpost () const {
  return id_post; 
}

// Restituisce data e ora di pubblicazione del post
Data Post::get_tempo() const {
  return tempo;
}

// Restituisce il testo del post
string Post::get_testo() const {
  return testo;
}

// Restituisce un puntatore all'utente autore del post
Utente* Post::get_autore(){
  return author;
}

// Restituisce un puntatore alla lista di commenti del post
list<Commento>* Post::get_listacommenti() {
  return (&lista_commenti);
}

// Visualizza il post in modo compatto, con numero di commenti e di likes
void Post::visualizza_post_light() {
  cout << "POST #" << id_post << endl;
  cout << "Autore: ";

  // Stampa autore del post
  if(author != NULL) {
    cout << author->get_cognome() << " ";
  	cout << author->get_nome() << " (";
		cout << author->get_email() << ")" << endl;
  }

  // Stampa data e ora di pubblicazione
  cout << "Data: " << tempo <<endl;

  // Stampa testo del post
  cout << endl << '"' << testo << '"' << endl << endl;

  // Stampa numero commenti del post
  if (lista_commenti.size() == 0) {
    cout << "Nessun commento" << endl;
  } else if (lista_commenti.size() == 1) {
    cout << "1 commento" << endl;
  } else {
    cout << lista_commenti.size() << " commenti" << endl;
  }

  // Stampa numero likes del post
  if (lista_likes.size() == 0) {
    cout << "Nessun \"mi piace\"" << endl;
  } else {
    cout << lista_likes.size() << " \"mi piace\"" << endl;
  }
  cout << endl;  
}

// Visualizza il post in modo dettagliato, con commenti e utenti che hanno espresso il proprio like
void Post::visualizza_post(){
  cout << "POST #" << id_post << " ####################" << endl;
  cout << "Autore: ";
  
  // Stampa autore
  if(author != NULL) {
    cout << author->get_cognome() << " " << author->get_nome() << " (" << author->get_email() << ")" << endl;
  }
  
  // Stampa data e ora di pubblicazione
  cout << "Data: " << tempo <<endl;

  // Stampa testo del post
  cout << endl << '"' << testo << '"' << endl << endl;

  // Stampa dei commenti del post
  if (lista_commenti.size() == 0) {
    cout << "Nessun commento" << endl;
  } else {
  	int i=0;
	  list<Commento>::iterator iter; 
  	for(iter = lista_commenti.begin(); iter != lista_commenti.end(); iter++){
  	  cout << "Commento #" << ++i << endl;
  	  iter->visualizza_commento();
	  }
	  cout << endl;
  }

  // Stampa likes del post
  if (lista_likes.size() == 0) {
    cout << "Ancora nessun \"mi piace\"" << endl;
  } else {
    map<string,Utente*>::iterator iter_listalike;
    cout << "Utenti a cui piace questo post:" << endl;
  	for (iter_listalike = lista_likes.begin(); iter_listalike != lista_likes.end(); iter_listalike++) {
      cout << " " << iter_listalike->second->get_cognome() << " ";
	    cout << iter_listalike->second->get_nome() << endl;
    }
  }
  cout << endl;
}

// Aggiunge un commento al post
void Post::commenta_post(Utente* autore){
	int s = 0;
	string testo_commento;
	do {
	  cout << "Inserisci testo:" << endl;

	  // Controllo input MAXPOST
	  testo_commento = inputString(MAXPOST);

	  cout << "Per confermare ed aggiungere il commento al post premi 2" << endl;
	  cout << "Per modificare il testo del commento premi 1" << endl;
	  cout << "Per annullare e tornare alla schermata precedente premi 0" << endl;

    s = inputInt(0,2);
	} while(s == 1);
  system("CLS");
	
  switch(s){
  	case 0:
      // Torna alla schermata iniziale
      cout << "Pubblicazione del commento annullata!" << endl << endl;
      return;
	  case 2:
      // Esce dallo switch ed aggiunge il commento
      break;
	}

  // Crea un'istanza di commento con i dati immessi
	Commento c(autore,testo_commento);
	
	// Aggiunge il commento alla lista di commenti del post
	lista_commenti.push_back( c );

	// Scrittura su file
	stringstream convert;
	convert << id_post;

  // Apre il file relativo ai commenti del determinato post
  string path = path_files_p + convert.str() + "/" + nome_file_commenti;
	ofstream file;
	file.open(path.c_str(), ios::app);

	// Controllo apertura corretta file
	if(!file){ cerr<< "Errore apertura file!"; return;}
	
	// Scrittura su file
	file << id_c << ";";
  file << autore->get_email() << ";"; 
	file << c.get_tempo() << ";";
	file << testo_commento << endl;

  // Chiusura del file
  file.close();

  // Incrementa il contatore dell'id univoco commenti
  id_c++;
  
  // Messaggio di conferma
  cout << "Commento pubblicato!" << endl << endl;
}

void Post::aggiungi_like(Utente* autore){	
	// Controlla se piace già
	map<string,Utente*>::iterator iter;
	
	// Cerca se l'utente è già presente nella lista di utenti che hanno espresso il proprio like
	iter = lista_likes.find( autore->get_email() );

  // Se non lo trova, aggiunge il like
	if( iter == lista_likes.end() ){
    // Aggiunge l'utente alla lista dei like del post, utilizzando la mail come key
	  lista_likes.insert( pair<string,Utente*> (autore->get_email(), autore) );

  	// Scrittura su file
	  stringstream convert;
  	convert << id_post;

    // Apre il file relativo al like del determinato post   
    string path = path_files_p + convert.str() + "/" + nome_file_likes;
  	ofstream file;
  	file.open(path.c_str(), ios::app);

  	// Controllo apertura corretta file
  	if(!file){ cerr<< "Errore apertura file!"; return;}
  	
  	// Stampa su file
  	file << autore->get_email() << endl;  
    file.close();

    system("CLS"); 
    
    // Messaggio di conferma
  	cout << "Liked!" << endl << endl; 
	} else { // se trova l'autore nella lista, rimuove il suo like
	  rimuovi_like(autore);	
	}
}

void Post::rimuovi_like(Utente* autore){
  // Controllo eseguito in aggiungi_like
  // Elimina l'utente dalla lista di utenti che hanno espresso il proprio like
  lista_likes.erase( autore->get_email() );

  // Riscrittura su nuovo file
  stringstream convert;
  convert << id_post;

  string path = path_files_p + convert.str() + "/" + nome_file_likes;	
  string path_copia = path_files_p + convert.str() + "/" + "copia_" + nome_file_likes;

  // Apertura file copia in scrittura
  ofstream file_copia;
  file_copia.open(path_copia.c_str(), ios::out);

  // Controllo apertura corretta file
  if(!file_copia){ cerr<< "Errore apertura file!"; return;}

  // Apertura file standard in lettura
  ifstream file;
  file.open(path.c_str(), ios::in);

  // Controllo apertura file
  if(!file){ cerr << "Errore apertura file!"; return;}

  char linea[150];
  while (!file.getline(linea,150).eof()) {
    // Token mail
    string _email = strtok (linea,";");
    
    // Copia tutti gli indirizzi tranne quello da rimuovere nel file di copia
    if(_email != autore->get_email() ){
      file_copia << _email << endl;
    }
  }

  // Chiude il file standard
  file.close();
  
  // Chiude il file di copia
  file_copia.close();

  // Elimina il precedente file standard
  if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }

  // Rinomina il file copia con il nome del file standard
  if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }

  system("CLS");
	
  // Messaggio di conferma
  cout << "Non ti piace piu'!" << endl << endl; 
}

// Inserisce la coppia passata all'interno della lista di likes
// Usato per importare likes degli utenti da file nelle loro liste
void Post::popola_lista_likes( pair<string, Utente* > pair ){
	lista_likes.insert( pair );	
}
