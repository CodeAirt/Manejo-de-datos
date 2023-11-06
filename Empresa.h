#ifndef EMPRESA_H
#define EMPRESA_H
#include "Rut.h"

class Empresa{
	private: //ATRIBUTOS
		string rol, nombre, direccion, giro;
		Rut rut;
	public: // METODOS
		Empresa(){rol=""; nombre=""; direccion=""; giro="";}
		Empresa(string, string, string, string, string, char); // CONSTRUCTOR
		void VisualizarE();
		string getRol(){return rol;}//getters
		string getNombre(){return nombre;}
		string getDireccion(){return direccion;}
		string getGiro(){return giro;}
		string setRol(string rol_){rol=rol_;}//setters
		string setNombre(string nombre_){nombre=nombre_;}
		string setDireccion(string direccion_){direccion=direccion_;}
		string setGiro(string giro_){giro=giro_;}
		///////RUT
		void getRut(){rut.mostrarRut();}
		string getNumeroR(){return rut.getNumero();}
		char getDvR(){return rut.getDv();}
		string setNumeroR(string numero_){rut.setNumero(numero_);}
		char setDvR(char dv_){rut.setDv(dv_);}
		
};

#endif
