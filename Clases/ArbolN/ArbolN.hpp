#ifndef ARBOLN_H
#define ARBOLN_H

#include <iostream>
#include <cmath>
#include "../NodoArb/NodoArb.hpp"
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
	void impArbol(NodoArb<T>*, int, bool&, Lista<int>&, std::ostream&) const;
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

	Lista< ntupla<T> > magic(const T&) const;		// <-- Funcion que determina los primos

	//Sobrecarga de operadores
	//~ template <class t>
	//~ friend std::ostream& operator << (std::ostream&, const ArbolN<t>&);
	
	//Destructor
	inline ~ArbolN();
};


/*Observadores*/
template <class T>
inline void ArbolN<T>::impArbol() const{
	bool f = false;
	// bool *arr = new bool[this->peso];
	Lista<int> l;
	impArbol(raizArb, 0, f, l, std::cout);
	// delete[] arr;
}

template <class T>
void ArbolN<T>::impArbol(NodoArb<T> *act, int n, bool &f, Lista<int> &l, std::ostream &o) const{
	if(act){
		for(int i=1; i<n; i++){
			o << (l.obtPos(i) ? "|  " : "   ");
		}
		
		if(n>0){
			if(f){
				o << "`--" << act->obtInfo() << ", Pa: " << (act->obtPa() != NULL ? act->obtPa()->obtInfo() : "") << std::endl;
				f = false;
			}else{
				o << "|--" << act->obtInfo() << ", Pa: " << (act->obtPa() != NULL ? act->obtPa()->obtInfo() : "") << std::endl;
			}
		}else{
			o << act->obtInfo() << ", Pa: " << (act->obtPa() != NULL ? act->obtPa()->obtInfo() : "") << std::endl;
		}
		
		// if(!((act->obtHi() || act->obtHd()) && (!act->obtHi() || !act->obtHd()))){}
			
		
		if(act->obtHd() != NULL && act->obtHd()->obtHd() == NULL){
			f = true;
		}else{
			l.insertar(n, l.longitud()+1);
		}
		
		impArbol(act->obtHi(), n+1, f, l, o);
		l.eliminar(l.obtPos(n));
		impArbol(act->obtHd(), n, f, l, o);
	}else{
		// f = true;
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
	hijos.~Cola();
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
Lista< ntupla<T> > ArbolN<T>::magic(const T& e) const {
	
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
