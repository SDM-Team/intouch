#include <conio.h>		/* getch								*/
#include <iostream>		/* cout, endl, cin, cerr				*/
#include <sstream>		/* stringstream							*/
#include <string>		/* string, getline						*/

// Libreria personalizzata
#include "input.h"

// Namespace
using namespace std;

int inputInt(int min, int max){
  int t = 0;
  string input = "";
  
  //controllo range int input
  while (true) {
  	
    //controllo input non-int
    while (true) {
  	  cin.clear();
  	  getline(cin, input);
  			
   	  //Questo codice converte da stringa a int in modo sicuro
   	  stringstream myStream(input);
      if (myStream >> t)
        break;
   	  cerr << "Errore: numero non valido;" << endl;
	  cout << "Reinserire: ";
    }
    
    if(t>=min && t<=max)
      break;
    else{
      cerr << "Errore: range non valido;" << endl;
	  cout << "Reinserire: ";
    }
  }
  return t;
}

string inputString(int max){
  string s;
  string::size_type max_chars = max;
  while(true){
    getline( cin, s );
    
    // Gestione errori
    if( s.size() > max_chars ) {
      cerr<<"Errore: inseriti piu' di "<<max<<" caratteri;" << endl;
      cout<<"Reinserire: ";
      //s = s.substr( 0, MAX_CHARS ) ; //per troncare
    } else if( s.empty() ){
	  cerr<<"Errore: inserita stringa vuota; "<<endl;
      cout<<"Reinserire:";
    } else if( s[0] == char(32) ){
	  cerr << "Errore: la stringa non puo' iniziare con uno spazio;" << endl;
      cout << "Reinserire: ";
    } else if( s.find( "\t" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (tab);" << endl;
      cout << "Reinserire: "; 
    } else {
      break;	
    }
  }
  return s;  	
}

string inputEmail(int max){
  string s;
  string::size_type max_chars = max;
  while(true){
    getline( cin, s );
    
    // Gestione errori e caratteri speciali che impediscono creazione cartella \ / : * ? " < > |
    if( s.size() > max_chars ) {
      cerr<<"Errore: inseriti piu' di "<<max<<" caratteri;" << endl;
      cout<<"Reinserire: ";
      //s = s.substr( 0, MAX_CHARS ) ; //per troncare
    } else if( s.empty() ){
	  cerr<<"Errore: inserita stringa vuota; "<<endl;
      cout<<"Reinserire:";
	} else if( s[0] == char(32) ){
	  cerr << "Errore: la stringa non puo' iniziare con uno spazio;" << endl;
      cout << "Reinserire: ";
	} else if( s.find( "\t" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (tab);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "\\" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (\\);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "/" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (/);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( ":" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (:);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "*" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (*);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "?" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (?);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "\"" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (\");" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "<" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (<);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( ">" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (>);" << endl;
      cout << "Reinserire: "; 
	} else if( s.find( "|" ) != string::npos ){ 
	  cerr << "Errore: la stringa contiene caratteri non validi (|);" << endl;
      cout << "Reinserire: "; 
	} else {
      break;	
    }
  }
	return s;  
}

string inputPassword(int max){
  char c;
  string s = "";
  string::size_type max_chars = max;	
  while(true){
    c = getch();
    
    // Se invio gestisco eventuali errori
    if( c == '\r' ){
	  // Errore se password vuota -> s.size() == 0
	  if( s.empty() ){
	    cerr << endl << "Errore: inserita password vuota;" << endl;
        cout << "Reinserire password: ";
        s="";
      }
      // Errore se invio con primo campo 'spazio' tasto 32
      else if( s[0] == char(32) ){
  	    cerr << endl << "Errore: la password non puo' iniziare con uno spazio;" << endl;
        cout << "Reinserire password: ";
        s="";
      }
      // Errore se viene inserito carattere delimitatore per CSV (tab)
      else if( s.find( "\t" ) != string::npos ){ 
  	    cerr << "Errore: la stringa contiene caratteri non validi (tab);" << endl;
        cout << "Reinserire: "; 
  	  }
      // Smette input se premi invio e la password è valida
      else {
  	    return s;
      }
    }
    
    // Gestisco caratteri backspace e delete tasti 8 e 127
    else if( c == '\b' || c == char(8) || c == char(127) ){
      // Controllo che la stringa contenga qualcosa prima di cancellare
      if(s.size() > 0){
	    cout << char(8);
  	    // Cancello un asterisco da schermo
  	    cout<<" ";
  	    cout << char(8);
  	    s = s.substr( 0, (s.size() - 1) ); // Tronca la stringa al carattere precedente
	  }
    }
	
	// Controllo che la stringa non sia piena
  	else if( s.size() >= max_chars ) {
      cerr << endl << "Errore: inseriti piu' di "<<max<<" caratteri;" << endl;
      cout << "Reinserire password: ";
      s="";
    } else { // Inserisco il carattere digitato e stampo un asterisco
      cout << "*";
      s+=c;
    }
  }
}
