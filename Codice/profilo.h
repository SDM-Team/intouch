#ifndef __PROFILO_H__
#define __PROFILO_H__

#include <string>		/* string								*/

// Librerie personalizzate
#include "config.h"		/* Definizione variabili globali 		*/
#include "data.h"		/* classe Data e metodi relativi 		*/


typedef char stringa [MAXLUN+1];

using namespace std;

class Profilo{
      private:
               //Utente utente; losanga piena 1,1
               string sesso;
               string professione;
               string situasent;
               Data datanasc;
               string luogonasc;
      public:
              Profilo();
              Profilo(const Profilo& p);
              Profilo(stringa _sex, string _prof, string _situa, string _luogo);              
              string get_sesso();
              string get_professione();
              string get_situasent();
              Data get_datanasc();
              string get_luogonasc();
              void set_sesso(const string& _sesso);
              void set_professione(const string& _professione);
              void set_situasent(const string& _situasent);
              void set_datanasc();
              void set_datanasc_par(const Data& d);
              void set_luogonasc(const string& _luogonasc);
};



#endif

