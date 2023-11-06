#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <cmath>
#include <algorithm>//funcion sort

#include "Rut.h"
#include "Fecha.h"
#include "Empresa.h"
#include "Patente.h"

#define Nombre_Archivo "patentesComerciales.txt"

using namespace std;

void CompletarValor(queue<Patente>& Cola);
void ActualizarDig(queue<Patente>& Cola);
int MasPatentes(queue<Patente>& Cola);
void Estadisticas(queue<Patente>& Cola, int UTM);
void ConsultaAyTP(queue<Patente>& Cola, int ano, string patente);
void GenerarArchivo(queue<Patente>& Cola);
void ProcesarPatentes(queue<Patente>& Cola);


int main(){
	///Rol, Nombre, Direccion, Giro, Rut(numero, dv), Fecha(dd, mm, aa), Tipo patente, Valor patente, Fue procesado(0, 1) ///
	//Patente patente4("12345","nombre","direccion","9876","12345678",'K',18,10,2023,"COMERCIAL",25000,0);   //el ultimo digito 0,1 es el bool
	
	ifstream archivo(Nombre_Archivo);
	string linea,guion="-",DigVerif;
	char delimitador = ';';
	char guionC = '-';
	int contador =0;
	
	queue <Patente> Cola; //crea la Cola
	
	getline(archivo,linea);
	while(getline(archivo,linea)){
		stringstream stream(linea);
		
		string Rol="",Nombre="",Direccion="",Giro="",NumeroR="",TipoPat="",rut="",fecha="",d,m,a;
		char dvR='0';
		int DD=0,MM=0,AA=0,ValorPat=0,Pross=0;
		
		getline(stream,Rol,delimitador);
		getline(stream,rut,delimitador);
		getline(stream,Nombre,delimitador);
		getline(stream,Direccion,delimitador);
		getline(stream,Giro,delimitador);
		getline(stream,fecha,delimitador);
		getline(stream,TipoPat,delimitador);
		//Rut (guarda los datos del rut, numero y dv)
		size_t posicion = rut.find(guion); // busca la posicion del guion en el string
		if(posicion != std::string::npos){ // verifica si se encontro el guion en el string
			DigVerif = rut.substr(posicion + guion.length()); // guarda el dig verificador
			rut.erase(posicion, guion.length()); //elimina el guion del string
			rut.erase(posicion, DigVerif.length());// saca del string el dig verificador
		}
		dvR = DigVerif[0];
		NumeroR = rut;
		//Fecha (guarda los datos de la fecha, dd,mm,aa)
		stringstream F(fecha);
		getline(F,d,guionC);
		getline(F,m,guionC);
		getline(F,a);
		DD = stoi(d);
		MM = stoi(m);
		AA = stoi(a);
		/////////////
		Patente patente1(Rol,Nombre,Direccion,Giro,NumeroR,dvR,DD,MM,AA,TipoPat,ValorPat,Pross); //guarda los datos en la variable de tipo Patente
		Cola.push(patente1); // pone los objetos de tipo Patente en una Cola
		
	}
	archivo.close();
	
	int ano, UTM;
	string patente;
	
	int opcion;
	do{
		cout<<"\n-----------------------------------------------------------";
        cout<<"\n                        MENU DE OPCIONES\n"<<endl;
        cout<<" (1)- Completar Valor Patente."<<endl;
        cout<<" (2)- Actualizar Digito Verificador."<<endl;
        cout<<" (3)- Ano con mas Patentes de Alcoholes."<<endl;
        cout<<" (4)- Estadisticas Descriptivas."<<endl;
        cout<<" (5)- Consultas por Ano y Tipo de Patente."<<endl;
        cout<<" (6)- Generacion de Archivos."<<endl;
        cout<<" (7)- Procesar Patentes."<<endl;
        cout<<"\n (8)- SALIR."<<endl;
        cout<<"-----------------------------------------------------------";
        cout<<"\n Ingrese una opcion: ";
        cin>>opcion;
        
        switch (opcion){
            case 1:
            	system("cls");
                CompletarValor(Cola);
                break; 
            case 2:
            	system("cls");
                ActualizarDig(Cola);
                break;
            case 3:
            	system("cls");
                cout<<"\n\n ---- EN EL ANO *"<<MasPatentes(Cola)<<"* SE OTORGARON MAS PATENTES DE Tipo Alcoholes ----\n"<<endl;
                break;
            case 4:
            	system("cls");
            	cout<<"\n\n Ingrese el Valor de la UTM actual: "; // 63960 pesos; actual al mes de noviembre
				cin>>UTM;
				Estadisticas(Cola, UTM);
            	break;
            case 5:
            	system("cls");
        		cout<<"\n\n Ingrese un Tipo de Patente (en mayusculas): ";
				cin>>patente;
				cout<<"\n Ingrese Ano: ";
				cin>>ano;
				ConsultaAyTP(Cola,ano,patente);
				cout<<"\n"<<endl;
            	break;
            case 6:
            	system("cls");
            	cout<<"\n"<<endl;
            	GenerarArchivo(Cola);
            	cout<<"\n"<<endl;
            	break;
            case 7:
            	system("cls");
            	cout<<"\n"<<endl;
            	ProcesarPatentes(Cola);
            	cout<<"\n"<<endl;
            	break;
        }
    }while(opcion != 8);
	
	return 0;
}
/////////////// MENU 1)
void CompletarValor(queue<Patente>& Cola){
	int utm;
	srand(time(NULL));
	
	queue<Patente> ColaAux; // crea una cola auxiliar
	
	while(!Cola.empty()){ // recorre la cola hasta que quede vacia
		string TipoDePatente="";
		TipoDePatente = Cola.front().getTipoPatente();
		if(TipoDePatente == "MICROEMPRESA"){
			utm = 1+rand()%(5+1-1);
			Cola.front().setValorPatente(utm);
		}
		else if(TipoDePatente == "PROFESIONALES"){
			utm = 2+rand()%(6+1-2);
			Cola.front().setValorPatente(utm);
		}
		else if(TipoDePatente == "INDUSTRIALES"){
			utm = 3+rand()%(7+1-3);
			Cola.front().setValorPatente(utm);
		}
		else if(TipoDePatente == "COMERCIALES"){
			utm = 4+rand()%(8+1-4);
			Cola.front().setValorPatente(utm);
		}
		else if(TipoDePatente == "ALCOHOLES"){
			utm = 5+rand()%(10+1-5);
			Cola.front().setValorPatente(utm);
		}
		ColaAux.push(Cola.front()); // guarda el dato de la cola original en la cola auxiliar
		Cola.pop(); // popea el dato para pasar al siguiente
	}
	Cola = ColaAux; // pasa los datos de la cola auxiliar a la cola original
	
	cout<<"\n\n ***Se han completado exitosamente los valores para cada Patente.***\n"<<endl;
}
////////////// MENU 2)
void ActualizarDig(queue<Patente>& Cola){
	int numeros=0, DigVerif=0, N=0;
	
	queue<Patente> ColaAux;
	while(!Cola.empty()){
		string X = Cola.front().getNumeroR();
		char Y = Cola.front().getDvR();
		
		numeros = stoi(X);
		if(Y == 'K'){
			DigVerif = 10;
		}else{
			DigVerif = Y - '0'; //el - '0' convierte el char en numero
		}
		// calculo digito verificador
		int aux=0, mult=0, sum=0, rest=0;
		int x = numeros, cont=2, fin=11;
		
		while(x > 0){
			aux = x % 10;
			x = x / 10;
			mult = aux*cont;
			sum = sum + mult;
			cont++;
			if(cont > 7){
				cont=2;
			}
		}
		rest = sum / 11;
		rest = rest * 11;
		sum = sum - rest;
		
		fin = fin - sum; // hasta aca se calcula el dig verificador del rut
		// verifica si el digito verificador esta correcto, si no es el caso lo reemplaza
		if(fin != DigVerif){
			char digitV;
			if(fin == 10){
				digitV = 'k';
			}
			else if(fin == 11){
				digitV = '0';
			}
			else{
				digitV = fin + '0'; // el + '0' convierte el numero en char
			}
			Cola.front().setDvR(digitV);
		}
		ColaAux.push(Cola.front()); // guarda el dato de la cola original en la cola auxiliar
		Cola.pop();
		N++;
	}
	Cola = ColaAux;
	
	cout <<"\n\n ***Se Verificaron y Actualizaron "<<N<<" Datos de Ruts.***\n"<<endl;
}
///////////// MENU 3)
int MasPatentes(queue<Patente>& Cola){
	time_t t= time(0);
	tm* hoy = localtime(&t);
	int A_actual = hoy->tm_year + 1900; // año actual
	
	int mayor=0, ano=0;
	
	queue<Patente> ColaAux;
	
	for(int i=1900; i<=A_actual; i++){ // recorre desde el año 1900 al presente (i=1900; i++)
		int cont=0;
		
		while(!Cola.empty()){ // cuenta cuantas patentes hay de tipo alcoholes en el año en que va el cilo [i]
			string TipoDePatente = Cola.front().getTipoPatente();
			int Faa = Cola.front().getFaa();
			
			if(Faa == i){
				if(TipoDePatente == "ALCOHOLES"){
					cont++; //cuenta el numero de patentes en el año [i]
				}
			}
			ColaAux.push(Cola.front()); //guarda el dato de la cola original en la cola auxiliar
			Cola.pop(); // popea el dato para pasar al siguiente
		}
		if(cont > mayor){ // verifica si el contador es mayor que "mayor", si es asi "mayor" pasa a tener el valor de cont que es la cantidad de patentes
			mayor = cont;
			ano = i; //guarda en una variable el año que es [i]
		}
		while(!ColaAux.empty()){ // pasa los datos de la Cola Auxiliar a la Cola original
			Cola.push(ColaAux.front());
			ColaAux.pop();
		}
	}
	// variable "mayor" es la cantidad de patentes
	return ano;
}
///////////////////// MENU 4)
//////// d.1)
void MMDeVPat(queue<Patente>& Cola, int UTM){
	long VpesosM,VpesosP,VpesosI,VpesosC,VpesosA;
	int cantM=0,cantP=0,cantI=0,cantC=0,cantA=0;
	long sumM=0,sumP=0,sumI=0,sumC=0,sumA=0;
	queue<Patente> ColaAux;//crea una cola auxiliar
	
	while(!Cola.empty()){//recorre la cola original hasta que quede vacia
		string TipoDePatente = Cola.front().getTipoPatente();
		int Valor = Cola.front().getValorPatente();
		if(TipoDePatente == "MICROEMPRESA"){ // por cada tipo de patente
			VpesosM = Valor*UTM; //calcula su valor de utm en pesos
			cantM++; // cuenta cuantas patentes del mismo tipo
			sumM = sumM + VpesosM; // suma sus valores
		}
		else if(TipoDePatente == "PROFESIONALES"){
			VpesosP = Valor*UTM;
			cantP++;
			sumP = sumP + VpesosP;
		}
		else if(TipoDePatente == "INDUSTRIALES"){
			VpesosI = Valor*UTM;
			cantI++;
			sumI = sumI + VpesosI;
		}
		else if(TipoDePatente == "COMERCIALES"){
			VpesosC = Valor*UTM;
			cantC++;
			sumC = sumC + VpesosC;
		}
		else if(TipoDePatente == "ALCOHOLES"){
			VpesosA = Valor*UTM;
			cantA++;
			sumA = sumA + VpesosA;
		}
		ColaAux.push(Cola.front());//guarda el dato de la cola original en la auxuliar, para que no se pierda
		Cola.pop();//popea el dato original para avanzar al siguiente
	}
	while(!ColaAux.empty()){ //guarda toda la cola auxiliar en la original que quedó vacia
		Cola.push(ColaAux.front());
		ColaAux.pop();
	}
	ColaAux = Cola;
	
	//MEDIA
	float mediaM,mediaP,mediaI,mediaC,mediaA; // saca la media con los valores obtenidos
	mediaM = sumM / cantM;//microempresa
	mediaP = sumP / cantP;//profesionales
	mediaI = sumI / cantI;//industriales
	mediaC = sumC / cantC;//comerciaes
	mediaA = sumA / cantA;//alcoholes
	
	cout<<"\n\nLA MEDIA DE LOS VALORES DE CADA PATENTE ES:"<<endl; // muestra las medias
	cout<<"\nMICROEMPRESA: "<<mediaM<<" pesos"<<endl;
	cout<<"PROFESIONALES: "<<mediaP<<" pesos"<<endl;
	cout<<"INDUSTRIALES: "<<mediaI<<" pesos"<<endl;
	cout<<"COMERCIALES: "<<mediaC<<" pesos"<<endl;
	cout<<"ALCOHOLES: "<<mediaA<<" pesos"<<endl;
	
	//MEDIANA
	vector<int> valoresM,valoresP,valoresI,valoresC,valoresA;//crea vectores
    while (!ColaAux.empty()) {
        string TipoDePatente = ColaAux.front().getTipoPatente();
        int Valor = ColaAux.front().getValorPatente() * UTM;

        if (TipoDePatente == "MICROEMPRESA") { // en cada tipo de patente
            valoresM.push_back(Valor); // guarda su valor en pesos en un vector
        }
        if (TipoDePatente == "PROFESIONALES") {
            valoresP.push_back(Valor);
        }
        if (TipoDePatente == "INDUSTRIALES") {
            valoresI.push_back(Valor);
        }
        if (TipoDePatente == "COMERCIALES") {
            valoresC.push_back(Valor);
        }
        if (TipoDePatente == "ALCOHOLES") {
            valoresA.push_back(Valor);
        }
        ColaAux.pop();
    }
    sort(valoresM.begin(), valoresM.end()); //ordena los vectores
    sort(valoresP.begin(), valoresP.end());
    sort(valoresI.begin(), valoresI.end());
    sort(valoresC.begin(), valoresC.end());
    sort(valoresA.begin(), valoresA.end());

    float medianaM,medianaP,medianaI,medianaC,medianaA;
    if (cantM % 2 == 0) { // si la cantidad de valores que hay es par
        medianaM = (valoresM[cantM / 2 - 1] + valoresM[cantM / 2]) / 2.0; // suma los dos valores del medio y saca su promedio, ese es la mediana
    } else {
        medianaM = valoresM[cantM / 2]; // sino, simplemente la mediana es el valor del medio
    }
    if (cantP % 2 == 0) {
        medianaP = (valoresP[cantP / 2 - 1] + valoresP[cantP / 2]) / 2.0;
    } else {
        medianaP = valoresP[cantP / 2];
    }
    if (cantI % 2 == 0) {
        medianaI = (valoresI[cantI / 2 - 1] + valoresI[cantI / 2]) / 2.0;
    } else {
        medianaI = valoresI[cantI / 2];
    }
    if (cantC % 2 == 0) {
        medianaC = (valoresC[cantC / 2 - 1] + valoresC[cantC / 2]) / 2.0;
    } else {
        medianaC = valoresC[cantC / 2];
    }
    if (cantA % 2 == 0) {
        medianaA = (valoresA[cantA / 2 - 1] + valoresA[cantA / 2]) / 2.0;
    } else {
        medianaA = valoresA[cantA / 2];
    }
    cout<<"\n\nLA MEDIANA DE LOS VALORES DE CADA PATENTE ES:"<<endl; // muestra las medianas
	cout<<"\nMICROEMPRESA: "<<medianaM<<" pesos"<<endl;
	cout<<"PROFESIONALES: "<<medianaP<<" pesos"<<endl;
	cout<<"INDUSTRIALES: "<<medianaI<<" pesos"<<endl;
	cout<<"COMERCIALES: "<<medianaC<<" pesos"<<endl;
	cout<<"ALCOHOLES: "<<medianaA<<" pesos"<<endl;
	
	//DESVIACION ESTANDAR
	float sumC2M,sumC2P,sumC2I,sumC2C,sumC2A; 
	sumC2M=sumC2P=sumC2I=sumC2C=sumC2A= 0.0;
    for (int i = 0; i < cantM; i++) {
        sumC2M += pow(valoresM[i] - mediaM, 2); //saca la distancia del valor a la media, y calcula su cuadrado, para luego sumarlos
    }
    for (int i = 0; i < cantP; i++) {
        sumC2P += pow(valoresP[i] - mediaP, 2);
    }
    for (int i = 0; i < cantI; i++) {
        sumC2I += pow(valoresI[i] - mediaI, 2);
    }
    for (int i = 0; i < cantC; i++) {
        sumC2C += pow(valoresC[i] - mediaC, 2);
    }
    for (int i = 0; i < cantA; i++) {
        sumC2A += pow(valoresA[i] - mediaA, 2);
    }
    float desviacionEstandarM = sqrt(sumC2M / cantM); //saca el promedio de la suma (del cuadrado de las distancias) calculo anterior, y saca su raiz
    float desviacionEstandarP = sqrt(sumC2P / cantP);
    float desviacionEstandarI = sqrt(sumC2I / cantI);   // **SI SE AGREGA (cantP - 1) es EL CALCULO DE DESVIACION ESTANDAR PARA MUESTRAS**
    float desviacionEstandarC = sqrt(sumC2C / cantC);	//   ahora como esta es desviacion estandar para poblacion **
    float desviacionEstandarA = sqrt(sumC2A / cantA);
    
    cout<<"\n\nLA DESVIACION ESTANDAR DE LOS VALORES DE CADA PATENTE ES:"<<endl; // muestra cada desviacion estandar
	cout<<"\nMICROEMPRESA: "<<desviacionEstandarM<<" pesos"<<endl;
	cout<<"PROFESIONALES: "<<desviacionEstandarP<<" pesos"<<endl;
	cout<<"INDUSTRIALES: "<<desviacionEstandarI<<" pesos"<<endl;
	cout<<"COMERCIALES: "<<desviacionEstandarC<<" pesos"<<endl;
	cout<<"ALCOHOLES: "<<desviacionEstandarA<<" pesos"<<endl;
}
//////////// d.2)
void variabilidad(queue<Patente>& Cola, int UTM){
	long VpesosB,VpesosM,VpesosRd;
	int  cantB=0,cantM=0,cantRd=0;
	long sumB=0,sumM=0,sumRd=0;
	queue<Patente> ColaAux;
	
	while(!Cola.empty()){//recorre la cola original hasta que quede vacia
		string Giro = Cola.front().getGiro();
		int Valor = Cola.front().getValorPatente();
		if(Giro == "BOTILLERIA"){
			VpesosB = Valor*UTM; //calcula su valor de utm en pesos
			cantB++; // cuenta cuantas giros del mismo tipo
			sumB = sumB + VpesosB; // suma sus valores
		}
		if(Giro == "MINIMERCADOS"){
			VpesosM = Valor*UTM;
			cantM++;
			sumM = sumM + VpesosM;
		}
		if(Giro == "REST.DIURNO"){
			VpesosRd = Valor*UTM;
			cantRd++;
			sumRd = sumRd + VpesosRd;
		}
		ColaAux.push(Cola.front());
		Cola.pop();
	}
	
	// MEDIA MUESTRAL
	float XB,XM,XRd;
	XB = sumB / cantB;
	XM = sumM / cantM;
	XRd = sumRd / cantRd;
	
	// DESVIACION ESTANDAR MUESTRAL
	float varianzaB=0.0,varianzaM=0.0,varianzaRd=0.0;
	while(!ColaAux.empty()){
		string Giro = ColaAux.front().getGiro();
		int Valor = ColaAux.front().getValorPatente();
		if(Giro == "BOTILLERIA"){
			VpesosB = Valor*UTM;
			varianzaB += pow(VpesosB - XB,2);
		}
		if(Giro == "MINIMERCADOS"){
			VpesosM = Valor*UTM;
			varianzaM += pow(VpesosM - XM,2);
		}
		if(Giro == "REST.DIURNO"){
			VpesosRd = Valor*UTM;
			varianzaRd += pow(VpesosRd - XRd,2);
		}
		Cola.push(ColaAux.front());
		ColaAux.pop();
	}
	float desviacionEstandarB = sqrt(varianzaB / (cantB - 1));
	float desviacionEstandarM = sqrt(varianzaM / (cantM - 1));
	float desviacionEstandarRd = sqrt(varianzaRd / (cantRd - 1));
	////// CV
	float CV_B = desviacionEstandarB / XB;
	float CV_M = desviacionEstandarM / XM;
	float CV_Rd = desviacionEstandarRd / XRd;
	
	if(CV_B > CV_M && CV_B > CV_Rd){
		cout<<"\n El Giro con Mayor variabilidad es: BOTILLERIA; Con una variabilidad de: "<<CV_B<<endl;
	}
	if(CV_M > CV_B && CV_M > CV_Rd){
		cout<<"\n El Giro con Mayor variabilidad es: MINIMERCADO; Con una variabilidad de: "<<CV_M<<endl;
	}
	if(CV_Rd > CV_B && CV_Rd > CV_M){
		cout<<"\n El Giro con Mayor variabilidad es: REST.DIURNO; Con una variabilidad de: "<<CV_Rd<<endl;
	}
	cout<<endl;
}
/////////// d.3)
void determinarPercentil(queue<Patente>& Cola, int UTM){
	vector<int> valoresComerciales;
	queue<Patente> ColaAux;
	
	while(!Cola.empty()){
		string TipoDePatente = Cola.front().getTipoPatente();
		int Valor = Cola.front().getValorPatente();
		if(TipoDePatente == "COMERCIALES"){
			valoresComerciales.push_back(Valor*UTM); // ingresa los valores de las patentes al vector
		}
		ColaAux.push(Cola.front());
		Cola.pop();
	}
	Cola = ColaAux;
	
	sort(valoresComerciales.begin(), valoresComerciales.end()); // ordena los valores en el vector
	int posicionPercentil_75 = 0.75 * valoresComerciales.size(); // calcula el percentil 75 (la posicion en el vector)
	int valorPercentil_75 = valoresComerciales[posicionPercentil_75]; // se obtiene el valor que esta en el percentil 75
	
	cout<<"\nEl valor de la patente sobre el cual se encuentra el 25% de las patentes de tipo COMERCIALES (percentil 75) es: "<<valorPercentil_75<<endl;
}

