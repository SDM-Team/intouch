#include <cstdlib>		/* system								*/
#include <cstring>		/* strtok								*/
#include <fstream>		/* ofstream, ifstream					*/
#include <iostream>		/* cout, endl, cerr						*/
#include <map>			/* map, map::iterator					*/
#include <string>		/* string								*/

// Librerie personalizzate
#include "utente.h"		/* Libreria di riferimento 				*/
#include "amicizia.h"	/* classe Amicizia e metodi relativi 	*/
#include "config.h"		/* Definizione variabili globali 		*/
#include "input.h"		/* inputInt, inputString, inputPassword */
#include "intouch.h"	/* classe InTouch e metodi relativi 	*/
#include "post.h"		/* classe Post e metodi relativi 		*/
#include "profilo.h"	/* classe Profilo e metodi relativi 	*/

// Namespace
using namespace std;

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

// Costruttore di copia
Utente::Utente(const Utente& u){
  id_utente = u.id_utente;
  nome= u.nome;
  cognome= u.cognome;
  email= u.email;
  password= u.password;
  bacheca= u.bacheca;
  profilo= u.profilo;
  lista_amicizie = u.lista_amicizie;
}

// Restituisce l'id dell'utente
int Utente::get_idutente() const {
  return id_utente;
}

// Restituisce il nome dell'utente
string Utente::get_nome() const {
  return nome;
}

// Restituisce il cognome dell'utente
string Utente::get_cognome() const {
  return cognome;
}

// Restituisce l'indirizzo email dell'utente
string Utente::get_email() const {
  return email;
}

// Restituisce la password dell'utente
string Utente::get_password() const {
  return password;
}

// Restituisce un puntatore alla bacheca dell'utente
Bacheca* Utente::get_bacheca() {
  return (&bacheca);
}

// Restituisce un puntatore al profilo dell'utente
Profilo* Utente::get_profilo() {
  return (&profilo);
}

// Restituisce un puntatore alla lista di amicizie dell'utente
map<int,Amicizia>* Utente::get_listaamicizie() {
  return (&lista_amicizie);
}

// Schermata iniziale che si visualizza una volta autenticati correttamente
void Utente::schermata_iniziale(map<string,Utente>* lista_utenti_p) {
  int s = 7;
  do { 
    // Schermata iniziale
    cout << "Benvenuto in InTouch!" << endl;
      
    // Eventuale notifica di richieste di amicizia in attesa di risposta
    if (num_richieste_pendenti() == 1) {
      cout << endl << "Hai " << num_richieste_pendenti() << " richiesta di amicizia in attesa!" << endl << endl;
    } else if (num_richieste_pendenti() > 1) {
      cout << endl << "Hai " << num_richieste_pendenti() << " richieste di amicizia in attesa!" << endl << endl;
    }
      
    // Voci di menu
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
        // Gestione amicizie
        gestisci_amicizie(lista_utenti_p);
        break;
      case 2:
        // Visualizzazione bacheca generale (post amici)
        visualizza_bacheca_generale();
        break;
      case 3:
        // Visualizzazione propria bacheca
        visualizza_bacheca();
        break;
      case 4:
        // Visualizzazione/modifica proprio profilo
        visualizza_profilo();
        break;
      case 5:
        // Visualizzazione profilo e bacheca amico
        visualizza_contenuto_amici();
        break;
      case 6:
        // Creazione post
        bacheca.aggiungi_post(this);
        break;
      case 7:
        // Esce dallo switch ed effettua il logout
        break;
    }
  } while(s != 7);
    
  // Se si preme 7, si procede al logout
  logout();
}

// Metodo di logout, rimanda alla schermata di autenticazione
void Utente::logout() {
  cout << "Logout effettuato!" << endl << endl;
  return;
}

void Utente::visualizza_profilo(){
  int s=0;
  do {       
    // Stampa nome e cognome dell'utente
    cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
    
    // Stampa le sue informazioni
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
      	//ritorna alla schermata iniziale
        return;
      case 1: 
        // Modifica profilo
        modifica_profilo();
        break;          
    }
  } while(s!=0);
}

void Utente::visualizza_profilo_amico(){
  // Stampa nome e cognome dell'amico
  cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
  
  // Stampa le sue informazioni
  cout << "Sesso: "<< profilo.get_sesso() <<endl;
  cout << "Professione: " << profilo.get_professione() <<endl;
  cout << "Situazione Sentimentale: " << profilo.get_situasent() <<endl;
  cout << "Data di nascita: " << profilo.get_datanasc() <<endl;
  cout << "Luogo di nascita: " << profilo.get_luogonasc() <<endl<<endl;
  cout << "Per tornare alla schermata precedente premi 0" <<endl;
  
  int c;
  c = inputInt(0,0); // l'utente può solo tornare alla schermata iniziale
  system("CLS");  
}

