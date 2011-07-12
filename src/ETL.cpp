#include <string>
#include <vector>
#include <iostream>
#include "Fonetica.h"
#include <cstdlib>
#include "DTO.h"
#include "Connector.h"
#include "Util.h"


	using namespace std;

	int rowCount= 0;
	int patientCount =0;


	// function object to print one person
	class fPrint {
		ostream & m_os;
	public:

		// constructor - remember which stream to use
		fPrint(ostream & os) :
			m_os(os) {
		};

		// person object arrives as a pair of key,object
		void operator()(const pair<const string, const DTO> & item) const {
			m_os << "key:" << item.first << " - nome: "<< item.second.name1 << endl;
		};

	}; // end of class fPrint



  void store(DTO* dto){
 // 	printDTO(dto);
 // 	cout << " stored !!!" << dto->co_usuario << endl;

 	//delete dto;
 	 patientCount++;

 	 Connector::getInstance().insert(dto);
  }

  void etl(int qtdRow){

  	//For time control:
  	struct rusage start, end;

  	cout << "-------------------------------------------------------" << endl;
  	cout << " ETL: [E]xtract [T]ransform [L]oad "  << endl;
  	cout << "-------------------------------------------------------" << endl;

  	cout << "[etl] qtdRow:" << qtdRow << endl;


  	char * s;
	char * s2;

	for(int i=0; i < qtdRow ; i++){
		s = Util::random_fill();
		s2 = Util::random_fill2();

		DTO * dto = new DTO();

		//pacientes.insert(make_pair(s, Paciente(s, s, i)));
		dto->id = s;
		dto->name1 = s2;
		dto->name2 = s2;

		store(dto);
		delete(s);
		delete(s2);
	}

  	cout << "[etl] ETL ended!" << endl;
  }


  int main(void) {

  	cout << "IMDB rev.476" << endl;
  	cout << "*************\n" << endl;

  	fPrint printer(cout); // instance of function output object
 	struct timeval start, end;

  	while (true) {
  		cout << "===========MENU==========" << endl;
  		cout << "1 - Carregar arvore (ETL)" << endl;
  		cout << "2 - Buscar por id" << endl;
  		cout << "3 - Buscar por Nome (primeiro e ultimo)" << endl;
  		cout << "7 - Estatisticas" << endl;
  		cout << "0 - Zerar arvore" << endl;
  		cout << "9 - Sair" << endl;
  		cout << "option> " << endl;

  		int op;
  		cin >> op;
  		switch (op) {
  			case 1:{
  				cout << "Digite a qtd de rows" << endl;
  				int qtd;
  				cin >> qtd;
  				gettimeofday(&start, NULL);

  				etl(qtd);

 				gettimeofday(&end, NULL);
 				Util::printTimeDiff(start, end);
  				break;
  			}
  			case 2: {

  				cout << "Digite a key" << endl;

  				string total;
  				cin >> total;

  				gettimeofday(&start, NULL);
  				DTO * p = Connector::getInstance().getTree()[total];
  				cout << "Paciente  " << endl;
  				p->print();

  				gettimeofday(&end, NULL);
  				Util::printTimeDiff(start, end);

  				break;

  			}

  			case 3: {
  				cout << "Digite o nome do paciente (ex: JOSE_SILVA ) :" << endl;
				string total;
				cin >> total;
				cout << "Buscando por " << total << endl;
				//getrusage(RUSAGE_SELF, &start);
				gettimeofday(&start, NULL);
				//Connector::getInstance().searchByNome(total);
				//getrusage(RUSAGE_SELF, &end);
				gettimeofday(&end, NULL);
				Util::printTimeDiff(start, end);
				break;
			}
  			case 7: {

  				map <string, DTO *> tr = Connector::getInstance().getTree();

  				cout << "Printing all using fPrint ..." << endl;
				for_each(tr.begin(), tr.end(), printer);

				break;
				//Connector::getInstance().stats();
			}
  			case 0: {
		  		Connector::getInstance().getTree().clear();
  				break;
  			}
  			case 9: {
  				exit(1);
  			}
  			default: {
  				break;
  			}
  		}
  	}


  	return 0;
  } // end of main



