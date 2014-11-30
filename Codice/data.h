#ifndef data_h
#define data_h
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

class data{
      private:
              int giorno;
              int mese;
              int anno;
              int ore;
              int minuti;
      public:
             data();
             data(int _g, int _m, int _a);
             friend ostream& operator<<(ostream& os,const data& d); 
             void imposta_data();
             void imposta_dataOra();
       
};

#endif

