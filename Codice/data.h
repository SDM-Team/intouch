#ifndef data_h
#define data_h
#include <cstdlib>
#include <iostream>

using namespace std;

class data{
      private:
              int giorno;
              int mese;
              int anno;
      public:
             data();
             data(int _g, int _m, int _a);
             friend ostream& operator<<(ostream& os,const data& d); 
             void imposta_data(); 
       
};

#endif
