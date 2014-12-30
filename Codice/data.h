#ifndef data_h
#define data_h
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

class Data{
      private:
              int giorno;
              int mese;
              int anno;
              int ore;
              int minuti;
      public:
             Data();
             Data(const Data& d);
             Data(int _g, int _m, int _a);
             Data(int _g, int _m, int _a, int _o, int _min);
             friend ostream& operator<<(ostream& os,const Data& d); 
             void imposta_data();
             void imposta_dataOra();
       
};

#endif

