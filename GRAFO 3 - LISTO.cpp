#include <iostream>
#include <vector>
#include <utility>
#include <conio.h>
using namespace std;

void crearGrafo(){
	volver:
	//DECLARACIONES
	int aristas=0, vertices=0, fir, sec; //VAR REGULAREs
	int limite, cont=0, flag1=0, flag2=0; //BANDERAS
	int indice=0, index=0, i=0, j=0; //CONTADORES
	bool  validation = false, tree = false;
	vector< pair<int,int> > vert;
	//FIN - DECLARACIONES
	
	
	cout<<"Cantidad de vertices del grafo : ";cin>>vertices;
	cout<<endl<<endl;
	int arrayV[vertices];
	int arrayV2[vertices];
	limite = vertices * (vertices - 1)/2;//CANTIDAD MAXIMA DE ARISTAS PERMITIDAS
	do{
		cout<<"Cantidad de aristas en el grafo: ";cin>>aristas;
		if(aristas > limite){
			cout<<"\n\nCantidad de aristas mayor a la permitida"<<endl<<endl;
			getch();
			system("cls");
		}else if(aristas == vertices - 1) tree = true; //VALIDACION DE ARBOL
	}while(aristas > limite);
	
	if(aristas == limite){
		cout<<endl<<endl;
		cout<<"\tEl grafo introducido es completo, por definicion no es bipartito. "<<endl<<endl
				<<"Ya que un grafo bipartito debe poder separarse en dos conjuntos de "<<endl
				<<"vertices que no tengan incidencia entre ellos. "<<endl<<endl;
				getch();
				return;
	}
	
	cout<<"\n\n"<<endl;
	
	while(i<aristas){
		
		do{
			system("cls");
			cout<<"\tArista #"<<i+1<<endl<<endl;
			cout<<"Origen : ";cin>>fir;
			cout<<"Destino: ";cin>>sec;	
			
			if(fir == sec){ //VALIDACION QUE NO POSEA LAZOS
				cout<<"No pueden existir lazos en un grafo simple."<<endl;
				getch();
				validation = true;
			}else if((fir <= 0 || sec <= 0) || (fir > vertices || sec > vertices)){ //PARA QUE SEA NEGATIVO
				cout<<"Uno de los vertices es menor o igual a 0, o excede el limite de vertices insertados...!"<<endl;
				validation = true;
				getch();	
			}else	validation = false;
			
			if(i>=1){ // VALIDA LUEGO DE LA SEGUNDA VUELTA (PARA QUE EXISTA AL MENOS UN PAR PARA COMPARAR)
				index = 0;
				while(index<vert.size()){// VALIDACION DE QUE EXISTA YA UNA ARISTA ENTRE DICHOS VERTICES
					if((vert[index].first==fir && vert[index].second==sec) || (vert[index].second==fir && vert[index].first==sec)){
						validation = true;
						cout<<"Existe ya una arista entre dichos vertices. Debe ser un grafo simple."<<endl<<endl;
						getch();
					}
					index++;
				}
			}
		}while(validation);
		
		//Arreglo con cada uno de los vertices
		
		if(i>=1){
			flag1 = 0;
			flag2 = 0;
			for(index = 0; index < vertices; index++){
				if(fir==arrayV[index])	flag1++;
				if(sec==arrayV[index])	flag2++;
			}	
		}
		if(flag1 == 0){
			arrayV[indice] = fir;
			indice = indice + 1;
		}
		if(flag2 == 0){
			arrayV[indice] = sec;
			indice = indice + 1;
		}
		// END - Arreglo con cada uno de los vertices	
	
		if(i == aristas - 1){
			for(int index=0; index < vertices; index++) arrayV2[index] = index + 1;
			
			for(int index=0; index < vertices; index++){
				for(int j=0; j < vertices; j++){
					if(arrayV2[index] == arrayV[j]) cont++;
				}
			}
			if(cont != vertices) {
				cout<<"Un grafo bipartito no debe poseer vertices aislados. Ya que por definición cada vertice del grupo V1 "<<endl
				 		<<"Debe tener relacion al menos con un vertice del grupo V2.  |--- Repita el proceso de registro ---| "<<endl<<endl;
				getch();
				system("cls");
				goto volver;	
			}
		}
	
		vert.push_back(make_pair(fir, sec));
		i++;
	}
	
	cout<<"\n\n"<<endl;
	cout<<"LISTA DE ARISTAS: "<<endl; //MOSTRAR LISTA DE ARISTAS POR PARES
	for(index = 0; index < vert.size(); index++){
		cout<<"( "<<vert[index].first<<", "<<vert[index].second<<" ) ";
	}
	cout<<"\n"<<endl<<endl;
	cout<<"LISTA DE VERTICES: "; //MOSTRAR LISTA DE VERTICES
	for(index = 0; index < vertices; index++){
		cout<<"[ "<<arrayV[index]<<" ] ";
	}	      
	 
	getch();
	cout<<"\n"<<endl<<endl;
	
	//____________________________________________
	//-------------BIPARTITO O NO----------------|
	//___________________________________________|
	
	if(aristas != limite){
		index = 0;
		vector< int >asd;//CAMBIAR NOMBRE A ADY
		int visited[vertices]; // Arreglo de nodos visitados... 1. para visitado  2. para no visitado
		int colors[vertices]; // 1. para blanco ... 0. para negro
		bool bipartito = true;
		int primero, aux;
		
		//Inicializar arreglo booleano en falso.
		//Todas las posiciones sean tanto "no visitados" como de color negro.
		for(indice = 0; indice < vertices; indice++){
			visited[indice] = false;
			colors[indice] = false;
		}	
		
		//Se agrega el primer valor del primer par ordenado del vector VERT.
		asd.push_back(vert[0].first);
		primero = asd[0] - 1;
		visited[primero] = true;//Este se marca como visitado.
		colors[primero] = true;//Como también de color blanco == true;
		
		while(!asd.empty()){  // 1............BLANCO                 0.................NEGRO
			aux = asd.front();
			cout<<"|------------------------------------|"<<endl;
			cout<<"\tValor de AUX = "<< aux <<" "<<endl;
			cout<<"\tTamaño antes de agregar: "<<asd.size()<<endl;
			for(index = 0; index < asd.size(); index++){
				cout<<"\t#"<<index<<" = "<<asd[index]<<endl;
			}		
			for(index = 0; index < vert.size(); index++){
				if(vert[index].first == aux && !visited[vert[index].second - 1]){ //SI EL PRIMER VALOR ES IGUAL A AUX Y EL SEGUNDO NO ESTA VISITADO.
																																								
					asd.push_back(vert[index].second);//SE AGREGA EL SEGUNDO DEL PAR AL VECTOR ASD
					int pos2 = vert[index].second - 1;//INSTANCIA DE VALOR DE VERTOR COMO INDICE
					
					visited[pos2] = true;//EL MISMO SE MARCA COMO VISITADO
					
					//SE VERIFICA EL COLOR DEL PRIMER VALOR ENCONTRADO PARA PINTAR EL SEGUNDO 	
					if(colors[aux - 1]){//SI ES BLANCO
						colors[pos2] = false;} //PINTO NEGRO
					else if(!colors[aux - 1]){//SI ES NEGRO
						colors[pos2] = true;} //PINTO BLANCO
								
				}
				if(vert[index].second == aux && !visited[vert[index].first - 1]){	//SI EL SEGUNDO VALOR ES IGUAL A AUX Y EL PRIMERO NO ESTA VISITADO.
				
					asd.push_back(vert[index].first);//SE AGREGA EL PRIMERO DEL PAR AL VECTOR ASD
					int pos1 = vert[index].first - 1;//INSTANCIACION DE VALOR DEL VECTOR COMO INDICE
					visited[pos1] = true;//EL MISMO SE MARCA COMO VISITADO
					
					//SE VERIFICA EL COLOR DE SEGUNDO VALOR ENCONTRADO PARA PINTAR EL PRIMERO
					if(colors[aux - 1]){//SI ES BLANCO
						colors[pos1] = false;} //PINTO NEGRO
					else if(!colors[aux - 1]){//SI ES NEGRO
						colors[pos1] = true;} //PINTO BLANCO
				
				}
			}
			
			cout<<"\n"<<endl;
			cout<<"\tTamaño luego de agregar: "<<asd.size()<<endl;
			for(index = 0; index < asd.size(); index++){
				cout<<"\t#"<<index<<" = "<<asd[index]<<endl;
			}
			asd.erase(asd.begin());
			cout<<"\n\tLuego de borrar: "<<endl;
			for(index = 0; index < asd.size(); index++){
				cout<<"\t#"<<index<<" = "<<asd[index]<<endl;
			}
			
			//-----------------------SALTO DE COMPONENTE
			if(asd.empty()){//Si el vector ASD esta vacio. 
				for(index = 0; index < vertices; index++){	
					if(visited[index] == false){//Si en el arreglo VISITED se encuentra algun vector no visitado
						asd.push_back(index + 1);//Agrega dicho vector al arreglo ASD
						visited[index] = true;//Marca el mismo como visitado
						break;//Rompe for
					}	
				}
			}
			cout<<"|------------------------------------|"<<endl;getch();
		}
		cout<<"\n"<<endl<<endl;
	
		cout<<"COLORES DE CADA VERTICE: "<<endl<<endl;//
		cout<<"1. BLANCO "<<endl
				<<"0. NEGRO "<<endl<<endl;
		for(index = 0; index < vertices; index++){
			cout<<"Vertice #"<<index + 1<<"= "<<colors[index]<<" --> ";
			if(colors[index]) cout<<"BLANCO "<<endl; 
			else cout<<"NEGRO "<<endl;
		}		
		cout<<endl;
	
		for(index = 0; index < vert.size();index++){//PARA IMPRIMIR LA ARISTA QUE POSEE VERTICES DEL MISMO COLOR, EN CASO DE QUE EXISTA. 		
			if(colors[vert[index].first - 1] == colors[vert[index].second - 1]){
				cout<<"El par de vertices ("<<vert[index].first<<", "<<vert[index].second<<") son de color: ";
				
				if(colors[vert[index].first - 1] && colors[vert[index].second - 1]) cout<<"BLANCO"<<endl;
				if(!colors[vert[index].first - 1] && !colors[vert[index].second - 1]) cout<<"NEGRO"<<endl<<endl<<endl;
				
				bipartito = false;	
			}
		}
		cout<<endl<<endl;

		if(bipartito){
			
			cout<<"V1:{ ";
			for(index = 0; index < vertices; index++){
				if(colors[arrayV[index] - 1]) cout<< arrayV[index] <<" ";			
			}cout<<"}"<<endl<<endl;
		
			cout<<"V2:{ ";
			for(index = 0; index < vertices; index++){
				if(!colors[arrayV[index] - 1]) cout<< arrayV[index] <<" ";			
			}cout<<"}"<<endl<<endl;
			
			
			if(tree)	cout<<"El grafo es un arbol.."<<endl<<endl;
			cout<<"\n\tEl grafo si es bipartito ya que por metodo de busqueda de anchura"<<endl
					<<"se comprueba es colorable con dos colores.."<<endl<<endl;
		}else{
			cout<<"El grafo introducido no es bipartito, ya que hay dos vertices que inciden entre ellos que son del mismo color."<<endl; 
		}
		
		getch();
	}else	cout<<"\n\tEl grafo ingresado es completo, por definicion, no es bipartito.. "<<endl<<endl;
		
	/*for(indice = 0; indice < vertices; indice++){
		cout<<"#"<<indice<<"= "<<visited[indice]<<endl;
	}*/
}

int main(){
	cout<<"\t\tTeoria de Grafos"<<endl<<endl;
	cout<<"\tEjercicio 3: GRAFOS BIPARTITOS"<<endl<<endl;
	crearGrafo();
	return 0;
}
