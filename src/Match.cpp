#include "Match.h"

#include <iostream>
#include <string>
#include "DTO.h"


bool matchUltimoNome (string ultimoNomeSoundex, DTO * dto){
//	cout << "matchUltimoNome" << endl;
       return ultimoNomeSoundex == dto->name2;
}

bool matchPrimeiroNome (string primeiroNomeSoundex, DTO * dto){
//	cout << "matchUltimoNome" << endl;
       return primeiroNomeSoundex == dto->name1;
}
