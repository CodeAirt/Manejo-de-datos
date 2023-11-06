#ifndef RUT_H
#define RUT_H
#include <iostream>

using namespace std;

class Rut{
	private:
		string numero;
		char dv;
	public:
		Rut(){numero=""; dv='0';}
		Rut(string,char);
		string getNumero(){return numero;} //getters
		char getDv(){return dv;}
		string setNumero(string numero_){numero=numero_;} //setters
		char setDv(char dv_){dv=dv_;}
		
		void mostrarRut(){cout << numero << "-" << dv;}// LO AGREGUE YO
};

#endif