void Utente::modifica_profilo(){
  int s = 1;
  
  // Stampa nome e cognome dell'utente
  cout << "[" << get_nome() << " " << get_cognome() << "]" << endl;
  
  // Stampa le sue informazioni
  cout << "1. Sesso: " << profilo.get_sesso() << endl;
  cout << "2. Professione: " << profilo.get_professione() << endl;
  cout << "3. Situazione Sentimentale: " << profilo.get_situasent() << endl;
  cout << "4. Data di nascita: " << profilo.get_datanasc() << endl;
  cout << "5. Luogo di nascita: " << profilo.get_luogonasc() << endl << endl; 
  cout << "Per modificare i campi selezionare il numero corrispondente"<<endl;
  cout << "Per tornare alla visualizzazione del profilo premi 0" << endl;

  // Richiede quale campo si desidera modificare
  s = inputInt(0,5);

  string modificaStringa;

  switch(s){
    case 0:
      // Ritorno alla visualizzazione del profilo
  	  system("CLS");
      return;
    case 1:
      // Modifica sesso
      cout << "Inserire Sesso (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_sesso(modificaStringa);
      cout << endl;
      break;
    case 2:
      // Modifica professione
      cout << "Inserire Professione (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_professione(modificaStringa);
      cout << endl;
      break;
    case 3:
      // Modifica situazione sentimentale
      cout << "Inserire situazione sentimentale (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_situasent(modificaStringa);
      cout << endl;
      break;
    case 4:
      // Modifica data di nascita
      cout << "Inserire data di nascita: \n";
      profilo.set_datanasc();
      cout << endl;
      break;
    case 5:
      // Modifica luogo di nascita
      cout << "Inserire Luogo di nascita (max " << MAXLUN << " caratteri): ";
      modificaStringa = inputString(MAXLUN);
      profilo.set_luogonasc(modificaStringa);
      cout << endl;
      break;
  }
  
  // Aggiorna il .csv se è stato modificato qualcosa
  if (s != 0) {
    // Apre il file relativo al profilo dell'utente, sovrascrivendo il contenuto precedente (ios::out)
    string path = path_files_u + get_email() + "/" + nome_file_profilo;
    ofstream file;
    file.open(path.c_str(), ios::out);
     
    // Sovrascrive le informazioni precedentemente presenti stampando quelle nuove
    file << profilo.get_sesso() << "\t";
    file << profilo.get_professione() << "\t";
    file << profilo.get_situasent() << "\t";
    file << profilo.get_datanasc() << "\t";
    file << profilo.get_luogonasc() << endl;
          
    // Chiude il file
    file.close();
  }

  system("CLS");
}

// Bacheca
void Utente::visualizza_bacheca() {
  map<int,Post>::reverse_iterator iter;
  int s = 0;
  int p = 0;
  int count = 0;
  do {
    // Stampa il nome del proprietario della bacheca
    cout << "Bacheca di " << get_nome() << " " << get_cognome() << endl << endl;
	  
    // Stampa tutti i post in maniera compatta
    for (iter = get_bacheca()->get_listapost()->rbegin(); iter != get_bacheca()->get_listapost()->rend(); iter++) {
      iter->second.visualizza_post_light();
      count++;
    }
    
    // Se non ci sono post rimando alla schermata iniziale
    if( count == 0) { 
      system("CLS");
      cout << "Non ci sono post nella bacheca!" << endl << endl;
      return;
    }
    
    cout << "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero";
    cout << "Per tornare alla schermata precedente premi 0" << endl;
    map<int,Post>::iterator piter;
    do { // Ciclo per controllo input post
      s = inputInt(0, (id_p-1) );
      if(s == 0){ system("CLS"); return; }
      piter = get_bacheca()->get_listapost()->find(s);
      if( piter == get_bacheca()->get_listapost()->end() ){ cerr << "Post non trovato! Reinserire: "; }
    } while( piter == get_bacheca()->get_listapost()->end() );   
    
    system("CLS");
    
    do { // Ciclo per tornare a visualizzazione post dopo aver commentato o messo mi piace
      // Se viene selezionato un post in particolare, lo visualizza in modo dettagliato
	  
  	  get_bacheca()->get_listapost()->find(s)->second.visualizza_post();
  	  cout << "Per commentare il post selezionato premi 1" << endl;
  	  cout << "Per";
    
      if (get_bacheca()->get_listapost()->find(s)->second.check_like(get_email())) {
        cout << " togliere ";
      } else {
        cout << " mettere ";
      }
    
      cout << "\"mi piace\" premi 2" << endl;
  	  cout << "Per tornare alla bacheca premi 0" << endl;
      p = inputInt(0,2);

   	  switch(p){
        case 0: 
          // Ritorno alla bacheca completa
          system("CLS");
          break;
        case 1:
          // Aggiunta commento al post
          get_bacheca()->get_listapost()->find(s)->second.commenta_post(this);
          break;
        case 2:
          // Aggiunta like al post
          get_bacheca()->get_listapost()->find(s)->second.aggiungi_like(this);
          break;
      }
    } while (p!=0);
  } while (true);
}

