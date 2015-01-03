#include <string>		/* string								*/

// Libreria personalizzata
#include "profilo.h"	/* Libreria di riferimento 				*/
#include "config.h"		/* Definizione variabili globali 		*/
#include "data.h"		/* classe Data e metodi relativi 		*/

// Namespace
using namespace std;

// Costruttore di default
Profilo::Profilo(){
  sesso = "ND";
  professione = "ND";
  situasent = "ND"; 
  luogonasc = "ND";                                        
}

// Costruttore di copia
Profilo::Profilo(const Profilo& p){
  sesso= p.sesso;
  professione= p.professione;
  situasent= p.situasent;
  datanasc= p.datanasc;
  luogonasc= p.luogonasc;                       
}

// Costruttore specifico
Profilo::Profilo(string _sex, string _prof, string _situa, string _luogo){
  sesso = _sex;
  professione = _prof;
  situasent = _situa;
  luogonasc = _luogo;                      
}

// Metodo che restituisce il sesso
string Profilo::get_sesso() {
  return sesso;
}

// Metodo che restituisce la professione
string Profilo::get_professione() {
  return professione;
}

// Metodo che restituisce la situazione sentimentale
string Profilo::get_situasent() {
  return situasent;
}

// Metodo che restituisce la data di nascita
Data Profilo::get_datanasc() {
  return datanasc;
}

// Metodo che restituisce il luogo di nascita
string Profilo::get_luogonasc() {
  return luogonasc;
}

// Metodo che imposta il sesso con il valore passato
void Profilo::set_sesso(const string& _sesso) {
  sesso = _sesso;
}

// Metodo che imposta la professione con il valore passato
void Profilo::set_professione(const string& _professione) {
  professione = _professione;
}

// Metodo che imposta la situazione sentimentale con il valore passato
void Profilo::set_situasent(const string& _situasent) {
  situasent = _situasent;
}

// Metodo che chiede all'utente di inserire giorno, mese e anno della data di nascita e la imposta su tali valori
void Profilo::set_datanasc() {
  Data d;
  d.imposta_data();
  datanasc = d;
}

// Metodo che imposta la data di nascita con il valore passato
void Profilo::set_datanasc_par(const Data& d) {
  datanasc = d;
}

// Metodo che imposta il luogo di nascita con il valore passato
void Profilo::set_luogonasc(const string& _luogonasc) {
  luogonasc = _luogonasc;
}
