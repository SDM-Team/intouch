#include "data.h"

// Costruttore di default
Data::Data() {
  giorno = 1;
  mese = 1;
  anno = 0;
	ore = 88;
	minuti = 88;             
}

// Costruttore specifico
Data::Data(int _g, int _m, int _a) {
  giorno =  _g;
  mese =  _m;
  anno =  _a;  
	ore = 88;
	minuti = 88;             
}

// L'operatore << aggiunge anche uno zero se il numero è valido e < 10
ostream& operator << (ostream& os,const Data& d) {
  
  // Se il giorno è tra 0 e 9 aggiunge uno 0 prima
  if((d.giorno > 0) && (d.giorno < 10)) {
    os << "0";
  }

  os<<d.giorno<<"/";

  // Se il mese è tra 0 e 9 aggiunge uno 0 prima
  if((d.mese > 0) && (d.mese < 10)) {
    os << "0";
  }

  os << d.mese << "/" << d.anno;

  // Se le ore sono tra 0 e 24 e i minuti tra 0 e 60 (fatto per non considerare l'ora di default 88:88
  if (((d.ore >= 0) && (d.ore <= 24)) && ((d.minuti >= 0) && (d.minuti < 60))) {
    os << "Ora: ";
		
    // Se l'ora è tra 0 e 9 aggiunge uno 0 prima
    if (d.ore < 10) {
      os << "0";
    }
    
    os<<d.ore<<":";
    
    // Se i minuti sono tra 0 e 9 aggiunge uno 0 prima
    if (d.minuti < 10) {
      os << "0";
    }
    
    os<<d.minuti;	   
  }
			   
  return os;               
}

// Funzione per impostare la data
void Data::imposta_data(){  
  cout << "Inserire giorno: ";
  cin >> giorno;
  cin.ignore();
  cout << endl;

  while ((giorno < 1) || (giorno > 31)) {
    if ((giorno < 1) || (giorno > 31)) {
      cout << "Errore: giorno non esistente" << endl;
    }
    printf("Inserire giorno: "); cin>>giorno; cin.ignore();                     
                          }                                                                           
                          printf("Inserire mese: "); cin>>mese; cin.ignore();                            
                          while((mese<1)||(mese>12)){
                                               if((mese<1)||(mese>12)){printf("Errore scelta non possibile\n");}
                                               printf("Inserire mese: "); cin>>mese; cin.ignore();                    
                          }                                                     
                          printf("Inserire anno: "); cin>>anno; cin.ignore();                        
                          while((anno<0)||(anno>2014)){
                                                 if((anno<0)||(anno>2014)){printf("Errore scelta non possibile\n");}
                                                 printf("Inserire anno: "); cin>>anno; cin.ignore();                      
                          }                           
}

void Data::imposta_dataOra(){
    time_t t = time(0);   //tempo corrente
    struct tm * now = localtime( & t );
		 
	giorno = now->tm_mday;
	mese = (now->tm_mon +1);
	anno = (now->tm_year + 1900);
	ore = now->tm_hour;
	minuti = now->tm_min;   
	               
}