// Bacheca amici, per ritornare alla schermata di selezione degli amici
void Utente::visualizza_bacheca_amico(Utente* u){
  map<int,Post>::reverse_iterator iter;
  int s = 0;
  int p = 0;
  int count = 0;
  do {
    // Stampa il nome del proprietario della bacheca
    cout << "Bacheca di " << get_nome() << " " << get_cognome() << endl << endl;
	  
    // Stampa tutti i post in maniera compatta
    for (iter = get_bacheca()->get_listapost()->rbegin(); iter != get_bacheca()->get_listapost()->rend(); iter++) {
      iter->second.visualizza_post_light();
      count++;
    }
    
    // Se non ci sono post rimando alla schermata iniziale
    if( count == 0) { 
      system("CLS");
      cout << "Non ci sono post nella bacheca!" << endl << endl;
      return;
    }
    
    cout << "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero";
    cout << "Per tornare alla schermata precedente premi 0" << endl;
    map<int,Post>::iterator piter;
    do { // Ciclo per controllo input post
      s = inputInt(0, (id_p-1) );
      if(s == 0){ system("CLS"); return; }
      piter = get_bacheca()->get_listapost()->find(s);
      if( piter == get_bacheca()->get_listapost()->end() ){ cerr << "Post non trovato! Reinserire: "; }
    } while( piter == get_bacheca()->get_listapost()->end() );   
    
    system("CLS");
    
    do { // Ciclo per tornare a visualizzazione post dopo aver commentato o messo mi piace
      // Se viene selezionato un post in particolare, lo visualizza in modo dettagliato
	  
  	  get_bacheca()->get_listapost()->find(s)->second.visualizza_post();
      cout << "Per commentare il post selezionato premi 1" << endl;
  	  cout << "Per";
    
      if (get_bacheca()->get_listapost()->find(s)->second.check_like(u->get_email())) {
        cout << " togliere ";
      } else {
        cout << " mettere ";
      }
    
      cout << "\"mi piace\" premi 2" << endl;
  	  cout << "Per tornare alla bacheca premi 0" << endl;
      p = inputInt(0,2);

      switch(p){
        case 0: 
          // Ritorno alla bacheca completa
          system("CLS");
          break;
        case 1:
          // Aggiunta commento al post
          get_bacheca()->get_listapost()->find(s)->second.commenta_post(u);
          break;
        case 2:
          // Aggiunta like al post
          system("CLS");
          get_bacheca()->get_listapost()->find(s)->second.aggiungi_like(u);
  	      break;
  	  }
    } while( p!=0 );
  } while(true); 
}

void Utente::visualizza_bacheca_generale() {
  map<int,Post*> lista_post_amici;
  map<int,Amicizia>::iterator iter_amicizie;
  map<int,Post>::iterator iter_post;
  int s = 0;
  int p = 0;

  // Scorre la lista di amicizie dell'utente
  for (iter_amicizie = lista_amicizie.begin(); iter_amicizie != lista_amicizie.end(); iter_amicizie++) {
    // Se l'amicizia è accettata
    if (iter_amicizie->second.get_status() == A) {
      // Scorre i post dell'amico e ne inserisce un puntatore in un map, utilizzando l'id del post come key
      for (iter_post = iter_amicizie->second.get_utente()->get_bacheca()->get_listapost()->begin();
           iter_post != iter_amicizie->second.get_utente()->get_bacheca()->get_listapost()->end();
           iter_post++) {
        lista_post_amici.insert(pair<int,Post*> (iter_post->first, &iter_post->second));
      }
    }
  }

  // Se la nuova lista è vuota, comunica che non ci sono ancora post degli amici
  if (lista_post_amici.size() == 0) {
    cout << "Ancora nessun post!" << endl << endl;
    return;
  }
  do { // Ciclo che fa tornare alla bacheca da visualizzazione post dettagliata
    // Altrimenti stampa l'elenco dei post degli amici in ordine cronologico inverso ed in modo compatto
    map<int,Post*>::iterator iter_post_amici;
    for (iter_post_amici = lista_post_amici.begin(); iter_post_amici != lista_post_amici.end(); iter_post_amici++) {
      iter_post_amici->second->visualizza_post_light();
    }

    cout<< "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero";
    cout<< "Per tornare alla schermata iniziale premi 0"<<endl;
  
    do { // Controllo input fino a inserimento post valido
      s = inputInt(0, (id_p-1) );
      // Ritorno alla schermata iniziale
      if( s == 0){ system("CLS"); return; }
      if( lista_post_amici.find(s) == lista_post_amici.end() ) {
        cerr << "Post non trovato!" << endl;
        cout << "Reinserire: ";
      }
    } while( lista_post_amici.find(s) == lista_post_amici.end() );
    
  	system("CLS");    
    // Se viene selezionato un post, lo visualizza in modo dettagliato
    do { // Ciclo che torna al post se viene commentato o messo mi piace
      lista_post_amici.find(s)->second->visualizza_post();
  	  cout << "Per commentare il post selezionato premi 1" << endl;
      cout << "Per";
    
      if (get_bacheca()->get_listapost()->find(s)->second.check_like(get_email())) {
        cout << " togliere ";
      } else {
        cout << " mettere ";
      }
    
      cout << "\"mi piace\" premi 2" << endl;
  	  cout << "Per tornare alla bacheca premi 0" << endl;
      p = inputInt(0,2);
    
      switch(p){
        case 0:
          // Ritorno alla bacheca generale completa        
          system("CLS");
          break;	
        case 1:
          // Aggiunta commento al post
          lista_post_amici.find(s)->second->commenta_post(this);
          break;
        case 2:
          // Aggiunta like al post
          lista_post_amici.find(s)->second->aggiungi_like(this);
          break;
   	  }
    } while( p!=0 );
  } while(true); 
}

