#ifndef __PROFILO_H__
#define __PROFILO_H__
#include <string>
#include <cstdlib>
#include <iostream>
#include "data.h"
#define MAXLUN 25

using namespace std;
typedef char stringa [MAXLUN+1];

class Profilo{
      private:
               //Utente utente; losanga piena 1,1
               stringa sesso;
               string professione;
               string situasent;
               data datanasc;
               string luogonasc;
      public:
              Profilo();
              Profilo(stringa _sex, string _prof, string _situa, string _luogo);              
              void visualizza_profilo();
              void modifica_profilo();                                
};



#endif

