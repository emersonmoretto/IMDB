/*
 * Fonetica.cpp
 *
 *  Created on: 07/12/2010
 *      Author: root
 */
#include <string>
#include <vector>
#include <iostream>
#include <sys/time.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/resource.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"

using namespace std;

#define _MAX_CHAR 255



void trim2(string * str)
{
  string::size_type pos = str->find_last_not_of(' ');
  if(pos != string::npos) {
    str->erase(pos + 1);
    pos = str->find_first_not_of(' ');
    if(pos != string::npos)
    	str->erase(0, pos);
  }
  else
	  str->erase(str->begin(), str->end());
}

void removeMultiple(string &str) {

	// Retira do texto carateres que estao multiplicados:
	// ss -> s, sss -> s, rr -> r
	char * foncmp = new char[_MAX_CHAR];
	// matriz de caracteres que armazena o texto sem duplicatas
	char * fonaux = new char[_MAX_CHAR];
	// matriz de caracteres que armazena o texto original
	char * tip = new char[1]; // armazena o caracter anterior

	int i, j; // contadores
	j = 0;
	tip[0] = ' ';
	fonaux = (char *) str.c_str();

	// a matriz de caracteres recebe o string original
	for (i = 0; i < str.length(); i++) {

		// percorre o texto, caracter a caracter
		// elimina o caracter se ele for duplicata e
		// nao for numero, espaco ou S
		if ((fonaux[i] != tip[0]) || (fonaux[i] == ' ')
		|| ((fonaux[i] >= '0') && (fonaux[i] <= '9'))
		|| ((fonaux[i] == 'S') && (fonaux[i - 1] == 'S') &&
		((i > 1) && (fonaux[i - 2] != 'S')))) {
			foncmp[j] = fonaux[i];
			j++;
		}
		tip[0] = fonaux[i];
		// reajusta o caracter de comparacao
	}

	// o string recebe o texto sem duplicatas
	str.clear();
	str.append(foncmp);
	//trim2(str);
	//return str;
}// removeMultiple


void removeDuplicated(string &str){

	str.append(" ");
	string result = "                                              ";

	int j=0;
	for(int i=0 ; i < str.length()-1 ; i++){
		if(str.at(i) != str.at(i+1)){
			result.at(j) = str.at(i);
			j++;
		}
	}
	string::size_type pos = result.find_first_of(' ');
	if(pos>0)
		result = result.substr(0,pos);

	str = result;
}