// Metodo che permette di visualizzare il profilo e la bacheca di un amico
void Utente::visualizza_contenuto_amici(){
  int t;
  do {
    // Mostra elenco degli amici
    map<int,Amicizia>::iterator iter;
    int count = 0;
    cout << "Lista amici:" << endl << endl;			
  
    // Scorro lista amicizie
    for (iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++) {
      // Se lo stato dell'amicizia è A (accettata) stampo l'amico nella lista amicizie
      if (iter->second.get_status() == A) {
        cout << "#" << iter->first <<" - ";
        cout << iter->second.get_utente()->get_cognome() << " ";
        cout << iter->second.get_utente()->get_nome() << " (";
        cout << iter->second.get_utente()->get_email() << ")" << endl;
        count++;
      }
      // Altrimenti continuo a scorrere la lista amicizie 
    }
  
    // Se lista amicizie è vuota stampo "Ancora nessun amico!"
    if(count == 0){
  	  system("CLS");
      cout << "Ancora nessun amico!" << endl << endl;
      return;
    } 
                                                                   
    int s = 0;
    // Menù di scelta
    cout << endl;
    cout << "Selezionare il numero dell'amico per visualizzare le sue informazioni " << endl;         
    cout << "Per tornare alla schermata iniziale premi 0" << endl;

    do {
      s = inputInt(0, (id_u-1) );
      // Ritorno alla schermata iniziale se la scelta è 0
      if(s == 0){system("CLS"); return;}
      // Cerco l'amico selezionato nella lista amicizie
      iter = lista_amicizie.find(s); 
      // Se non lo trovo, stampo "Non è amico"
      if(iter == lista_amicizie.end()) {cerr << "Non e' tuo amico! Riseleziona: ";}                              
    } while(iter == lista_amicizie.end()); // Continuo finchè non viene selezionato un amico
    system("CLS");
    do { // Ciclo per tornare al menu di selezione dopo aver visualizzato bacheca o profilo
      
      cout << "#" << iter->first << " - ";
      cout << iter->second.get_utente()->get_nome() << " ";
      cout << iter->second.get_utente()->get_cognome() << " (";
      cout << iter->second.get_utente()->get_email() << ")" << endl << endl;
	
      // Menù di scelta         
      cout << "Per visualizzare la sua bacheca premi 1" << endl;
      cout << "Per visualizzare il suo profilo premi 2" << endl;
      cout << "Per tornare alla selezione dell'amico premi 3" << endl;
      cout << "Per tornare alla schermata iniziale premi 0" << endl;

      t = inputInt(0,3);
      system("CLS");

      switch(t){
        case 1:
          // Visualizzo bacheca amico
          iter->second.get_utente()->visualizza_bacheca_amico(this);
          break;
        case 2:
          // Visualizzo profilo amico
          iter->second.get_utente()->visualizza_profilo_amico();
          break;
        case 3:
          // Torno alla schermata di selezione dell'amico
          break;
        case 0:
          // Torno alla schermata iniziale
          return;                    
      }
    } while(t!=0 && t!=3);
  } while (t!=0); // Continuo finchè t=0         
}

// Metodo che permette di visualizzare gli amici                                
void Utente::visualizza_amici() {
  map<int,Amicizia>::iterator iter;
  int count = 0;
  int s = 0;
  cout << "Lista amici:" << endl << endl;
				
  
  // Scorro lista amicizie
  for (iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++) {
    // Se lo stato dell'amicizia è A (accettata) stampo l'amico nella lista amicizie
    if (iter->second.get_status() == A) {
      cout << iter->first <<" - ";
      cout << iter->second.get_utente()->get_nome() << " " << iter->second.get_utente()->get_cognome() << endl;
      count++;
    }
    // Altrimenti continuo a scorrere la lista amicizie 
  }
  
  // Se lista amicizie è vuota stampo "Ancora nessun amico!"
  if(count == 0){
  	system("CLS");
    cout << "Ancora nessun amico!" << endl << endl;
    return;
  } 
  cout << endl;
  cout << "Premi 0 per tornare alla schermata precedente" << endl;
  s = inputInt(0,0);
  
  // Rimanda alla schermata precedente
  system("CLS");
}

