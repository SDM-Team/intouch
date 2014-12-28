#include "utente.h"
#include "intouch.h"
#include "config.h"
//per le prove
#include "post.h"
#include "input.h"

// Variabili di configurazione
extern int id_p;

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

Profilo* Utente::get_profilo() {
  return (&profilo);
}

map<int,Amicizia>* Utente::get_listaamicizie() {
  return (&lista_amicizie);
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
    	    visualizza_bacheca_generale();
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
          bacheca.aggiungi_post(this);
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
  int s = 1;
  cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
  cout<< "1. Sesso: " << profilo.get_sesso() << endl;
  cout<< "2. Professione: " << profilo.get_professione() << endl;
  cout<< "3. Situazione Sentimentale: " << profilo.get_situasent() << endl;
  cout<< "4. Data di nascita: " << profilo.get_datanasc() << endl;
  cout<< "5. Luogo di nascita: " << profilo.get_luogonasc() << endl << endl; 
  cout<< "Per modificare i campi selezionare il numero corrispondente: "<<endl;
  cout<< "Per tornare alla schermata iniziale premi 0" << endl;
         
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
  
  // Aggiorno il .csv se è stato modificato qualcosa
  if (s != 0) {
     string path = path_files_u + get_email() + "/" + nome_file_profilo;
     ofstream file;
     file.open(path.c_str(), ios::out);
     
     file << profilo.get_sesso() << ";"
          << profilo.get_professione() << ";"
          << profilo.get_situasent() << ";"
          << profilo.get_datanasc() << ";"
          << profilo.get_luogonasc() << endl;
          
     file.close();
  }
  
  system("CLS");        
		                            
}


//Bacheca
void Utente::visualizza_bacheca() {
  map<int,Post>::reverse_iterator iter;
  int s = 0;
  
  do{
	cout<< "Bacheca di " << get_nome() << " " << get_cognome()<<endl;
    for (iter = get_bacheca()->get_listapost()->rbegin(); iter != get_bacheca()->get_listapost()->rend(); iter++) {
      /*cout << "ID Post: " << iter->first << endl;
      cout << iter->second.get_testo() << endl;
      cout << iter->second.get_tempo() << endl << endl;*/
      
      iter->second.visualizza_post_light();
    }
                                   
    
    cout<< "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero"<<endl;
    cout<< "Per tornare alla schermata iniziale premi 0"<<endl;
    s = inputInt(0,id_p);
    system("CLS");
    
    if( s == 0){ return; }
    if ( get_bacheca()->get_listapost()->find(s) != get_bacheca()->get_listapost()->end() ){
      	  
			get_bacheca()->get_listapost()->find(s)->second.visualizza_post();
			cout<< "Per commentare il post selezionato premi 1" << endl;
			cout<< "Per mettere[/togliere] \"mi piace\" premi 2" << endl;
			cout<< "Per tornare alla schermata iniziale premi 0" << endl;
      	  int p = inputInt(0,2);
      	  
      	  switch(p){
		    case 0: system("CLS"); return;	
			case 1: get_bacheca()->get_listapost()->find(s)->second.commenta_post(email); break;
			case 2: system("CLS"); cout<<"Liked!" << endl << endl; return;
			
		  }
    system("CLS");  	  
      	  
    }else{ system("CLS"); cerr << "Post non trovato!" << endl << endl;}
    
  }while(s!=0);
  
   
}

void Utente::visualizza_bacheca_generale() {
    map<int,Post*> lista_post_amici;
    map<int,Amicizia>::iterator iter_amicizie;
    map<int,Post>::iterator iter_post;
    int s = 0;
    
    for (iter_amicizie = lista_amicizie.begin(); iter_amicizie != lista_amicizie.end(); iter_amicizie++) {
      if (iter_amicizie->second.get_status() == A) {
        for (iter_post = iter_amicizie->second.get_utente()->get_bacheca()->get_listapost()->begin();
             iter_post != iter_amicizie->second.get_utente()->get_bacheca()->get_listapost()->end();
             iter_post++) {
               lista_post_amici.insert(pair<int,Post*> (iter_post->first, &iter_post->second));
        }
      }
    }
    
    if (lista_post_amici.size() == 0) {
      cout << "Ancora nessun post!" << endl << endl;
      return;
    }
    
    map<int,Post*>::iterator iter_post_amici;
    for (iter_post_amici = lista_post_amici.begin(); iter_post_amici != lista_post_amici.end(); iter_post_amici++) {
      iter_post_amici->second->visualizza_post_light();
    }
    
    cout<< "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero"<<endl;
    cout<< "Per tornare alla schermata iniziale premi 0"<<endl;
    
    s = inputInt(0,id_p);
    system("CLS");
    
    if( s == 0){ return; }
    if ( lista_post_amici.find(s) != lista_post_amici.end() ){
      	  
			lista_post_amici.find(s)->second->visualizza_post();
			cout<< "Per commentare il post selezionato premi 1" << endl;
			cout<< "Per mettere[/togliere] \"mi piace\" premi 2" << endl;
			cout<< "Per tornare alla schermata iniziale premi 0" << endl;
      	  int p = inputInt(0,2);
      	  
      	  switch(p){
		    case 0: system("CLS");
					return;	
			case 1: lista_post_amici.find(s)->second->commenta_post(email);
					break;
			case 2: cout<<"Like!";
					break;
			
		  }
    system("CLS");  	  
      	  
    }else{ system("CLS"); cerr << "Post non trovato!" << endl << endl;}
    
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