string fonetizar(string str){

	// todos os caracteres duplicados sao eliminados
	// exemplo: SS -> S, RR -> R
	//removeMultiple(str);

	removeDuplicated(str);

	string retorno = "                                           ";

	str.append("       ");

	int j=0; //contador do retorno..

	for(int i=0 ; i < str.length() ; i++){
		if (str.at(i) == '_')
			str.at(i) = 'Y'; // _ -> Y
		else if (str.at(i) == '&')
			str.at(i) = 'i'; // & -> i
		else if ( str.at(i) == 'E' || str.at(i) == 'Y'  || str.at(i) == 'I')
			str.at(i) = 'i'; // E, Y, I -> i
		else if (str.at(i) == 'O' || str.at(i) == 'U')
			str.at(i) = 'o'; // O, U -> u
		else if (str.at(i) == 'A')
			str.at(i) = 'a'; // A -> a
	}

	for(int i=0 ; i < str.length() ; i++){

		int newmud = 0;
		int x = 0;

		switch (str.at(i)) {

			// se o caracter for a
			case 'a':

				// se a palavra termina com As, AZ, AM, ou AN,
				// elimina a consoante do final da palavra
				if ( str.at(i + 1) == 's' || str.at(i + 1) == 'Z' || str.at(i + 1) == 'M' || str.at(i + 1) == 'N'){
					if (str.at(i + 2) == ' '){
						retorno.at(j) = 'a';
						retorno.at(j + 1) = ' ';
						j+=2;
						i++;
						break;
					}
				}

				retorno.at(j) = 'a';
				j++;
				break;

			case 'B':
				retorno.at(j) = 'B';
				j++;
				break;
			case 'C': // se o caracter for C

				// ci vira si
				if (str.at(i + 1) == 'i') {
					retorno.at(j) = 's';
					j++;
					break;
				}// if

				// coes final vira cao
				if (str.at(i + 1) == 'o'
						&& str.at(i + 2) == 'i'
						&& str.at(i + 3) == 's'
						&& str.at(i + 4) == ' ') {

					retorno.at(j) = 'K';
					retorno.at(j + 1) = 'a';
					retorno.at(j + 2) = 'o';
					j += 3;
					i = i + 4;
					break;
				}

				// ct vira t
				if (str.at(i + 1) == 'T'){
					retorno.at(j) = 't';
					j++;
					break;
				}

				// ch vira k
				if (str.at(i + 1) != 'H') {

					retorno.at(j) = 'K';
					j++;
					newmud = 1;

					// ck vira k
					if (str.at(i + 1) == 'K') {
						retorno.at(j) = 'K';
						j++;
						i++;
						break;
					} else
						break;

				}// if

				// ch vira k para chi final, chi vogal, chini final (bachi -> bak)
				// e
				// chiti final
				// chi final ou chi vogal
				x = 0;
				if (str.at(i + 1) == 'H')
					if (str.at(i + 2) == 'i')
						if (str.at(i + 3) == 'a' || str.at(i + 3) == 'i' || str.at(i + 3) == 'o') {
							x = 1;
						// chini final
						}else{
							if (str.at(i + 3) == 'N')
								if (str.at(i + 4) == 'i')
									if (str.at(i + 5) == ' ')
										x = 1;
							}else{
								// chiti final
								if (str.at(i + 3) == 'T')
									if (str.at(i + 4) == 'i')
										if (str.at(i + 5) == ' ')
											x = 1;
							}

				if (x == 1) {
					retorno.at(j) = 'K';
					j++;
					i++;
					break;
				}

				// chi, nao sendo no final
				// chiti final
				// ch nao seguido de i
				// se anterior nao e s, ch = x
				if (j > 0){
					// sch: fonema recua uma posicao e vira X
					if (retorno.at(j - 1) == 's') {
						j--;
					}
				}
				retorno.at(j) = 'X';
				j++;
				newmud = 1;
				i++;

				break;

			case 'D':

				x = 0;

				// D final eh eliminado
				if (str.at(i + 1) == ' ')
					break;

				// procura por dor
				if (str.at(i + 1) != 'o'){
					retorno.at(j) = 'D';
					j++;
					break;

				}else if (str.at(i + 2) == 'R'){
					if (i != 0)
						x = 1; // dor nao inicial
					else{
						retorno.at(j) = 'D';
						j++;
					}
				}else{
					retorno.at(j) = 'D';
					j++;
				}

				if (x == 1){
					if (str.at(i + 3) == 'i'){
						if (str.at(i + 4) == 's'){ // dores
							if (str.at(i + 5) != ' '){
								x = 0; // nao e dores
							}
						}else{
							x = 0;
						}
					}else{

						if (str.at(i + 3) == 'a'){
							if (str.at(i + 4) != ' '){
								if (str.at(i + 4) != 's'){
									x = 0;
								}else{
									if (str.at(i + 5) != ' ')
										x = 0;
								}
							}
						}else{
							x = 0;
						}
					}
				}else{
					x = 0;

					if (x == 1){
//						retorno.at(j) = 'D';
//						retorno.at(j+1) = 'o';
//						retorno.at(j+2) = 'R';
//
//						i = i + 5;
					}else{
						retorno.at(j) = 'D';
						j++;
					}
				}

				break;

			case 'F':
				retorno.at(j) = 'F';
				j++;
				break;

			case 'G':

				// gui -> gi
				if (str.at(i + 1) == 'o'){ //lembrando.. todos os "U" viraram "O" la em cima
					if (str.at(i + 2) == 'i'){
						retorno.at(j) = 'G';
						retorno.at(j + 1) = 'i';
						j += 2;
						i += 2;

					// diferente de gui copia como consoante muda
					}else{
						retorno.at(j) = 'G';
						j++;
					}

				}else{
					// gl
					if (str.at(i + 1) == 'L'){
						if (str.at(i + 2) == 'i'){
							// gli + vogal -> li + vogal
							if (str.at(i + 3) == 'a' || str.at(i + 3) == 'i' || str.at(i + 3) == 'o'){
								retorno.at(j) = str.at(i + 1);
								retorno.at(j + 1) = str.at(i + 2);
								j += 2;
								i += 2;

							// glin -> lin
							}else{
								if (str.at(i + 3) == 'N'){
									retorno.at(j) = str.at(i + 1);
									retorno.at(j + 1) = str.at(i + 2);
									j += 2;
									i += 2;
								}else{
									retorno.at(j) = 'G';
									j++;
								}
							}
						}else{
							retorno.at(j) = 'G';
							j++;
						}
					}else{

						// gn + vogal -> ni + vogal
						if (str.at(i + 1) == 'N'){
							if ((str.at(i + 2) != 'a') && (str.at(i + 2) != 'i') && (str.at(i + 2) != 'o')){
								retorno.at(j) = 'G';
								j++;
							}else{
								retorno.at(j) = 'N';
								retorno.at(j + 1) = 'i';
								j += 2;
								i++;
							}

						}else{

						// ghi -> gi
							if (str.at(i + 1) == 'H'){
								if (str.at(i + 2) == 'i'){
									retorno.at(j) = 'G';
									retorno.at(j+1) = 'i';
									j += 2;
									i += 2;
								}else{
									retorno.at(j) = 'G';
									j++;
								}
							}else{
								retorno.at(j) = 'G';
								j++;
							}
						}
					}
				}
				break;

			case 'H':
				//desconsiderar o H
				break;

			case 'i': // se o caracter for i

				if (str.at(i + 2) == ' ') {
					// is ou iz final perde a consoante

					// emoretto tuning BEGIN - correcao JULI e JULIA
					if (str.at(i + 1) == 'a') {
						retorno.at(j) = 'i';
						j++;
						i++;
						break;
						// emoretto tuning END

					} else if (str.at(i + 1) == 's') {
						retorno.at(j) = 'i';
						j++;
						break;
					} else if (str.at(i + 1) == 'Z') {
						retorno.at(j) = 'i';
						j++;
						break;
					}
				}

				// ix
				if (str.at(i + 1) != 'X'){
					retorno.at(j) = 'i';
					j++;
				}else if (i != 0){
					retorno.at(j) = 'i';
					j++;
				}else{

					// ix vogal no inicio torna-se iz
					if (str.at(i + 2) == 'a' || str.at(i + 2) == 'i' || str.at(i + 2) == 'o') {
						retorno.at(j) = 'i';
						retorno.at(j + 1) = 'Z';
						j += 2;
						i++;
						break;

					}else{

						// ix consoante no inicio torna-se is
						if (str.at(i + 2) == 'C' || str.at(i + 2) == 's') {
							retorno.at(j) = 'i';
							j++;
							i++;
							break;
						}else{
							retorno.at(j) = 'i';
							retorno.at(j + 1) = 's';
							j += 2;
							i++;
							break;
						}
					}
				}
				break;

			case 'J':
				// J -> Gi
				retorno.at(j) = 'G';
				retorno.at(j + 1) = 'i';
				j += 2;
				break;
			case 'K':
				// KT -> T
				//if (str.at(i + 1) != 'T')
				retorno.at(j) = 'K';
				j++;
				break;

			case 'L':
				// L + vogal nao eh modificado
				if (str.at(i + 1) == 'a' || str.at(i + 1) == 'i' || str.at(i + 1) == 'o'){
					retorno.at(j) = 'L';
					j++;
				}else{
					// L + consoante -> U + consoante
					if (str.at(i + 1) != 'H'){
						retorno.at(j) = 'o';
						j++;
						break;

					// LH + consoante nao eh modificado
					}else{
						if (str.at(i + 2) != 'a' && str.at(i + 2) != 'i' && str.at(i + 2) != 'o'){
							retorno.at(j) = 'L';
							j++;

						// LH + vogal -> LI + vogal
						}else{
							retorno.at(j) = 'L';
							retorno.at(j+1) = 'i';
							j += 2;
							i++;
							break;
						}
					}
				}
				break;
			case 'M':
					// M + consoante -> N + consoante
					// M final -> N
					// M + vogal -> N + vogal
					if (str.at(i + 1) != 'a' && str.at(i + 1) != 'i' && str.at(i + 1) != 'o' || str.at(i + 1) == ' '){
						retorno.at(j) = 'N';
						j++;
					// M nao eh alterado
					}else{
						retorno.at(j) = 'M';
						j++;
					}

					break;

			case 'N': // se o caracter for N

					// NH + consoante nao eh modificado
					if (str.at(i + 1) == 'H'){
						if (str.at(i + 2) != 'a' && str.at(i + 2) != 'i' && str.at(i + 2) != 'o'){
							retorno.at(j) = 'N';
							j++;

						// NH + vogal -> Ni + vogal
						}else{
							retorno.at(j) = 'N';
							retorno.at(j + 1) = 'i';
							j+=2;
							i++;
						}
					}else{ //se for um N a toa
						retorno.at(j) = 'N';
						j++;
					}

					break;

			case 'o':
				// oS final -> o
				// oZ final -> o
				if ( (str.at(i + 1) == 's' || str.at(i + 1) == 'Z') && str.at(i + 2) == ' '){
					i++;
				}

				retorno.at(j) = 'o';
				j++;

				break;

			case 'P': // se o caracter for P

				// PH -> F
				if (str.at(i + 1) == 'H'){
					retorno.at(j) = 'F';
					j++;
					i++;
					newmud = 1;
				}else{
					retorno.at(j) = 'P';
					j++;
				}

				break;

			case 'Q': // se o caracter for Q

				// Koi -> Ki (QUE, QUI -> KE, KI)
				if (str.at(i + 1) == 'o')
					if (str.at(i + 2) == 'i'){
						retorno.at(j) = 'K';
						j++;
						i++;
						break;
					}
				// QoA -> KoA (QUA -> KUA)
				retorno.at(j) = 'K';
				j++;
				break;

			case 'R':
				// R nao eh modificado
				retorno.at(j) = 'R';
				j++;
				break;

			case 's':

					// s final eh ignorado
					if (str.at(i + 1) == ' ')
						break;

					// S + vogal nao eh modificado
					if (str.at(i + 1) == 'a' || str.at(i + 1) == 'i' || str.at(i + 1) == 'o'){

						if (i == 0){
							retorno.at(j) = 's';
							j++;
							break;
							// s entre duas vogais -> s
						}else if (str.at(i - 1) == 'a' || str.at(i - 1) == 'i' || str.at(i - 1) == 'o'){
							//fonwrk[j] = 'Z';
							//j++;
							//i++;
							retorno.at(j) = 's';
							j++;
							break;

						}else{

							// SoL nao eh modificado
							if (str.at(i + 1) == 'o' && str.at(i + 2) == 'L' && str.at(i + 3) == ' '){
								retorno.at(j) = 's';
								j++;
								break;
							}else{
								retorno.at(j) = 'Z';
								j++;
								break;

							}
						}
					}

					// ss -> s
//					if (str.at(i + 1) == 's')
//						if (str.at(i + 2) != ' '){
//							retorno.at(j) = 's';
//							j++;
//							i++;
//							break;
//						}else{
//							//str.at(i + 1) = ' ';
//							break;
//						}

					// s inicial seguido de consoante fica precedido de i
					// se nao for sci, sh ou sch nao seguido de vogal

					if (i == 0)
						if (!(str.at(i + 1) == 'C' && str.at(i + 2) == 'i'))
							if (str.at(i + 1) != 'H')
								if (!(str.at(i + 1) == 'C' && str.at(i + 2) == 'H' && str.at(i + 3) != 'a' && str.at(i + 3) != 'i' && str.at(i + 3) != 'o')){
									retorno.at(j) = 'i';
									j++;
									retorno.at(j) = 's';
									j++;
									break;
								}// if

					// sH -> X;
					if (str.at(i + 1) == 'H'){
						retorno.at(j) = 'X';
						j++;
						i++;
						newmud = 1;
						break;
					}// if

					if (str.at(i + 1) != 'C'){
						retorno.at(j) = 's';
						j++;
						break;
					}// if

					// sCh nao seguido de i torna-se X
					if (str.at(i + 2) == 'H'){
						retorno.at(j) = 'X';
						j++;
						i += 2;
						newmud = 1;
						break;
					}// if

					if (str.at(i + 2) != 'i'){
						retorno.at(j) = 's';
						j++;
						break;
					}// if


					// sCi final -> Xi
					if (str.at(i + 3) == ' '){
						retorno.at(j) = 'X';
						j++;
						retorno.at(j + 1) = 'i';
						j+=2;
						i = i + 3;
						break;

					}

					// sCi vogal -> X
					if (str.at(i + 3) == 'a' || str.at(i + 3) == 'i' || str.at(i + 3) == 'o'){
						retorno.at(j) = 'X';
						j+=2;
						i += 2;
						break;
					}

					// sCi consoante -> si
					retorno.at(j) = '2';
					retorno.at(j + 1) = 'i';
					j += 2;
					i += 2;
					break;


			case 'T': // se o caracter for T
				// T final eh eliminado
				if (str.at(i + 1) == ' ')
					break;

				// TS -> S
				if (str.at(i + 1) == 's'){
					break;

				// TZ -> Z
				}else{
					if (str.at(i + 1) == 'Z')
						break;
					else{
						retorno.at(j) = 'T';
						j++;
					}
				}

				break;
			case 'V':

			case 'W': // ou se o caracter for W

				// V,W inicial + vogal -> o + vogal (U + vogal)
				if (str.at(i + 1) == 'a' || str.at(i + 1) == 'i' || str.at(i + 1) == 'o'){
					if (i == 0){
						retorno.at(j) = 'o';
						j++;

					// V,W NAO inicial + vogal -> V + vogal
					}else{
						retorno.at(j) = 'V';
						j++;
						newmud = 1;
					}
				}else{
					retorno.at(j) = 'V';
					j++;
					newmud = 1;
				}

				break;

			case 'X':
				retorno.at(j) = 'X';
				j++;
				break;

			case 'Y':
				// Y jah foi tratado acima
				break;

			case 'Z': // se o caracter for Z

				// Z final eh eliminado
				if (str.at(i + 1) == ' ')
					break;

				// Z + vogal -> S
				if (str.at(i + 1) == 'a' || str.at(i + 1) == 'i' || str.at(i + 1) == 'o'){
					retorno.at(j) = 's';
					j++;

				// Z + consoante -> S + consoante
				}else{
					retorno.at(j) = 's';
					j++;
				}// else

				break;

			default: // se o caracter nao for um dos jah relacionados
				// o caracter nao eh modificado
				retorno.at(j) = str.at(i);
				j++;
				break;
		}//switch


		//Parece que eh quando for final mudo
		if (newmud == 1){
			int k = 0;
			while (k == 0){
				// e final mudo
				if (str.at(i + 1) == ' '){
					retorno.at(j) = 'i';
					k = 1;
				}else if (str.at(i + 1) == 'a' || str.at(i + 1) == 'i' || str.at(i + 1) == 'o'){
					k = 1;
				}else if (j > 1 && retorno.at(j - 1) == 'X'){
					retorno.at(j) = 'i';
					j++;
					k = 1;
				}else if (str.at(i + 1) == 'R'){
					k = 1;
				}else if (str.at(i + 1) == 'L'){
					k = 1;
				}else if (str.at(i + 1) != 'H'){
					retorno.at(j) = 'i';
					j++;
					k = 1;
				}else{
					i++;
				}
			}
		}
	}

	for(int i=0 ; i < retorno.length() ; i++){
		// percorre toda a palavra, letra a letra
		// i -> I
		if (retorno.at(i) == 'i')
			retorno.at(i) = 'I';
		else
		// a -> A
		if (retorno.at(i) == 'a')
			retorno.at(i) = 'A';
		else

		// o -> U
		if (retorno.at(i) == 'o')
			retorno.at(i) = 'U';
		else
		// s -> S
		if (retorno.at(i) == 's')
			retorno.at(i) = 'S';
		else
		// E -> b
		if (retorno.at(i) == 'E')
			retorno.at(i) = ' ';
		else
		// Y -> _
		if (retorno.at(i) == 'Y')
			retorno.at(i) = '_';
	}

	removeDuplicated(retorno);

	return retorno;
}



