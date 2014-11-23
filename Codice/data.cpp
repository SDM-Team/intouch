#include "data.h"

data::data(){
             giorno=1;
             mese=1;
             anno=0;             
}

data::data(int _g, int _m, int _a){
               giorno= _g;
               mese= _m;
               anno= _a;               
}

ostream& operator<<(ostream& os,const data& d){
               os<<d.giorno<<"/"<<d.mese<<"/"<<d.anno;
               return os;               
}

void data::imposta_data(){
                          printf("Inserire giorno: "); scanf("%d",&giorno);                                                 
                          while((giorno<1)||(giorno>31)){
                                               if((giorno<1)||(giorno>31)){printf("Errore scelta non possibile\n");}
                                               printf("Inserire giorno: "); scanf("%d",&giorno);                     
                          }                                                                           
                          printf("Inserire mese: "); scanf("%d",&mese);                             
                          while((mese<1)||(mese>12)){
                                               if((mese<1)||(mese>12)){printf("Errore scelta non possibile\n");}
                                               printf("Inserire mese: "); scanf("%d",&mese);                     
                          }                                                     
                          printf("Inserire anno: "); scanf("%d",&anno);                           
                          while((anno<0)||(anno>2014)){
                                                 if((anno<0)||(anno>2014)){printf("Errore scelta non possibile\n");}
                                                 printf("Inserire anno: "); scanf("%d",&anno);                     
                          }                           
}


