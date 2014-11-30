#include "data.h"

data::data(){
             giorno=1;
             mese=1;
             anno=0;
			 ore=88;
			 minuti=88;             
}

data::data(int _g, int _m, int _a){
               giorno= _g;
               mese= _m;
               anno= _a;  
			   ore=88;
			   minuti=88;             
}

//l'operatore<< aggiunge anche uno zero se il numero è valido e <10
ostream& operator<<(ostream& os,const data& d){
			
               if(d.giorno>0 && d.giorno<10){os << "0"; } os<<d.giorno<<"/";
			   if(d.mese>0 && d.mese<10){os << "0"; } os<<d.mese<<"/"
			   <<d.anno;
			   
			   if((d.ore>=0 && d.ore <=24) && (d.minuti>=0 && d.minuti<60)){
			   					os<<" Ora: ";
								if(d.ore<10){os << "0"; } os<<d.ore<<":";
								if(d.minuti<10){os << "0"; } os<<d.minuti;	   
			   }
			   
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

void data::imposta_dataOra(){
    time_t t = time(0);   //tempo corrente
    struct tm * now = localtime( & t );
		 
	giorno = now->tm_mday;
	mese = (now->tm_mon +1);
	anno = (now->tm_year + 1900);
	ore = now->tm_hour;
	minuti = now->tm_min;   
	               
}
