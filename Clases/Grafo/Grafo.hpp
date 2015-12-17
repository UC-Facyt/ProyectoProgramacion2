#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>
#include "../NodoV/NodoV.hpp"
#include "../NodoA/NodoA.hpp"
#include "../Lista/Lista.hpp"
#include "../Cola/Cola.hpp"
#include "../Pila/Pila.hpp"

const bool verbose = true;

template <class T, class C = float>
class Grafo{
protected:
	NodoV<T,C> *g, *fin; //g es un apuntador al primer vertice, y fin al ultimo.
	int vertices, arcos; //numero de vertices y numero de arcos.

protected:
	//Metodos Auxiliares
	bool esEuleriano(T, Grafo<T,C>&) const;
	bool esHamiltoniano(int, bool*, Lista<int>&) const;
	NodoV<T,C>* agregarAlFinal(const T&);
	void eliminarTodosArcos(NodoV<T,C>*);
	void eliminarArcoDe(const T&, NodoV<T,C>*);
	void ubicarAmbos(const T&, const T&, NodoV<T,C>*&, NodoV<T,C>*&) const;
	NodoV<T,C>* ubicar(const T&) const;
	NodoV<T,C>* ubicarPorId(int) const;
	NodoA<T,C>* ubicar(NodoA<T,C>*, const T&) const;
	NodoA<T,C>* ubicarPorId(NodoA<T,C>*, int) const;
	void copiarVertices(const Grafo<T,C>&);
	void copiarArcos(const Grafo<T,C>&);
	int distanciaMin(Lista<int>&, int*) const;
	T* obtNombres() const;
	
public:
	//Constructores
	inline Grafo(): g(0), fin(0), vertices(0), arcos(0) {}
	inline Grafo(const Grafo<T,C> &g2): g(0), fin(0){ *this = g2; }
	
	//Observadores
	bool esEuleriano() const;
	bool esHamiltoniano() const;
	inline bool esVacio() const{ return(!g); }
	inline int orden() const{ return(vertices); }
	inline int nArcos() const{ return(arcos); }
	bool existeVertice(const T&) const;
	bool existeArco(const T&, const T&) const;
	C costoArco(const T&, const T&) const;
	C costoArcoPorId(int, int) const;
	bool esFuente(const T&) const;
	bool esSumidero(const T&) const;
	bool estaAislado(const T&) const;
	void mostrar(std::ostream&) const;
	inline void mostrar() const;
	inline T obtUltimo() const{ return(this->fin ? this->fin->obtInfo() : T()); }
	int gradoInterior(const T&) const;
	int gradoExterior(const T&) const;
	int grado(const T&) const;
	bool adyacentes(const T&, const T&) const;
	bool adyacentesPorId(const T&, const T&) const;
	Lista<T> listaVertices() const;
	Lista<T> sucesores(const T&) const;
	Lista<int> sucesoresPorId(int) const;
	Lista<T> predecesores(const T&) const;
	Lista<T> fuentes() const;
	Lista<T> sumideros() const;
	Lista<T> vecindad(const T&) const;
	Lista<T> camino(const T&, const T&) const;
	bool igual(const Grafo<T,C>&) const;
	bool obtMarca(const T&) const;
	int obtId(const T&) const;
	void BFS(int, int*, int*);
	void BFS(const T&);	
	void DFS();
	void DFS(int, int*, int*, int*, std::string*, int&);
	
	//Modificadores
	void agregarVertice(const T&);
	void agregarArco(const T&, const T&, const C& = 0);
	void agregarArcoNoDirigido(const T&, const T&, const C& = 0);
	void eliminarArco(const T&, const T&);
	void eliminarVertice(const T&);
	void nulo();
	void marcar(const T&);
	void desmarcar(const T&);
	void copiar(const Grafo<T,C>&);
	void modIds();
	
	//Operadores
	Grafo<T,C>& operator = (const Grafo<T,C>&);
	bool operator == (const Grafo<T,C>&);
	
	template <class t, class c>
	friend std::ostream& operator << (std::ostream&, const Lista<t>&);
	
	//Destructor
	~Grafo();
};


/***Constructores*/

/***Fin de Constructores*/