int main22(int argc, char * argv[]){

	struct rusage start, end;

	getrusage(RUSAGE_SELF, &start);

	for(int i=0; i< 1 ; i++){
		string a = "AANDRESS";
		removeDuplicated(a);
		cout << a << endl;


		cout << fonetizar("ALFRED XAVES") << endl;

		cout << fonetizar("CINTIA FEREIRA") << endl;
		cout << fonetizar("CYNTIA FEREIRA") << endl;
		cout << fonetizar("SYNTHYA FERREIRA") << endl;

		cout << "[Result]" +fonetizar("GUILHERME ALVIRO") << endl;
		cout << "[Result]" +fonetizar("GOILHERME ALVES") << endl;

		cout << "[Result]" +fonetizar("PAULO ALVIRO") << endl;
		cout << "[Result]" +fonetizar("SAULO ALVES") << endl;

		cout << "[Result]" +fonetizar("JOSE SOUZA") << endl;
		cout << "[Result]" +fonetizar("JUZE SOUZA") << endl;
		cout << "[Result]" +fonetizar("JESSE SOUSA") << endl;

		cout << fonetizar("WALESKA SOUZA") << endl;
		cout << fonetizar("VALESCA SOUSA") << endl;

		cout << fonetizar("CLEBER LIMA") << endl;
		cout << fonetizar("KLEBER LIRA") << endl;

		cout << fonetizar("LIANDRO MORAIS") << endl;
		cout << fonetizar("LEANDRO MORAES") << endl;

		cout << fonetizar("JULIANO CAMOES") << endl;
		cout << fonetizar("GIULIANO CAMOES") << endl;

		cout << fonetizar("JULLYE CAMOES") << endl;
		cout << fonetizar("JULIA CAMOES") << endl;

		cout << fonetizar("ANDREZA ALVES") << endl;
		cout << fonetizar("ANDRESSA GALVES") << endl;

		cout << fonetizar("ANDREA AUMEIDA") << endl;
		cout << fonetizar("ANDREIA ALMEIDA") << endl;

		cout << fonetizar("PAULA AUMEIDA") << endl;
		cout << fonetizar("PAULINA ALMEIDA") << endl;

		cout << fonetizar("RONALDO AUMEIDA") << endl;
		cout << fonetizar("REINALDO ALMEIDA") << endl;


		cout << fonetizar("ALFREDO CHAVES") << endl;

		cout << fonetizar("davi XAVES") << endl;
		cout << fonetizar("DAVId XAVES") << endl;
		cout << fonetizar("DEIVID CHAVES") << endl;

		cout << fonetizar("CAIQUE MORREIRA") << endl;
		cout << fonetizar("KAIQUE MOREIRA") << endl;

	}
	getrusage(RUSAGE_SELF, &end);


	return 0;

}




