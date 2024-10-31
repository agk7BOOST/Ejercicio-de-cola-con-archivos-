#include <iostream> 
#include <stdlib.h> //Para usar rand
#include <time.h> // Para cargar la semilla con time(NULL)
#include <string> //Para iterar cifras de numeros
#include <fstream> //leer y escribir en archivos externos
using namespace std;
struct Node{
	int dato;
	Node* next= NULL;
};
Node* cabeza=NULL;  //Esto sirve para tener una cola vacia, util para las funciones asociadas a la misma
Node* cola=NULL;
//Crear funciones para:
//Revisar si esta vacio
//agregar a la cola (enqueue) 
//quitar de la cola (dequeue)
//mostrar los valores (show)
//cargar los valores en un archivo (cargar_archivo) 
//Funciones para contar digitos pares e impares
bool isempty(){ //Revisa si esta vacio 
	if(cabeza==NULL and cola==NULL){
		return true;
	} else {
		return false;
	}
} 
void enqueue(int data){ //Funcion para insertar datos (crea nodos) 
	Node* ptr= new Node();
	ptr->dato=data;
	ptr->next=NULL;
	if(cabeza==NULL){//Si la lista esta vacia, el nuevo nodo se vuelve la cabeza y la cola de la lista
		cabeza=ptr; 
		cola=ptr;
	} else {
		cola->next=ptr; //El link de la cola actual de la lista pasa a señalar al nuevo nodo
		cola=ptr; //El nuevo nodo se vuelve la nueva cola de la lista
	}
}
void dequeue(){
	if(isempty()){
		cout<<"La cola esta vacia";
	} else if(cabeza==cola){ //En caso de que solo exista un nodo en la lista
		delete cabeza; //cabeza apunta a la misma direccion que cola, entonces solo hay que eliminar cabeza para liberar memoria
		cabeza==NULL;
		cola==NULL;
	} else { 
		Node* ptr= cabeza; //En este puntero auxiliar guardamos la cabeza para luego poder liberarla
		cabeza=cabeza->next; // La cabeza pasa a ser el que le sigue a nuestra cabeza a sacar
		delete ptr; //Se libera la cabeza anterior
	}
	}

void show(){
	if(isempty()){
		cout<<"La cola esta vacia"<<endl;
	} else{
		Node* ptr=cabeza;
		while(ptr->next!=NULL){
			cout<<ptr->dato<<endl;
			ptr=ptr->next;
		}
	}
}
int digitospares(int num){
	int c=0; 
	int i;
	char cifras[5]; //4 cifras mas el terminador nulo (el quinto elemento no va tener nada entonces se desprecia en el bucle)
	sprintf(cifras, "%d", num); //convierte num a una cadena de caracteres que se carga a cifras
	for(i=0; i<4; i++){
		int digito=cifras[i] - '0'; //Convierte la cifra (caracter) a entero
		if(digito % 2==0 and digito!=0){
			c++;
		}
	}
	return c;
}
int digitosimpares(int num){
	int c=0;
	int i;
	char cifras[5];
	sprintf(cifras, "%d", num);
	for(i=0; i<4; i++){
		int digito= cifras[i] - '0';
		if(digito % 2!=0 and digito!=0){
			c++;
		}
	}
	if(c==3){
		enqueue(num);
	}
	return c;
}
void cargar_archivo(){
	ofstream archivo("colaprimos.txt"); //declaramos un objeto ofstream (fichero de solo escritura)
	Node* ptr=cabeza; //Puntero auxiliar a la cabeza de la queue
	while(ptr->next!=NULL){
		archivo << ptr->dato<<endl;
		ptr=ptr->next;
	}
	archivo.close();
	cout<<"Los elementos de la cola fueron cargados a colaprimos.txt, revisar";
}
int main(){
	int i;
	int aux;
	//Definimos un minimo y maximo del numero para que todos tengan 4 cifras
	int minimo=1000;
	int maximo=9999;
	srand(time(NULL)); //cargamos la semilla con time
	for(i=0; i<50; i++){
		aux=(rand()%(maximo - minimo + 1) ) + minimo; //Genera un numero dentro de un rango, usando la formula de rand
		cout<<aux<<endl;
		cout<<"El numero tiene "<<digitospares(aux)<<" cifras pares y "<<digitosimpares(aux)<<" cifras impares"<<endl;
	}
	cout<<"A continuacion vamos a ver todos los elementos con 3 cifras impares cargados en la cola: "<<endl;
	show();
	cargar_archivo();
	return 0;
}
