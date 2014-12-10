#include <sstream>
#include <fstream>
#include <cstring>
#include "intouch.h"
#include "input.h"

extern int id_u;
extern int id_p;

// Costruttore di default, per importare i dati da file all'avvio
InTouch::InTouch() {
    importa_utenti();
    importa_post();
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
       
 	s = inputInt(1,3);

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
       // Se l'utente esiste e la password inserita è corretta rimanda alla schermata principale
       cout << "Login riuscito!" << endl << endl;

       // Carico i dati dell'utente una volta autenticato
       map<string,Utente>::iterator iter;
       iter = lista_utenti.find(email);
       iter->second.schermata_iniziale();
    } else {
       // Se l'utente esiste ma la password inserita non è corretta stampa un messaggio di errore
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
             // Se l'utente esiste già stampa un messaggio di errore e rimanda alla schermata di autenticazione
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

// Metodo che controlla se un utente esiste già o meno
bool InTouch::utente_esiste(const Utente& u) {
    map<string,Utente>::iterator iter;
    iter = lista_utenti.find(u.get_email());
    return (iter != lista_utenti.end());
}

// Metodo che aggiunge un nuovo utente nella lista degli utenti
void InTouch::aggiungi_utente(const Utente& u) {
    lista_utenti.insert(pair<string,Utente> (u.get_email(), u));
    
    ofstream utenti("utenti.csv", ios::app);
    
    utenti << u.get_idutente() << ";";
    utenti << u.get_nome() << ";";
    utenti << u.get_cognome() << ";";
    utenti << u.get_email() << ";";
    utenti << u.get_password() << endl;
    
    utenti.close();
    
    id_u++;
}

// Metodo che verifica la correttezza della password inserita in fase di login
bool InTouch::check_login(const Utente& u) {
    map<string,Utente>::iterator iter;
    iter = lista_utenti.find(u.get_email());
    if ((u.get_email() == iter->second.get_email()) && (u.get_password() == iter->second.get_password())) return true;
    return false;
}

// Metodo che carica gli utenti presenti sul file di testo
void InTouch::importa_utenti() {
    lista_utenti.clear();
    ifstream utenti;
    
    char linea[100];
    
    utenti.open("utenti.csv", ios::in);
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
       
       id_u = id_utente + 1;
    } 
    
    utenti.close();
}

void InTouch::importa_post() {
    ifstream post;
    
    char linea[150];
    
    post.open("post.csv", ios::in);
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
       
       id_p = id_post + 1;
    } 
    
    post.close();
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

