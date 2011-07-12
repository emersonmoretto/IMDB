//============================================================================
// Name        : IMDB.cpp
// Author      : emoretto
// Version     :
// Copyright   : 
// Description : In-memory database - hard performance is -always- ugly code!
//============================================================================

#include <boost/bind.hpp>
#include <boost/flyweight.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string.h>
#include <sys/time.h>

#include <cstdlib>
#include <sys/types.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
using namespace boost::flyweights;


class Paciente {

	// private members
	flyweight<std::string> nome;
	flyweight<std::string> nomeMae;
	//string nome;
	//string nomeMae;
	int cpf;

public:

	// constructor
	Paciente(const string nome, const string nomeMae, const int cpf) :
		nome(nome), nomeMae(nomeMae), cpf(cpf) {
	};

	// default constructor
	Paciente() :
		cpf(0) {
	};

	// copy constructor
	Paciente(const Paciente & p) :
		nome(p.nome), nomeMae(p.nomeMae), cpf(p.cpf) {
	};

	// operator =
	Paciente & operator=(const Paciente & rhs) {

		// don't assign to self
		if (this == &rhs)
			return *this;

		nome = rhs.nome;
		nomeMae = rhs.nomeMae;
		cpf = rhs.cpf;
		return *this;
	};

	// access private members
	string GetNome() const {
		return nome;
	};

	string GetNomeMae() const {
		return nomeMae;
	};

	int GetCpf() const {
		return cpf;
	};

}; // end of class Person


// function object to print one person
class fPrint {
	ostream & m_os;
public:

	// constructor - remember which stream to use
	fPrint(ostream & os) :
		m_os(os) {
	};

	// person object arrives as a pair of key,object
	void operator()(const pair<const string, const Paciente> & item) const {
		m_os << "key:" << item.first << " - nome: " << item.second.GetNome()
				<< " nomeMae: " << item.second.GetNomeMae() << ", cpf " << item.second.GetCpf() << endl;
	};

}; // end of class fPrint



void printtimevaldiff(struct timeval a, struct timeval b)
{
	int dsec;
	int dusec;

	dsec = a.tv_sec - b.tv_sec;
	dusec = a.tv_usec - b.tv_usec;

	if (dusec < 0) {
		dsec--;
		dusec += 1000000;
	}
	printf("%d.%012ds \n", dsec, dusec);
}

char * random_fill2()
{
    //const char *src = "aaaaaaaa";
    const char *src = "abcdefghijklm";
    //const char *src = "1234567890";
    const size_t n = 100;

    char * s = (char *) malloc(100);

    size_t src_len = strlen(src);
    size_t s_len = sizeof(s);
    size_t i;

    for (i = 0; i < n; i++)
    {
        s[i] = src[rand() % src_len];
    }
    return s;
}

char * random_fill()
{
    //const char *src = "aaaaaaaa";
    const char *src = "abcdefghijklm";
    //const char *src = "1234567890";
    const size_t n = 10;

    char * s = (char *) malloc(10);

    size_t src_len = strlen(src);
    size_t s_len = sizeof(s);
    size_t i;

    for (i = 0; i < n; i++)
    {
        s[i] = src[rand() % src_len];
    }
    return s;
}



// declare type for storing people (numeric key, person object)

typedef map<string, Paciente> people_map;

//typedef map<int, Paciente, less<int> > paciente_map;

//typedef map<string, Paciente, less<int> > paciente_map2;

int main_simple(void) {


	cout << "RBTree C+-" << endl; // prints !!!Hello World!!!
	cout << "*************\n" << endl;

	//std::map <string, Paciente> pacientes;

	people_map pacientes;

	fPrint printer(cout); // instance of function output object
	struct rusage start, end;

	while (true) {
		cout << "===========MENU==========" << endl;
		cout << "1 - Carregar arvore" << endl;
		cout << "2 - Salvar arvore" << endl;
		cout << "3 - Imprimir arvore" << endl;
		cout << "4 - Imprimir nodes da arvore" << endl;
		cout << "5 - Cria arvore random" << endl;
		cout << "6 - Buscar na arvore" << endl;
		cout << "7 - Tamanho da arvore" << endl;
		cout << "0 - Zerar arvore" << endl;
		cout << "9 - Sair" << endl;
		cout << "Opção: " << endl;
		int op;
		cin >> op;
		switch (op) {
			case 1: {
				getrusage(RUSAGE_SELF, &start);


				getrusage(RUSAGE_SELF, &end);
				printf("time: ");
				printtimevaldiff(end.ru_utime, start.ru_utime);
				break;
			}
			case 2: {
				getrusage(RUSAGE_SELF, &start);

				getrusage(RUSAGE_SELF, &end);
				printf("time: ");
				printtimevaldiff(end.ru_utime, start.ru_utime);
				break;
			}
			case 3: {
				break;
			}
			case 4: {
				cout << "Printing all using fPrint ..." << endl;
				for_each(pacientes.begin(), pacientes.end(), printer);
				break;
			}
			case 5:{

				cout << "Digite a qtd de nodes" << endl;
				int total;
				cin >> total;
				char * s;
				char * s2;
				getrusage(RUSAGE_SELF, &start);

				for(int i=0; i < total ; i++){
					s = random_fill();
					s2 = random_fill2();
					//pacientes.insert(make_pair(s, Paciente(s, s, i)));
					pacientes[s2] = Paciente(s, s, i);
					delete(s);
					delete(s2);
				}
				getrusage(RUSAGE_SELF, &end);
				printf("time: ");
				printtimevaldiff(end.ru_utime, start.ru_utime);
				break;
			}
			case 6: {
				getrusage(RUSAGE_SELF, &start);

				cout << "Digite a key" << endl;

				string total;
				cin >> total;

				Paciente & p = pacientes[total];
				cout << "Paciente has name " << p.GetNome() << endl;

				getrusage(RUSAGE_SELF, &end);
				printf("time: ");
				printtimevaldiff(end.ru_utime, start.ru_utime);
				break;

			}
			case 7: {
				cout << pacientes.size() << endl;
				break;
			}
			case 0: {
				pacientes.clear();
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

	cout << "Goodbye" << endl; // prints !!!Hello World!!!
	return 0;
}
