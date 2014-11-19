#include <cstdlib>
#include <iostream>
#include "intouch.h"

using namespace std;

list<Utente> lista_utenti;

int main(int argc, char *argv[])
{
    InTouch applicazione;
    applicazione.schermata_autenticazione();
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