void Estadisticas(queue<Patente>& Cola, int UTM){
	int opcion;
	do{
		cout<<"\n\n---------------------------------------------------------------------------------------------------------";
        cout<<"\n                        OPCIONES\n"<<endl;
        cout<<" (1)- Determinar Media, Mediana y Desviacion Estandar del Valor de Patente por TIPO PATENTE."<<endl;
        cout<<"\n (2)- Determinar en que GIRO existe la mayor variabilidad en el pago de VALOR DE PATENTE."<<endl;
        cout<<"      (considera solo los Giros de: BOTILLERIA, MINIMERCADO Y REST.DIURNO)"<<endl;
        cout<<"\n (3)- Determinar el valor patente sobre el cual se encuentra el 25% de las patentes COMERCIALES (percentil 75)."<<endl;
        cout<<"\n (4)- SALIR."<<endl;
        cout<<"\n---------------------------------------------------------------------------------------------------------";
        cout<<"\n Ingrese una opcion: ";
        cin>>opcion;
        
        switch (opcion){
            case 1:
            	system("cls");
                MMDeVPat(Cola,UTM);
                cout<<"\n"<<endl;
                break; 
            case 2:
            	system("cls");
            	cout<<"\n"<<endl;
                variabilidad(Cola,UTM);
                break;
            case 3:
            	system("cls");
            	cout<<"\n"<<endl;
                determinarPercentil(Cola,UTM);
                break;
        }
    }while(opcion != 4);
    system("cls");
}
/////////// MENU 5)
void ConsultaAyTP(queue<Patente>& Cola, int ano, string patente){
	
	queue<Patente> ColaAux;
	
	while(!Cola.empty()){
		string TipoDePatente = Cola.front().getTipoPatente();
		int FAA = Cola.front().getFaa();
		
		if(TipoDePatente == patente){
			if(FAA == ano){
				cout<<"\n";
				cout<<"-----------------------\n"<<endl;
				cout<<"ROl: "<<Cola.front().getRol()<<endl;
				cout<<"RUT: ";Cola.front().getRut();
				cout<<"\nNOMBRE: "<<Cola.front().getNombre()<<endl;
			}
		}
		ColaAux.push(Cola.front());
		Cola.pop();
	}
	Cola = ColaAux;
}
////////// MENU 6)
void GenerarArchivo(queue<Patente>& Cola){
	queue<Patente> ColaA;
	stack<Patente> PilaA,PilaB,PilaAux;
	ColaA = Cola; //pasa los datos de la Cola original a la ColaA (para no perder la original)
	
	while(!ColaA.empty()){ // pasa los datos de la ColaA a una PilaA
		PilaA.push(ColaA.front());
		ColaA.pop();
	}
	while(!PilaA.empty()){ //ORDENAMIENTO DE PILA (los datos quedan ordenados en la PilaB)
    	Patente dato = PilaA.top();//asigna el valor top de la PilaA en la variable dato y lo saca de la pilaA
    	PilaA.pop();
        if(PilaB.empty() || dato.getNumeroR().compare(PilaB.top().getNumeroR()) < 0){ // verifica si la PilaB está vacia O si el rut de dato es menor a el rut que esta en la PilaB
            PilaB.push(dato); // si se cumple alguna de las dos, ingresa el dato en PilaB
        } else {
            while (!PilaB.empty() && dato.getNumeroR().compare(PilaB.top().getNumeroR()) > 0) { //sino,mientras PilaB no este vacia Y rut de dato sea mayor a rut de PilaB 
                PilaAux.push(PilaB.top()); // ingresa el dato de PilaB a PilaAux y lo saca de la pilaB
                PilaB.pop();
            }
            PilaB.push(dato); // ingresa el dato en PilaB
            while (!PilaAux.empty()) {
                PilaB.push(PilaAux.top()); //ingresa nuevamente a PilaB los datos de PilaAux (fueron los que se sacaron en el anterior while)
                PilaAux.pop();
            }
        }
    }
	while(!PilaB.empty()){
		ColaA.push(PilaB.top()); // devuelve los datos ORDENADOS a la ColaA
		PilaB.pop();
	}
	///////////////// HASTA AQUI EL ORDENAMIENTO DE LA COLA \\\\\\\\\\\\\\\\\\\
	
	ofstream archivo; // ingresa los datos ordenados al archivo "salida1.txt"
	archivo.open("salida1.txt");
	archivo<<"RUT ;ROL ;NOMBRE ;DIRECCIÓN COMERCIAL ;GIRO ;FECHA OTORGAMIENTO ;TIPO PATENTE; VALOR PATENTE\n"<<endl;
	
	int LL=0;
	while(!ColaA.empty()){
		archivo<<ColaA.front().getNumeroR()<<"-"<<ColaA.front().getDvR()<<" ;"; //RUT
		archivo<<ColaA.front().getRol()<<" ;"<<ColaA.front().getNombre()<<" ;"; //ROL,NOMBRE
		archivo<<ColaA.front().getDireccion()<<" ;"<<ColaA.front().getGiro()<<" ;"; //DIRECCION,GIRO
		archivo<<ColaA.front().getFdd()<<"-"<<ColaA.front().getFmm()<<"-"<<ColaA.front().getFaa()<<" ;"; //FECHA
		archivo<<ColaA.front().getTipoPatente()<<" ;"<<ColaA.front().getValorPatente()<<endl; //TIPO PATENTE, VALOR PATENTE
		ColaA.pop();
		LL++;
	}
	archivo.close();
	
	cout<<"\n ***Se genero el archivo --> salida1.txt <-- con "<<LL<<" datos de patentes ordenados por RUT.***"<<endl;
}
///////// MENU 7)
void ProcesarPatentes(queue<Patente>& Cola){
	stack<Patente> Aux;
	queue<Patente> ColaAux;
	
	while(!Cola.empty()){ // invierte la cola
		Aux.push(Cola.front());
		Cola.pop();
	}
	while(!Aux.empty()){
		Cola.push(Aux.top());
		Aux.pop();
	}
	
	ofstream archivo1; //crea el archivo y pasa los ultimos 25 datos a procesar
	archivo1.open("procesar.txt");
	int cont=0;
	while(cont<25){
		if(Cola.front().getFueProcesado() == false){
			archivo1<<"\nRUT: "<<Cola.front().getNumeroR()<<"-"<<Cola.front().getDvR()<<endl; //RUT
			archivo1<<"ROL: "<<Cola.front().getRol()<<endl; //ROL
			archivo1<<"NOMBRE: "<<Cola.front().getNombre()<<endl; //NOMBRE
			archivo1<<"DIRECCION: "<<Cola.front().getDireccion()<<endl; //DIRECCION
			archivo1<<"GIRO: "<<Cola.front().getGiro()<<endl; //GIRO
			archivo1<<"FECHA: "<<Cola.front().getFdd()<<"-"<<Cola.front().getFmm()<<"-"<<Cola.front().getFaa()<<endl; //FECHA
			archivo1<<"TIPO PATENTE: "<<Cola.front().getTipoPatente()<<endl; //TIPO PATENTE
			archivo1<<"VALOR PATENTE (utm): "<<Cola.front().getValorPatente()<<endl; //VALOR PATENTE
			cont++;
			Cola.front().setFueProcesado(true);
		}
		ColaAux.push(Cola.front());// guarda los datos en una cola auxiliar
		Cola.pop();
	}
	archivo1.close();
	
	while(!ColaAux.empty()){ // pasa los datos de la cola auxiliar a la cola original
		Cola.push(ColaAux.front());
		ColaAux.pop();
	}
	
	cout<<"\n\t***Se han procesado exitosamente las ultimas "<<cont<<" patentes.***"<<endl;
	cout<<"\t   Y se han registrado en el archivo --> procesar.txt <--"<<endl;
}