// Metodo per gestire amicizie
void Utente::gestisci_amicizie(map<string,Utente>* lista_utenti_p) {
  int s=0;
  do {
    // Menù di scelta
    cout << "Seleziona la funzione desiderata:" << endl;
    cout << "1. Richiedi amicizia" << endl;
    cout << "2. Accetta/rifiuta amicizia" << endl;
    cout << "3. Cancella amicizia" << endl;
    cout << "4. Visualizza amicizie" << endl;
    cout << "Premi 0 per tornare alla schermata iniziale" << endl;
    s = inputInt(0,4);
    system("CLS");
    
    switch (s) {
      case 0:
        // Torno alla schermata iniziale
        return; 
      case 1:
        // Richiedo amicizia
        richiedi_amicizia(lista_utenti_p);
        break;
      case 2:
      	// Accetto/rifiuto amicizia
        accetta_rifiuta_amicizia();
        break;
      case 3:
      	// Cancella amicizia
        cancella_amicizia();
        break;      
      case 4:
      	// Visualizzo lista amici
      	visualizza_amici();
      	break;
    }
  } while (s != 0); // Continuo finchè s!=0
  system("CLS");
}

// Metodo per richiedere amicizia ad un utente
void Utente::richiedi_amicizia(map<string,Utente>* lista_utenti_p){
  int s=0;
  map<int,Utente*> lista_amicizie_richiedibili;
  map<int,Utente*>::iterator iter_lar;
  //map<int,Amicizia>::iterator iter_amicizie;
  map<string,Utente>::iterator iter;

  do {
    // Controllo se è l'unico utente registrato
    if (lista_utenti_p->size() == 1) {
      system("CLS");
      cout << "Nessun altro utente registrato!" << endl << endl;
      return;
    }
	
    // Mostro elenco tutti utenti a cui è possibile richiedere l'amicizia
    cout << "Lista utenti a cui puoi richiedere l'amicizia:" << endl << endl;
    for(iter = lista_utenti_p->begin(); iter != lista_utenti_p->end(); iter++){
  	  // Controllo se è l'utente stesso
      if (email == iter->first) {
        continue;
      } else {
        // Controllo se richiesta già effettuata (accettata, in corso, rifiutata)
  	    map<int,Amicizia>::iterator piter;
        int check = 0;
  	    for (piter = lista_amicizie.begin(); piter != lista_amicizie.end(); piter++) {
    	    if (piter->second.get_utente()->get_email() == iter->first) {
    	      // Se email utente da lista utenti = email amico lista amici
     	      check = 1;
    	    }
        }
		
        // Se l'utente non è già amico o con una richiesta, lo stampo e inserisco nella lista provvisoria
        if(check != 1) {
          cout << "#" << iter->second.get_idutente() << " - ";
          cout << iter->second.get_cognome() << " " << iter->second.get_nome() << endl;
          lista_amicizie_richiedibili.insert(pair<int,Utente*> (iter->second.get_idutente(), &iter->second));		  
        }
      }
    }
	
    // Se non ci sono amici a cui è possibile chiedere l'amicizia, lo stampo
    if (lista_amicizie_richiedibili.size() == 0) {
      system("CLS");
      cout << "Nessun utente a cui chiedere l'amicizia!" << endl << endl;
      return;
    }
    cout << endl;
    cout << "Seleziona utente a cui chiedere l'amicizia," << endl;
    cout << "Premi 0 per tornare alla schermata precedente" << endl;
	  
    // Controllo se l'utente può chiedere l'amicizia a quello selezionato
    do {
      s = inputInt(0,lista_utenti_p->size());
  	  if(s == 0) {system("CLS"); return;}
      iter_lar = lista_amicizie_richiedibili.find(s);
      if( iter_lar == lista_amicizie_richiedibili.end() ) {
        cerr << "Non puoi chiedere l'amicizia a questo utente!" << endl;
        cout << "Reinserire: ";
      }
  	} while(iter_lar == lista_amicizie_richiedibili.end() );

    // Creo amicizia fittizia da inserire nella lista del mittente
    Amicizia mitt(iter_lar->second, MITTENTE);
	  
    // Inserisco amicizia nella lista del mittente
    lista_amicizie.insert( pair<int,Amicizia> (id_a,mitt) );
	 
    string path = path_files_u + email.c_str() + "/" + nome_file_amicizie;
    
    // Apro file mittente
    ofstream file;
    file.open(path.c_str(), ios::app);

    // Controllo apertura corretta file
    if(!file){ cerr<< "Errore apertura file!"; return;}
  
    // Stampo su file
    file << id_a << "\t";
    file << iter_lar->second->get_email() << "\t"; 
    file << "X" << "\t";
  	file << "MITTENTE" << endl;

    // Chiudo il file
    file.close();

    // Creo amicizia fittizia da inserire nella lista del destinatario
  	Amicizia dest(this, DESTINATARIO);
  	iter_lar->second->get_listaamicizie()->insert( pair<int,Amicizia> (id_a,dest) );
	  
  	// Scrivo su file destinatario
  	path = path_files_u + (iter_lar->second->get_email()).c_str() + "/" + nome_file_amicizie;
 
  	file.open(path.c_str(), ios::app);
	  
    // Controllo apertura corretta file
    if(!file){ cerr<< "Errore apertura file!"; return;}
  	file << id_a << "\t";
    file << email << "\t"; 
  	file << "X" << "\t";
    file << "DESTINATARIO" << endl;
	     
    // Chiudo file destinatario
    file.close();

    // Incremento numero amicizie globale
    id_a++;

    system("CLS");
    
    // Messaggio di conferma
    cout << "Amicizia richiesta correttamente!" << endl << endl;

    return;
  } while(true);
}

