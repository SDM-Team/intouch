#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "bacheca.h"

using namespace std;

// Richiamo la variabile globale id_p per il tracciamento degli ID univoci dei post
extern int id_p;

// Funzione che permette l'aggiunta di un post alla bacheca dell'utente
void Bacheca::aggiungi_post(const string _email){
  int s;
  string titolo;
  string testo;

  // Inserimento testo
  cout << "Inserire Testo Post: " << endl;
  getline(cin,testo);
  
  // Conferma
  cout << "Per confermare e aggiungere il post alla tua Bacheca premi 1: ";
  cin >> s;

  if (s == 1) {
    // Creo un post con le informazioni date
    Post p(id_p,_email,testo);
    
    // Inserisco il post nel map dei post (id,post)
    lista_post.insert(pair<int,Post> (p.get_idpost(),p));

    // Apro un flusso su file in scrittura
    ofstream post("post.csv", ios::app);

    // Scrivo dati su file
    post << id_p << ";";
    post << _email << ";";
    post << p.get_tempo() << ";";
    post << testo << endl;

    // Chiudo il flusso su file
    post.close();
      
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
