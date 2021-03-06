#ifndef ARBOLN_H
#define ARBOLN_H

#include <iostream>
#include <vector>
#include <cmath>
#include "../Nodo/NodoArb/NodoArb.hpp"
#include "../Lista/Lista.hpp"
#include "../Cola/Cola.hpp"
#include "../Pila/Pila.hpp"

template <class T>
struct ntupla {
	T p;
	Lista<T> h;
};

template <class T>
class ArbolN{
protected:
	NodoArb<T> *raizArb;
	int pesoArb;

protected:
	//Metodos Auxiliares
	void nulo(NodoArb<T>*);													//Para borrar la instancia (Podar el arbol)
	NodoArb<T>* localizar(NodoArb<T>*, const T&) const;
	void localizar(NodoArb<T>*, const T&, NodoArb<T>*&) const;
	NodoArb<T>* localizarUltimoHijo(NodoArb<T>*) const;

public:
	//Constructores
	inline ArbolN(): raizArb(0), pesoArb(0) {}

	//Observadores
	inline void impArbol() const;
	Lista<T> niveles() const;

	//Modificadores
	void nulo();
	void insertarHijos(const T&, Cola<T>&);

	Lista< ntupla<T> > primos(const T&) const;		// <-- Funcion que determina los primos

	//Sobrecarga de operadores
	//~ template <class t>
	//~ friend std::ostream& operator << (std::ostream&, const ArbolN<t>&);

	//Destructor
	inline ~ArbolN();
};


/*Observadores*/
// Impresion del Arbol
template <class T>
inline void ArbolN<T>::impArbol() const{

	int nivel;
	bool flag;
	Lista<int> mem;
	NodoArb<T> *act;
	Pila< NodoArb<T>* > q;

	if(this->raizArb != NULL) {
		nivel = 0;
		flag = false;
		q.apilar(this->raizArb);
		while(!q.esVacia()) {
			act = q.tope();
			if(!flag) {
				if(nivel > 0) {
					for(int i=1; i < nivel; i++) 
						std::cout << (mem.obtPos(i) ? "|    " : "     ");
					if(act->obtHd() == NULL) {
						std::cout << "`----";
						mem.eliminar(mem.obtPos(nivel));
					}	
					else std::cout << "|----";
				}	std::cout << act->obtInfo() << std::endl;
			}
			if(act->obtHi() == NULL or flag) {
				flag = false;
				q.desapilar();
				if(act->obtHd() != NULL) q.apilar(act->obtHd());
				else {
					if(!q.esVacia()) flag = true;
					mem.eliminar(nivel--);
				}
			}
			else {
				nivel++;
				q.apilar(act->obtHi());
				if(act->obtHi()->obtHd() != NULL) 
					mem.insertar(nivel, mem.longitud()+1);
			}
		}
	}
}

template <class T>
Lista<T> ArbolN<T>::niveles() const{
	Lista<T> res;
	Cola< NodoArb<T>* > q;
	NodoArb<T>* act;
	q.encolar(raizArb);
	while(!q.esVacia()){
		act = q.frente();
		q.desencolar();
		if(act){
			res.insertar(act->obtInfo(), res.longitud()+1);
			for(NodoArb<T>* ptr = act->obtHi(); ptr != NULL; ptr = ptr->obtHd()){
				q.encolar(ptr);
				std::cout << ptr->obtInfo() << " ";
			}
			std::cout << std::endl;
		}
	}
	return(res);
}
/*Fin de Observadores*/


/*Modificadores*/
template <class T>
void ArbolN<T>::nulo(NodoArb<T> *act){
	if(act != NULL){
		nulo(act->obtHi());
		nulo(act->obtHd());
		delete(act);
	}
}

template <class T>
void ArbolN<T>::nulo(){
	if(raizArb != NULL){
		nulo(raizArb);
		raizArb = 0;
		pesoArb = 0;
	}
}

template <class T>
void ArbolN<T>::insertarHijos(const T &padre, Cola<T> &hijos){
	NodoArb<T> *act = 0, *papa = 0;
	if(raizArb == NULL){
		if(!hijos.esVacia()){
			raizArb = new NodoArb<T>(padre, 0, new NodoArb<T>(hijos.desencolar()));
			act = raizArb->obtHi();
			act->modPa(raizArb);
		}else{
			raizArb = new NodoArb<T>(padre);
		}
		papa = raizArb;
	}else{
		act = localizar(raizArb, padre);
		papa = act;
		if(act){
			if(act->obtHi()){
				act = localizarUltimoHijo(act);
			}else if(!hijos.esVacia()){
				act->modHi(new NodoArb<T>(hijos.desencolar(), act));
				act = act->obtHi();
			}
		}
	}
	while(!hijos.esVacia() && act){
		act->modHd(new NodoArb<T>(hijos.desencolar(), papa));
		act = act->obtHd();
	}
	hijos.reset();
}

template <class T>
NodoArb<T>* ArbolN<T>::localizar(NodoArb<T> *act, const T &busq) const{
	NodoArb<T> *encontrado = 0;
	localizar(act, busq, encontrado);
	return(encontrado);
}

template <class T>
void ArbolN<T>::localizar(NodoArb<T> *act, const T &busq, NodoArb<T> *&encontrado) const{
	if(act != NULL){
		if(act->obtInfo() == busq)
			encontrado = act;
		if(encontrado == NULL) localizar(act->obtHi(), busq, encontrado);
		if(encontrado == NULL) localizar(act->obtHd(), busq, encontrado);
	}
}

template <class T>
NodoArb<T>* ArbolN<T>::localizarUltimoHijo(NodoArb<T> *act) const{
	NodoArb<T> *ant = 0;
	if(act && (act = act->obtHi())){
		while(act){
			ant = act;
			act = act->obtHd();
		}
	}
	return(ant);
}

/*Fin de Modificadores*/


/*Sobrecarga*/
// template <class T>
// std::ostream& operator << (std::ostream &o, const ArbolN<T> &a){
	// bool f = false;
	// bool *arr = new bool[a.peso];
	// a.impArbol(a.raizArb, 0, f, arr, o);
	// return(o);
// }
/*Fin de Sobrecarga*/

//Destructor
template <class T>
inline ArbolN<T>::~ArbolN(){
	nulo();
}

template <class T>
Lista< ntupla<T> > ArbolN<T>::primos(const T& e) const {

	NodoArb<T> *act(0), *father(0), *pri(0);
	Lista< ntupla<T> > output;
	ntupla<T> swag;

	if((act = localizar(raizArb, e)) != NULL) {
		father = act->obtPa(); // Father
		if(father != NULL) {
			// Uncle Grandpa
			for(act = father->obtPa()->obtHi(); act != NULL; act = act->obtHd()) {
				if(act != father) {
					swag.p = act->obtInfo();
					for(pri = act->obtHi(); pri != NULL; pri = pri->obtHd())
						swag.h.insertar(pri->obtInfo(), swag.h.longitud()+1);
					if(!swag.h.esVacia()) output.insertar(swag, output.longitud()+1);
					swag.h.nulo();
				}
			}
		}
	}

	return output;
}

#endif
