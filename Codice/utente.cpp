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

// Variabili di configurazione
extern int id_p;
extern int id_a;
int id_u = 1;

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
  string t;
    do { 
      // Schermata iniziale
      cout << "Benvenuto!" << endl;
      
      // Eventuale notifica di richieste di amicizia in attesa di risposta
      if (num_richieste_pendenti() == 1) {
        cout << endl << "Hai " << num_richieste_pendenti() << " richiesta di amicizia pendente!" << endl << endl;
      } else if (num_richieste_pendenti() > 1) {
        cout << endl << "Hai " << num_richieste_pendenti() << " richieste di amicizia pendenti!" << endl << endl;
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
    cout << "Logout effettuato!" << endl << endl;
    logout();
}

// Metodo di logout, rimanda alla schermata di autenticazione
void Utente::logout() {
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
		    return; //ritorna alla schermata iniziale
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
  cout << "Per modificare i campi selezionare il numero corrispondente: "<<endl;
  cout << "Per tornare alla schermata iniziale premi 0" << endl;

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
     file << profilo.get_sesso() << ";"
          << profilo.get_professione() << ";"
          << profilo.get_situasent() << ";"
          << profilo.get_datanasc() << ";"
          << profilo.get_luogonasc() << endl;
          
     // Chiude il file
     file.close();
  }

  system("CLS");
}

//Bacheca
void Utente::visualizza_bacheca() {
  map<int,Post>::reverse_iterator iter;
  int s = 0;
  
  do {
    // Stampa il nome del proprietario della bacheca
	  cout << "Bacheca di " << get_nome() << " " << get_cognome()<<endl;
	  
	  // Stampa tutti i post in maniera compatta
    for (iter = get_bacheca()->get_listapost()->rbegin(); iter != get_bacheca()->get_listapost()->rend(); iter++) {
      iter->second.visualizza_post_light();
    }

    cout << "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero";
    cout << "Per tornare alla schermata iniziale premi 0" << endl;
    s = inputInt(0,id_p);
    system("CLS");
    
    if(s == 0){ return; }
    
    // Se viene selezionato un post in particolare, lo visualizza in modo dettagliato
    if ( get_bacheca()->get_listapost()->find(s) != get_bacheca()->get_listapost()->end() ){
			get_bacheca()->get_listapost()->find(s)->second.visualizza_post();
			cout << "Per commentare il post selezionato premi 1" << endl;
			cout << "Per mettere[/togliere] \"mi piace\" premi 2" << endl;
			cout << "Per tornare alla schermata iniziale premi 0" << endl;
      int p = inputInt(0,2);

   	  switch(p){
		    case 0: system("CLS");
          // Ritorno alla bacheca completa
					return;
   			case 1:
          // Aggiunta commento al post
          get_bacheca()->get_listapost()->find(s)->second.commenta_post(this);
					break;
		  	case 2:
          // Aggiunta like al post
          get_bacheca()->get_listapost()->find(s)->second.aggiungi_like(this);
					return;
		  }
      system("CLS");  	  
    } else { // se non si trova il numero di post immesso
      system("CLS");
      cerr << "Post non trovato!" << endl << endl;
    }
  } while(s!=0); 
}

