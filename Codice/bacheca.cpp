#include <cstdlib>
#include <iostream>
#include <string>
#include "bacheca.h"
#include <sstream>
#include <fstream>
using namespace std;

extern int id_p;

void Bacheca::aggiungi_post(const string _email){
   int s;
   string titolo;
   string testo;
   
   cout<<"Inserire Titolo Post: "<<endl;
   cin >> titolo;
   cout<<"Inserire Testo Post: "<<endl;
   cin >> testo;
   cout<<"Per confermare e aggiungere il post alla tua Bacheca premi 1: ";
   cin>>s;

   if (s == 1) {
      Post p(id_p,_email,titolo,testo);
      lista_post.insert(pair<int,Post> (p.get_idpost(),p));
             
      ofstream post("post.csv", ios::app);
    
      post << id_p << ";";
      post << _email << ";";
      post << titolo << ";";
      post << testo << endl;
    
      post.close();
      
      id_p++;
    } else {return;}
                    
}

map<int,Post> Bacheca::get_listapost() const {
    return lista_post;
}
