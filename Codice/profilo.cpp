#include <cstdlib>
#include <iostream>
#include "profilo.h"

using namespace std;

Profilo::Profilo(){
         sex= F; 
         professione= "non dichiarata";
         situasent= "non dichiarata"; 
         luogonasc= "non dichiarato";                                        
}

Profilo::Profilo(Sesso _sex, string _prof, string _situa, string _luogo){
                       sex= _sex;
                       professione= _prof;
                       situasent= _situa; 
                       luogonasc= _luogo;                      
}

void Profilo::modifica_profilo(){
                            
}