/**Observadores**/
template <class T, class C>
bool Grafo<T,C>::esEuleriano() const{
	Grafo<T,C> g2;
	Lista<T> l = this->listaVertices();
	T v;
	while(!l.esVacia()){
		g2 = *this;
		v = l.consultar(1);
		l.eliminar(1);
		if(esEuleriano(v, g2)){
			return(true);
		}
	}
	return(false);
}

template <class T, class C>
bool Grafo<T,C>::esEuleriano(T v, Grafo<T,C> &g2) const{
	Lista<T> verticesIngresar, s = g2.sucesores(v);
	T u;
	while(!s.esVacia()){
		u = s.consultar(1);
		s.eliminar(1);
		g2.eliminarArco(v, u);
		verticesIngresar.insertar(u, verticesIngresar.longitud() + 1);
		esEuleriano(u, g2);
	}
	if(g2.nArcos() == 0){
		return(true);
	}
	// while(!verticesIngresar.esVacia()){
	// 	g2.agregarArco(v, verticesIngresar.consultar(1));
	// 	verticesIngresar.eliminar(1);
	// }
	return(false);
}

template <class T, class C>
bool Grafo<T,C>::esHamiltoniano() const{
	Lista<T> l = listaVertices();
	Lista<int> recorrido;
	int v;
	bool *visitados = new bool[vertices];
	for(int i = 0; i < vertices; i++){
		visitados[i] = false;
	}
	while(!l.esVacia()){
		v = obtId(l.consultar(1));
		l.eliminar(1);
		if(esHamiltoniano(v, visitados, recorrido)){
			return(true);
		}
		recorrido.nulo();
	}
	return(false);
}

template <class T, class C>
bool Grafo<T,C>::esHamiltoniano(int v, bool *visitados, Lista<int> &recorrido) const{
	Lista<int> s = sucesoresPorId(v);
	int u, pos;
	recorrido.insertar(v, recorrido.longitud() + 1);
	pos = recorrido.longitud();
	visitados[v] = true;
	while(!s.esVacia()){
		u = s.consultar(1);
		s.eliminar(1);
		if(!visitados[u]){
			esHamiltoniano(u, visitados, recorrido);
		}
	}
	if(recorrido.longitud() == vertices){
		return(true);
	}
	recorrido.eliminar(pos);
	visitados[v] = false;
	return(false);
}

template <class T, class C>
bool Grafo<T,C>::existeVertice(const T &v) const{
	NodoV<T,C> *actV;
	actV = this->ubicar(v);
	return(actV ? true : false);
}

template <class T, class C>
bool Grafo<T,C>::existeArco(const T &v, const T &w) const{
	NodoV<T,C> *actV;
	NodoA<T,C> *actW;
	actV = this->ubicar(v);
	if(actV){
		actW = this->ubicar(actV->obtPri(), w);
		return(actW ? true : false);
	}else{
		return(false);
	}
}

template <class T, class C>
C Grafo<T,C>::costoArco(const T &v, const T &w) const{
	NodoV<T,C> *actV;
	NodoA<T,C> *actW;
	actV = this->ubicar(v);
	if(actV){
		actW = this->ubicar(actV->obtPri(), w);
		return(actW ? actW->obtCosto() : C());
	}else{
		return(C());
	}
}

template <class T, class C>
C Grafo<T,C>::costoArcoPorId(int v, int w) const{
	NodoV<T,C> *actV;
	NodoA<T,C> *actW;
	actV = this->ubicarPorId(v);
	if(actV){
		actW = this->ubicarPorId(actV->obtPri(), w);
		return(actW ? actW->obtCosto() : C());
	}else{
		return(C());
	}
}

template <class T, class C>
bool Grafo<T,C>::esFuente(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	bool flag = false;
	while(actV){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				return(false);
			}
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	return(flag);
}

template <class T, class C>
bool Grafo<T,C>::esSumidero(const T &v) const{
	NodoV<T,C> *actV;
	actV = this->ubicar(v);
	return(actV ? (actV->obtPri() ? false : true) : false);
}

template <class T, class C>
bool Grafo<T,C>::estaAislado(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	while(actV){
		actA = actV->obtPri();
		if(actV->obtInfo() == v){
			while(actA){
				if(actA->obtVert()->obtInfo() != v){
					return(false);
				}
				actA = actA->obtSig();
			}
		}else{
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					return(false);
				}
				actA = actA->obtSig();
			}
		}
		actV = actV->obtSig();
	}
	return(true);
}

