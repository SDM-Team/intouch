#include <cstdlib>		/* system, atoi 						*/
#include <cstring>		/* strtok 								*/
#include <direct.h>		/* mkdir, rmdir 						*/
#include <fstream>		/* ofstream, ifstream 					*/
#include <iostream>		/* cout, endl, remove, rename, cerr		*/
#include <map>			/* map, map::iterator					*/
#include <sstream>		/* stringstream 						*/
#include <string>		/* string		 						*/

// Librerie personalizzate
#include "intouch.h"	/* Libreria di riferimento 				*/
#include "amicizia.h"	/* classe Amicizia e costruttori 		*/
#include "commento.h"	/* classe Commento e metodi relativi 	*/
#include "config.h"		/* Definizione variabili globali 		*/
#include "data.h"		/* classe Data e metodi relativi 		*/
#include "input.h"		/* inputInt, inputString, inputPassword */
#include "post.h"		/* classe Post e metodi relativi 		*/
#include "utente.h" 	/* classe Utente e metodi relativi 		*/

using namespace std;

// Costruttore di default, per importare i dati da file all'avvio
InTouch::InTouch() {
  importa_utenti();
  importa_post();
  importa_profilo();
  importa_amicizie();
}

// Costruttore di copia 
InTouch::InTouch(const InTouch& i){
  lista_utenti= i.lista_utenti;                   
}

// Restituisce la lista degli utenti registrati
map<string,Utente> InTouch::get_listautenti() {
  return lista_utenti;
}

// Schermata iniziale per registrarsi o autenticarsi nell'applicazione
void InTouch::schermata_autenticazione() {
  int s = 3;
  while(true) {
       
    // Voci del menu
    cout << "Benvenuto in InTouch!" << endl;
    cout << "Seleziona cosa vuoi fare:" << endl;
    cout << "1. Registrati" << endl;
    cout << "2. Autenticati" << endl;
    cout << "3. Chiudi applicazione" << endl;
    cout << "4. Reset applicazione" << endl;
       
 	s = inputInt(1,4);
	system("CLS");
	
    switch (s) {
      case 1:
        registrazione();
    	break;
      case 2:
        login();
        break;
      case 3:
        exit(1);
        break;
      case 4:
        reset();
        break;
    }
  }
}

// Metodo di login
void InTouch::login() {
  string email;
  string password;

  // Inserimento email
  cout << "Inserisci il tuo indirizzo email: ";
  email = inputString(MAXLUN);

  // Inserimento password
  cout << "Inserisci la tua password: ";
  password = inputPassword(MAXLUN);

  // Creazione istanza di utente con i parametri immessi
  Utente u(email,password);

  system("CLS");
  if (!(utente_esiste(u))) {
    // Se l'utente non esiste stampa un messaggio di errore e rimanda alla schermata di autenticazione
    cerr << "Errore: Indirizzo email non registrato" << endl << endl;
  } else if (check_login(u)) {
    // Se l'utente esiste e la password inserita è corretta rimanda alla schermata principale
    cout << "Login riuscito!" << endl << endl;

    // Carico i dati dell'utente una volta autenticato
    map<string,Utente>::iterator iter;
    iter = lista_utenti.find(email);
    iter->second.schermata_iniziale(&lista_utenti);
  } else {
    // Se l'utente esiste ma la password inserita non è corretta stampa un messaggio di errore
    // e rimanda alla schermata di autenticazione
    cerr << "Errore: Mancata corrispondenza tra indirizzo email e password" << endl << endl;
  }
}

// Metodo di registrazione
void InTouch::registrazione() {
  int s;
  string nome;
  string cognome;
  string email;
  string password;

  // Inserimento nome
  cout << "Inserisci il tuo nome (max " << MAXLUN << " caratteri): ";
  nome = inputString(MAXLUN);

  // Inserimento cognome
  cout << "Inserisci il tuo cognome (max " << MAXLUN << " caratteri): ";
  cognome = inputString(MAXLUN);

  // Inserimento email
  cout << "Inserisci il tuo indirizzo email (max " << MAXLUN << " caratteri): ";
  email = inputEmail(MAXLUN);

  // Inserimento password
  cout << "Inserisci una password (max " << MAXLUN << " caratteri): ";
  password = inputString(MAXLUN);

  cout << endl;
  cout << "Premi 1 per confermare la registrazione," << endl;
  cout << "Premi 0 per annullare e tornare alla schermata di accesso" << endl;

  s = inputInt(0,1);
  system("CLS");

  switch (s) {
    case 0:
      break;
    case 1:
      // Creazione istanza di utente con i dati immessi
      Utente u(nome,cognome,email,password);

      if (utente_esiste(u)) {
        // Se l'utente esiste già stampa un messaggio di errore e rimanda alla schermata di autenticazione
        cerr << "Errore: Indirizzo email gia' registrato" << endl << endl;
      } else {
        // Se l'utente non esiste ancora richama la funzione di creazione utente
        cerr << "Utente registrato correttamente!" << endl << endl;
        aggiungi_utente(u);
      }
      break;
  }
  // In ogni caso rimanda alla schermata di autenticazione per registrarsi o effettuare il login
}

