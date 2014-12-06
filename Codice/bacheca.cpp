#include <cstdlib>
#include <iostream>
#include <string>
#include "bacheca.h"
#include <sstream>
#include <fstream>
using namespace std;

void Bacheca::aggiungi_post(const Post& p){
   int s;
   cout<<"Post %d "<<p.get_idpost()<<endl;
   cout<<"Inserire Titolo Post: "<<endl << p.get_titolo()<<endl;
   cout<<"Inserire Testo Post: "<<endl<< p.get_testo()<<endl;
   cout<<"Per confermare e aggiungere il post alla tua Bacheca premi 1: ";
   cin>>s; 
   lista_post.insert(pair<int,Post> (p.get_idpost(),p));   
             
    ofstream post("post.csv", ios::app);
    
    post << p.get_idpost() << ";";
    post << p.get_titolo() << ";";
    post << p.get_testo();
    
    post.close();
                    
}

void Bacheca::importa_post() {
    lista_post.clear();
    ifstream post;
    
    char linea[150];
    
    post.open("post.csv", ios::in);
    while (!post.getline(linea,150).eof()) {
       char* pch;
       
       //token ID post
       pch = strtok (linea,";");
       int id_post = atoi(pch);
       
       // token titolo
       string titolo = strtok (NULL,";");
       
       // token testo
       string testo = strtok (NULL,";");
       
       
       Post p(titolo, testo);
       
       lista_post.insert(pair<int,Post> (id_post,p));
       
       id_post = id_post + 1;
    } 
    
    post.close();
}