void Utente::visualizza_bacheca_generale() {
  map<int,Post*> lista_post_amici;
  map<int,Amicizia>::iterator iter_amicizie;
  map<int,Post>::iterator iter_post;
  int s = 0;

  // Scorre la lista di amicizie dell'utente
  for (iter_amicizie = lista_amicizie.begin(); iter_amicizie != lista_amicizie.end(); iter_amicizie++) {
    // Se l'amicizia è accettata
    if (iter_amicizie->second.get_status() == A) {
      // scorre i post dell'amico e ne inserisce un puntatore in un map, utilizzando l'id del post come key
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

  // Altrimenti stampa l'elenco dei post degli amici in ordine cronologico inverso ed in modo compatto
  map<int,Post*>::iterator iter_post_amici;
  for (iter_post_amici = lista_post_amici.begin(); iter_post_amici != lista_post_amici.end(); iter_post_amici++) {
    iter_post_amici->second->visualizza_post_light();
  }

  cout<< "Per visualizzare i dettagli di un post e interagire con esso digitarne il numero";
  cout<< "Per tornare alla schermata iniziale premi 0"<<endl;

  s = inputInt(0,id_p);
  system("CLS");

  // Ritorno alla schermata iniziale
  if( s == 0){ return; }
  
  // Se viene selezionato un post, lo visualizza in modo dettagliato
  if ( lista_post_amici.find(s) != lista_post_amici.end() ){
  	lista_post_amici.find(s)->second->visualizza_post();
	  cout<< "Per commentare il post selezionato premi 1" << endl;
		cout<< "Per mettere[/togliere] \"mi piace\" premi 2" << endl;
		cout<< "Per tornare alla schermata iniziale premi 0" << endl;
    int p = inputInt(0,2);

	  switch(p){
	    case 0:
        // Ritorno alla bacheca generale completa
        system("CLS");
				return;	
			case 1:
        // Aggiunta commento al post
        lista_post_amici.find(s)->second->commenta_post(this);
				break;
			case 2:
        // Aggiunta like al post
        lista_post_amici.find(s)->second->aggiungi_like(this);
				return;
	  }
    system("CLS");  	  
  } else { // se non trova il numero del post immesso
    system("CLS");
    cerr << "Post non trovato!" << endl << endl;
  }
}

// Metodo che permette di visualizzare il profilo e la bacheca di un amico
void Utente::visualizza_contenuto_amici(){
  int t;
  do {
    // Mostra elenco degli amici
    cout << "Elenco dei tuoi amici:" << endl;
    visualizza_amici();                                                                      
    int s;          
    map<int,Amicizia>::iterator iter;
    
    // Menù di scelta
    cout << "Selezionare il numero dell'amico per visualizzare le sue informazioni " << endl;         
    cout << "Per tornare alla schermata iniziale premi 0" << endl;

    do {
      s = inputInt(0,id_u);
      // Ritorno alla schermata iniziale se la scelta è 0
      if(s == 0){system("CLS"); return;}
      // Cerco l'amico selezionato nella lista amicizie
      iter = lista_amicizie.find(s); 
      // Se non lo trovo, stampo "Non è amico"
      if(iter == lista_amicizie.end()) {cerr << "Non e' tuo amico" << endl;}                              
    } while(iter == lista_amicizie.end()); // Continuo finchè non viene selezionato un amico

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
        iter->second.get_utente()->visualizza_bacheca();
        return;
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
  } while ((t!=0) && (t!=1)); // Continuo finchè t=0 e t=1          
}
   
// Metodo che permette di visualizzare gli amici                                
void Utente::visualizza_amici() {
  map<int,Amicizia>::iterator iter;
  int count = 0;
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
    cout << "Ancora nessun amico!" << endl;
    return;
  } 
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
        cout << "Lista amici:" << endl << endl;
      	visualizza_amici();
      	// Torno alla schermata iniziale
        cout << endl << "Premi 0 per tornare alla schermata iniziale" << endl;
      	s = inputInt(0,0);
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
	  
	  if (lista_amicizie_richiedibili.size() == 0) {
    	system("CLS");
        cout << "Nessun utente a cui chiedere l'amicizia!" << endl << endl;
        return;
      }
	  cout << "Seleziona utente a cui chiedere l'amicizia," << endl;
	  cout << "Premi 0 per tornare alla schermata precedente" << endl;
	  s = inputInt(0,lista_utenti_p->size());

  	if(s == 0) {system("CLS"); return;}

  	iter_lar = lista_amicizie_richiedibili.find(s);
	  if(iter_lar != lista_amicizie_richiedibili.end() ){

	    Amicizia mitt(iter_lar->second, MITTENTE);
	    lista_amicizie.insert( pair<int,Amicizia> (id_a,mitt) );
	
      string path = path_files_u + email.c_str() + "/" + nome_file_amicizie;
    
	    ofstream file;
	    file.open(path.c_str(), ios::app);

	    // Controllo apertura corretta file
	    if(!file){ cerr<< "Errore apertura file!"; return;}
  	  file << id_a << ";";
      file << iter_lar->second->get_email() << ";"; 
  	  file << "X" << ";";
  	  file << "MITTENTE" << endl;

      file.close();

  	  Amicizia dest(this, DESTINATARIO);
  	  iter_lar->second->get_listaamicizie()->insert( pair<int,Amicizia> (id_a,dest) );
	  
  	  // Scrivo su file destinatario
  	  path = path_files_u + (iter_lar->second->get_email()).c_str() + "/" + nome_file_amicizie;
 
  	  file.open(path.c_str(), ios::app);
	    // Controllo apertura corretta file
	    if(!file){ cerr<< "Errore apertura file!"; return;}
  	  file << id_a << ";";
      file << email << ";"; 
  	  file << "X" << ";";
	    file << "DESTINATARIO" << endl;
	     
      file.close();

      // Incremento numero amicizie globale
      id_a++;

      system("CLS");
      cout << "Amicizia richiesta correttamente!" << endl << endl;

      return;
  	} else {
      system("CLS");
	    cerr << "Non puoi chiedere l'amicizia a questo utente!" << endl << endl;
    }
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
  
    for(iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++){
      // Trovata richiesta in corso
	    if( iter->second.get_status() == X && iter->second.get_ruolo() == DESTINATARIO){
	  	  cout << "#" << iter->second.get_idamicizia();
		  cout << "- " << iter->second.get_utente()->get_cognome();
	  	  cout << " " << iter->second.get_utente()->get_nome() << endl;
	  	  richieste_amicizia.insert( pair<int,Amicizia> (iter->second.get_idamicizia(),iter->second) );
	    }
    }
      // Controllo se non ci sono richieste
      if( richieste_amicizia.size() == 0 ) {
      	system("CLS");
      	cout << "Nessuna richiesta pendente!" << endl << endl;
      	return;
	  }
    
    cout << endl;
    cout << "Seleziona utente del quale accettare o rifiutare l'amicizia," << endl;
    cout << "Premi 0 per tornare alla schermata precedente" << endl;
    s = inputInt(0,id_a);

    if( s == 0 ) {system("CLS"); return;}

  	iter_ra = richieste_amicizia.find(s);
  	if(iter_ra != richieste_amicizia.end() ){
  	  string e = "R";
  	  Stato status;
  	  do { // Destino dell'amicizia selezionata
  	  	system("CLS");
  	  	cout << "#" << iter_ra->second.get_idamicizia();
    	cout << "- " << iter_ra->second.get_utente()->get_cognome();
  	  	cout << " " << iter_ra->second.get_utente()->get_nome() << endl << endl;

  	  	cout << "Accettare o rifiutare l'amicizia (A/R)?"; e = inputString(1);

  	  	if (e == "A" || e == "a") { status = A; }
  	  	if (e == "R" || e == "r") { status = R; }
  	  } while ((e != "A") && (e != "a") && (e != "R") && (e != "r"));
	
  	  int keep_id = iter_ra->second.get_idamicizia();
  	  
  	  // Utente mittente
      Amicizia mitt(keep_id,this,status,DESTINATARIO);
      iter_mit = iter_ra->second.get_utente()->get_listaamicizie()->find(s);
      if( iter_mit != iter_ra->second.get_utente()->get_listaamicizie()->end() ){
	    iter_ra->second.get_utente()->get_listaamicizie()->erase(iter_mit);
  	    iter_ra->second.get_utente()->get_listaamicizie()->insert( pair<int,Amicizia> (keep_id,mitt) );
	  } else {
	    system("CLS");
	    cerr << "Richiesta non trovata!" << endl << endl;
	    continue;
	    }
	  char linea[150];
      string path = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + nome_file_amicizie;
      string path_copia = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + "copia_" + nome_file_amicizie;
      
      ofstream file_copia;
  	  file_copia.open(path_copia.c_str(), ios::out);
	
      // Controllo apertura corretta file
  	  if(!file_copia){ cerr<< "Errore apertura file!"; return;}

      ifstream file2;

  	  file2.open(path.c_str(), ios::in);
	    // Controllo apertura corretta file
  	  if(!file2){ cerr<< "Errore apertura file!"; return;}
  	  while (!file2.getline(linea,150).eof()) {
  		  // Token ID amicizia
        int _id = atoi(strtok(linea,";"));
        
        // Token utente amicizia
        string _utente = strtok(NULL,";");
        
        // Token status amicizia
        string _s = strtok(NULL,";");
        
        // Token ruolo amicizia
        string _r = strtok(NULL,";");
        
        // Aggiorno l'amicizia da accettare o rifiutare
        if(_id == keep_id) { 
			    if(status == A) { _s = "A"; }
          else if(status == R) { _s = "R"; }
	      }
        
        file_copia << _id << ";";
		    file_copia << _utente << ";";
		    file_copia << _s << ";";
		    file_copia << _r << endl;
	    }	
 
      file2.close();
      file_copia.close();
    
      // Elimino il precedente file
      if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }

      // Rinomino
      if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }
      //
      //
      //
      // Rimuovo e creo amicizia con status aggiornato per utente (destinatario)
	  Amicizia dest(keep_id,iter_ra->second.get_utente(),status,DESTINATARIO);
	  
	  iter_ra = lista_amicizie.find(s);
	  if(iter_ra != lista_amicizie.end() ) {
  	  lista_amicizie.erase(iter_ra);
  	  lista_amicizie.insert( pair<int,Amicizia> (keep_id,dest) );
	  }  else {
	    system("CLS");
	    cout << "Richiesta non trovata!" << endl << endl;
	    continue;
	  }
      path = path_files_u + email.c_str() + "/" + nome_file_amicizie;
      path_copia = path_files_u + email.c_str() + "/" + "copia_" + nome_file_amicizie;
      
	  file_copia.open(path_copia.c_str(), ios::out);
  
  	  // Controllo apertura corretta file
	    if(!file_copia){ cerr<< "Errore apertura file!"; return;}

  	  ifstream file;
  	  file.open(path.c_str(), ios::in);
  
  	  // Controllo apertura corretta file
  	  if(!file){ cerr<< "Errore apertura file!"; return;}
  	  while (!file.getline(linea,150).eof()) {
    		// Token ID amicizia
        int _id = atoi(strtok(linea,";"));
        
        // Token utente amicizia
        string _utente = strtok(NULL,";");
        
        // Token status amicizia
        string _s = strtok(NULL,";");
        
        // Token ruolo amicizia
        string _r = strtok(NULL,";");
        
        // Aggiorno l'amicizia da accettare o rifiutare
        if(_id == keep_id) { 
          if(status == A) { _s = "A"; }
		  else if(status == R) { _s = "R"; }
	    }

        file_copia << _id << ";"
  				   << _utente << ";"
	  			   << _s << ";"
				   << _r << endl;
	    }	
 
      file.close();
      file_copia.close();
    
      //elimino il precedente file
      if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }
      //rinomino
      if( rename( path_copia.c_str(),path.c_str() ) != 0){ cerr << "Errore rinomino file!"; return; }
	  
      system("CLS");
      cout << "Amicizia ";
	    if(status == A) { cout << "accettata"; }
	    else if(status == R) { cout << "rifiutata"; }
	    cout<<" correttamente!" << endl << endl;
      
      return;
	  	 
	  } else {
	    system("CLS");
	    cerr << "Richiesta non trovata!" << endl << endl;
	  }
  } while(true);
}

