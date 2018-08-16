
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <conio.h>
#include <windows.h>
#include <locale.h>
using namespace std;

///// Función para maximizar pantalla
void AltEnter(){
	keybd_event(VK_LWIN,0x38,0,0);
	keybd_event(VK_UP,0x1c,0,0);
	keybd_event(VK_LWIN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_UP,0x38,KEYEVENTF_KEYUP,0);
	return;
}

void membrete(){
	cout<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl
			<<"::                                                                                                ::"<<endl
			<<":: Ing. de Sistemas                                                          INTEGRANTES:         ::"<<endl
			<<":: 5to semestre                               GRAFO 13            - Chirinos, Enmanuel 26.058.259 ::"<<endl
			<<":: Sección \"A\"                                                    - Petit, Anyelo      26.057.580 ::"<<endl
			<<"::                                                                - Vargas, Paola      25.723.540 ::"<<endl
			<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl<<endl;
}

// añadir vértice
int addnode(int &v){
	cout<<"\n Vértices que contendrá el nuevo grafo: ";cin>>v;
	return v;
}

// grafo
void grafo13(){
	int op, v=0, q=0, e[99][99], impares=0, val[99], vi[99], vf[99], vio[99], vfo[99];
  int aislados=0, repite=0, repitemas=0, impar1=0, impar2=0, o=0, condiciones=0, cumple=0;
  set<int> k;
	vector<int> inc;
	char saludo[] = "\n ¡ B I E N V E N I D O / A ! \n";
	bool saludado=false;
	
	comienzo:
		system("cls");
		membrete();
		for(int i=0;saludo[i]!='\0'&&saludado==false;i++){
  		cout<<saludo[i];
  		Sleep(30); 
  	} 
  	saludado=true;
		addnode(v);
	
	do{
	  int aux2=0;
    int av[v];// DECLARACION DE ARREGLO DE VÉRTICES
		int visited[q], ordenada[q], aux; // Aux es el current node mientras se recorre el vértice
		set<int> vr; // vértices recorridos
    bool allvisited=false;
		system("cls");
		membrete();
		cout<<" 1. Añadir arista."<<endl
				<<" 2. Ver matriz adyacencia (de valencias)."<<endl
				<<" 3. Ver lista de aristas."<<endl
				<<" 4. Verificar si existe un circuito o recorrido euleriano."<<endl
        <<" 5. Eliminar grafo."<<endl<<endl
				<<" 0. Salir."<<endl<<endl
				<<" Vértices= "<<v<<" Aristas= "<<q<<": "; // Cantidad de vértices (v) y aristas (q) en el grafo
				for(int i=0;i<q;i++){
				  cout<<"("<<vi[i]<<","<<vf[i]<<") ";
        }
    cout<<endl<<endl 
				<<"    Opción: ";
		cin>>op;
		cout<<endl;
		
		switch (op){
	
			case 1: int v1, v2;
				if (v==0){
					 cout<<"\n ERROR: DEBE EXISTIR AL MENOS UN VÉRTICE PAR CREAR UNA ARISTA";
					 getch();
					 break;
				}
				else if (v==1){
					cout<<" ¿Desea crear un bucle en este único vértice? 1=Si 2=No: ";
					int opc;
					cin>>opc;
					if (opc==1){
						e[0][0]+=2; // el vértice 1 pasaría a tener valencia 2 por el lazo
						vi[0]=1; // el vértice inicial de la arista es 1
						vf[0]=1; // el vértice final de la arista también es 1
						q++; // se le suma 1 a la cantidad total de aristas
						// la arista e en la posicion i=1 y j=1 ahora es 2
					}
					break;
				}
				do{
					cout<<" Primer vértice que desee conectar: ";
					cin>>v1;
					vi[q]=v1;
					if (v1>v||v1<=0) cout<<" ERROR: EL VÉRTICE NO SE ENCUENTRA EN EL GRAFO\a"<<endl;
				}while(v1>v||v1<=0);
				do{
					cout<<" Segundo vértice que desee conectar: ";
					cin>>v2;
					vf[q]=v2;
					if (v2>v||v2<=0) cout<<" ERROR: EL VÉRTICE NO SE ENCUENTRA EN EL GRAFO\a"<<endl;
				}while(v2>v||v2<=0);
				if (v1==v2){
					cout<<" ¿Desea crear un bucle en este vértice? 1=Si 2=No: ";
					int opc;
					cin>>opc;
					if (opc==1){
						e[v1-1][v1-1]+=2; // se crea un lazo en el índice que indicó el usuario -1
						vi[q]=v1; // se agrega i como vértice inicial en la posición q
						vf[q]=v1; // se agrega j como vértice final en la posición q
						q++;
					}
					break;
				}
				e[v1-1][v2-1]+=1; // se le suma la arista al valor ixj y al jxi porque es no-dirigido
				e[v2-1][v1-1]+=1; // al ser un grafo no-dirigido la matriz adyacencia es simétrica
				vi[q]=v1; // se agrega i como vértice inicial en la posición q
				vf[q]=v2; // se agrega j como vértice final en la posición q
				q++;
        break;
			
			case 2: 
				// se muestra la fila de arriba E 1 2 3 ... N
				if (v==0){
				  cout<<" ERROR: *** MATRIZ VACÍA *** NO EXISTEN VÉRTICES EN EL GRAFO.";
				  getch();
				  break;
        }
				cout<<" E ";
				for(int i=0; i<v; i++){
					cout<<i+1<<" ";
				}
				cout<<endl;
				// se muestra cada fila con sus valores y su índice 1\n 2\n 3\n... N\n
				for(int j=0; j<v; j++){
				  cout<<" "<<j+1<<" ";
					for(int i=0; i<v; i++){
						cout<<e[i][j]<<" ";
					}
					cout<<endl;
				}
				getch();
				break;
				
			case 3:
			  if (q==0){
			    cout<<" ERROR: *** LISTA VACÍA *** NO EXISTEN ARISTAS EN EL GRAFO";
			    getch();
			    break;
        }
        cout<<"\n LISTA DE ARISTAS:"<<endl;
			  for(int i=0; i<q; i++){
			    cout<<" "<<i+1<<": ("<<vi[i]<<","<<vf[i]<<")"<<endl;
        }
        getch();
			  break;
			
			case 4:
        
				// Inicialización del arreglo de visitado
				for(int i=0; i<q; ++i){
				  visited[i]=false; // Ninguna arista visitada
				  ordenada[i]=false; // Ninguna arista ordenada
        }
        
        for(int i=0; i<v; ++i){
          av[i]=i+1; //LLENADO DEL ARRAY DE VÉRTICES 
        }
        
        if(v==0){
          cout<<"\n ERROR: NO EXISTEN VÉRTICES EN EL GRAFO. INGRESE VÉRTICES ANTES DE VERIFICAR."<<endl;
          getch();
          break;
        }
        else if(q==0){
          cout<<"\n No existen aristas en el grafo, por lo tanto es no-conexo con "<<v<<" componentes."<<endl;
  	   		cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
  	   		getch();
  	   		break;
        }
        
  			// Verificar si el grafo es conexo
				k.insert(vi[0]);
				k.insert(vf[0]);
  			for(int j=0; j<q; j++){
    			for(int i=0; i<q; i++){
    				if (k.count(vi[i])>0) k.insert(vf[i]);
    				if (k.count(vf[i])>0) k.insert(vi[i]);
          }
        }
				
        if (k.size()!=v){
          cout<<"\n Existe más de un componente en el grafo, por lo tanto es no-conexo."<<endl;
          cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
          getch();
          break;
        } 
        impares=0;
        aislados=0;
        for(int i=0;i<v;++i) val[i]=0; // Se inicializan todas las valencias en 0
        
				for(int j=0;j<v;++j){
					for(int i=0;i<v;++i){
						val[j]+=e[i][j];
					}
					if (val[j]==0){
					  aislados++;
          }
					if (val[j]%2!=0){
						impares++;
						if(impar1==0) impar1=av[j];
						else if(impar2==0) impar2=av[j];
					}
					//cout<<" val("<<j+1<<")="<<val[j]<<" impares="<<impares<<" aislados="<<aislados<<endl;
				}
				if (aislados>0){
				  cout<<"\n Existen "<<aislados<<" vértices aislados en el grafo, por lo tanto es no-conexo."<<endl;
				  cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
        }
				else if ((impares==0&&aislados==0)||(impares==2&&aislados==0)){ // Si cumple con circuito o recorrido
				  if (impares==0&&aislados==0){ // Circuito
  				  cout<<"\n Todos los vértices son de grado PAR. \n\n ***** EXISTE UN CIRCUITO EULERIANO. *****"<<endl
  				      <<"\n El circuito euleriano podría ser: "<<endl<<endl;
  				  aux=av[0];
          }
          else if (impares==2&&aislados==0){ // Recorrido
            cout<<"\n Existen exactamente dos vértices de valencia IMPAR."<<endl
                <<"\n ***** EXISTE UN RECORRIDO EULERIANO *****"// impar1="<<impar1<<" impar2="<<impar2<<endl
                <<"\n El recorrido euleriano podría ser: "<<endl<<endl;
              // Se asigna un vértice de grado impar como auxiliar
  				  aux=impar1;
          }
          vr.insert(aux);
          cout<<" "<<aux; // Se muestra el primer vértice del recorrido
				  
          for (int i=1; i<=v; i++){
            //cout<<"bucle"<<i;
            for (int j=0; j<q; j++){
              if (vi[j]==i&&!ordenada[j]){
                vio[o]=vi[j];
                vfo[o]=vf[j];
                o++;
                ordenada[j]=true;
              }
              else if (vf[j]==i&&!ordenada[j]){
                vio[o]=vf[j];
                vfo[o]=vi[j];
                o++;
                ordenada[j]=true;
              }
            }
          }
          
          /*for(int i=0;i<q;i++){
            cout<<"\n vio["<<i<<"]="<<vio[i];
            cout<<" vfo["<<i<<"]="<<vfo[i];
          }*/
          //Circuito y recorrido
          while(allvisited==false){
            //cout<<"paso1";
            aux2=0;
            repite=0;
            repitemas=0;
            //cout<<"paso2";
            inc.erase (inc.begin(),inc.begin()+inc.size());
					  for(int i=0;i<q;i++){
    					if(aux==vio[i]&&visited[i]==false){ // si aux es el vértice inicial de una arista no visitada
    					  inc.push_back(vfo[i]);
              }
    					else if(aux==vfo[i]&&visited[i]==false){ // si aux es el vértice final de una arista no visitada
    					  inc.push_back(vio[i]);
              }
    				}
            //cout<<"paso3";
    				//cout<<endl<<" inc=";for(int i=0;i<inc.size();i++) cout<<inc[i];
    				for(int i=0;i<inc.size();i++){
    				  for(int j=0;j<inc.size();j++){
    				    if(inc[i]==inc[j]) repite++;
              }
              if (repite>repitemas){
                for(int c=0;c<inc.size();c++){
                  if (vr.count(inc[c])==0){
                    cumple++;
                  }
                  if(val[aux-1]==1||(val[aux-1]>1&&val[inc[c]-1]>1)){
                    cumple++;
                  }
                  if (cumple>condiciones){
                    condiciones=cumple;
                    aux2=inc[c];
                    repitemas=repite;
                  }
                  cumple=0;
                }
                condiciones=0;
              } 
              repite=0;
            }
            //cout<<" aux="<<aux<<" aux2="<<aux2<<endl;
					  for(int l=0;l<q;l++){ // verifica si alguna de las aristas es un lazo de aux
					    if((aux==vio[l]&&aux==vfo[l])&&visited[l]==false){ // si aux posee un lazo no visitado
					      cout<<" - "<<aux;
                val[aux-1]-=2; // se le restan 2 valencias del lazo
					      visited[l]=true;
					      vr.insert(aux);
              }
            }
					  for(int j=0;j<=q;j++){
					    if((aux==vio[j]&&aux2==vfo[j])&&(visited[j]==false)){ // si aux es igual al vértice inicial de una arista no visitada
					      if((val[aux-1]==1) 
					      ||(val[aux-1]>1&&val[aux2-1]>1)){ // si los vértices de la arista tienen valencia > 
					        //cout<<" 1cumple condicion"<<endl;
                  val[aux-1]--; // se le resta una valencia al vértice
                  aux=aux2;
                  val[aux-1]--;
                  cout<<" - "<<aux;
                  visited[j]=true;
					        vr.insert(aux);
                }
                //else cout<<" 1no entra"<<endl;
              }
              
              else if((aux==vfo[j]&&aux2==vio[j])&&(visited[j]==false)){ // si aux es igual al vértice final de una arista no visitada
					      if((val[aux-1]==1) 
					      ||(val[aux-1]>1&&val[aux2-1]>1)){ // si los vértices de la arista tienen valencia >
					        //cout<<" 2cumple condicion"<<endl;
                  val[aux-1]--; // se le resta una valencia al vértice
                  aux=aux2;
                  val[aux-1]--;
                  cout<<" - "<<aux;
                  visited[j]=true;
                  vr.insert(aux);
                }
                //else cout<<" 2no entra"<<endl;
              }
            }
            int suma=0, grad=0;
            for(int i=0;i<q;++i) suma+=visited[i];
            for(int j=0;j<v;++j) grad+=val[j];
            if(suma==q&&grad==0) allvisited=true;
            //cout<<" suma="<<suma<<" grad="<<grad;
          }
        }
				else {
	   		  if (impares==1) 
   		      cout<<"\n Sólo un vértice es de valencia impar. "<<endl;
					else if (impares>2) 
  		 		  cout<<"\n Existen más de dos vértices de grado impar."<<endl;
				  cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
				}
				getch();
				//////////////////// SE DETIENE EL PROGRAMA
				break;
 			
 			case 5: 
  		  for(int j=0;j<v;++j){
  				for(int i=0;i<v;++i){
  					e[i][j]=0;
  				}
  				vi[j]=0;
          vf[j]=0;
  			}
  			v=0, q=0;
  			goto comienzo;
        break;
				
			case 0: break;					
			
			default:
				cout<<" ERROR: INGRESE UNA OPCIÓN VÁLIDA\a";
				getch();
				break;
		}
	}while(op!=0);
}

int main(){
	setlocale(LC_CTYPE, "Spanish");
	system("color 00");
	AltEnter();
	char despedida[] = " Hasta luego... ¡Vuelva pronto!";
	
	grafo13();
	
	for(int i=0;despedida[i]!='\0';i++){
		cout<<despedida[i];
		Sleep(30); 
	}  
}