void Utente::accetta_rifiuta_amicizia(){
  cout << "Lista richieste ricevute:" << endl << endl;
  int s = 0;
  map<int,Amicizia>::iterator iter;
  map<int,Amicizia> richieste_amicizia;
  map<int,Amicizia>::iterator iter_ra;
  map<int,Amicizia>::iterator iter_mit;
  
  do {
    // Scorro lista di amicizie
    for(iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++){
      // Trovata richiesta in corso
      if( iter->second.get_status() == X && iter->second.get_ruolo() == DESTINATARIO){
        cout << "#" << iter->second.get_idamicizia();
        cout << " - " << iter->second.get_utente()->get_cognome();
        cout << " " << iter->second.get_utente()->get_nome() << endl;
        richieste_amicizia.insert( pair<int,Amicizia> (iter->second.get_idamicizia(),iter->second) );
      }
    }
    
    // Controllo se non ci sono richieste
    if( richieste_amicizia.size() == 0 ) {
      system("CLS");
      cout << "Nessuna richiesta in attesa!" << endl << endl;
      return;
    }
    
    cout << endl;
    cout << "Seleziona utente del quale accettare o rifiutare l'amicizia," << endl;
    cout << "Premi 0 per tornare alla schermata precedente" << endl;
    
    do { // Controllo input finché non si sceglie un'amicizia da accettare/rifiutare valida
      s = inputInt(0, (id_a-1) );
      if( s == 0 ) {system("CLS"); return;}
  	  iter_ra = richieste_amicizia.find(s);
  	  if( iter_ra == richieste_amicizia.end() ){
        cerr << "Richiesta non trovata!" << endl;
        cout << "Reinserire: ";
      }
  	} while( iter_ra == richieste_amicizia.end() );

    string e = "R";
  	Stato status;
  	  
  	system("CLS");
  	cout << "#" << iter_ra->second.get_idamicizia();
    cout << "- " << iter_ra->second.get_utente()->get_cognome();
  	cout << " " << iter_ra->second.get_utente()->get_nome() << endl << endl;
  	cout << "Accettare o rifiutare l'amicizia (A/R)?";
  	  
    do { // Destino dell'amicizia selezionata
      e = inputString(1);
  	  if (e == "A" || e == "a") { status = A; }
  	  else if (e == "R" || e == "r") { status = R; }
  	  else {
  	    cerr << "Comando non valido!" << endl;
        cout << "Inserire \"A\" per accettare o \"R\" per rifiutare: ";	
      }
    } while ((e != "A") && (e != "a") && (e != "R") && (e != "r"));
	
    int keep_id = iter_ra->second.get_idamicizia();
  	  
  	// UTENTE MITTENTE
  	// Creo amicizia fittizia con status aggiornato da inserire nella lista del mittente
    Amicizia mitt(keep_id,this,status,DESTINATARIO);
    
    // Cerco la richiesta corrispondente
    iter_mit = iter_ra->second.get_utente()->get_listaamicizie()->find(s);
    
    if( iter_mit != iter_ra->second.get_utente()->get_listaamicizie()->end() ){
      // Se la trovo cancello quella vecchia e inserisco quella aggiornata
      iter_ra->second.get_utente()->get_listaamicizie()->erase(iter_mit);
  	  iter_ra->second.get_utente()->get_listaamicizie()->insert( pair<int,Amicizia> (keep_id,mitt) );
    } else {
      // Altrimenti stampo un messaggio di errore
      system("CLS");
      cerr << "Richiesta non trovata!" << endl << endl;
      continue;
    }
	
    char linea[11+MAXLUN+17];
    string path = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + nome_file_amicizie;
    string path_copia = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + "copia_" + nome_file_amicizie;
      
    // Apro file di copia
    ofstream file_copia;
  	file_copia.open(path_copia.c_str(), ios::out);
	
    // Controllo apertura corretta file
  	if(!file_copia){ cerr<< "Errore apertura file!"; return;}

    // Apro file standard
    ifstream file2;
    file2.open(path.c_str(), ios::in);

    // Controllo apertura corretta file
    if(!file2){ cerr<< "Errore apertura file!"; return;}
    while (!file2.getline(linea,11+MAXLUN+17).eof()) {
      // Token ID amicizia
      int _id = atoi(strtok(linea,"\t"));
        
      // Token utente amicizia
      string _utente = strtok(NULL,"\t");
       
      // Token status amicizia
      string _s = strtok(NULL,"\t");
        
      // Token ruolo amicizia
      string _r = strtok(NULL,"\n");
        
      // Aggiorno l'amicizia da accettare o rifiutare
      if(_id == keep_id) { 
        if(status == A) { _s = "A"; }
        else if(status == R) { _s = "R"; }
      }
        
      // Riscrivo le amicizie nel file di copia aggiornando lo stato di quella in questione
      file_copia << _id << "\t";
      file_copia << _utente << "\t";
      file_copia << _s << "\t";
      file_copia << _r << endl;
    }	
 
    // Chiudo i file
    file2.close();
    file_copia.close();
    
    // Elimino il precedente file standard
    if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }

    // Rinomino il file copia col nome del file standard
    if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }

    // UTENTE DESTINATARIO
    // Creo amicizia fittizia con status aggiornato da inserire nella lista del destinatario
    Amicizia dest(keep_id,iter_ra->second.get_utente(),status,DESTINATARIO);
	  
    // Cerco la richiesta in questione nella lista del destinatario
    iter_ra = lista_amicizie.find(s);
    if(iter_ra != lista_amicizie.end() ) {
      // Se la trovo cancello quella preesistente e inserisco quella aggiornata
  	  lista_amicizie.erase(iter_ra);
  	  lista_amicizie.insert( pair<int,Amicizia> (keep_id,dest) );
    } else {
      // Se non la trovo stampo un messaggio di errore
      system("CLS");
      cout << "Richiesta non trovata!" << endl << endl;
      continue;
    }
    
    path = path_files_u + email.c_str() + "/" + nome_file_amicizie;
    path_copia = path_files_u + email.c_str() + "/" + "copia_" + nome_file_amicizie;
      
    // Apro il file di copia
    file_copia.open(path_copia.c_str(), ios::out);
  
  	// Controllo apertura corretta file
    if(!file_copia){ cerr<< "Errore apertura file!"; return;}

    // Apro il file standard
  	ifstream file;
  	file.open(path.c_str(), ios::in);
  
  	// Controllo apertura corretta file
  	if(!file){ cerr<< "Errore apertura file!"; return;}
  	while (!file.getline(linea,11+MAXLUN+17).eof()) {
      // Token ID amicizia
      int _id = atoi(strtok(linea,"\t"));
        
      // Token utente amicizia
      string _utente = strtok(NULL,"\t");
        
      // Token status amicizia
      string _s = strtok(NULL,"\t");
        
      // Token ruolo amicizia
      string _r = strtok(NULL,"\n");
        
      // Aggiorno l'amicizia da accettare o rifiutare
      if(_id == keep_id) { 
        if(status == A) { _s = "A"; }
        else if(status == R) { _s = "R"; }
      }

      // Riscrivo sul file di copia le amicizie preesistenti aggiornando lo status di quella in questione
      file_copia << _id << "\t";
  	  file_copia << _utente << "\t";
      file_copia << _s << "\t";
      file_copia << _r << endl;
    }	
 
    // Chiudo i file
    file.close();
    file_copia.close();
    
    // Elimino il precedente file standard
    if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }
    
    // Rinomino il file di copia con il nume del file standard
    if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }
	  
	  // Stampo un messaggio di conferma
    system("CLS");
    cout << "Amicizia ";
    if(status == A) { cout << "accettata"; }
    else if(status == R) { cout << "rifiutata"; }
    cout<<" correttamente!" << endl << endl;
      
    return;
  } while(true);
}

