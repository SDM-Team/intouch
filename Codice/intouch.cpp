#include "intouch.h"

// Schermata iniziale per registrarsi o autenticarsi nell'applicazione
void InTouch::schermata_autenticazione() {
    int s = 0;
    while ((s < 1) || (s > 3)) {
       cout << "Benvenuto!" << endl;
       cout << "Seleziona cosa vuoi fare:" << endl;
       cout << "1. Registrati" << endl;
       cout << "2. Autenticati" << endl;
       cout << "3. Chiudi applicazione" << endl;
       cin >> s;
       cout << endl;
       if ((s < 1) || (s > 3)) {
          cout << "Errore: Scelta non possibile" << endl << endl;
       }
    }
    
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

// Schermata iniziale che si visualizza una volte autenticato correttamente
void InTouch::schermata_iniziale() {
    int s = 0;
    while ((s < 1) || (s > 7)) {
       cout << "Benvenuto!" << endl;
       cout << "Seleziona la funzione desiderata:" << endl;
       cout << "1. Gestisci amicizie" << endl;
       cout << "2. Visualizza i post degli amici" << endl;
       cout << "3. Visualizza la tua bacheca" << endl;
       cout << "4. Visualizza e modifica il tuo profilo" << endl;
       cout << "5. Visualizza il profilo e la bacheca di un amico" << endl;
       cout << "6. Crea post" << endl;
       cout << "7. Logout" << endl;
       cin >> s;
       cout << endl;
       if ((s < 1) && (s > 7)) {
          cout << "Errore: Scelta non possibile" << endl << endl;
       }
    }
    
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
          // Profilo
          break;
       case 5:
          // Profilo e bacheca amico
          break;
       case 6:
          // Crea post
          break;
       case 7:
          cout << "Logout effettuato!" << endl << endl;
          logout();
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
    cout << endl;
    
    Utente u(email,password);
    
    if (!(u.utente_esiste(&lista_utenti))) {
       // Se l'utente non esiste stampa un messaggio di errore e rimanda alla schermata di autenticazione
       cout << "Errore: Indirizzo email non registrato" << endl << endl;
       schermata_autenticazione();
    } else if (u.check_login(&lista_utenti)) {
       // Se l'utente esiste e la password inserita è corretta rimanda alla schermata principale
       cout << "Login riuscito!" << endl << endl;
       schermata_iniziale();
    } else {
       // Se l'utente esiste ma la password inserita non è corretta stampa un messaggio di errore
       // e rimanda alla schermata di autenticazione
       cout << "Errore: Mancata corrispondenza tra indirizzo email e password" << endl << endl;
       schermata_autenticazione();
    }
}

// Metodo di logout, rimanda alla schermata di autenticazione
void InTouch::logout() {
    schermata_autenticazione();
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
    
    switch (s) {
       case 0:
          schermata_autenticazione();
          break;
       case 1:
          Utente u(nome,cognome,email,password);
          
          if (u.utente_esiste(&lista_utenti)) {
             // Se l'utente esiste già stampa un messaggio di errore e rimanda alla schermata di autenticazione
             cout << "Errore: Indirizzo email gia' registrato" << endl << endl;
          } else {
             // Se l'utente non esiste ancora richama la funzione di creazione utente
             u.aggiungi_utente(&lista_utenti);
          }
          break;
    }

    // In ogni caso rimanda alla schermata di autenticazione per registrarsi o effettuare il login
    schermata_autenticazione();
}
