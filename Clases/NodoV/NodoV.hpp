#ifndef NODOV_H
#define NODOV_H

#include <iostream>

template <class T, class C>
class NodoA;

template <class T, class C>
class NodoV{
private:
	NodoV<T,C> *sig;
	NodoA<T,C> *pri;
	T info;
	int id;
	bool marca;
	
public:
	//Constructores
	inline NodoV(NodoV<T,C>* s = 0, NodoA<T,C>* a = 0, const T &e = T()): sig(s), pri(a), info(e), marca(false){}
	inline NodoV(const T &e): sig(0), pri(0), marca(false){ info = e; }
	
	//Observadores
	inline NodoV<T,C>* obtSig() const{ return(sig); }
	inline NodoA<T,C>* obtPri() const{ return(pri); }
	//~ inline NodoV<T,C>*& obtSig(){ return(sig); }
	//~ inline NodoA<T,C>*& obtPri(){ return(pri); }
	inline T obtInfo() const{ return(info); }
	inline int obtId() const{ return(id); }
	inline bool obtMarca() const{ return(marca); }
	
	//Modificadores
	inline void modSig(NodoV<T,C> *s){ sig = s; }
	inline void modPri(NodoA<T,C> *a){ pri = a; }
	inline void modInfo(T e){ info = e; }
	inline void modId(int n){ id = n; }
	inline void marcar(){ marca = true; }
	inline void desmarcar(){ marca = false; }
};
#endif
