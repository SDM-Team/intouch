#include "utente.h"
#include "intouch.h"
#include <sstream>

//per le prove
#include "post.h"

extern InTouch applicazione;

int id_u = 1;

// Costruttore specifico a due parametri per la procedura di login
Utente::Utente(string e, string p) {
    id_utente = 0;
    nome = "";
    cognome = "";
    email = e;
    password = p;
}

// Costruttore specifico a quattro parametri per la procedura di creazione utente
Utente::Utente(string n, string c, string e, string p) {
    id_utente = id_u;
    nome = n;
    cognome = c;
    email = e;
    password = p;
}

int Utente::get_idutente() const {
    return id_utente;
}

string Utente::get_nome() const {
    return nome;
}

string Utente::get_cognome() const {
    return cognome;
}

string Utente::get_email() const {
    return email;
}

string Utente::get_password() const {
    return password;
}

// Metodo che stampa i dati di un utente
void Utente::stampa() {
    cout << id_utente << endl;
    cout << nome << endl;
    cout << cognome << endl;
    cout << email << endl;
    cout << password << endl << endl;
}

// Schermata iniziale che si visualizza una volte autenticato correttamente
void Utente::schermata_iniziale() {
    int s = 7;
    string input = "";
    do{ 
	//che belo l menu tuto pulito ara
	//system("CLS");
	
	if ((s < 1) || (s > 7)) {
        cout << "Errore: Scelta non possibile" << endl << endl;
    }
    
	//schermata iniziale
    cout << "Benvenuto!" << endl;
    cout << "Seleziona la funzione desiderata:" << endl;
    cout << "1. Gestisci amicizie" << endl;
    cout << "2. Visualizza i post degli amici" << endl;
    cout << "3. Visualizza la tua bacheca" << endl;
    cout << "4. Visualizza e modifica il tuo profilo" << endl;
    cout << "5. Visualizza il profilo e la bacheca di un amico" << endl;
    cout << "6. Crea post" << endl;
    cout << "7. Logout" << endl;
	
	//controllo input non-int
 	while (true) {
 	   		cin.clear();
  			getline(cin, input);
  			
   			//Questo codice converte da stringa a int in modo sicuro
   			stringstream myStream(input);
   			if (myStream >> s)
     				break;
   			cout << "Errore: numero non valido" << endl;
 	}
 	
    cout << endl;
    
    
    switch (s) {
       case 1:
          // Amicizie
          break;
       case 2:
          // Post amici
          break;
       case 3:
          visualizza_bacheca();
          break;
       case 4:
          visualizza_profilo();
          break;
       case 5:
          // Profilo e bacheca amico
          break;
       case 6:
          // Crea post
          //prove post e commenti
          {
		  string s = "ciao come va?";
		  string t = "titolonzo";
		  Post a(s);
		  Post b(t,s);
		  b.commenta_post();
		  b.visualizza_post();
		  system("PAUSE");
		  }
          break;
       case 7:
          break;
    	}
	}while(s != 7);
    
    //if (s == 7){
    cout << "Logout effettuato!" << endl << endl;
    logout();	
    //}
    
}

// Metodo di logout, rimanda alla schermata di autenticazione
void Utente::logout() {
    applicazione.schermata_autenticazione();
}

void Utente::visualizza_profilo(){
         int s=0;
         string input = "";
         
         
         //Prendo il nome e cognome dell'utente e le informazioni sono di default se non modificate
         cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
         cout << "Sesso: "<< profilo.get_sesso() <<endl;
         cout << "Professione: " << profilo.get_professione() <<endl;
         cout << "Situazione Sentimentale: " << profilo.get_situasent() <<endl;
         cout << "Data di nascita: " << profilo.get_datanasc() <<endl;
         cout << "Luogo di nascita: " << profilo.get_luogonasc() <<endl<<endl; 
                  
         cout << "Per modificare il tuo profilo premi 1"<<endl;
         cout << "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
        
         do{
              if((s<0)||(s>1)){cout<< "Errore scelta non possibile"<<endl;
                               cout<< "Per modificare il tuo profilo premi 1"<<endl;
                               cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                               }
         //controllo input non-int
 	     while (true) {
 	   		cin.clear();
  			getline(cin, input);
  			
   			//Questo codice converte da stringa a int in modo sicuro
   			stringstream myStream(input);
   			if (myStream >> s)
     				break;
   			cout << "Errore: numero non valido" << endl;
   			
 	  }
         
         }while((s<0)||(s>1));
                                                                                     
         switch(s){
                   case 0: schermata_iniziale(); break;
                   case 1: modifica_profilo(); break;          
         } 
                                            
}

void Utente::modifica_profilo(){
         int s=1;
         string input = "";
         cout<< "1. Sesso: "<< profilo.get_sesso()<<endl;
         cout<< "2. Professione: "<<profilo.get_professione()<<endl;
         cout<< "3. Situazione Sentimentale: "<<profilo.get_situasent()<<endl;
         cout<< "4. Data di nascita: "<<profilo.get_datanasc()<<endl;
         cout<< "5. Luogo di nascita: "<< profilo.get_luogonasc()<<endl<<endl; 
         cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
         cout<< "Per tornare alla schermata iniziale premi 0 "<<endl<<endl;
         
		  do{
              if((s<1)||(s>5)){cout<< "Errore scelta non possibile"<<endl;
                               cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
                               cout<< "Per tornare alla schermata iniziale premi 0"<<endl<<endl;
                               }
         //controllo input non-int
 	     while (true) {
 	   		cin.clear();
  			getline(cin, input);
  			
   			//Questo codice converte da stringa a int in modo sicuro
   			stringstream myStream(input);
   			if (myStream >> s)
     				break;
   			cout << "Errore: numero non valido" << endl;
   			
 	    }
        
        }while((s<1)||(s>5));
      
         
         string modificaStringa;
         
         switch(s){
                   case 1:
                      cout<<"Inserire Sesso: ";
                      cin >> modificaStringa; cin.ignore();
                      profilo.set_sesso(modificaStringa);
                      cout<<endl;
                      break;
                   case 2:
                      cout<<"Inserire Professione: ";
                      cin>>modificaStringa; cin.ignore();
                      profilo.set_professione(modificaStringa);
                      cout<<endl;
                      break;
                   case 3:
                      cout<<"Inserire situazione sentimentale: ";
                      cin>>modificaStringa; cin.ignore();
                      profilo.set_situasent(modificaStringa);
                      cout<<endl;
                      break;
                   case 4:
                      cout<<"Inserire data di nascita: \n";
                      profilo.set_datanasc();
                      cout<<endl;
                      break;
                   case 5:
                      cout<<"Inserire Luogo di nascita: ";
                      cin>>modificaStringa; cin.ignore();
                      profilo.set_luogonasc(modificaStringa);
                      cout<<endl;
                      break;
         }                                
         visualizza_profilo();                                    
}


//Bacheca
void Utente::visualizza_bacheca(){
                                   cout<< "Bacheca di " << get_nome() << " " << get_cognome()<<endl; 
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
                                   case 0: schermata_iniziale(); break;
                                   case 1: modifica_bacheca(); break;          
         }                                         
}

void Utente::modifica_bacheca(){
                                 cout<< "Bacheca di " << get_nome() << " " << get_cognome()<<endl; 
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
                                   case 0: schermata_iniziale(); break;
                                   case 1: modifica_bacheca(); break;          
         }                                         
}
                                    






