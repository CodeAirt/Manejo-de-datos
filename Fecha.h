#ifndef FECHA_H
#define FECHA_H

using namespace std;

class Fecha{
	private:
		int dd,mm,aa;
	public:
		Fecha(){dd=0; mm=0; aa=0;}
		Fecha(int,int,int);
		int getDD(){return dd;} //getters
		int getMM(){return mm;}
		int getAA(){return aa;}
		int setDD(int dd_){dd=dd_;} //setters
		int setMM(int mm_){mm=mm_;}
		int setAA(int aa_){aa=aa_;}
		
		void mostrarFecha(){cout<<dd<<"-"<<mm<<"-"<<aa;} // LO AGREGUE YO
};

#endif
