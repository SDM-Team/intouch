#include <sstream>
#include <fstream>
#include <cstring>
#include <direct.h>
#include <map>
#include <list>

#include "intouch.h"
#include "input.h"

// Variabili globali relative a nomi e path dei file di testo
string path_files = "File/";
string path_files_u = "File/Dati utente/";
string path_files_p = "File/Dati post/";

string nome_file_utenti = "utenti.csv";
string nome_file_post = "post.csv";
string nome_file_commenti = "commenti.csv";
string nome_file_likes = "likes.csv";
string nome_file_amicizie = "amicizie.csv";
string nome_file_profilo = "profilo.csv";

extern int id_u;
extern int id_p;

// Costruttore di default, per importare i dati da file all'avvio
InTouch::InTouch() {
    importa_utenti();
    importa_post();
    importa_profilo();
    importa_amicizie();
}

map<string,Utente> InTouch::get_listautenti() {
    return lista_utenti;
}

// Schermata iniziale per registrarsi o autenticarsi nell'applicazione
void InTouch::schermata_autenticazione() {
  int s = 3;
  while(true) {
       
    //voci menu
    cout << "Benvenuto!" << endl;
    cout << "Seleziona cosa vuoi fare:" << endl;
    cout << "1. Registrati" << endl;
    cout << "2. Autenticati" << endl;
    cout << "3. Chiudi applicazione" << endl;
    cout << "4. Reset programma" << endl;
       
 	s = inputInt(1,4);

    switch (s) {
      case 1:
        system("CLS");
        registrazione();
    	break;
      case 2:
        system("CLS");
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
    //password = inputString(MAXLUN);
    password = inputPassword(MAXLUN);
    
    Utente u(email,password);
    
    system("CLS");
    if (!(utente_esiste(u))) {
       // Se l'utente non esiste stampa un messaggio di errore e rimanda alla schermata di autenticazione
       cout << "Errore: Indirizzo email non registrato" << endl << endl;
    } else if (check_login(u)) {
       // Se l'utente esiste e la password inserita � corretta rimanda alla schermata principale
       cout << "Login riuscito!" << endl << endl;

       // Carico i dati dell'utente una volta autenticato
       map<string,Utente>::iterator iter;
       iter = lista_utenti.find(email);
       iter->second.schermata_iniziale();
    } else {
       // Se l'utente esiste ma la password inserita non � corretta stampa un messaggio di errore
       // e rimanda alla schermata di autenticazione
       cout << "Errore: Mancata corrispondenza tra indirizzo email e password" << endl << endl;
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
    email = inputString(MAXLUN);
    
    // Inserimento password
    cout << "Inserisci una password (max " << MAXLUN << " caratteri): ";
    password = inputString(MAXLUN);
    
    
    cout << "Premi 1 per confermare la registrazione," << endl;
    cout << "Premi 0 per annullare e tornare alla schermata di accesso" << endl;
    
    s = inputInt(0,1);
    cout << endl;
    
    switch (s) {
       case 0:
          break;
       case 1:
          Utente u(nome,cognome,email,password);
          
          if (utente_esiste(u)) {
             // Se l'utente esiste gi� stampa un messaggio di errore e rimanda alla schermata di autenticazione
             system("CLS");
             cout << "Errore: Indirizzo email gia' registrato" << endl << endl;
          } else {
                 system("CLS");
             // Se l'utente non esiste ancora richama la funzione di creazione utente
             aggiungi_utente(u);
          }
          break;
    }

    // In ogni caso rimanda alla schermata di autenticazione per registrarsi o effettuare il login
    
}

// Metodo che controlla se un utente esiste gi� o meno
bool InTouch::utente_esiste(const Utente& u) {
    map<string,Utente>::iterator iter;
    iter = lista_utenti.find(u.get_email());
    return (iter != lista_utenti.end());
}

// Metodo che aggiunge un nuovo utente nella lista degli utenti
void InTouch::aggiungi_utente(const Utente& u) {
    lista_utenti.insert(pair<string,Utente> (u.get_email(), u));
    
    string path = path_files + nome_file_utenti;
    ofstream utenti(path.c_str(), ios::app);
    
    utenti << u.get_idutente() << ";";
    utenti << u.get_nome() << ";";
    utenti << u.get_cognome() << ";";
    utenti << u.get_email() << ";";
    utenti << u.get_password() << endl;
    
    utenti.close();
    
    id_u++;
    
    path = path_files_u + u.get_email();
    mkdir(path.c_str());
    
    // Creo file di default
    string path1 = path + "/" + nome_file_profilo;
    ofstream profilo(path1.c_str(), ios::out);
    profilo << "ND;ND;ND;01/01/0;ND" << endl;
    profilo.close();
    
    path1 = path + "/" + nome_file_amicizie;
    ofstream amicizie(path1.c_str(), ios::out);
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

// Metodo che resetta il sistema eliminando utenti e post creati finora, con opportuni file e cartelle
void InTouch::reset() { 
    // Svuoto database utenti
    string path = path_files + nome_file_utenti;
    ofstream file;
    file.open(path.c_str(), ios::out);
    file << "";
    file.close();
    
    // Svuoto database post
    path = path_files + nome_file_post;
    file.open(path.c_str(), ios::out);
    file << "";
    file.close();
    
    // Elimino cartelle e dati utenti
    map<string,Utente>::iterator iter;
    for (iter = lista_utenti.begin(); iter != lista_utenti.end(); iter++) {
       path = path_files_u + iter->first;
       remove((path + "/" + nome_file_amicizie).c_str());
       remove((path + "/" + nome_file_profilo).c_str());
       rmdir(path.c_str());
    }
    
    // Elimino cartelle e dati post
    for (int i = 1; i < id_p; i++) {
       stringstream convert;
       convert << i;
       path = path_files_p + convert.str();
       remove((path + "/" + nome_file_likes).c_str());
       remove((path + "/" + nome_file_commenti).c_str());
       rmdir(path.c_str());
    }
    
    exit(1);
}    

// Metodo che carica gli utenti presenti sul file di testo
void InTouch::importa_utenti() {
    lista_utenti.clear();
    ifstream utenti;
    
    char linea[100];
    
    string path = path_files + nome_file_utenti;
    utenti.open(path.c_str(), ios::in);
    while (!utenti.getline(linea,100).eof()) {
       char* pch;
       
       // Primo token: ID utente
       pch = strtok (linea,";");
       int id_utente = atoi(pch);
       
       // Secondo token: Nome
       string nome = strtok (NULL,";");
       
       // Terzo token: Cognome
       string cognome = strtok (NULL,";");
       
       // Quarto token: Email
       string email = strtok (NULL,";");
       
       // Quinto token: Password
       string password = strtok (NULL,";");
       
       Utente u(nome,cognome,email,password);
       
       lista_utenti.insert(pair<string,Utente> (email,u));
       
       // Crea la cartella nel caso fosse stata cancellata
       string path = path_files_u + email;
       mkdir(path.c_str());
       
       id_u = id_utente + 1;
    } 
    
    utenti.close();
}

void InTouch::importa_post() {
    ifstream post;
    
    char linea[150];
    
    string path = path_files + nome_file_post;
    
    post.open(path.c_str(), ios::in);
    while (!post.getline(linea,150).eof()) {
       char* pch;
       
       //token ID post
       pch = strtok (linea,";");
       int id_post = atoi(pch);
       
       // token autore
       string autore = strtok (NULL,";");
       
       // token giorno
       int giorno = atoi(strtok(NULL,"/"));
       
       // token mese
       int mese = atoi(strtok(NULL,"/"));
       
       // token anno
       int anno = atoi(strtok(NULL," "));
       
       // token ora
       int ora = atoi(strtok(NULL,":"));
       
       // token minuti
       int minuti = atoi(strtok(NULL,";"));
       
       // token testo
       string testo = strtok (NULL,";");
       
       Data temp(giorno,mese,anno,ora,minuti);
       
       Post p(id_post,autore,testo,temp);
       
       map<string,Utente>::iterator iter;
       
       iter = lista_utenti.find(autore);
       
       iter->second.get_bacheca()->get_listapost()->insert(pair<int,Post> (id_post,p));
       
       // Crea la cartella nel caso fosse stata cancellata
       stringstream convert;
       convert << id_post;
       string path = path_files_p + convert.str();
       mkdir(path.c_str());
       
       importa_commenti(autore,id_post);
       
       id_p = id_post + 1;
    } 
    
    post.close();
}

void InTouch::importa_commenti(string _autore, int id_post) {
    stringstream convert;
    convert << id_post;

    string path = path_files_p + convert.str() + "/" + nome_file_commenti;
    ifstream file;
    file.open(path.c_str(), ios::in);
    
    map<string,Utente>::iterator iter_utente;
    iter_utente = lista_utenti.find(_autore);
    
    char linea[150];
    
    while (!file.getline(linea,150).eof()) {
       //autore, tempo, testo
       int id = atoi(strtok(linea,";"));
       string autore = strtok(NULL,";");
       int giorno = atoi(strtok(NULL,"/"));
       int mese = atoi(strtok(NULL,"/"));
       int anno = atoi(strtok(NULL," "));
       int ore = atoi(strtok(NULL,":"));
       int minuti = atoi(strtok(NULL,";"));
       string testo = strtok(NULL,";");
       
       Data temp(giorno,mese,anno,ore,minuti);
       Commento c(id,autore,temp,testo);
       
       map<int,Post>::iterator iter_post;
       iter_post = iter_utente->second.get_bacheca()->get_listapost()->find(id_post);
       iter_post->second.get_listacommenti()->push_back(c);
   }
}

void InTouch::importa_profilo() {
    char linea[150];
    
    map<string,Utente>::iterator iter;
    for (iter = lista_utenti.begin(); iter != lista_utenti.end(); iter++) {
      ifstream file;
      string path = path_files_u + iter->first + "/" + nome_file_profilo;
      file.open(path.c_str(), ios::in);
      
      while (!file.getline(linea,150).eof()) {
      
      // Token
      string t_sesso = strtok(linea,";");
      string t_professione = strtok(NULL,";");
      string t_situazione_sent = strtok(NULL,";");
      int t_giorno_nascita = atoi(strtok(NULL,"/"));
      int t_mese_nascita = atoi(strtok(NULL,"/"));
      int t_anno_nascita = atoi(strtok(NULL,";"));
      string t_luogo_nascita = strtok(NULL,";");
      
      iter->second.get_profilo()->set_sesso(t_sesso);
      iter->second.get_profilo()->set_professione(t_professione);
      iter->second.get_profilo()->set_situasent(t_situazione_sent);
      iter->second.get_profilo()->set_luogonasc(t_luogo_nascita);
      
      Data d(t_giorno_nascita, t_mese_nascita, t_anno_nascita);
      iter->second.get_profilo()->set_datanasc_par(d);
    }
  }
}
      
void InTouch::importa_amicizie() {

}

//controllo input: http://www.dreamincode.net/forums/topic/137648-limiting-string-length/

/*

int charsread = 0;
string str;
char c;
while (// more input
)
{
    // read a character (c)
    if (charsread < 5)
        str += c;
    ++charsread;
}

*/
//alternativa: https://www.daniweb.com/software-development/cpp/threads/398829/restricting-string-input-size-c-vs-c-strings
/* 

std::string name ;
    constexpr std::string::size_type MAX_CHARS = 20 ;
    if( std::cout << "name (max " << MAX_CHARS << " chars)? " && std::getline( std::cin, name  ) )
    {
        if( name.size() > MAX_CHARS )
        {
            std::cerr << name << " is too long; truncating it\n" ;
            name = name.substr( 0, MAX_CHARS ) ;
        }
        // use name
    }
    // else i/o error
    
*/

