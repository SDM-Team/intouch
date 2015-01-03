#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>		/* string							*/

// Definizione variabili globali
#define MAXPOST 250
#define MAXTITLE 30
#define MAXLUN 25

using namespace std;

// Variabili globali relative a nomi e path dei file di testo
extern string path_files;
extern string path_files_u;
extern string path_files_p;

extern string nome_file_utenti;
extern string nome_file_post;
extern string nome_file_commenti;
extern string nome_file_likes;
extern string nome_file_amicizie;
extern string nome_file_profilo;

#endif
