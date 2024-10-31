#include <iostream>
#include <fstream> //Para abrir y leer archivos
#include <time.h> //Si vas a usar rand es necesario asignarle una semilla con time.h para no repetir valores al ejecutar otra vez
#include <stdlib.h> 
#include <math.h> //para usar la funcion pow(x,y) que devuelve x^y
using namespace std;

struct Node{
	double base;
	int potencia;
	Node* next;
};
//Basicamente declaramos una lista vacia
Node* head=NULL;
Node* tail=NULL;

void enqueue(double x, int y){ //Funcion para insertar datos (crea nodos) 
	Node* nuevo=new Node();
	nuevo->base=x;
	nuevo->potencia=y;
	nuevo->next=NULL;
	if(head==NULL){ 
		//Si no hay cabeza la cola esta vacia, nuevo se convierte en head y en tail
		head=nuevo;
		tail=nuevo;
	} else{
		//La cola anterior apunta al nuevo nodo para enlazarse
		//El nuevo nodo pasa a ser la cola 
		tail->next=nuevo;
		tail=nuevo;
	}
}

void show(){
	cout<<"Datos guardados en la cola, con el primer elemento elevado al segundo a un lado: "<<endl;
	Node*ptr=head;
	while(ptr!=NULL){ //Se itera hasta que pase la "tail"
		cout<<ptr->base<<"; "<<ptr->potencia<<"; "<<pow(ptr->base, ptr->potencia)<<endl; 
		ptr=ptr->next;
	}
}

double agregarx(){
	int intx=(rand()% 298)+ 2; //Se genera un numero entero del 2 al 300
	// Al entero lo multiplicamos por 1 con 3 decimales y le sumamos un numero del 1 al 999 dividido 1000.000
	double realx=intx*1.000 + ((rand()%998)+1)/1000.000; 
	return realx;
	//Si el tercer decimal es 0 entonces el numero solo toma dos decimales,
	//Intentar que funcione tal como esta fue un cancer, es un error que ocurre 100 de cada 999 veces entonces medio bien, cosa de suerte ig
	//IDE de mierda antiguo y bugeado lo odio ojala se muera el que lo hizo
}

int main(){
	srand(time(NULL));
	
	//Parte 1: crear y llenar un archivo con dos cosas: 
	//Un x con 3 decimales del 2 al 300
	//Un y entero del 2 al 50
	ofstream archivoEscritura("poten.dat");
	if(!archivoEscritura){
		cout<<"Error al generar archivo";
		return 0;
	}
	for(int i=0; i<50;i++){
		double x=agregarx();
		int y=(rand()%48)+2;
		archivoEscritura<<x<<" "<<y<<endl;
	} 
	archivoEscritura.close();
	 
	//Declaramos x e y nuevamente (x debe ser de tipo double para tener los decimales)
	double x;
	int y;
	//Paso 2: llenar una cola con los registros del archivo
	ifstream archivoLectura("poten.dat");
	if(!archivoLectura){
		cout<<"Error al abrir el archivo";
		return 0;
	}
	//Este while verifica si en cada registro existen dos numeros entre espacios en blanco
	//Cuando apunte a un registro vacio se rompe el ciclo 
	while(archivoLectura>>x>>y){
		//en cada cilo x e y cambian de acuerdo a los valores del registro
		//No tengo ni puta idea de porque es asi, pero funciona
		enqueue(x, y); 
	} 
	archivoLectura.close();
	
	//Paso 3: imprimir la cola (mira la definicion de la funcion asociada)
	show();
	
	return 0;
}