template <class T, class C>
void Grafo<T,C>::mostrar(std::ostream &o) const{
	NodoV<T,C> *act = this->g;
	NodoA<T,C> *aux;
	Cola< NodoA<T,C>* > c1, c2;
	C costoAux;
	bool flag = false;
	std::cout << std::setfill(' ');	//setting fill character for output stream.
	while(act){
		std::cout << act->obtInfo() << "(" << act->obtId() << ")" << " ----> ";
		c1.encolar(act->obtPri());
		if(!flag){
			flag = act->obtPri() ? true : false;
		}
		act = act->obtSig();
	}
	std::cout << std::endl;
	while(flag){
		flag = false;
		while(!c1.esVacia()){
			aux = c1.frente();
			c1.desencolar();
			if(aux){
				costoAux = aux->obtCosto();
				std::cout << "|";
				if(costoAux != 0){
					std::cout << "(";
					std::cout << std::setw(6) << std::setprecision(2);
					std::cout << std::left << costoAux;
					std::cout << ")  ";
				}else{
					std::cout << std::setw(10) << std::setprecision(2);
					std::cout << " ";
				}
				flag = true;
			}else{
				std::cout << std::setw(11) << " ";
			}
			c2.encolar(aux);
		}
		std::cout << std::endl;
		while(!c2.esVacia() && flag){
			aux = c2.frente();
			c2.desencolar();
			if(aux){
				std::cout << std::setw(11) << std::setprecision(2);
				std:: cout << std::left;
				std::cout << aux->obtVert()->obtInfo();
				aux = aux->obtSig();
			}else{
				std::cout << std::setw(11) << " ";
			}
			c1.encolar(aux);
		}
		std::cout << std::endl;
	}
}

template <class T, class C>
inline void Grafo<T,C>::mostrar() const{
	this->mostrar(std::cout);
}

template <class T, class C>
int Grafo<T,C>::gradoInterior(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	int grado = 0;
	while(actV){		
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				grado++;
			}
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	return(grado);
}

template <class T, class C>
int Grafo<T,C>::gradoExterior(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	int grado = 0;
	actV = ubicar(v);
	if(actV){
		actA = actV->obtPri();
		while(actA){
			grado++;
			actA = actA->obtSig();
		}
	}
	return(grado);
}

template <class T, class C>
int Grafo<T,C>::grado(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	int grado = 0;
	while(actV){		
		actA = actV->obtPri();
		if(actV->obtInfo() == v){
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					grado++;
				}
				grado++;
				actA = actA->obtSig();
			}
		}else{
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					grado++;
				}
				actA = actA->obtSig();
			}
		}
		actV = actV->obtSig();
	}
	return(grado);
}

template <class T, class C>
bool Grafo<T,C>::adyacentes(const T &v, const T &w) const{
	NodoV<T,C> *actV, *actW;
	NodoA<T,C> *actA;
	ubicarAmbos(v, w, actV, actW);	
	if(actV && actW){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == w){
				return(true);
			}
			actA = actA->obtSig();
		}
		actA = actW->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){

				return(true);
			}
			actA = actA->obtSig();
		}
	}
	return(false);
}

template <class T, class C>
bool Grafo<T,C>::adyacentesPorId(const T &v, const T &w) const{
	NodoV<T,C> *actV, *actW;
	NodoA<T,C> *actA;
	ubicarAmbos(v, w, actV, actW);	
	if(actV && actW){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtId() == w){
				return(true);
			}
			actA = actA->obtSig();
		}
		actA = actW->obtPri();
		while(actA){
			if(actA->obtVert()->obtId() == v){
				return(true);
			}
			actA = actA->obtSig();
		}
	}
	return(false);
}

