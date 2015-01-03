#include <cstdlib>		/* system								*/
#include <direct.h>		/* mkdir		 						*/
#include <fstream>		/* ofstream								*/
#include <iostream>		/* cin									*/
#include <map>			/* map									*/
#include <sstream>		/* stringstream							*/
#include <string>		/* string, getline						*/

// Librerie personalizzate
#include "bacheca.h"	/* Libreria di riferimento 				*/
#include "commento.h"	/* classe Commento e metodi relativi 	*/
#include "config.h"		/* Definizione variabili globali 		*/
#include "input.h"		/* inputInt								*/
#include "utente.h"		/* classe Utente e metodi relativi 		*/

using namespace std;


// Costruttore di default
Bacheca::Bacheca(){
  lista_post.clear();   
}

// Costruttore di copia
Bacheca::Bacheca(const Bacheca& b){
  lista_post= b.lista_post;                       
}

// Richiamo la variabile globale id_p per il tracciamento degli ID univoci dei post
extern int id_p;

// Metodo che permette l'aggiunta di un post alla bacheca dell'utente
void Bacheca::aggiungi_post(Utente* _u){
	int s;
  string testo;

  // Inserimento testo
  cout << "Inserire Testo Post: " << endl;
  getline(cin,testo);
  
  // Conferma
  cout << "Per confermare e aggiungere il post alla tua Bacheca premi 1: "<<endl;
  cout << "Per tornare alla schermata iniziale premi 0"<<endl;
  s = inputInt(0,1);
  system("CLS");
  if (s == 1) {
    // Creo un post con le informazioni date
    Post p(_u,testo);
    
    // Inserisco il post nel map dei post (id,post)
    lista_post.insert(pair<int,Post> (p.get_idpost(),p));

    // Apro un flusso su file in scrittura
    string path = path_files + nome_file_post;
    ofstream post(path.c_str(), ios::app);

    // Scrivo dati su file
    post << id_p << ";";
    post << _u->get_email() << ";";
    post << p.get_tempo() << ";";
    post << testo << endl;

    // Chiudo il flusso su file
    post.close();
    
    // Creo opportuna cartella
    stringstream convert;
    convert << id_p;
    path = path_files_p + convert.str();
    mkdir(path.c_str());
    
    // Creo file di default
    string path1 = path + "/" + nome_file_commenti;
    ofstream commenti(path1.c_str(), ios::out);
    if(!commenti){ cerr << "Errore apertura file!"; return;}
    commenti << "";
    commenti.close();
    
    path1 = path + "/" + nome_file_likes;
    ofstream likes(path1.c_str(), ios::out);
    if(!likes){ cerr << "Errore apertura file!"; return;}
    likes << "";
    likes.close();
      
    // Una volta aggiunto un post, incremento l'ID successivo
    id_p++;
    
  } else {
    return;
  }	
}

// Restituisce un puntatore alla lista dei post
map<int,Post>* Bacheca::get_listapost() {
  return &lista_post;
}
