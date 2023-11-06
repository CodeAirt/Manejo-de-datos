#include "Patente.h"

Patente::Patente(string rol_,string nombre_,string direccion_,string giro_,string numeroR,char dvR,int d,int m,int a,string tipoP,int valorP,bool pross) : Empresa(rol_,nombre_,direccion_,giro_,numeroR,dvR){
	fechaPatente= Fecha(d,m,a);
	tipoPatente=tipoP;
	valorPatente=valorP;
	fueProcesado=pross;
}

void Patente::VisualizarP(){
	VisualizarE();
	cout<<"FECHA: ";getFecha();
	cout<<"\nTIPO PATENTE: "<<tipoPatente<<endl;
	cout<<"VALOR PATENTE (UTM): "<<valorPatente<<endl;
	/*if(fueProcesado == true){
		cout<<"PROCESADO: "<<"SI."<<endl;
	}else{
		cout<<"PROCESADO: "<<"NO."<<endl;
	}*/
}
