#include <cstdlib>
#include <iostream>
#include <string.h>
#include "profilo.h"

using namespace std;

Profilo::Profilo(){
         sesso="non dichiarato";
         professione= "non dichiarata";
         situasent= "non dichiarata"; 
         luogonasc= "non dichiarato";                                        
}

Profilo::Profilo(stringa _sex, string _prof, string _situa, string _luogo){
                       sesso= _sex;
                       professione= _prof;
                       situasent= _situa; 
                       luogonasc= _luogo;                      
}

void Profilo::modifica_profilo(){
         int s=0;
         cout<< "1. Sesso: "<< sesso<<endl;
         cout<< "2. Professione: "<<professione<<endl;
         cout<< "3. Situazione Sentimentale: "<<situasent<<endl;
         cout<< "4. Data di nascita: "<<datanasc<<endl;
         cout<< "5. Luogo di nascita: "<< luogonasc<<endl<<endl; 
         cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
         cout<< "Per tornare alla schermata iniziale premi 0 "<<endl<<endl;
         
		 //controllo input
		 cin>> s;
         
         while((s<1)||(s>5)){
                             if((s<1)||(s>5)){cout<< "Errore scelta non possibile"<<endl;}
                             cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
                             cout<< "Per tornare alla schermata iniziale premi 0 "<<endl<<endl;
                             //controllo input
							 cin >> s;                             
         }
         switch(s){
                   case 1: cout<<"Inserire Sesso: "; cin>>sesso; cout<<endl; break;
                   case 2: cout<<"Inserire Professione: "; cin>>professione; cout<<endl; break;  
                   case 3: cout<<"Inserire situazione sentimentale: "; cin>>situasent; cout<<endl; break;
                   case 4: cout<<"Inserire data di nascita: \n"; datanasc.imposta_data(); cout<<endl; break;
                   case 5: cout<<"Inserire Luogo di nascita: "; cin>>luogonasc; cout<<endl; break;    
         }                                
//         visualizza_profilo();                                    
}

string Profilo::get_sesso() {
    return sesso;
}

string Profilo::get_professione() {
    return professione;
}

string Profilo::get_situasent() {
    return situasent;
}

data Profilo::get_datanasc() {
    return datanasc;
}

string Profilo::get_luogonasc() {
    return luogonasc;
}
