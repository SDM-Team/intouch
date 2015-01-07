#include <time.h>		/* time(0), struct tm, localtime		*/
#include <iostream>		/* cout, endl, cerr, ostream			*/

// Librerie personalizzate
#include "data.h"		/* Libreria di riferimento 				*/
#include "input.h"		/* inputInt								*/

// Costruttore di default, inizializza data e ora ad un valore di default
Data::Data() {
  giorno = 1;
  mese = 1;
  anno = 0;
  ore = 88; // inizializzo ore a valore di default
  minuti = 88; // inizializzo minuti a valore di default
}

// Costruttore di copia
Data::Data(const Data& d){
  giorno = d.giorno;
  mese = d.mese;
  anno = d.anno;
  ore = d.ore;
  minuti = d.minuti;                 
}

// Costruttore specifico, solo per la data
Data::Data(int _g, int _m, int _a) {
  giorno = _g;
  mese = _m;
  anno = _a;  
  ore = 88;
  minuti = 88;
}

// Costruttore specifico, per data e ora
Data::Data(int _g, int _m, int _a, int _o, int _min) {
  giorno = _g;
  mese = _m;
  anno = _a;  
  ore = _o;
  minuti = _min;
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
    os << " ";
		
    // Se l'ora è tra 0 e 9 aggiunge uno 0 prima
    if (d.ore < 10) {
      os << "0";
    }
    
    os << d.ore << ":";
    
    // Se i minuti sono tra 0 e 9 aggiunge uno 0 prima
    if (d.minuti < 10) {
      os << "0";
    }
    
    os<<d.minuti;	   
  }
			   
  return os;               
}

// Funzione per impostare la data, con richiesta all'utente
void Data::imposta_data(){  
  int _giorno;
  int _mese;
  int _anno;
  
  // Necessario per i controllo rispetto alla data corrente
  Data temp;
  temp.imposta_dataOra();
  
  do {
    cout << "Inserire giorno: ";
    _giorno = inputInt(1,31);
  
    cout << "Inserire mese: ";
    _mese = inputInt(1,12);                            
  
    cout << "Inserire anno: ";
    _anno = inputInt(0,temp.anno);
    
    // Controllo validità della data rispetto a quella corrente
    if((_anno < temp.anno) ||	(_anno == temp.anno && _mese < temp.mese) ||
      (_anno == temp.anno && _mese == temp.mese && _giorno <= temp.giorno)) {
    
      // Controllo validità giorni rispetto al mese
      if(_giorno <= 31 && (_mese == 1 || _mese == 3 || _mese == 5 || _mese == 7 || _mese == 8 || _mese == 10 || _mese == 12) ){ break;}    
      if(_giorno <= 30 && (_mese == 4 || _mese == 6 || _mese == 9 || _mese == 11) ) { break; }

      // Controllo anni bisestili e controllo standard su febbraio
	    if(_giorno == 29 && _mese == 2 && (_anno % 400 == 0 || (_anno % 100 != 0 && _anno % 4 == 0)) ) { break; }
	    if(_giorno <=28 && _mese == 2) { break; }
	  }
	
    // Se non è una data valida si ripete l'input
    cerr << "La data inserita non e' valida! Reinserire." << endl << endl;
    
  } while(true);
 
  giorno = _giorno;
  mese = _mese;
  anno = _anno;
}

// Metodo che prende la data e l'ora corrente
void Data::imposta_dataOra(){
  time_t t = time(0);   //tempo corrente
  struct tm * now = localtime( & t );
		 
  giorno = now->tm_mday;
  mese = (now->tm_mon +1);
  anno = (now->tm_year + 1900);
  ore = now->tm_hour;
  minuti = now->tm_min;
}
