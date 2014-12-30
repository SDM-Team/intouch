#include <cstdlib>		/* system								*/

// Libreria personalizzata
#include "intouch.h"

using namespace std;

InTouch applicazione;

int main(int argc, char *argv[])
{
    applicazione.schermata_autenticazione();
        
    system("PAUSE");
    return EXIT_SUCCESS;
}
