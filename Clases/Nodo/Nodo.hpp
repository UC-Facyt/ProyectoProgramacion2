#ifndef NODO_H
#define NODO_H

#include <iostream>

template <class T>
class Nodo{
private:
	Nodo<T> *sig;
	T info;
	
public:
	//Constructores
	Nodo();
	Nodo(Nodo<T>*, T);
	
	//Observadores
	Nodo<T>* obtSig() const;
	T obtInfo() const;
	
	//Modificadores
	void modSig(Nodo<T>*);
	void modInfo(T);
};

/*Constructores*/
template <class T>
Nodo<T>::Nodo() : sig(0), info(T()) {}

template <class T>
Nodo<T>::Nodo(Nodo<T> *s, T e) : sig(s), info(e) {}
/*Fin de Constructores*/

/*Observadores*/
template <class T>
Nodo<T>* Nodo<T>::obtSig() const{ return(this->sig); }

template <class T>
T Nodo<T>::obtInfo() const{ return(this->info); }
/*Fin de Observadores*/

/*Modificadores*/
template <class T>
void Nodo<T>::modSig(Nodo<T> *s){ this->sig = s; }

template <class T>
void Nodo<T>::modInfo(T e){ this->info = e; }
/*Fin de Modificadores*/
#endif
