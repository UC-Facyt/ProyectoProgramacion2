#ifndef ARBINB_H
#define ARBINB_H

#include <iostream>
#include <cmath>
#include "../Arbol_Binario/ArBin.hpp"
#include "../Lista/Lista.hpp"
#include "../Cola/Cola.hpp"
#include "../Pila/Pila.hpp"

template <class T>
class ArBinB : public ArBin<T>{
protected:
	void insertar(NodoArb<T> *&, const T&);

public:
	//Constructores
	ArBinB();
	ArBinB(const T&);
	ArBinB(Lista<T>, Lista<T>);
	
	//Modificadores
	void insertar(const T&);	
	
	//Sobrecargas
	template <class t>
	friend std::ostream& operator << (std::ostream&, const ArBinB<t>&);
};

template <class T>
ArBinB<T>::ArBinB() : ArBin<T>::ArBin() {}

template <class T>
ArBinB<T>::ArBinB(const T &e) : ArBin<T>::ArBin()
{ this->insertar(e); }

template <class T>
ArBinB<T>::ArBinB(Lista<T> preorden, Lista<T> inorden) : ArBin<T>::ArBin(preorden, inorden) {}

template <class T>
void ArBinB<T>::insertar(NodoArb<T> *&act, const T &e){
	if(!act){
		act = new NodoArb<T>(e);
	}else{
		if(e < act->obtInfo())
			this->insertar(act->obtHi(), e);
		else if(e > act->obtInfo())
			this->insertar(act->obtHd(), e);
	}
}

template <class T>
void ArBinB<T>::insertar(const T &e){
	ArBin<T>::pesoArb++;
	this->insertar(ArBin<T>::raizArb, e);
}

template <class T>
std::ostream& operator << (std::ostream &o, const ArBinB<T> &a){
	ArBin<T> b = a;
	o << b;
	return(o);
}
#endif
