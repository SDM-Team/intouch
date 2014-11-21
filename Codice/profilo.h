#ifndef __PROFILO_H__
#define __PROFILO_H__
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef enum {M, F} Sesso;

class Profilo{
      private:
               Sesso sex;
               string professione;
               string situasent;
               string luogonasc;
      public:
              Profilo();
              Profilo(Sesso _sex, string _prof, string _situa, string _luogo);              
              void visualizza_profilo();
              void modifica_profilo();                                
};



#endif
