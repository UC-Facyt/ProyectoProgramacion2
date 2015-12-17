#ifndef PILA_H
#define PILA_H

#include <iostream>
#include "../Nodo/Nodo.hpp"

template <class T>
class Pila{
private:
	Nodo<T> *pri;
	int tam;
	
public:
	//Constructores
	Pila();
	Pila(const Pila<T>&);
	
	//Observadores
	bool esVacia() const;
	int longitud() const;
	T tope() const;
	
	//Modificadores
	void apilar(const T);
	void desapilar();
	
	//Sobrecarga
	Pila<T>& operator = (const Pila<T>&);
	
	template <class t>
	friend std::ostream& operator << (std::ostream&, const Pila<t>&);
	//~ friend std::istream& operator >> (std::istream&, Lista<T>&);
	
	//Destructor
	~Pila();
};

/*Constructores*/
template <class T>
Pila<T>::Pila() : pri(0), tam(0) {}

template <class T>
Pila<T>::Pila(const Pila<T> &p) : pri(0), tam(0) { *this = p; }
/*Fin de Constructores*/


/*Observadores*/
template <class T>
bool Pila<T>::esVacia() const{ return(this->pri==NULL); }

template <class T>
int Pila<T>::longitud() const{ return(this->tam); }

template <class T>
T Pila<T>::tope() const{ return(this->pri->obtInfo()); }
/*Fin de Observadores*/


/*Modificadores*/
template <class T>
void Pila<T>::apilar(const T e){
	Nodo<T> *nuevo = new Nodo<T>(this->pri, e);
	this->pri = nuevo;
	this->tam++;
}

template <class T>
void Pila<T>::desapilar(){
	Nodo<T> *act = this->pri;
	if(act){
		this->pri = this->pri->obtSig();
		delete(act);
		this->tam--;
	}
}
/*Fin de Modificadores*/


/*Sobrecarga*/
template <class T>
Pila<T>& Pila<T>::operator = (const Pila<T> &p){
	Nodo<T> *act, *act2, nuevo;
	this->~Pila();
	this->tam = p.tam;
	act = p.pri;
	if(act){
		this->pri = new Nodo<T>(0, act->obtInfo());
		act2 = this->pri;
		act = act->obtSig();
		while(act){
			act2->modSig(new Nodo<T>(0, act->obtInfo()));
			act2 = act2->obtSig();
			act = act->obtSig();
		}
	}
	return(*this);
}

template <class T>
std::ostream& operator << (std::ostream &output, const Pila<T> &l){
	Nodo<T> *act;
	act = l.pri;
	while(act){
		output << act->obtInfo() << "\n---" << std::endl;
		act = act->obtSig();
	}
	return(output);
}
/*Fin de Sobrecarga*/


/*Destructor*/
template <class T>
Pila<T>::~Pila(){
	Nodo<T> *act;
	act = this->pri;
	while(this->pri){
		act = this->pri;
		this->pri = this->pri->obtSig();
		delete(act);
	}
	this->tam = 0;
}

/*Fin de Destructor*/
#endif
