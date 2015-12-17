#ifndef NODO_ARB_H
#define NODO_ARB_H

#include <iostream>

template <class T>
class NodoArb{
private:
	NodoArb<T> *hi, *hd, *pa;
	T info;

public:
	//Constructores
	inline NodoArb() : hi(0), hd(0), info(T()) {}
	NodoArb(const T &e = T(), NodoArb<T> *f = 0, NodoArb<T> *i = 0, NodoArb<T> *d = 0) : hi(i), hd(d), pa(f), info(e) {}

	//Observadores
	NodoArb<T>* obtHi() const{ return(hi); }
	NodoArb<T>* obtHd() const{ return(hd); }
	NodoArb<T>* obtPa() const{ return(pa); }
	// NodoArb<T>*& obtHi(){ return(hi); }
	// NodoArb<T>*& obtHd(){ return(hd); }
	T obtInfo() const{ return(this->info); }
	
	//Modificadores
	void modHi(NodoArb<T> *i){ this->hi = i; }
	void modHd(NodoArb<T> *d){ this->hd = d; }
	void modPa(NodoArb<T> *f){ this->pa = f; }
	void modInfo(const T &e){ this->info = e; }
	
	//Destructor
};


#endif