void Utente::cancella_amicizia(){
	map<int,Amicizia>::iterator iter_ra;
	map<int,Amicizia>::iterator iter_mit;
	int s = 0;
	
	do {
	  cout << "Lista amici:" << endl;
  	map<int,Amicizia>::iterator iter;
  	int count = 0;
  	
    // Scorro lista amicizie
    for (iter = lista_amicizie.begin(); iter != lista_amicizie.end(); iter++) {
      // Se lo stato dell'amicizia è A (accettata) stampo l'amico nella lista amicizie
      if (iter->second.get_status() == A) {
        cout << iter->first <<" - ";
        cout << iter->second.get_utente()->get_nome() << " " << iter->second.get_utente()->get_cognome() << endl;
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

	  cout << "Seleziona numero dell'amico da cancellare" << endl;
	  cout << "Premi 0 per tornare alla schermata precedente" << endl;
	
	  s = inputInt( 0, id_a );
	
	  if( s == 0 ) { system("CLS"); return; }

  	iter_ra = lista_amicizie.find(s);
  	if( iter_ra != lista_amicizie.end() ){ // Amicizia trovata nell'utente
  	  Stato status = R;
  	  char linea[150];
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
	      cout << "Non puoi togliere questo amico!" << endl << endl;
	      continue;
	    }

      string path = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + nome_file_amicizie;
      string path_copia = path_files_u + (iter_ra->second.get_utente()->get_email()).c_str() + "/" + "copia_" + nome_file_amicizie;
      
      ofstream file_copia;
  	  file_copia.open(path_copia.c_str(), ios::out);
	    // Controllo apertura corretta file
	    if(!file_copia){ cerr<< "Errore apertura file!"; return;}

      ifstream file2;
	    file2.open(path.c_str(), ios::in);
  	  // Controllo apertura corretta file
  	  if(!file2){ cerr<< "Errore apertura file!"; return;}
  	  while (!file2.getline(linea,150).eof()) {      
    		// Token ID amicizia
        int _id = atoi(strtok(linea,";"));
        
        // Token utente amicizia
        string _utente = strtok(NULL,";");
        
        // Token status amicizia
        string _s = strtok(NULL,";");
        
        // Token ruolo amicizia
        string _r = strtok(NULL,";");
        
        // Aggiorno l'amicizia da cancellare
        if(_id == keep_id) { 
		  _s = "R"; 
		}
        
        file_copia << _id << ";";
		    file_copia << _utente << ";";
  		  file_copia << _s << ";";
  		  file_copia << _r << endl;
	    }	

      file2.close();
      file_copia.close();

      // Elimino il precedente file
      if( remove(path.c_str()) != 0){ cerr << "Errore eliminazione file!"; return; }

      // Rinomino
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
  	  while (!file.getline(linea,150).eof()) {
    		// Token ID amicizia
        int _id = atoi(strtok(linea,";"));

        // Token utente amicizia
        string _utente = strtok(NULL,";");

        // Token status amicizia
        string _s = strtok(NULL,";");

        // Token ruolo amicizia
        string _r = strtok(NULL,";");
        
        // Aggiorno l'amicizia da accettare o rifiutare
        if(_id == keep_id){ _s = "R"; }
        
        file_copia << _id << ";";
        file_copia << _utente << ";";
        file_copia << _s << ";";
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
      
      return;
	  } else {
	  system("CLS");
	  cout << "Non puoi togliere questo amico!" << endl << endl;
	  }
	} while(true);
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
