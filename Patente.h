#ifndef PATENTE_H
#define PATENTE_H
#include "Empresa.h"
#include "Fecha.h"

class Patente : public Empresa{
	private: //ATRIBUTOS
		Fecha fechaPatente;
		string tipoPatente;
		int valorPatente;
		bool fueProcesado;
	public: //METODOS
		Patente(){tipoPatente=""; valorPatente=0; fueProcesado=false;}
		Patente(string,string,string,string,string,char,int,int,int,string,int,bool); //CONSTRUCTOR
		void VisualizarP();
		string getTipoPatente(){return tipoPatente;}//getters
		int getValorPatente(){return valorPatente;}
		bool getFueProcesado(){return fueProcesado;}
		string setTipoPatente(string tipoPatente_){tipoPatente=tipoPatente_;}//setters
		int setValorPatente(int valorPatente_){valorPatente=valorPatente_;}
		bool setFueProcesado(bool fueProcesado_){fueProcesado=fueProcesado_;}
		/////FECHA
		void getFecha(){fechaPatente.mostrarFecha();}
		int getFdd(){return fechaPatente.getDD();}
		int getFmm(){return fechaPatente.getMM();}
		int getFaa(){return fechaPatente.getAA();}
		int setFdd(int dd_){fechaPatente.setDD(dd_);}
		int setFmm(int mm_){fechaPatente.setMM(mm_);}
		int setFaa(int aa_){fechaPatente.setAA(aa_);}
};

#endif