// Metodo che controlla se un utente esiste già o meno
bool InTouch::utente_esiste(const Utente& u) {
  map<string,Utente>::iterator iter;
  iter = lista_utenti.find(u.get_email());
  return (iter != lista_utenti.end());
}

// Metodo che aggiunge un nuovo utente nella lista degli utenti
void InTouch::aggiungi_utente(const Utente& u) {
  // Inserisce l'utente passato come parametro al map di utenti, con l'id come key
  lista_utenti.insert(pair<string,Utente> (u.get_email(), u));

  // Apre il file conteente la lista di utenti
  string path = path_files + nome_file_utenti;
  ofstream utenti(path.c_str(), ios::app);

  // Controllo corretta creazione o apertura file
  if(!utenti){cerr<<"Errore apertura file!"<<endl; return;}

  // Scrittura su file
  utenti << u.get_idutente() << "\t";
  utenti << u.get_nome() << "\t";
  utenti << u.get_cognome() << "\t";
  utenti << u.get_email() << "\t";
  utenti << u.get_password() << endl;

  // Chiusura file
  utenti.close();

  // Incremento ID univoco per il prossimo utente
  id_u++;

  // Creazione cartelle per l'utente
  path = path_files_u + u.get_email();
  mkdir(path.c_str());

  // Creazione file di default
  // File profilo
  string path1 = path + "/" + nome_file_profilo;
  ofstream profilo(path1.c_str(), ios::out);
  if(!profilo){cerr<<"Errore apertura file!"<<endl;}
  profilo << "ND" << "\t";
  profilo << "ND" << "\t";
  profilo << "ND" << "\t";
  profilo << "01/01/0" << "\t";
  profilo << "ND" << endl;
  profilo.close();

  // File amicizie
  path1 = path + "/" + nome_file_amicizie;
  ofstream amicizie(path1.c_str(), ios::out);
  if(!amicizie){cerr<<"Errore apertura file!"<<endl;}
  amicizie << "";
  amicizie.close();
}

// Metodo che verifica la correttezza della password inserita in fase di login
bool InTouch::check_login(const Utente& u) {
  map<string,Utente>::iterator iter;
  iter = lista_utenti.find(u.get_email());
  if ((u.get_email() == iter->second.get_email()) && (u.get_password() == iter->second.get_password())) return true;
  return false;
}

