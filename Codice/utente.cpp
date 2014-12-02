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
