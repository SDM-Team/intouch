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
               string sesso;
               string professione;
               string situasent;
               data datanasc;
               string luogonasc;
      public:
              Profilo();
              Profilo(stringa _sex, string _prof, string _situa, string _luogo);              
              string get_sesso();
              string get_professione();
              string get_situasent();
              data get_datanasc();
              string get_luogonasc();
              void set_sesso(const string& _sesso);
              void set_professione(const string& _professione);
              void set_situasent(const string& _situasent);
              void set_datanasc();
              void set_luogonasc(const string& _luogonasc);
};



#endif

