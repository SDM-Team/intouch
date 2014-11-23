#include <cstdlib>
#include <iostream>
#include "profilo.h"

using namespace std;

Profilo::Profilo(){
         strcpy(sesso,"non dichiarato");
         professione= "non dichiarata";
         situasent= "non dichiarata"; 
         luogonasc= "non dichiarato";                                        
}

Profilo::Profilo(stringa _sex, string _prof, string _situa, string _luogo){
                       strcpy(sesso, _sex);
                       professione= _prof;
                       situasent= _situa; 
                       luogonasc= _luogo;                      
}

void Profilo::visualizza_profilo(){
         int s=0;
         printf("[NOME COGNOME] \n"); //Prendo il nome e cognome dell'utente e le informazioni sono di default se non modificate
         cout<< "Sesso: "<< sesso<<endl;
         cout<< "Professione: "<<professione<<endl;
         cout<< "Situazione Sentimentale: "<<situasent<<endl;
         cout<< "Data di nascita: "<<datanasc<<endl;
         cout<< "Luogo di nascita: "<< luogonasc<<endl<<endl; 
                  
         cout<< "Per modificare il tuo profilo premi 1"<<endl;
         cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
         cin>> s;
         
         while((s<0)||(s>1)){
                             if((s<0)||(s>1)){cout<< "Errore scelta non possibile"<<endl;}
                             cout<< "Per modificare il tuo profilo premi 1"<<endl;
                             cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                             cin >> s;                             
         }
         switch(s){
                   //case 0: schermata_iniziale(); break;
                   case 1: modifica_profilo(); break;          
         }                                    
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
         cin>> s;
         
         while((s<1)||(s>5)){
                             if((s<1)||(s>5)){cout<< "Errore scelta non possibile"<<endl;}
                             cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
                             cout<< "Per tornare alla schermata iniziale premi 0 "<<endl<<endl;
                             cin >> s;                             
         }
         switch(s){
                   case 1: cout<<"Inserire Sesso: "; cin>>sesso; cout<<endl; break;
                   case 2: cout<<"Inserire Professione: "; cin>>professione; cout<<endl; break;  
                   case 3: cout<<"Inserire situazione sentimentale: "; cin>>situasent; cout<<endl; break;
                   case 4: cout<<"Inserire data di nascita: \n"; datanasc.imposta_data(); cout<<endl; break;
                   case 5: cout<<"Inserire Luogo di nascita: "; cin>>luogonasc; cout<<endl; break;    
         }                                
         visualizza_profilo();                                    
}