template <class T, class C>
Lista<T> Grafo<T,C>::listaVertices() const{
	NodoV<T,C> *act = this->g;
	Lista<T> l;
	while(act){
		l.insertar(act->obtInfo(), l.longitud() + 1);
		act = act->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::sucesores(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	actV = this->ubicar(v);
	if(actV){
		actA = actV->obtPri();
		while(actA){
			l.insertar(actA->obtVert()->obtInfo(), l.longitud() + 1);
			actA = actA->obtSig();
		}
	}
	return(l);
}

template <class T, class C>
Lista<int> Grafo<T,C>::sucesoresPorId(int v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<int> l;
	actV = this->ubicarPorId(v);
	if(actV){
		actA = actV->obtPri();
		while(actA){
			l.insertar(actA->obtVert()->obtId(), l.longitud() + 1);
			actA = actA->obtSig();
		}
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::predecesores(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	while(actV){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				l.insertar(actV->obtInfo(), l.longitud() + 1);
			}
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::fuentes() const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	while(actV){
		actA = actV->obtPri();
		while(actA){
			actA->obtVert()->marcar();
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	actV = this->g;
	while(actV){
		if(!actV->obtMarca()){
			l.insertar(actV->obtInfo(), l.longitud() + 1);
		}
		actV->desmarcar();
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::sumideros() const{
	NodoV<T,C> *actV = this->g;
	Lista<T> l;
	while(actV){
		if(!actV->obtPri()){
			l.insertar(actV->obtInfo(), l.longitud() + 1);
		}
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::vecindad(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	while(actV){
		actA = actV->obtPri();
		if(actV->obtInfo() == v){
			while(actA){
				l.insertar(actA->obtVert()->obtInfo(), l.longitud() + 1);
				actA = actA->obtSig();
			}
		}else{
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					l.insertar(actV->obtInfo(), l.longitud() + 1);
				}
				actA = actA->obtSig();
			}
		}
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::camino(const T &v, const T &w) const{
	Lista<int> q, sucesores;
	Lista<T> res;
	if(arcos == 0 || !existeVertice(v) || !existeVertice(w)){
		return(res);
	}
	bool flag;
	int u, k, vi, vf;
	T* nameArr = obtNombres();
	vi = obtId(v);
	vf = obtId(w);
	bool *visitados = new bool[vertices];
	int *distancia = new int[vertices];
	int *predecesor = new int[vertices];
	for(int i = 0; i < vertices; i++){
		visitados[i] = false;
		distancia[i] = std::numeric_limits<int>::max();
		predecesor[i] = -1;
		q.insertar(i , q.longitud() + 1);
	}
	distancia[vi] = 0;
	while(!q.esVacia()){
		u = distanciaMin(q, distancia);
		if(u == vf){
			while(true){
				res.insertar(nameArr[u], 1);
				if(u == vi){
					return(res);
				}
				u = predecesor[u];
			}
		}
		visitados[u] = true;
		flag = false;
		sucesores = this->sucesoresPorId(u);
		while(!sucesores.esVacia()){
			k = sucesores.consultar(1);
			sucesores.eliminar(1);
			if(!visitados[k] && distancia[u] + costoArcoPorId(u, k) < distancia[k]){
				distancia[k] = distancia[u] + (int)costoArcoPorId(u, k);
				predecesor[k] = u;
			}
			flag = true;
		}
		if(sucesores.esVacia() && !flag){
			return(res);
		}
	}
	//~ for(int i = 0; i < vertices; i++){
		//~ std::cout << "dist[ " << i+1 << "] = " << distancia[i] << std::endl;
	//~ }	
	//~ for(int i = 0; i < vertices; i++){
		//~ cout << "pred[ " << i+1 << "] = " << predecesor[i] << endl;
	//~ }
	delete[] nameArr;
	return(res);
}

template <class T, class C>
int Grafo<T,C>::distanciaMin(Lista<int> &l, int *dist) const{
	int tam = l.longitud();
	int min = 0, aux;
	int minVar = std::numeric_limits<int>::max();
	for(int i = 0; i < tam; i++){
		aux = l.consultar(i+1);
		if(dist[aux] < minVar){
			min = aux;
			minVar = dist[aux];
		}
	}
	l.eliminar(l.obtPos(min));
	return(min);
}

template <class T, class C>
bool Grafo<T,C>::igual(const Grafo<T,C> &g2) const{
	NodoV<T,C> *actV1, *actV2;
	NodoA<T,C> *actA1, *actA2;
	actV1 = this->g;
	actV2 = g2.g;
	while(actV1 && actV2){
		if(actV1->obtInfo() != actV2->obtInfo()){
			return(false);
		}
		actA1 = actV1->obtPri();
		actA2 = actV2->obtPri();
		while(actA1 && actA2){
			if(actA1->obtVert()->obtInfo() != actA2->obtVert()->obtInfo() ||
				actA1->obtCosto() != actA2->obtCosto()){
				return(false);
			}
			actA1 = actA1->obtSig();
			actA2 = actA2->obtSig();
		}
		if(actA1 || actA2){
			return(false);
		}
		actV1 = actV1->obtSig();
		actV2 = actV2->obtSig();
	}
	if(actV1 || actV2){
		return(false);
	}
	return(true);
}

template <class T, class C>
bool Grafo<T,C>::obtMarca(const T &v) const{
	NodoV<T,C> *actV = this->ubicar(v);
	return(actV ? actV->obtMarca() : false);
}

template <class T, class C>
int Grafo<T,C>::obtId(const T &v) const{
	NodoV<T,C> *actV = this->ubicar(v);
	return(actV->obtId());
}

template <class T, class C>
T* Grafo<T,C>::obtNombres() const{
	NodoV<T,C> *actV = g;
	T* arr = new T[vertices];
	int i = 0;
	while(actV){
		arr[i++] = actV->obtInfo();
		actV = actV->obtSig();
	}
	return arr;
}

template <class T, class C>
void Grafo<T,C>::BFS(int s, int *dist, int *pred){
	Lista<int> l;
	Cola<int> c;
	T* nameArr = obtNombres();
	std::string *color = new std::string[this->vertices];
	int u, v;
	for(int i = 0; i < this->vertices; i++){
		dist[i] = std::numeric_limits<int>::max();
		color[i] = "blanco";
		pred[i] = 0;
	}
	color[s] = "gris";
	dist[s] = 0;
	pred[s] = -1;
	c.encolar(s);
	while(!c.esVacia()){
		u = c.frente();
		c.desencolar();
		l = this->sucesoresPorId(u);
		while(!l.esVacia()){
			v = l.consultar(1);
			l.eliminar(1);
			if(color[v] == "blanco"){
				color[v] = "gris";
				dist[v] = dist[u] + 1;
				pred[v] = u;
				c.encolar(v);
			}
		}
		color[u] = "negro";
	}
	if(verbose){
		for(int i = 0; i < vertices; i++){
			std::cout << "dist[" << nameArr[i] << "] = " << dist[i] << std::endl;
			std::cout << "pred[" << nameArr[i] << "] = " << nameArr[pred[i]] << std::endl;
			std::cout << "color[" << nameArr[i] << "] = " << color[i] << std::endl;
			std::cout << "---------------------------" << std::endl;
		}
	}
	delete[] color;
	delete[] nameArr;
}

template <class T, class C>
void Grafo<T,C>::BFS(const T &v){
	int tam = this->vertices;
	if(tam > 0){
		modIds();
		int *dist = new int[tam];
		int *pred = new int[tam];
		BFS(obtId(v), dist, pred);
		delete[] dist;
		delete[] pred;
	}
}

template <class T, class C>
void Grafo<T,C>::DFS(){
	Lista<T> l = this->listaVertices();
	T s;
	T* nameArr = obtNombres();
	int v;
	std::string *color = new std::string[vertices];
	int *tdesc = new int[vertices];
	int *pred = new int[vertices];
	int *tfinal = new int[vertices];
	int tiempo = 0;
	for(int i = 0; i < vertices; i++){
		color[i] = "blanco";
		pred[i] = 0;
	}
	while(!l.esVacia()){
		s = l.consultar(1);
		l.eliminar(1);
		v = obtId(s);
		if(color[v] == "blanco"){
			this->DFS(v, pred, tdesc, tfinal, color, tiempo);
		}
	}
	if(verbose){
		for(int i = 0; i < vertices; i++){
			std::cout << "pred[" << nameArr[i] << "] = " << nameArr[pred[i]] << std::endl;
			std::cout << "tfinal[" << nameArr[i] << "] = " << tfinal[i] << std::endl;
			std::cout << "tdesc[" << nameArr[i] << "] = " << tdesc[i] << std::endl;
			std::cout << "color[" << nameArr[i] << "] = " << color[i] << std::endl;
			std::cout << "---------------------------" << std::endl;
		}
	}
	delete[] color;
	delete[] tdesc;
	delete[] pred;
	delete[] nameArr;
	delete[] tfinal;
}

//Se resta 1 a v para indice en vector de 0 hasta instancia.orden()-1
template <class T, class C>
void Grafo<T,C>::DFS(int v, int *pred, int *tdesc, int *tfinal, std::string *color, int &tiempo){
	Lista<int> sucesores;
	int u;
	tiempo += 1;
	tdesc[v] = tiempo;
	color[v] = "gris";
	sucesores = this->sucesoresPorId(v);
	while(!sucesores.esVacia()){
		u = sucesores.consultar(1);
		sucesores.eliminar(1);
		if(color[u] == "blanco"){
			pred[u] = v;
			this->DFS(u, pred, tdesc, tfinal, color, tiempo);
		}
	}
	color[v] = "negro";
	tiempo += 1;
	tfinal[v] = tiempo;
}

//Esta funcion busca los nodos que contienen a los vertices v y w
//y guarda apuntadores a ellos por referencia
template <class T, class C>
void Grafo<T,C>::ubicarAmbos(const T &v, const T &w, NodoV<T,C> *&actV, NodoV<T,C> *&actW) const{
	NodoV<T,C> *act = g;
	actV = actW = 0;
	while(act && (!actV || !actW)){
		if(act->obtInfo() == v){
			actV = act;
		}
		if(act->obtInfo() == w){
			actW = act;
		}
		act = act->obtSig();
	}
}

//Esta funcion busca el nodo que contiene al vertice v
//y guarda un apuntador a el por referencia.
template <class T, class C>
NodoV<T,C>* Grafo<T,C>::ubicar(const T &v) const{
	NodoV<T,C> *act = g;
	while(act){
		if(act->obtInfo() == v){
			return(act);
		}
		act = act->obtSig();
	}
	return(0);
}

template <class T, class C>
NodoV<T,C>* Grafo<T,C>::ubicarPorId(int v) const{
	NodoV<T,C> *act = g;
	while(act){
		if(act->obtId() == v){
			return(act);
		}
		act = act->obtSig();
	}
	return(0);
}

template <class T, class C>
NodoA<T,C>* Grafo<T,C>::ubicar(NodoA<T,C> *actW, const T &w) const{
	NodoA<T,C> *act = actW;
	while(act){
		if(act->obtVert()->obtInfo() == w){
			return(act);
		}
		act = act->obtSig();
	}
	return(0);
}

template <class T, class C>
NodoA<T,C>* Grafo<T,C>::ubicarPorId(NodoA<T,C> *actW, int w) const{
	NodoA<T,C> *act = actW;
	while(act){
		if(act->obtVert()->obtId() == w){
			return(act);
		}
		act = act->obtSig();
	}
	return(0);
}
/**Fin de Observadores**/


/**Modificadores**/
template <class T, class C>
void Grafo<T,C>::agregarVertice(const T &v){
	NodoV<T,C> *ant, *act, *nuevo;
	ant = 0;
	act = this->g;
	while(act && act->obtInfo() != v){
		ant = act;
		act = act->obtSig();
	}
	if(!act){
		nuevo = new NodoV<T,C>(v);
		if(!ant)
			this->g = nuevo;
		else
			ant->modSig(nuevo);
		this->fin = nuevo;
		this->vertices++;
	}
}

template <class T, class C>
void Grafo<T,C>::agregarArco(const T &v, const T &w, const C &p){
	NodoV<T,C> *act, *actV, *actW;
	NodoA<T,C> *arcV, *arcW, *nuevo;
	actV = actW = 0;
	arcV = arcW = 0;
	act = this->g;
	while(act && (!actV || !actW)){
		if(act->obtInfo() == v)
			actV = act;
		if(act->obtInfo() == w)
			actW = act;
		act = act->obtSig();
	}
	if(!actV){
		actV = this->agregarAlFinal(v);
	}
	if(!actW){
		actW = (w == v ? actV : this->agregarAlFinal(w));
	}
	arcV = actV->obtPri();
	while(arcV && arcV->obtVert()->obtInfo() != w){
		arcW = arcV;
		arcV = arcV->obtSig();
	}
	if(!arcV){
		nuevo = new NodoA<T,C>(actW, p);
		if(!arcW){
			actV->modPri(nuevo);
		}else{
			arcW->modSig(nuevo);
		}
		this->arcos++;
	}
}

template <class T, class C>
void Grafo<T,C>::agregarArcoNoDirigido(const T &v, const T &w, const C &p){
	NodoV<T,C> *act, *actV, *actW;
	NodoA<T,C> *arcV, *arcW, *nuevo, *nuevo2;
	bool flag = false;
	actV = actW = 0;
	arcV = arcW = 0;
	act = this->g;
	while(act && (!actV || !actW)){
		if(act->obtInfo() == v)
			actV = act;
		if(act->obtInfo() == w)
			actW = act;
		act = act->obtSig();
	}
	if(!actV){
		actV = this->agregarAlFinal(v);
	}
	if(!actW){
		actW = (w == v ? actV : this->agregarAlFinal(w));
	}
	
	arcV = actV->obtPri();
	while(arcV && arcV->obtVert()->obtInfo() != w){
		arcW = arcV;
		arcV = arcV->obtSig();
	}
	if(!arcV){
		nuevo = new NodoA<T,C>(actW, p);
		if(!arcW){
			actV->modPri(nuevo);
		}else{
			arcW->modSig(nuevo);
		}
		flag = true;
	}
	
	arcW = actW->obtPri();
	while(arcW && arcW->obtVert()->obtInfo() != v){
		arcV = arcW;
		arcW = arcW->obtSig();
	}
	if(!arcW){
		nuevo2 = new NodoA<T,C>(actV, p);
		if(!arcV){
			actW->modPri(nuevo2);
		}else{
			arcV->modSig(nuevo2);
		}
		flag = true;
	}
	if(flag){
		this->arcos++;
	}
}

template <class T, class C>
void Grafo<T,C>::eliminarArco(const T &v, const T &w){
	NodoV<T,C> *actV;
	NodoA<T,C> *arc, *arcAnt;
	bool flag = true;
	actV = 0;
	actV = this->ubicar(v);
	if(actV){		
		arc = actV->obtPri();
		while(arc && flag){
			if(arc->obtVert()->obtInfo() == w){
				if(arcAnt){
					arcAnt->modSig(arc->obtSig());
				}else{
					actV->modPri(arc->obtSig());
				}
				delete(arc);
				this->arcos--;
				flag = false;
			}else{				
				arcAnt = arc;
				arc = arc->obtSig();
			}
		}
	}
}

//Este metodo elimina el vertice v del grafo
template <class T, class C>
void Grafo<T,C>::eliminarVertice(const T &v){
	NodoV<T,C> *act, *ant, *actV, *antV;
	ant = actV = antV = 0;
	act = g;
	while(act){
		if(act->obtInfo() == v){
			eliminarTodosArcos(act);
			antV = ant;
			actV = act;
		}else{
			eliminarArcoDe(v, act);
		}
		ant = act;
		act = act->obtSig();
	}
	if(actV){
		if(antV){
			antV->modSig(actV->obtSig());			
			this->fin = (actV->obtInfo() == this->fin->obtInfo() ? antV : this->fin);
		}else{
			this->g = actV->obtSig();
			this->fin = (this->g ? this->fin : 0);
		}
		
		delete(actV);
		this->vertices--;
	}
}

//elimina todos los arcos que tenga el vertice al que apunta act
template <class T, class C>
void Grafo<T,C>::eliminarTodosArcos(NodoV<T,C> *act){
	NodoA<T,C> *arc, *arcAux;
	arc = act->obtPri();
	while(arc){
		arcAux = arc;
		arc = arc->obtSig();
		delete(arcAux);
		this->arcos--;
	}
	act->modPri(arc);
}

//Esta funcion elimina el arco v del vertice al que apunta act
template <class T, class C>
void Grafo<T,C>::eliminarArcoDe(const T &v, NodoV<T,C> *act){
	NodoA<T,C> *arcAux, *arc;
	bool flag = true;
	arcAux = 0;
	arc = act->obtPri();
	while(arc && flag){
		if(arc->obtVert()->obtInfo() == v){
			if(arcAux){
				arcAux->modSig(arc->obtSig());
			}else{
				act->modPri(arc->obtSig());
			}
			delete(arc);
			this->arcos--;
			flag = false;
		}else{
			arcAux = arc;
			arc = arc->obtSig();
		}
	}
}

//Este metodo agrega un nuevo vertice al final de la "lista"
//y retorna un apuntador a este.
template <class T, class C>
NodoV<T,C>* Grafo<T,C>::agregarAlFinal(const T &v){
	NodoV<T,C> *nuevo = new NodoV<T,C>(v);
	if(this->fin){
		this->fin->modSig(nuevo);
		this->fin = this->fin->obtSig();
	}else{
		this->g = this->fin = nuevo;
	}
	this->vertices++;
	return(this->fin);
}

template <class T, class C>
void Grafo<T,C>::nulo(){
	NodoV<T,C> *actV = this->g, *auxV;
	NodoA<T,C> *actA, *auxA;
	while(actV){
		auxV = actV;
		actA = actV->obtPri();	//Obteniendo primer arco del vertice actV
		actV = actV->obtSig();	//Moviendose al siguiente vertice
		while(actA){
			auxA = actA;
			actA = actA->obtSig();	//Obteniendo siguiente arco
			delete(auxA);
		}
		delete(auxV);
	}
	this->g = this->fin = 0;
	this->vertices = this->arcos = 0;
}

template <class T, class C>
void Grafo<T,C>::copiar(const Grafo<T,C> &g2){
	this->nulo();
	this->copiarVertices(g2);
	this->copiarArcos(g2);
	this->vertices = g2.vertices;
	this->arcos = g2.arcos;
}

template <class T, class C>
void Grafo<T,C>::modIds(){
	NodoV<T,C> *act = this->g;
	int i = 0;
	while(act){
		act->modId(i++);
		act = act->obtSig();
	}
}


template <class T, class C>
void Grafo<T,C>::copiarVertices(const Grafo<T,C> &g2){
	NodoV<T,C> *actVg2, *actV, *nuevo;
	actVg2 = g2.g;
	actV = 0;
	while(actVg2){
		nuevo = new NodoV<T,C>(actVg2->obtInfo());
		if(this->g){
			actV->modSig(nuevo);
			actV = actV->obtSig();
		}else{
			actV = nuevo;
			this->g = actV;
		}
		actVg2 = actVg2->obtSig();
	}
	this->fin = actV;
}

//Copia todos los arcos de g2 a la instancia, suponiendo que la
//instancia ya posee los vertices.
template <class T, class C>
void Grafo<T,C>::copiarArcos(const Grafo<T,C> &g2){
	NodoV<T,C> *actVg2, *actV;
	NodoA<T,C> *actAg2, *actA, *nuevo;
	actVg2 = g2.g;
	actV = this->g;
	while(actVg2){
		actAg2 = actVg2->obtPri();
		while(actAg2){
			nuevo = new NodoA<T,C>(this->ubicar(actAg2->obtVert()->obtInfo()), actAg2->obtCosto());
			if(actV->obtPri()){
				actA->modSig(nuevo);
				actA = actA->obtSig();
			}else{
				actA = nuevo;
				actV->modPri(actA);
			}
			actAg2 = actAg2->obtSig();
		}
		actV = actV->obtSig();
		actVg2 = actVg2->obtSig();
	}
}

template <class T, class C>
void Grafo<T,C>::marcar(const T &v){
	NodoV<T,C> *actV = this->ubicar(v);
	if(actV){
		actV->marcar();
	}
}

template <class T, class C>
void Grafo<T,C>::desmarcar(const T &v){
	NodoV<T,C> *actV = this->ubicar(v);
	if(actV){
		actV->desmarcar();
	}
}
/**Fin de Modificadores**/


/**Sobrecarga de Operadores**/
template <class T, class C>
Grafo<T,C>& Grafo<T,C>::operator = (const Grafo<T,C> &g2){
	this->copiar(g2);
	return(*this);
}

template <class T, class C>
bool Grafo<T,C>::operator == (const Grafo<T,C> &g2){
	return(this->igual(g2));
}

template <class t, class c>
std::ostream& operator << (std::ostream &o, const Grafo<t, c> &g){
	g.mostrar(o);
	return(o);
}
/**Fin deSobrecarga de Operadores**/


/**Destructor**/
template <class T, class C>
Grafo<T,C>::~Grafo(){
	this->nulo();
}
/**Fin de Destructor**/
#endif