void Utente::cancella_amicizia(){
  map<int,Amicizia>::iterator iter_ra;
  map<int,Amicizia>::iterator iter_mit;
  int s = 0;
	
  cout << "Lista amici:" << endl << endl;
  map<int,Amicizia>::iterator iter;
  int count = 0;
  	
  // Scorro lista amicizie
  for (iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++) {
    // Se lo stato dell'amicizia è A (accettata) stampo l'amico nella lista amicizie
    if (iter->second.get_status() == A) {
      cout << iter->first <<" - ";
      cout << iter->second.get_utente()->get_cognome() << " " << iter->second.get_utente()->get_nome() << endl;
      count++;
    }
    // Se no, continuo a scorrere la lista amicizie 
  } 
    
  // Se lista amicizie è vuota stampo "Ancora nessun amico!"    
  if(count == 0){
    system("CLS");
    cout << "Ancora nessun amico!" << endl << endl;
    return;
  }
  cout << endl;
  cout << "Seleziona numero dell'amico da cancellare" << endl;
  cout << "Premi 0 per tornare alla schermata precedente" << endl;
	
  do { // Controllo input fino ad amicizia valida
    s = inputInt( 0, (id_a-1) );
  	if( s == 0 ) { system("CLS"); return; }
  	iter_ra = lista_amicizie.find(s);
    if( iter_ra == lista_amicizie.end() ) {
      cerr << "Non puoi togliere questo amico!" << endl;
      cout << "Reinserire: ";
    } else {
      if( iter_ra->second.get_status() != A ){
        cerr << "Non puoi togliere questo amico!" << endl;
        cout << "Reinserire: ";
      }
  	}
  } while ( iter_ra == lista_amicizie.end() || iter_ra->second.get_status() != A );
  
  // Amicizia trovata nell'utente
  Stato status = R;
  char linea[11+MAXLUN+17];
  int keep_id = iter_ra->second.get_idamicizia();
	  
  // Utente esterno coinvolto
  iter_mit = iter_ra->second.get_utente()->get_listaamicizie()->find(s);
  if(iter_mit != iter_ra->second.get_utente()->get_listaamicizie()->end() ){ // Amicizia trovata nell'utente esterno
   
    // Variabili fittizie per creare copia amicizia precedente con status R
  	Ruolo _r;
  	if( iter_mit->second.get_ruolo() == MITTENTE ) {
  	  _r = MITTENTE;
  	} else if( iter_mit->second.get_ruolo() == DESTINATARIO ) { 
  	  _r = DESTINATARIO;
  	}
   	Amicizia mitt(keep_id,this,status,_r);
  	iter_ra->second.get_utente()->get_listaamicizie()->erase(iter_mit);
  	iter_ra->second.get_utente()->get_listaamicizie()->insert( pair<int,Amicizia> (keep_id,mitt) );
  } else {
    system("CLS");
    cerr << "Errore allineamento amicizie!" << endl << endl;
  	return;
  }

  string path = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + nome_file_amicizie;
  string path_copia = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + "copia_" + nome_file_amicizie;
      
  // Apro file di copia
  ofstream file_copia;
  file_copia.open(path_copia.c_str(), ios::out);
  
  // Controllo apertura corretta file
  if(!file_copia){ cerr<< "Errore apertura file!"; return;}

  // Apro file standard
  ifstream file2;
  file2.open(path.c_str(), ios::in);
  
  // Controllo apertura corretta file
  if(!file2){ cerr<< "Errore apertura file!"; return;}
  
  while (!file2.getline(linea,11+MAXLUN+17).eof()) {      
    // Token ID amicizia
    int _id = atoi(strtok(linea,"\t"));
        
    // Token utente amicizia
    string _utente = strtok(NULL,"\t");
        
    // Token status amicizia
    string _s = strtok(NULL,"\t");
        
    // Token ruolo amicizia
    string _r = strtok(NULL,"/n");
        
    // Aggiorno l'amicizia da cancellare
    if(_id == keep_id) { 
	    _s = "R"; 
  	}
      
    // Scrivo sul file di copia le amicizie preesistenti aggiornando lo status di quella in questione  
    file_copia << _id << "\t";
    file_copia << _utente << "\t";
  	file_copia << _s << "\t";
  	file_copia << _r << endl;
  }

  // Chiudo i file
  file2.close();
  file_copia.close();

  // Elimino il precedente file standard
  if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }

  // Rinomino il file di copia con il nome del file standard
  if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }

  // Utente stesso
  // Rimuovo e creo amicizia con status aggiornato per utente (destinatario)
  Amicizia dest(keep_id,iter_ra->second.get_utente(),status, iter_ra->second.get_ruolo() );
  lista_amicizie.erase(iter_ra);
  lista_amicizie.insert( pair<int,Amicizia> (keep_id,dest) );
      
  path = path_files_u + email.c_str() + "/" + nome_file_amicizie;
  path_copia = path_files_u + email.c_str() + "/" + "copia_" + nome_file_amicizie;
      
  file_copia.open(path_copia.c_str(), ios::out);
	  
  // Controllo apertura corretta file
  if(!file_copia){ cerr<< "Errore apertura file!"; return;}

  ifstream file;
  file.open(path.c_str(), ios::in);
	  
  // Controllo apertura corretta file
  if(!file){ cerr<< "Errore apertura file!"; return;}
  while (!file.getline(linea,11+MAXLUN+17).eof()) {
    // Token ID amicizia
    int _id = atoi(strtok(linea,"\t"));

    // Token utente amicizia
    string _utente = strtok(NULL,"\t");

    // Token status amicizia
    string _s = strtok(NULL,"\t");

    // Token ruolo amicizia
    string _r = strtok(NULL,"/n");
        
    // Aggiorno l'amicizia da accettare o rifiutare
    if(_id == keep_id){ _s = "R"; }
        
    file_copia << _id << "\t";
    file_copia << _utente << "\t";
    file_copia << _s << "\t";
    file_copia << _r << endl;
  }
 
  file.close();
  file_copia.close();
    
  // Elimino il precedente file
  if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }

  // Rinomino
  if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }
		
  system("CLS");
  cout << "Amicizia cancellata correttamente! Un rifiuto e' per sempre!" << endl << endl;
}

int Utente::num_richieste_pendenti() {
  int count = 0;
  map<int,Amicizia>::iterator iter;
  
  for (iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++) {
    if ((iter->second.get_status() == X) && (iter->second.get_ruolo() == DESTINATARIO)) {
      count += 1;
    }
  }
  
  return count;
}
