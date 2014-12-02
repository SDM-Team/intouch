#include <sstream>
#include "intouch.h"

extern int id_u;

// Schermata iniziale per registrarsi o autenticarsi nell'applicazione
void InTouch::schermata_autenticazione() {
    int s = 3;
    string input = "";
     do{
     	//system("CLS");
     	
     	//controllo range int input
     	if ((s < 1) || (s > 3)) {
          cout << "Errore: Scelta non possibile" << endl << endl;
       }
       
       //voci menu
       cout << "Benvenuto!" << endl;
       cout << "Seleziona cosa vuoi fare:" << endl;
       cout << "1. Registrati" << endl;
       cout << "2. Autenticati" << endl;
       cout << "3. Chiudi applicazione" << endl;
       
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
       
    }while ((s < 1) || (s > 3));
    
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
    }
}

// Metodo di login
void InTouch::login() {
    string email;
    string password;
    
    // Inserimento email
    cout << "Inserisci il tuo indirizzo email: ";
    cin >> email;
    
    // Inserimento password
    cout << "Inserisci la tua password: ";
    cin >> password;
    cin.ignore();
    cout << endl;
    
    Utente u(email,password);
    
    if (!(utente_esiste(u))) {
       // Se l'utente non esiste stampa un messaggio di errore e rimanda alla schermata di autenticazione
       cout << "Errore: Indirizzo email non registrato" << endl << endl;
       schermata_autenticazione();
    } else if (check_login(u)) {
       // Se l'utente esiste e la password inserita è corretta rimanda alla schermata principale
       cout << "Login riuscito!" << endl << endl;
       u.schermata_iniziale();
    } else {
       // Se l'utente esiste ma la password inserita non è corretta stampa un messaggio di errore
       // e rimanda alla schermata di autenticazione
       cout << "Errore: Mancata corrispondenza tra indirizzo email e password" << endl << endl;
       schermata_autenticazione();
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
    cout << "Inserisci il tuo nome: ";
    cin >> nome;
    
    // Inserimento cognome
    cout << "Inserisci il tuo cognome: ";
    cin >> cognome;
    
    // Inserimento email
    cout << "Inserisci il tuo indirizzo email: ";
    cin >> email;
    
    // Inserimento password
    cout << "Inserisci una password: ";
    cin >> password;
    
    cout << "Premi 1 per confermare la registrazione," << endl;
    cout << "Premi 0 per annullare e tornare alla schermata di accesso" << endl;
    cin >> s;
    cout << endl;
    cin.ignore();
    
    switch (s) {
       case 0:
          schermata_autenticazione();
          break;
       case 1:
          Utente u(nome,cognome,email,password);
          
          if (utente_esiste(u)) {
             // Se l'utente esiste già stampa un messaggio di errore e rimanda alla schermata di autenticazione
             cout << "Errore: Indirizzo email gia' registrato" << endl << endl;
          } else {
             // Se l'utente non esiste ancora richama la funzione di creazione utente
             aggiungi_utente(u);
          }
          break;
    }

    // In ogni caso rimanda alla schermata di autenticazione per registrarsi o effettuare il login
    schermata_autenticazione();
}

// Metodo che controlla se un utente esiste già o meno
bool InTouch::utente_esiste(const Utente& u) {
    list<Utente>::iterator iter;
    for (iter = lista_utenti.begin(); iter != lista_utenti.end(); iter++) {
       if (u.get_email() == iter->get_email()) return true;
    }
       
    return false;
}

// Metodo che aggiunge un nuovo utente nella lista degli utenti
void InTouch::aggiungi_utente(const Utente& u) {
    lista_utenti.push_back(u);
    
    /*fstream utenti;
    utenti.open("utenti.txt");
    
    if(utenti == NULL) {
       perror("Errore in apertura del file");
       exit(1);
    }
    
    utenti << id_utente << endl;
    utenti << nome << endl;
    utenti << cognome << endl;
    utenti << email << endl;
    utenti << password << endl << endl;
    
    utenti.close();*/
    
    id_u++;
}

// Metodo che verifica la correttezza della password inserita in fase di login
bool InTouch::check_login(const Utente& u) {
    list<Utente>::iterator iter;
    for (iter = lista_utenti.begin(); iter != lista_utenti.end(); iter++) {
       if ((u.get_email() == iter->get_email()) && (u.get_password() == iter->get_password())) return true;
    }
    return false;
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

