#include <conio.h>		/* getch								*/
#include <iostream>		/* cout, endl, cin						*/
#include <sstream>		/* stringstream							*/
#include <string>		/* string, getline						*/

// Libreria personalizzata
#include "input.h"

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
   	  cout << "Errore: numero non valido" << endl;
    }
    
    if(t>=min && t<=max)
      break;
    else{
      cout << "Errore: range non valido" << endl;	
    }
  }
  return t;
}

string inputString(int max){
  string s;
  string::size_type max_chars = max;
  while(true){
    getline( cin, s );
    
    if( s.size() > max_chars ) {
      cerr<<"Errore: inseriti piu' di "<<max<<" caratteri; reinserire:"<<endl;
      //s = s.substr( 0, MAX_CHARS ) ; //per troncare
    } else {
      break;	
    }
  }
	return s;  	
}

string inputPassword(int max){
  char c;
  int i = 0;
  string s = "";
  string::size_type max_chars = max;	
  while(true){
    c = getch();
    
    //smette input se premi invio
    if( c == '\r'){
	    return s;
    }
    
	  if( s.size() > max_chars ) {
      cerr<<"Errore: inseriti piu' di "<<max<<" caratteri; "<<endl;
      cout<<"Reinserire password:"<<endl;
      s="";
    } else if( c == '\b' || c == char(8)){ //c != 8 && c != 127 && //tasti backspace e delete
      if(i > 0){
	      //cout << string(1,'\b' ); //cancella 1 carattere
	      cout << char(8);
	      cout<<" ";
	      cout << char(8);
          i--;
	      s = s.substr( 0, i ); //tronca la stringa al carattere precedente
	    }
    } else {
      cout << "*";
      s+=c;
      i++;
    }
  }
}