// Metodo che resetta il sistema eliminando utenti e post creati, con opportuni file e cartelle
void InTouch::reset() {
  string path;

  // Elimino cartelle e dati utenti
  map<string,Utente>::iterator iter;
  
  // Scorro la lista degli utenti
  for (iter = lista_utenti.begin(); iter != lista_utenti.end(); iter++) {
    path = path_files_u + iter->first;
    
    // Cancello file amicizie
    cout<<"Cancello "<<(path + "/" + nome_file_amicizie).c_str()<<endl;
    if( remove((path + "/" + nome_file_amicizie).c_str()) != 0){ cerr << " Errore eliminazione file\n"; }
    
    // Cancello file profilo
    cout<<"Cancello "<<(path + "/" + nome_file_profilo).c_str()<<endl;
    if( remove((path + "/" + nome_file_profilo).c_str()) != 0){ cerr << " Errore eliminazione file\n"; }
    
    // Elimino cartella utente
    rmdir(path.c_str());
  }

  // Elimino cartelle e dati post
  // Scorro gli id dei post
  for (int i = 1; i < id_p; i++) {
    stringstream convert;
    convert << i;
    path = path_files_p + convert.str();
    
    // Cancello file likes
    cout<<"Cancello "<<(path + "/" + nome_file_likes).c_str()<<endl;
    if( remove((path + "/" + nome_file_likes).c_str()) != 0){ cerr << " Errore eliminazione file\n"; }
    
    // Cancello file commenti
    cout<<"Cancello "<<(path + "/" + nome_file_commenti).c_str()<<endl;
    if( remove((path + "/" + nome_file_commenti).c_str()) != 0){ cerr << " Errore eliminazione file\n"; }
    
    // Elimino cartella post
    rmdir(path.c_str());
  }

  // Elimino directory principale
  // Elimino file contenente i dati degli utenti
  cout<<"Cancello "<<(path_files + nome_file_utenti).c_str()<<endl;
  if( remove((path_files + nome_file_utenti).c_str()) != 0){ cerr << " Errore eliminazione file\n"; }

  // Elimino file contenente i dati dei post
  cout<<"Cancello "<<(path_files + nome_file_post).c_str()<<endl;
  if( remove((path_files + nome_file_post).c_str()) != 0){ cerr << " Errore eliminazione file\n"; }

  // Elimino cartella contenente i dati dei post
  cout<<"Cancello "<<(path_files_p).c_str()<<endl;
	if( rmdir(path_files_p.c_str()) != 0){ cerr << " Errore eliminazione cartella\n"; }
	
	// Elimino cartella contenente i dati degli utenti
	cout<<"Cancello "<<(path_files_u).c_str()<<endl;
  if( rmdir(path_files_u.c_str()) != 0){ cerr << " Errore eliminazione cartella\n"; }
  
  // Elimino cartella generale contenente tutti i file e le cartelle
  cout<<"Cancello "<<(path_files).c_str()<<endl;
  if( rmdir(path_files.c_str()) != 0){ cerr << " Errore eliminazione cartella\n"; }

  system("PAUSE");
  exit(1);
}    

// Metodo che carica gli utenti presenti sul file di testo
void InTouch::importa_utenti() {
  lista_utenti.clear();
  ifstream utenti;

  char linea[100];

  // Creazione files se non esistenti
  mkdir(path_files.c_str());
  mkdir(path_files_u.c_str());
  mkdir(path_files_p.c_str());

  string path = path_files + nome_file_utenti;
  utenti.open(path.c_str(), ios::in);

  // Controllo file esistente e aperto correttamente
	if(utenti){
    while (!utenti.getline(linea,100).eof()) {
      char* pch;
      
      // Primo token: ID utente
      pch = strtok (linea,"\t");
      int id_utente = atoi(pch);

      // Secondo token: Nome
      string nome = strtok (NULL,"\t");

      // Terzo token: Cognome
      string cognome = strtok (NULL,"\t");

      // Quarto token: Email
      string email = strtok (NULL,"\t");

      // Quinto token: Password
      string password = strtok (NULL,"\n");

      // CReazione istanza di utente con i parametri letti da file
      Utente u(nome,cognome,email,password);

      // Inserimento utente nella lista degli utenti, con l'id come key
      lista_utenti.insert(pair<string,Utente> (email,u));

      // Crea la cartella nel caso fosse stata cancellata
      path = path_files_u + email;
      mkdir(path.c_str());

      // Aggiorna l'id utente univoco in modo tale da riprendere la numerazione dall'ultimo esistente
      id_u = id_utente + 1;
	  }
	} else { // se non riesce ad aprire il file
	  //reset utenti.csv
	  //cerr << "Lista utenti vuota!" << endl;
	  string path = path_files + nome_file_utenti;
    ofstream file(path.c_str(), ios::out);
    if(!file){cerr<<"Errore apertura file!"<<endl;}
    file << "";
    file.close();
	}
	
	// Chiude il file
	utenti.close();
}

