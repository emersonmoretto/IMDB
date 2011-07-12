/*
 * Util.h
 *
 *  Created on: 09/12/2010
 *      Author: root
 */
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

#ifndef UTIL_H_
#define UTIL_H_

const int CO_USUARIO = 1;
const int NO_USUARIO = 2;
const int NO_MAE = 3;
const int NO_PAI = 4;
const int DT_NASCIMENTO = 5;
const int CO_ESTADO_CIVIL = 6;
const int CO_RACA = 7;
const int CO_SEXO = 8;
const int CO_MUNICIPIO_NASC = 9;
const int CO_MUNICIPIO_RESIDENCIA = 10;
const int NU_DOCUMENTO = 11;
const int CO_TIPO_DOCUMENTO = 12;
const int CNS = 13;
const int DS_TIPO_LOGRADOURO = 14;
const int NO_LOGRADOURO = 15;
const int NU_LOGRADOURO = 16;
const int NO_COMPL_LOGRADOURO = 17;
const int NO_BAIRRO = 18;
const int CO_CEP = 19;
const int CO_MUNICIPIO = 20;
const int SG_UF = 21;
const int DS_MUNICIPIO = 22;
const int NU_DDD = 23;
const int NU_TELEFONE = 24;
const int DT_INCLUSAO = 25;
const int DT_PREENCHIMENTO_FORM = 26;
const int DT_ATUALIZACAO = 27;


class Util {

public:

	Util();
	virtual ~Util();

	static void printTimeDiff(struct timeval a, struct timeval b);
	static void StringSplit(string str, string separator, vector<string>* results);

	//static void printRecord(ResultSet* rs);

	static char * random_fill();
	static char * random_fill2();

	static string itoa(int value);

	static string replace(string text,string from,string to);
	static string replaceAll(string text,string from,string to);
	static string clearAccent(string texto);



};

#endif /* UTIL_H_ */
