/*
 * Util.cpp
 *
 *  Created on: 09/12/2010
 *      Author: root
 */

#include "Util.h"

Util::Util() {

}

Util::~Util() {
}



char * Util::random_fill2()
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

char * Util::random_fill()
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

void Util::StringSplit(string str, string separator, vector<string>* results){
  int found;
  found = str.find_first_of(separator);
  while(found != string::npos){
	  if(found > 0){
		  results->push_back(str.substr(0,found));
	  }
	  str = str.substr(found+1);
	  found = str.find_first_of(separator);
  }
  if(str.length() > 0){
	  results->push_back(str);
  }
}

void Util::printTimeDiff(timeval a, timeval b){

	long mtime, seconds, useconds;

	seconds  = b.tv_sec  - a.tv_sec;
	useconds = b.tv_usec - a.tv_usec;

	mtime = ( (seconds * 1000) + (useconds/1000.0) ) + 0.5;

	printf("Elapsed time: %ld ms\n", mtime);
	//printf("Elapsed time: %ld microseconds\n", useconds);

	/*int dsec;
	int dusec;

	dsec = a.tv_sec - b.tv_sec;
	dusec = a.tv_usec - b.tv_usec;

	cout << dusec << endl;

	if (dusec < 0) {
		dsec--;
		dusec += 1000000;
	}
	printf("time: ");
	printf("%d.%012ds \n", dsec, dusec);
	*/

}

/**
   * C++ version 0.4 std::string style "itoa":
   */
string Util::itoa(int value) {

	string buf;
	int base = 10;

	// check that the base if valid
	if (base < 2 || base > 16) return buf;

	enum { kMaxDigits = 35 };
	buf.reserve( kMaxDigits ); // Pre-allocate enough space.

	int quotient = value;

	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
		quotient /= base;
	} while ( quotient );

	// Append the negative sign
	if ( value < 0) buf += '-';

	std::reverse( buf.begin(), buf.end() );

	//reverse( buf.begin(), buf.end() );

	return buf;
  }

string Util::replace(string text,string from,string to)
 {
         int pos = text.find(from);
         if (pos != string::npos) text.replace(pos, to.length(), to);
         return text;
 }

 string Util::replaceAll(string text,string from,string to)
 {
         int pos = text.find(from);
         while(pos != string::npos){
       	  text.replace(pos, to.length(), to);
       	  pos = text.find(from);
         }
         return text;
 }


 string Util::clearAccent(string texto){
       if(texto.empty())
           return "";
       string sAcento = "aaaaaeeeeiiiiooooouuuuAAAAAEEEEIIIOOOOOUUUUcCnN";
       string cAcento = "àáâãäèéêëìíîïòóôõöùúûüÀÁÂÃÄÈÉÊËÌÍÎÒÓÔÕÖÙÚÛÜçÇñÑ";


       for(int i=0,j=0; i < cAcento.size()/2 ; i++ , j=j+2){
       	string to = sAcento.substr(i,1);
       	string from = cAcento.substr(j,2);
       	//cout << texto << " " << from << " "<< to << " i:" << itoa(i,10) <<endl;
       	texto =  replaceAll(texto,from,to);
       }

       return texto;

 }