void InTouch::importa_post() {
  ifstream post;
  char linea[150];

  string path = path_files + nome_file_post;

  // Apre il file contenente l'elenco dei post
  post.open(path.c_str(), ios::in);

  // Controllo file esistente e aperto correttamente
  if(post){
    while (!post.getline(linea,150).eof()) {
      char* pch;

      // Token ID post
      pch = strtok (linea,"\t");
      int id_post = atoi(pch);

      // Token autore
      string autore = strtok (NULL,"\t");

      // Token giorno
      int giorno = atoi(strtok(NULL,"/"));

      // Token mese
      int mese = atoi(strtok(NULL,"/"));

      // Token anno
      int anno = atoi(strtok(NULL," "));

      // Token ora
      int ora = atoi(strtok(NULL,":"));

      // Token minuti
      int minuti = atoi(strtok(NULL,"\t"));

      // Token testo
      string testo = strtok (NULL,"\n");

      // Crea un'istanza di data con le informazioni lette da file
      Data temp(giorno,mese,anno,ora,minuti);

      map<string,Utente>::iterator iter;

      // Trova l'autore del post nella lista utenti
      iter = lista_utenti.find(autore);
      
      // Crea un'istanza di post contenente i dati letti da file
      Post p(id_post, &(iter->second) ,testo,temp);
      
      // Inserisce il post nella bacheca dell'utente autore, utilizzando l'id del post come key
      iter->second.get_bacheca()->get_listapost()->insert(pair<int,Post> (id_post,p));

      // Importa i commenti relativi al post in questione
      importa_commenti(autore,id_post);

      // Importa i likes relativi al post in questione
      importa_likes(autore,id_post);

      // Crea la cartella nel caso fosse stata cancellata
      stringstream convert;
      convert << id_post;
      string path = path_files_p + convert.str();
      mkdir(path.c_str());

      // Aggiorna l'id post univoco in modo tale da riprendere la numerazione dall'ultimo esistente
      id_p = id_post + 1;
    }
	} else { // se non riesce ad aprire il file
	  //reset post.csv
	  //cerr << "Lista post vuota!" << endl;
	  string path = path_files + nome_file_post;
    ofstream file(path.c_str(), ios::out);
    if(!file){cerr<<"Errore apertura file!"<<endl;}
    file << "";
    file.close();	
	}
	
	// Chiude il file
  post.close();
}

void InTouch::importa_commenti(string _autore, int id_post) {
  stringstream convert;
  convert << id_post;

  // Apro il file dei commenti relativo al post il cui id è stato passato
  string path = path_files_p + convert.str() + "/" + nome_file_commenti;
  ifstream file_c;
  file_c.open(path.c_str(), ios::in);

  // Controllo file esistente e aperto correttamente
  if(file_c){
    map<string,Utente>::iterator iter_autore_post;
    
    // Trovo l'autore del post nella lista utenti
    iter_autore_post = lista_utenti.find(_autore);
    map<string,Utente>::iterator iter_autore_commento;
    char linea[150];

    while (!file_c.getline(linea,150).eof()) {
      char* pch;
      
      // Token ID post
      pch = strtok (linea,"\t");
      int id = atoi(pch);

      // Token autore
      string autore = strtok (NULL,"\t");

      // Token giorno
      int giorno = atoi(strtok(NULL,"/"));

      // Token mese
      int mese = atoi(strtok(NULL,"/"));

      // Token anno
      int anno = atoi(strtok(NULL," "));

      // Token ora
      int ora = atoi(strtok(NULL,":"));

      // Token minuti
      int minuti = atoi(strtok(NULL,"\t"));

      // Token testo
      string testo = strtok (NULL,"\n");

      // CReo un'istanza di data con i parametri letti da file
      Data temp(giorno,mese,anno,ora,minuti);

      // Trovo l'utente autore del commento nella lista utenti
     	iter_autore_commento = lista_utenti.find(autore);
     	
     	// CReo un'istanza di commento con i dati letti da file
      Commento c(id,&(iter_autore_commento->second),temp,testo);

      map<int,Post>::iterator iter_post;

      // Trovo il post a cui il commento si riferisce all'interno della bacheca dell'utente autore del post
      iter_post = iter_autore_post->second.get_bacheca()->get_listapost()->find(id_post);
      
      // Aggiungo il commento alla lista di commenti del post
      iter_post->second.get_listacommenti()->push_back(c);

      // Aggiorno l'id univoco commento in modo tale da riprendere la numerazione dall'ultimo esistente
      id_c = id + 1;
    }
  } else { // se non riesco ad aprire il file
	  cerr << "Errore import commenti!" << endl;	
	}

	// Chiudo il file
  file_c.close();
}

void InTouch::importa_likes(string _autore, int id_post){
	stringstream convert;
  convert << id_post;

  // Apro il file dei likes relativo al post
  string path = path_files_p + convert.str() + "/" + nome_file_likes;
  ifstream file;
  file.open(path.c_str(), ios::in);

  // Controllo file esistente e aperto correttamente
  if(file){
    map<string,Utente>::iterator iter_autore_post;
    
    // Trovo l'utente autore del post nella lista utenti
    iter_autore_post = lista_utenti.find(_autore);
    
	  map<int,Post>::iterator iter_post;
	  
	  // Trovo il post il cui id è stato passato come parametro
	  iter_post = iter_autore_post->second.get_bacheca()->get_listapost()->find(id_post);
	  
	  map<string,Utente>::iterator iter_autore_like;

    char linea[150];

    while (!file.getline(linea,150).eof()) {
      // Token mail
      string _email = strtok (linea,"\n");

      // Trovo l'utente autore del like nella lista utenti
      iter_autore_like = lista_utenti.find(_email);
      
      // Aggiungo i like relativi al determinato post nella lista di likes relativa al post in questione
	    iter_post->second.popola_lista_likes( pair<string,Utente*> (_email, &(iter_autore_like->second )) );
	  }	
  } else { // se non riesce ad aprire il file
    cerr << "Errore import likes!" << endl;	
  }
  
  // Chiude il file
  file.close();
}

