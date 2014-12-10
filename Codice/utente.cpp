#include "utente.h"
#include "intouch.h"

//per le prove
#include "post.h"
#include "input.h"

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

Bacheca* Utente::get_bacheca() {
  return (&bacheca);
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
  string t;
    do { 
	   
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
	
	  s = inputInt(1,7);
      
      system("CLS");
      switch (s) {
        case 1:
          gestisci_amicizie();
          break;
        case 2:
    	  
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
          bacheca.aggiungi_post(email);
          break;
        case 7:
          break;
    	}
	  } while(s != 7);
    
    //if (s == 7){
    cout << "Logout effettuato!" << endl << endl;
    logout();	
    //}
  
}

// Metodo di logout, rimanda alla schermata di autenticazione
void Utente::logout() {
  return;
}

void Utente::visualizza_profilo(){
  int s=0;
  
  do{       
      //Prendo il nome e cognome dell'utente e le informazioni sono di default se non modificate
    cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
    cout << "Sesso: "<< profilo.get_sesso() <<endl;
    cout << "Professione: " << profilo.get_professione() <<endl;
    cout << "Situazione Sentimentale: " << profilo.get_situasent() <<endl;
    cout << "Data di nascita: " << profilo.get_datanasc() <<endl;
    cout << "Luogo di nascita: " << profilo.get_luogonasc() <<endl<<endl; 
  
    cout << "Per modificare il tuo profilo premi 1"<<endl;
    cout << "Per tornare alla schermata iniziale premi 0"<<endl;
  
    s = inputInt(0,1);
    
    system("CLS");                                                                            
    switch(s){
      case 0: 
		return; //ritorna alla schermata iniziale
      case 1: 
		modifica_profilo();
		break;          
    } 
  }while(s!=0);
}

void Utente::modifica_profilo(){
  int s=1;
  cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
  cout<< "1. Sesso: "<< profilo.get_sesso()<<endl;
  cout<< "2. Professione: "<<profilo.get_professione()<<endl;
  cout<< "3. Situazione Sentimentale: "<<profilo.get_situasent()<<endl;
  cout<< "4. Data di nascita: "<<profilo.get_datanasc()<<endl;
  cout<< "5. Luogo di nascita: "<< profilo.get_luogonasc()<<endl<<endl; 
  cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
  cout<< "Per tornare alla schermata iniziale premi 0 "<<endl;
         
  s = inputInt(0,5);
         
  string modificaStringa;
         
  switch(s){
    case 0:
	  system("CLS");
	  return; //rimanda al profilo 
    case 1:
      cout<<"Inserire Sesso (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_sesso(modificaStringa);
      cout<<endl;
      break;
    case 2:
      cout<<"Inserire Professione (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_professione(modificaStringa);
      cout<<endl;
      break;
    case 3:
      cout<<"Inserire situazione sentimentale (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_situasent(modificaStringa);
      cout<<endl;
      break;
    case 4:
      cout<<"Inserire data di nascita: \n";
      profilo.set_datanasc();
      cout<<endl;
      break;
    case 5:
      cout<<"Inserire Luogo di nascita (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_luogonasc(modificaStringa);
      cout<<endl;
      break;
  }                                
  system("CLS");        
		                            
}


//Bacheca
void Utente::visualizza_bacheca() {
  map<int,Post>::reverse_iterator iter;
  int s=0;
  
  do{
    
	cout<< "Bacheca di " << get_nome() << " " << get_cognome()<<endl;
    for (iter = get_bacheca()->get_listapost()->rbegin(); iter != get_bacheca()->get_listapost()->rend(); iter++) {
      cout << "ID Post: " << iter->first << endl;
      cout << iter->second.get_testo() << endl;
      cout << iter->second.get_tempo() << endl << endl;
    }
                                   
    
    cout<< "Per modificare la tua bacheca premi 1"<<endl;
    cout<< "Per tornare alla schermata iniziale premi 0"<<endl;
    s = inputInt(0,1);
    
    system("CLS");
    switch(s){
      case 0: 
	    return;
		//ritorna alla schermata iniziale 
      case 1: 
	    modifica_bacheca();
	    break;          
    }
    
  }while(s!=0);
   
}

void Utente::modifica_bacheca(){
  int s=0;
  do{
    cout<< "Bacheca di " << get_nome() << " " << get_cognome()<<endl; 
    cout<< "Modifica bacheca"<<endl;
    //opzioni da implementare 

    cout<< "Per modificare nuovamente la tua bacheca premi 1"<<endl;
    cout<< "Per tornare alla bacheca premi 0"<<endl;
    s = inputInt(0,1);
  
    system("CLS");
    switch(s){
      case 0: 
	    return;
		//ritorna alla bacheca 
      case 1: 
	    break;          
    }
  
  }while(s == 1);                                      
}
                                    
void Utente::visualizza_amici() {
    map<int,Amicizia>::iterator iter;
    for (iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++) {
       if (iter->second.get_status() == A) {
          cout << iter->second.get_utente()->get_nome() << " " << iter->second.get_utente()->get_cognome() << endl;
       } else {
          continue;
       }
    }
}

void Utente::gestisci_amicizie() {
  int s=0;
  do{
    cout << "Seleziona la funzione desiderata:" << endl;
    cout << "1. Richiedi amicizia" << endl;
    cout << "2. Accetta/rifiuta amicizia" << endl;
    cout << "3. Cancella amicizia" << endl;
    cout << "Premi 0 per tornare alla schermata iniziale" << endl;
    s = inputInt(0,3);
    
    system("CLS");
    switch (s) {
      case 0:
        return; //riporta alla schermata iniziale
      case 1:
//      richiedi_amicizia();
        break;
      case 2:
        cout << "A/R amicizia" << endl;
        break;
      case 3:
        cout << "Canc amicizia" << endl;
        break;      
	}
  }while(s != 0);
  
}
