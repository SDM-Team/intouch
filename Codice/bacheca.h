#ifndef __BACHECA_H__
#define __BACHECA_H__

#include <map>			/* map									*/

// Libreria personalizzata
#include "post.h"

// Forward declaration
class Utente;

// Namespace
using namespace std;

// Dichiarazione della classe Bacheca
class Bacheca {
  private:
    map<int,Post> lista_post;
  public:
    Bacheca();
    Bacheca(const Bacheca& b);
    void aggiungi_post(Utente* _u);
    map<int,Post>* get_listapost();
};

#endif