void InTouch::importa_profilo() {
  char linea[150];

  map<string,Utente>::iterator iter;
  
  // Scorro la lista degli utenti
  for (iter = lista_utenti.begin(); iter != lista_utenti.end(); iter++) {
    // Per ogni utente apro il relativo file del profilo
    ifstream file;
    string path = path_files_u + iter->first + "/" + nome_file_profilo;
    file.open(path.c_str(), ios::in);

    // Controllo file esistente e aperto correttamente
    if(file){
      while (!file.getline(linea,150).eof()) {

        // Token sesso
    	  string t_sesso = strtok(linea,"\t");
    	  
        // Token professione
      	string t_professione = strtok(NULL,"\t");
      	
        // Token situazione sentimentale
        string t_situazione_sent = strtok(NULL,"\t");

        // Token giorno nascita
   	    int t_giorno_nascita = atoi(strtok(NULL,"/"));
   	    
        // Token mese nascita
    	  int t_mese_nascita = atoi(strtok(NULL,"/"));
    	  
        // Token anno nascita
      	int t_anno_nascita = atoi(strtok(NULL,"\t"));
      	
        // Token luogo nascita
      	string t_luogo_nascita = strtok(NULL,"\t");

        // Imposto gli attributi del profilo con i dati presenti nel database
      	iter->second.get_profilo()->set_sesso(t_sesso);
      	iter->second.get_profilo()->set_professione(t_professione);
      	iter->second.get_profilo()->set_situasent(t_situazione_sent);
      	iter->second.get_profilo()->set_luogonasc(t_luogo_nascita);

        // Imposto la data di nascita
      	Data d(t_giorno_nascita, t_mese_nascita, t_anno_nascita);
      	iter->second.get_profilo()->set_datanasc_par(d);
      }
	  } else { // se non riesce d prire il file
	    cerr << "Errore import profilo!" << endl;	
	  }
	  
	  // Chiude il file
	  file.close();
  }
}

void InTouch::importa_amicizie() {
  char linea[150];

  map<string,Utente>::iterator iter_utenti;
  map<string,Utente>::iterator iter_utenti2;

  // Scorro la lista degli utenti
  for (iter_utenti = lista_utenti.begin(); iter_utenti != lista_utenti.end(); iter_utenti++) {
    // Per ogni utente apro il file delle amicizie relativo
    string path = path_files_u + iter_utenti->first + "/" + nome_file_amicizie;
    ifstream file;
    file.open(path.c_str(), ios::in);

    // Controllo file esistente e aperto correttamente
    if(file){
      while (!file.getline(linea,150).eof()) {

        // Token ID
        int id = atoi(strtok(linea,"\t"));
        
        // Token utente coinvolto
        string utente = strtok(NULL,"\t");
        
        // Token status
        string s = strtok(NULL,"\t");
        
        // Token ruolo
        string r = strtok(NULL,"\t");

        // Imposto lo stato
        Stato stato;
        if(s == "A") {
          stato = A;
        } else if (s == "X") {
          stato = X;
        } else if (s == "R") {
          stato = R;
        }

        // Imposto il ruolo
        Ruolo ruolo;
        if (r == "MITTENTE") {
          ruolo = MITTENTE;
        } else if (r == "DESTINATARIO") {
          ruolo = DESTINATARIO;
        }

        // Trovo l'utente oggetto della richiesta
        iter_utenti2 = lista_utenti.find(utente);    

        // Creo un'istanza di amicizia con i dati presenti nel database
        Amicizia a(id,&iter_utenti2->second,stato,ruolo);

        // Aggiungo l'amicizia nella lista
        iter_utenti->second.get_listaamicizie()->insert(pair<int,Amicizia> (id,a));

        // Incremento l'id univoco
        id_a = id + 1;
      }
    } else { // se non riesce ad aprire il file
	    cerr << "Errore import amicizia!" << endl;	
	  }
	  
	  // Chiude il file
    file.close();
  }
}
