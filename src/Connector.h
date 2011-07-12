/*
 * Connector.h
 *
 *  Created on: 09/12/2010
 *      Author: root
 */

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "DTO.h"
#include "Util.h"
#include "Fonetica.h"
#include "Match.h"
#include "Levenshtein.h"


#ifndef CONNECTOR_H_
#define CONNECTOR_H_

using namespace std;


class Connector {

private:
	Connector();
	virtual ~Connector();

	map <string, DTO *> tree;
	multimap <string, DTO * > treeName1;


	//Phono
	multimap <string, DTO * > treeName2;
	//multimap <string, DTO * > treeUltimoNomeSoundex;


public:
	static Connector& getInstance()
	{
		 static Connector * instance = 0;
		 if (!instance) instance = new Connector();
		 return *instance;
	}

	map <string, DTO * > getTree(void){
		return tree;
	}

	void insert(DTO * dto){
		//tree[dto->co_usuario] = dto;
		tree.insert( pair<string, DTO * > (dto->id, dto) );

		treeName1.insert( pair<string, DTO * > (dto->name1, dto) );

		treeName2.insert( pair<string, DTO * > (dto->name2, dto) );

	}

	void stats(void){

		cout << "Main Tree: " << tree.size() << endl;
		cout << "\tTree 1 Nome: " << treeName1.size() << endl;
		//cout << "\tTree Primeiro Nome with key JOSE: " << treePrimeiroNome.count("JOSE") << endl;
		cout << "\tTree 2 Nome:" << treeName2.size() << endl;


//		cout << "\tTree treePrimeiroNomeSoundex with key GIUSI: " << treePrimeiroNomeSoundex.count("GIUSI") << endl;
		//cout << "\tTree treeUltimoNomeSoundex with key SIUVA: " << treeUltimoNomeSoundex.count("SIUVA") << endl;


	}


	void searchByPrimeiroNome(string str){

		pair<multimap<string, DTO * >::iterator, multimap<string, DTO * >::iterator> ppp;

		ppp = treeName1.equal_range(str);

		cout << endl << "Range of "+str+" elements:" << endl;

		for (multimap<string, DTO * >::iterator it = ppp.first; it != ppp.second; ++it)
		{
		   DTO * dto = ((DTO *) (*it).second);
		   DTO * dtoCO = tree[dto->id];
		   cout << "  [" << dto->name1 << "]" << endl;
		   if(dto==dtoCO){
			   cout << "igual " << dto << " " << dtoCO;
		   }else{
			   cout << "NAOigual " << dto << " " << dtoCO;
		   }

		}

	}

	//RS
	struct DTOResultSet{
		double relevance;
		DTO * dto;
	};


	//Inverse comparator
	struct compare
	{
		bool operator()(double a, double b)
		{
		      return a > b;
		}
	};

/*
	multimap <double, DTOResultSet *, compare> searchByNome(string str){

		vector<string> result;
		Util::StringSplit(str,"_", &result);

		multimap <double, DTOResultSet * , compare> resultSet;

		if(result.size() < 2) return resultSet;

		flyweight<string> primeiroNomeSoundex = (flyweight<string>) Fonetica::fonetizar(result.at(0) );
		flyweight<string> ultimoNomeSoundex   = (flyweight<string>) Fonetica::fonetizar(result.at(1) );

		multimap<string, DTO * > * treeToIterate;
		string treeToIterateKey;
		bool (*pfmatch)(string,DTO*) = NULL;
		flyweight<string> matchKey;

		if(treePrimeiroNomeSoundex.count(primeiroNomeSoundex) > treeUltimoNomeSoundex.count(ultimoNomeSoundex)){
			treeToIterate = &treeUltimoNomeSoundex;
			treeToIterateKey = ultimoNomeSoundex;
			pfmatch = &matchPrimeiroNome;
			matchKey = primeiroNomeSoundex;
		}else{
			treeToIterate = &treePrimeiroNomeSoundex;
			treeToIterateKey = primeiroNomeSoundex;
			pfmatch = &matchUltimoNome;
			matchKey = ultimoNomeSoundex;
		}
		cout << "treeUltimoNomeSoundex : " << &treeUltimoNomeSoundex << endl;
		cout << "treePrimeiroNomeSoundex : " << &treePrimeiroNomeSoundex << endl;

		cout << "Using Tree : " << treeToIterate << endl;

		cout << "IterateKey : " << treeToIterateKey << endl;
		cout << "MatchKey : " << matchKey << endl;

		pair<multimap<string, DTO * >::iterator, multimap<string, DTO * >::iterator> ppp;
		ppp = treeToIterate->equal_range(treeToIterateKey);

		for (multimap<string, DTO * >::iterator it = ppp.first; it != ppp.second; ++it)
		{
			DTO * dto = ((DTO *) (*it).second);

			if( (*pfmatch)(matchKey,dto)){
				//cout << "  [" << dto ->nomeCompleto << "]" << Levenshtein::distance(dto->nomeCompleto, str) << endl;

				DTOResultSet * dtoTemp = new DTOResultSet;
				dtoTemp->dto = dto;
				dtoTemp->relevance = Levenshtein::distance(dto->name1, str) * 100;

				resultSet.insert( pair<double, DTOResultSet * > (dtoTemp->relevance, dtoTemp) );
			}
		}

		//Print sorted RS
		cout << "--- ResultSet ---" << endl;
		multimap<double, DTOResultSet * >::iterator ii;
		for( ii = resultSet.begin() ; ii != resultSet.end() ; ++ii)
		{
			cout << fixed << setprecision(1) << ((DTOResultSet *) (*ii).second)->relevance << "% \t" << ((DTOResultSet *) (*ii).second)->dto->name1 << endl;
		}
		cout << "--- End of ResultSet ---" << endl;

		//TODO return the resultSet map
		return resultSet;
	}
	*/

};


#endif /* CONNECTOR_H_ */











