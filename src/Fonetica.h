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


#ifndef FONETICANOVO_H_
#define FONETICANOVO_H_


class Fonetica {

public:

	Fonetica();
	virtual ~Fonetica();

	static void trim2(string * str)
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

	static void removeMultiple(string &str) {

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



	static string fonetizar(string str){

			char * foncmp = (char*) malloc(_MAX_CHAR);

			char * fonwrk = (char*) malloc(_MAX_CHAR);

			char * fonaux = (char*) malloc(_MAX_CHAR);

			char * fonfon = (char*) malloc(_MAX_CHAR);

			int i, j, x, k, // contadores
			desloc, // posicao atual no vetor
			endfon, // indica se eh ultimo fonema
			copfon, // indica se o fonema deve ser copiado
			copmud, newmud; // indica se o fonema eh mudo

			// Vetor utilizado para armazenar o texto:
			// cada palavra do texto e armazenada em uma posicao do vetor

			//Vector component = new Vector();
			vector<string> component;

			string result = "";
			string retorno = "";
			i = 0;
			j = 0;// zera os contadores

			// todos os caracteres duplicados sao eliminados
			// exemplo: SS -> S, RR -> R
			//removeMultiple(str);

			//component = strToVector(str);
			Util::StringSplit(str, " ",&component);

			// o texto eh armazenado no vetor:
			// cada palavra ocupa uma posicao do vetor
			for (desloc = 0; desloc < component.size() ; desloc++) {

				//cout << "iniciando.." << component[desloc] << endl;
				// percorre o vetor, palavra a palavra
				for (i = 0; i < _MAX_CHAR; i++) {
					fonwrk[i] = ' ';
					fonfon[i] = ' ';// branqueia as matrizes
					foncmp[i] = ' ';
					fonaux[i] = ' ';
				}// for

				foncmp = (char *) component.at(desloc).c_str();//.toCharArray();
				fonaux = foncmp;

				// matrizes recebem os caracteres da palavra atual
				j = 0;
				if (component.at(desloc).length() == 1) {

					fonwrk[0] = foncmp[0];

					// se o caracter for "E", "&" ou "I", troca por "i"
					if ((foncmp[0] == 'E') || (foncmp[0] == '&') || (foncmp[0] == 'I')) {
						fonwrk[0] = 'i';
					}

				}else {

					// percorre a palavra corrente, caracter a caracter
					for (i = 0; i < component.at(desloc).length(); i++){

						if (foncmp[i] == '_')
							fonfon[i] = 'Y'; // _ -> Y
						else if (foncmp[i] == '&')
							fonfon[i] = 'i'; // & -> i
						else if ((foncmp[i] == 'E') || (foncmp[i] == 'Y') || (foncmp[i] == 'I'))
							fonfon[i] = 'i'; // E, Y, I -> i
						else if ((foncmp[i] == 'O') || (foncmp[i] == 'U'))
							fonfon[i] = 'o'; // O, U -> u
						else if (foncmp[i] == 'A')
							fonfon[i] = 'a'; // A -> a
						else{

							if (foncmp[i] == 'S')
								fonfon[i] = 's'; // S -> s
							else
								fonfon[i] = foncmp[i];
						}

					}

					// caracter nao eh modificado
					endfon = 0;
					fonaux = fonfon;

					// palavras formadas por apenas 3 consoantes
					// sao dispensadas do processo de fonetizacao

					if (fonaux[3] == ' ')
						if ((fonaux[0] == 'a') || (fonaux[0] == 'i') || (fonaux[0] == 'o'))
							endfon = 0;
						else{
							if ((fonaux[1] == 'a') || (fonaux[1] == 'i') || (fonaux[1] == 'o'))
								endfon = 0;
							else{

								if ((fonaux[2] == 'a') || (fonaux[2] == 'i') || (fonaux[2] == 'o'))
									endfon = 0;
								else {
									endfon = 1;
									fonwrk[0] = fonaux[0];
									fonwrk[1] = fonaux[1];
									fonwrk[2] = fonaux[2];
								}
							}
						}

					if (endfon != 1) { // se a palavra nao for formada por apenas 3
										// consoantes...

						for (i = 0; i < component.at(desloc).length(); i++) {

							// percorre a palavra corrente, letra a letra
							copfon = 0;
							copmud = 0;
							newmud = 0;

							// zera variaveis de controle
							switch (fonaux[i]) {

							// se o caracter for a
							case 'a':

								// se a palavra termina com As, AZ, AM, ou AN,
								// elimina a consoante do final da palavra

								if ((fonaux[i + 1] == 's') || (fonaux[i + 1] == 'Z') || (fonaux[i + 1] == 'M') || (fonaux[i + 1] == 'N')){
									if (fonaux[i + 2] != ' ')
										copfon = 1;
									else {
										fonwrk[j] = 'a';
										fonwrk[j + 1] = ' ';
										j++;
										i++;
									}
								}else
									copfon = 1;

								break;

							case 'B':
								// B nao eh modificado
								copmud = 1;
								break;

							case 'C': // se o caracter for C
								x = 0;

								// ci vira si
								if (fonaux[i + 1] == 'i') {
									fonwrk[j] = 's';
									j++;
									break;
								}// if

								// coes final vira cao
								if ((fonaux[i + 1] == 'o')
										&& (fonaux[i + 2] == 'i')
										&& (fonaux[i + 3] == 's')
										&& (fonaux[i + 4] == ' ')) {

									fonwrk[j] = 'K';
									fonwrk[j + 1] = 'a';
									fonwrk[j + 2] = 'o';
									i = i + 4;
									break;
								}

								// ct vira t
								if (fonaux[i + 1] == 'T')
									break;

								// ch vira k
								if (fonaux[i + 1] != 'H') {

									fonwrk[j] = 'K';
									newmud = 1;

									// ck vira k
									if (fonaux[i + 1] == 'K') {
										i++;
										break;
									} else
										break;

								}// if

								// ch vira k para chi final, chi vogal, chini final
								// e
								// chiti final
								// chi final ou chi vogal

								if (fonaux[i + 1] == 'H')
									if (fonaux[i + 2] == 'i')
										if ((fonaux[i + 3] == 'a') || (fonaux[i + 3] == 'i') || (fonaux[i + 3] == 'o')) {
											x = 1;
										// chini final
										}else{
											if (fonaux[i + 3] == 'N')
												if (fonaux[i + 4] == 'i')
													if (fonaux[i + 5] == ' ')
														x = 1;
											}else{
												// chiti final
												if (fonaux[i + 3] == 'T')
													if (fonaux[i + 4] == 'i')
														if (fonaux[i + 5] == ' ')
															x = 1;
											}

								if (x == 1) {
									fonwrk[j] = 'K';
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
									if (fonwrk[j - 1] == 's') {
										j--;
									}
								}

								fonwrk[j] = 'X';
								newmud = 1;
								i++;

								break;

							case 'D':

								x = 0;

								// D final eh eliminado
								if (fonaux[i + 1] == ' ')
									break;

								// procura por dor
								if (fonaux[i + 1] != 'o'){
									copmud = 1;
									break;

								}else if (fonaux[i + 2] == 'R'){
									if (i != 0)
										x = 1; // dor nao inicial
									else
										copfon = 1; // dor inicial
								}else
									copfon = 1; // nao e dor

								if (x == 1){
									if (fonaux[i + 3] == 'i'){
										if (fonaux[i + 4] == 's'){ // dores
											if (fonaux[i + 5] != ' '){
												x = 0; // nao e dores
											}
										}else{
											x = 0;
										}
									}else{

										if (fonaux[i + 3] == 'a'){
											if (fonaux[i + 4] != ' '){
												if (fonaux[i + 4] != 's'){
													x = 0;
												}else{
													if (fonaux[i + 5] != ' ')
														x = 0;
												}
											}
										}else{
											x = 0;
										}
									}
								}else
									x = 0;



								if (x == 1){
									fonwrk[j] = 'D';
									fonwrk[j + 1] = 'o';
									fonwrk[j + 2] = 'R';
									i = i + 5;
								}else
									copfon = 1;

								break;

							case 'F':
								// F nao eh modificado
								copmud = 1;
								break;

							case 'G':

								// gui -> gi
								if (fonaux[i + 1] == 'o'){ //lembrando.. todos os "U" viraram "O" la em cima
									if (fonaux[i + 2] == 'i'){
										fonwrk[j] = 'G';
										fonwrk[j + 1] = 'i';
										j += 2;
										i += 2;

									// diferente de gui copia como consoante muda
									}else{
										copmud = 1;
									}

								}else{
									// gl
									if (fonaux[i + 1] == 'L'){
										if (fonaux[i + 2] == 'i'){
											// gli + vogal -> li + vogal
											if ((fonaux[i + 3] == 'a') || (fonaux[i + 3] == 'i') || (fonaux[i + 3] == 'o')){
												fonwrk[j] = fonaux[i + 1];
												fonwrk[j + 1] = fonaux[i + 2];
												j += 2;
												i += 2;

											// glin -> lin
											}else{
												if (fonaux[i + 3] == 'N'){
													fonwrk[j] = fonaux[i + 1];
													fonwrk[j + 1] = fonaux[i + 2];
													j += 2;
													i += 2;
												}else{
													copmud = 1;
												}
											}
										}else{
											copmud = 1;
										}
									}else{

										// gn + vogal -> ni + vogal
										if (fonaux[i + 1] == 'N'){
											if ((fonaux[i + 2] != 'a') && (fonaux[i + 2] != 'i') && (fonaux[i + 2] != 'o')){
												copmud = 1;
											}else{
												fonwrk[j] = 'N';
												fonwrk[j + 1] = 'i';
												j += 2;
												i++;
											}

										}else{

										// ghi -> gi
											if (fonaux[i + 1] == 'H'){
												if (fonaux[i + 2] == 'i'){
													fonwrk[j] = 'G';
													fonwrk[j + 1] = 'i';
													j += 2;
													i += 2;
												}else{
													copmud = 1;
												}
											}else{
												copmud = 1;
											}
										}
									}
								}
								break;

							case 'H':

								// H eh desconsiderado
								break;

							case 'i': // se o caracter for i

								if (fonaux[i + 2] == ' ') {
									// is ou iz final perde a consoante

									// emoretto tuning BEGIN - correcao JULI e JULIA
									if (fonaux[i + 1] == 'a') {
										fonwrk[j] = 'i';
										i++;
										break;
										// emoretto tuning END

									} else if (fonaux[i + 1] == 's') {
										fonwrk[j] = 'i';
										break;
									} else if (fonaux[i + 1] == 'Z') {
										fonwrk[j] = 'i';
										break;
									}
								}

								// ix
								if (fonaux[i + 1] != 'X')
									copfon = 1;
								else if (i != 0)
									copfon = 1;
								else

								// ix vogal no inicio torna-se iz
								if ((fonaux[i + 2] == 'a') || (fonaux[i + 2] == 'i') || (fonaux[i + 2] == 'o')) {
									fonwrk[j] = 'i';
									fonwrk[j + 1] = 'Z';
									j += 2;
									i++;
									break;

								}else{

									// ix consoante no inicio torna-se is
									if (fonaux[i + 2] == 'C' || fonaux[i + 2] == 's') {
										fonwrk[j] = 'i';
										j++;
										i++;
										break;
									}else{
										fonwrk[j] = 'i';
										fonwrk[j + 1] = 's';
										j += 2;
										i++;
										break;
									}
								}

								break;

							case 'J': // se o caracter for J

								// J -> Gi
								fonwrk[j] = 'G';
								fonwrk[j + 1] = 'i';
								j += 2;
								break;

							case 'K': // se o caracter for K

								// KT -> T
								if (fonaux[i + 1] != 'T')
									copmud = 1;
								break;

							case 'L': // se o caracter for L

								// L + vogal nao eh modificado
								if ((fonaux[i + 1] == 'a') || (fonaux[i + 1] == 'i') || (fonaux[i + 1] == 'o'))
									copfon = 1;
								else

									// L + consoante -> U + consoante
								if (fonaux[i + 1] != 'H'){
									fonwrk[j] = 'o';
									j++;
									break;

								// LH + consoante nao eh modificado
								}else{

									if (fonaux[i + 2] != 'a' && fonaux[i + 2] != 'i' && fonaux[i + 2] != 'o'){
										copfon = 1;

									// LH + vogal -> LI + vogal
									}else{
										fonwrk[j] = 'L';
										fonwrk[j + 1] = 'i';
										j += 2;
										i++;
										break;
									}
								}

								break;

							case 'M':
								// M + consoante -> N + consoante
								// M final -> N
								// M + vogal -> N + vogal
								if ((fonaux[i + 1] != 'a' && fonaux[i + 1] != 'i' && fonaux[i + 1] != 'o') || (fonaux[i + 1] == ' ')){
									fonwrk[j] = 'N';
									j++;

								// M nao eh alterado
								}else
									copfon = 1;

								break;

							case 'N': // se o caracter for N

								// NGT -> NT
								if ((fonaux[i + 1] == 'G') && (fonaux[i + 2] == 'T')){
									fonaux[i + 1] = 'N';
									copfon = 1;

									// NH + consoante nao eh modificado
								}else if (fonaux[i + 1] == 'H'){
									if ((fonaux[i + 2] != 'a') && (fonaux[i + 2] != 'i') && (fonaux[i + 2] != 'o')){
										copfon = 1;

									// NH + vogal -> Ni + vogal
									}else{
										fonwrk[j] = 'N';
										fonwrk[j + 1] = 'i';
										j += 2;
										i++;
									}
								}else{
									copfon = 1;
								}

								break;

							case 'o':

								// oS final -> o
								// oZ final -> o
								if ((fonaux[i + 1] == 's' || fonaux[i + 1] == 'Z') && fonaux[i + 2] == ' '){
										fonwrk[j] = 'o';
										break;
								}else{
									copfon = 1;
								}

								break;

							case 'P': // se o caracter for P

								// PH -> F
								if (fonaux[i + 1] == 'H'){
									fonwrk[j] = 'F';
									i++;
									newmud = 1;
								}else
									copmud = 1;

								break;

							case 'Q': // se o caracter for Q

								// Koi -> Ki (QUE, QUI -> KE, KI)
								if (fonaux[i + 1] == 'o')
									if (fonaux[i + 2] == 'i'){
										fonwrk[j] = 'K';
										j++;
										i++;
										break;
									}
								// QoA -> KoA (QUA -> KUA)
								fonwrk[j] = 'K';
								j++;
								break;

							case 'R':

								// R nao eh modificado
								copfon = 1;
								break;

							case 's':

								// s final eh ignorado
								if (fonaux[i + 1] == ' ')
									break;

								// S + vogal nao eh modificado
								if ((fonaux[i + 1] == 'a') || (fonaux[i + 1] == 'i') || (fonaux[i + 1] == 'o')){

									if (i == 0){
										copfon = 1;
										break;
										// s entre duas vogais -> s
									}else if ((fonaux[i - 1] == 'a') || (fonaux[i - 1] == 'i') || (fonaux[i - 1] == 'o')){
										//fonwrk[j] = 'Z';
										//j++;
										//i++;
										copfon = 1;
										break;

									}else{

										// SoL nao eh modificado
										if ((fonaux[i + 1] == 'o') && (fonaux[i + 2] == 'L') && (fonaux[i + 3] == ' ')){
											copfon = 1;
											break;
										}else{
											fonwrk[j] = 'Z';
											j++;
											break;

										}
									}
								}

								// ss -> s
								if (fonaux[i + 1] == 's')
									if (fonaux[i + 2] != ' '){
										copfon = 1;
										i++;
										break;
									}else{
										fonaux[i + 1] = ' ';
										break;
									}

								// s inicial seguido de consoante fica precedido de
								// i

								// se nao for sci, sh ou sch nao seguido de vogal

								if (i == 0)
									if (!((fonaux[i + 1] == 'C') && (fonaux[i + 2] == 'i')))
										if (fonaux[i + 1] != 'H')
											if (!((fonaux[i + 1] == 'C') && (fonaux[i + 2] == 'H') && ((fonaux[i + 3] != 'a') && (fonaux[i + 3] != 'i') && (fonaux[i + 3] != 'o')))){
												fonwrk[j] = 'i';
												j++;
												copfon = 1;
												break;
											}// if

								// sH -> X;
								if (fonaux[i + 1] == 'H'){
									fonwrk[j] = 'X';
									i++;
									newmud = 1;
									break;
								}// if

								if (fonaux[i + 1] != 'C'){
									copfon = 1;
									break;
								}// if

								// sCh nao seguido de i torna-se X
								if (fonaux[i + 2] == 'H'){
									fonwrk[j] = 'X';
									i += 2;
									newmud = 1;
									break;
								}// if

								if (fonaux[i + 2] != 'i'){
									copfon = 1;
									break;
								}// if


								// sCi final -> Xi
								if (fonaux[i + 3] == ' '){
									fonwrk[j] = 'X';
									fonwrk[j + 1] = 'i';
									i = i + 3;
									break;

								}

								// sCi vogal -> X
								if ((fonaux[i + 3] == 'a') || (fonaux[i + 3] == 'i') || (fonaux[i + 3] == 'o')){
									fonwrk[j] = 'X';
									j++;
									i += 2;
									break;
								}

								// sCi consoante -> si
								fonwrk[j] = 's';
								fonwrk[j + 1] = 'i';
								j += 2;
								i += 2;
								break;

							case 'T': // se o caracter for T


								// T final eh eliminado
								if (fonaux[i + 1] == ' ')
									break;

								// TS -> S
								if (fonaux[i + 1] == 's'){
									break;

								// TZ -> Z
								}else{
									if (fonaux[i + 1] == 'Z')
										break;
									else
										copmud = 1;
								}

								break;

							case 'V': // se o caracter for V

							case 'W': // ou se o caracter for W

								// V,W inicial + vogal -> o + vogal (U + vogal)
								if (fonaux[i + 1] == 'a' || fonaux[i + 1] == 'i' || fonaux[i + 1] == 'o'){
									if (i == 0){
										fonwrk[j] = 'o';
										j++;

									// V,W NAO inicial + vogal -> V + vogal
									}else{
										fonwrk[j] = 'V';
										newmud = 1;
									}
								}else{
									fonwrk[j] = 'V';
									newmud = 1;
								}

								break;

							case 'X':
								// caracter nao eh modificado
								copmud = 1;
								break;

							case 'Y':
								// Y jah foi tratado acima
								break;

							case 'Z': // se o caracter for Z

								// Z final eh eliminado
								if (fonaux[i + 1] == ' ')
									break;

								// Z + vogal -> S
								if ((fonaux[i + 1] == 'a') || (fonaux[i + 1] == 'i') || (fonaux[i + 1] == 'o')){
									fonwrk[j] = 's';
									j++;

								// Z + consoante -> S + consoante
								}else{
									fonwrk[j] = 's';
									j++;
								}// else

								break;

							default: // se o caracter nao for um dos jah
										// relacionados
								// o caracter nao eh modificado
								fonwrk[j] = fonaux[i];
								j++;
								break;
							}// switch




							// copia caracter corrente
							if (copfon == 1){
								fonwrk[j] = fonaux[i];
								j++;
							}

							// insercao de i apos consoante muda
							if (copmud == 1)
								fonwrk[j] = fonaux[i];
							if (copmud == 1 || newmud == 1){
								j++;
								k = 0;
								while (k == 0){
									// e final mudo
									if (fonaux[i + 1] == ' '){
										fonwrk[j] = 'i';
										k = 1;
									}else if ((fonaux[i + 1] == 'a') || (fonaux[i + 1] == 'i') || (fonaux[i + 1] == 'o'))
										k = 1;
									else if (fonwrk[j - 1] == 'X'){
										fonwrk[j] = 'i';
										j++;
										k = 1;
									}else if (fonaux[i + 1] == 'R')
										k = 1;
									else if (fonaux[i + 1] == 'L')
										k = 1;
									else if (fonaux[i + 1] != 'H'){
										fonwrk[j] = 'i';
										j++;
										k = 1;
									}else
										i++;
								}
							}

						}// for

					}// if

				}// else

				for (i = 0; i < component.at(desloc).length() + 3; i++){
					// percorre toda a palavra, letra a letra
					// i -> I
					if (fonwrk[i] == 'i')
						fonwrk[i] = 'I';
					else
					// a -> A
					if (fonwrk[i] == 'a')
						fonwrk[i] = 'A';
					else

					// o -> U
					if (fonwrk[i] == 'o')
						fonwrk[i] = 'U';
					else
					// s -> S
					if (fonwrk[i] == 's')
						fonwrk[i] = 'S';
					else
					// E -> b
					if (fonwrk[i] == 'E')
						fonwrk[i] = ' ';
					else
					// Y -> _
					if (fonwrk[i] == 'Y')
						fonwrk[i] = '_';
				}

				// retorna a palavra, modificada, ao vetor que contem o texto
				result.clear();
				result.append(fonwrk);
				//trim2(&result);

				//Quem apela, sempre ganha
				string::size_type pos = str.find_first_of(' ');
				if(pos>0)
					result = result.substr(0,pos-1);

				//cout << "added " << result << endl;
				retorno.append(result+" ");

				j = 0; // zera o contador

			}// for

			//trim2(&retorno);

			//Quem apela, sempre ganha
			string::size_type pos = retorno.find_first_of(' ');
			if(pos>0)
				retorno = retorno.substr(0,pos);

			return retorno;

		}
};



#endif

