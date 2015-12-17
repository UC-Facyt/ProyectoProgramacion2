#ifndef NODOA_H
#define NODOA_H

#include <iostream>

template <class T, class C>
class NodoV;

template <class T, class C>
class NodoA{
private:
	NodoA<T,C> *sig;
	NodoV<T,C> *vert;
	C costo;	
	
public:
	//Constructores
	inline NodoA(NodoA<T,C>* s = 0, NodoV<T,C>* a = 0, const C &c = C()): sig(s), vert(a), costo(c){}
	inline NodoA(const C &c): sig(0), vert(0){ costo = c; }
	inline NodoA(NodoV<T,C> *v, const C &c = 0): sig(0){ vert = v, costo = c;}
	
	//Observadores
	inline NodoA<T,C>* obtSig() const{ return(sig); }
	inline NodoV<T,C>* obtVert() const{ return(vert); }
	//~ inline NodoA<T,C>*& obtSig(){ return(sig); }
	//~ inline NodoV<T,C>*& obtVert(){ return(vert); }
	inline C obtCosto() const{ return(costo); }
	
	//Modificadores
	inline void modSig(NodoA<T,C> *s){ sig = s; }
	inline void modVert(NodoV<T,C> *a){ vert = a; }
	inline void modCosto(const C &c){ costo = c; }
};
#endif
