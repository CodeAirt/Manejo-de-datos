#include "Empresa.h"

Empresa::Empresa(string rol_,string nombre_,string direccion_,string giro_,string numeroR,char dvR){
	rol=rol_;
	nombre=nombre_;
	direccion=direccion_;
	giro=giro_;
	rut= Rut(numeroR, dvR);
}

void Empresa::VisualizarE(){
	cout<<"ROL: "<<rol<<endl;
	cout<<"NOMBRE: "<<nombre<<endl;
	cout<<"DIRECCION: "<<direccion<<endl;
	cout<<"GIRO: "<<giro<<endl;
	cout<<"RUT: ";getRut();
	cout<<endl;
}
