#ifndef __BACHECA_H__
#define __BACHECA_H__

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "data.h"
#include "post.h"

class Utente;

// Dichiarazione della classe Bacheca
class Bacheca {
  private:
    map<int,Post> lista_post;
  public:
    void aggiungi_post(Utente* _u);
    map<int,Post>* get_listapost();
};

#endif
