#include "bacheca.h"
#include <cstdlib>
#include <iostream>
#include "utente.h"
extern Utente utente;
using namespace std;

void Bacheca::visualizza_bacheca(){
                                   cout<< "Bacheca di "; utente.get_nc(); cout<<endl; 
                                   //prendo la lista di post (da implementare)
                                   
                                   int s;
                                   cout<< "Per modificare la tua bacheca premi 1"<<endl;
                                   cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                                   cin>> s;
         
                                   while((s<0)||(s>1)){
                                   if((s<0)||(s>1)){cout<< "Errore scelta non possibile"<<endl;}
                                   cout<< "Per modificare la tua bacheca premi 1"<<endl;
                                   cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                                   cin >> s;                             
         }   
                                   switch(s){
                                   case 0: utente.schermata_iniziale(); break;
                                   case 1: modifica_bacheca(); break;          
         }                                         
}

void Bacheca::modifica_bacheca(){
                                 cout<< "Bacheca di "; utente.get_nc(); cout<<endl;
                                 cout<< "Modifica bacheca"<<endl;
                                 //opzioni da implementare 
                                  
                                 int s;
                                   cout<< "Per modificare nuovamente la tua bacheca premi 1"<<endl;
                                   cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                                   cin>> s;
         
                                   while((s<0)||(s>1)){
                                   if((s<0)||(s>1)){cout<< "Errore scelta non possibile"<<endl;}
                                   cout<< "Per modificare nuovamente la tua bacheca premi 1"<<endl;
                                   cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                                   cin >> s;                             
         }   
                                   switch(s){
                                   case 0: utente.schermata_iniziale(); break;
                                   case 1: modifica_bacheca(); break;          
         }                                         
}
                                    


