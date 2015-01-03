#include <cstdlib>		/* system								*/

// Libreria personalizzata
#include "intouch.h"

// Namespace
using namespace std;

int main(int argc, char *argv[])
{
  InTouch applicazione;
  applicazione.schermata_autenticazione();

  system("PAUSE");
  return EXIT_SUCCESS;
}
