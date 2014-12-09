#include <cstdlib>
#include <iostream>
#include <string.h>
#include "profilo.h"

using namespace std;

Profilo::Profilo(){
         sesso="non dichiarato";
         professione= "non dichiarata";
         situasent= "non dichiarata"; 
         luogonasc= "non dichiarato";                                        
}

Profilo::Profilo(stringa _sex, string _prof, string _situa, string _luogo){
                       sesso= _sex;
                       professione= _prof;
                       situasent= _situa; 
                       luogonasc= _luogo;                      
}

string Profilo::get_sesso() {
    return sesso;
}

string Profilo::get_professione() {
    return professione;
}

string Profilo::get_situasent() {
    return situasent;
}

Data Profilo::get_datanasc() {
    return datanasc;
}

string Profilo::get_luogonasc() {
    return luogonasc;
}

void Profilo::set_sesso(const string& _sesso) {
    sesso = _sesso;
}

void Profilo::set_professione(const string& _professione) {
    professione = _professione;
}

void Profilo::set_situasent(const string& _situasent) {
    situasent = _situasent;
}

void Profilo::set_datanasc() {
    Data d;
    d.imposta_data();
    datanasc = d;
}

void Profilo::set_luogonasc(const string& _luogonasc) {
    luogonasc = _luogonasc;
}
