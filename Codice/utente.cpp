#include "utente.h"
#include "intouch.h"

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

// Metodo che controlla se un utente esiste già o meno
bool Utente::utente_esiste(list<Utente>* p_lista_utenti) {
    list<Utente>::iterator iter;
    for (iter = p_lista_utenti->begin(); iter != p_lista_utenti->end(); iter++) {
       if (email == iter->email) return true;
    }
       
    return false;
}

// Metodo che aggiunge un nuovo utente nella lista degli utenti
void Utente::aggiungi_utente(list<Utente>* p_lista_utenti) {
    p_lista_utenti->push_back(*this);
    
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
bool Utente::check_login(list<Utente>* p_lista_utenti) {
    list<Utente>::iterator iter;
    for (iter = p_lista_utenti->begin(); iter != p_lista_utenti->end(); iter++) {
       if ((email == iter->email) && (password == iter->password)) return true;
    }
    return false;
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
    
    do{ 
	//che belo l menu tuto pulito ara
	system("CLS");
	
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
	
	//flush stdin
	cin.clear();
	//impedisce loop su input non-int
	cin.get();
		
	cin >> s;
    cout << endl;
    
    
    switch (s) {
       case 1:
          // Amicizie
          break;
       case 2:
          // Post amici
          break;
       case 3:
          // Bacheca
          break;
       case 4:
          profilo.visualizza_profilo();
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