/*
string removePrep(string str) {

	int i, j;

	Vector palavra = new Vector();

	palavra = strToVector(str);

	String prep[] = { "DEL", "DA", "DE", "DI", "DO", "DU", "DAS", "DOS",
			"DEU", "DER", "E", "LA", "LE", "LES", "LOS", "VAN", "VON", "EL" };

	for (i = 0; i < palavra.size(); i++) {

		for (j = 0; j < prep.length; j++) {

			if (palavra.elementAt(i).toString().compareTo(prep[j]) == 0) {

				palavra.removeElementAt(i);

				i--;

			}

		}

	}

	return vectorToStr(palavra);

}


string removeAccentuation(string str) {

	// Substitui os caracteres acentuados por caracteres nao acentuados

	char * aux = new char[256];

	// matriz de caracteres onde o texto eh manipulado

	int i; // contador

	aux = str.toCharArray();

	// matriz recebe o texto

	for (i = 0; i < str.length(); i++) {

		// percorre o texto, caracter a caracter

		switch (aux[i])

		{
		case 'É':

			aux[i] = 'E'; // É -> E

			break;

		case 'Ê':

			aux[i] = 'E'; // Ê -> E

			break;

		case 'Ë':

			aux[i] = 'E'; // Ë -> E

			break;

		case 'Á':

			aux[i] = 'A'; // Á -> A

			break;

		case 'À':

			aux[i] = 'A'; // À -> A

			break;

		case 'Â':

			aux[i] = 'A'; // Â -> A

			break;

		case 'Ã':

			aux[i] = 'A'; // Ã -> A

			break;

		case 'Ä':

			aux[i] = 'A'; // Ä -> A

			break;

		case 'Ç':

			aux[i] = 'C'; // Ç -> C

			break;

		case 'Í':

			aux[i] = 'I'; // Í -> I

			break;

		case 'Ó':

			aux[i] = 'O'; // Ó -> O

			break;

		case 'Õ':

			aux[i] = 'O'; // Õ -> O

			break;

		case 'Ô':

			aux[i] = 'O'; // Ô -> O

			break;

		case 'Ö':

			aux[i] = 'O'; // Ö -> O

			break;

		case 'Ú':

			aux[i] = 'U'; // Ú -> U

			break;

		case 'Ü':

			aux[i] = 'U'; // Ü -> U

			break;

		case 'Ñ':

			aux[i] = 'N'; // Ñ -> N

			break;

		}

	}

	str = str.copyValueOf(aux).trim();

	// o string recebe o texto sem acentuacao

	return str;

}// removeAccentuation

string removeStrange(string str) {

	// Elimina os caracteres que NAO sejam alfanumericos ou espacos

	char * foncmp = new char[256];

	// matriz de caracteres que armazena o texto original

	char * fonaux = new char[256];

	// matriz de caracteres que armazena o texto modificado

	int i, j, // contadores

	first; // indica se exitem espacos em branco antes do primeiro

	// caracter: se 1 -> existem, se 0 -> nao existem

	j = 0;

	first = 1;

	fonaux = str.toCharArray();

	// matriz de caracteres recebe o texto

	for (i = 0; i < 256; i++)

		foncmp[i] = ' ';

	// branqueia a matriz de caracteres

	for (i = 0; i < str.length(); i++) {

		// percorre o texto, caracter a caracter

		// elimina os caracteres que nao forem alfanumericos ou espacos

		if (((fonaux[i] >= 'A') &&

		(fonaux[i] <= 'Z')) ||

		((fonaux[i] >= 'a') &&

		(fonaux[i] <= 'z')) ||

		((fonaux[i] >= '0') &&

		(fonaux[i] <= '9')) ||

		(fonaux[i] == '&') ||

		(fonaux[i] == '_') ||

		((fonaux[i] == ' ') && first == 0)) {

			foncmp[j] = fonaux[i];

			j++;

			first = 0;

		}// if

	}// for

	str = str.valueOf(foncmp);

	// string recebe o texto da matriz de caracteres

	return str.trim();

}// removeStrange

Vector strToVector(string str) {

	// armazena o texto de um string em um vetor onde

	// cada palavra do texto ocupa uma posicao do vetor

	str = str.trim();

	char[] fonaux = new char[256];

	// matriz de caracteres que armazena o texto completo

	char[] foncmp = new char[256];

	// matriz de caracteres que armazena cada palavra

	Vector component = new Vector();

	// vetor que armazena o texto

	String aux = new String();

	int i, j, // contadores

	pos, // posicao da matriz

	rep, // indica se eh espaco em branco repetido

	first; // indica se eh o primeiro caracter

	first = 1;

	pos = 0;

	rep = 0;

	fonaux = str.toCharArray();

	// matriz de caracteres recebe o texto

	for (j = 0; j < 256; j++)

		foncmp[j] = ' ';

	// branqueia matriz de caracteres

	for (i = 0; i < str.length(); i++) {

		// percorre o texto, caracter a caracter

		// se encontrar um espaco e nao for o primeiro caracter,

		// armazena a palavra no vetor

		if ((fonaux[i] == ' ') && (first != 1)) {

			if (rep == 0) {

				component.addElement(aux.copyValueOf(foncmp).trim());

				pos = 0;

				rep = 1;

				for (j = 0; j < 256; j++)

					foncmp[j] = ' ';

			}// if

		}// if

		// forma a palavra, letra a letra, antes de envia-la a uma

		// posicao do vetor

		else {

			foncmp[pos] = fonaux[i];

			first = 0;

			pos++;

			rep = 0;

		}// else

	}// for

	if (foncmp[0] != ' ')

		component.addElement(aux.copyValueOf(foncmp).trim());

	return component;


}
*/
