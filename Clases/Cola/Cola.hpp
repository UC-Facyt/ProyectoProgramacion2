#ifndef COLA_H
#define COLA_H

#include <iostream>
#include "../Nodo/Nodo.hpp"

template <class T>
class Cola{
private:
	Nodo<T> *pri, *ult;
	int tam;
	
public:
	//Constructores
	Cola();
	Cola(const Cola<T>&);
	
	//Observadores
	inline bool esVacia() const;
	inline int longitud() const;
	inline T frente() const;
	inline T final() const;
	
	//Modificadores
	void encolar(const T);
	T desencolar();
	
	//Sobrecarga
	Cola<T>& operator = (const Cola<T>&);
	
	template <class t>
	friend std::ostream& operator << (std::ostream&, const Cola<t>&);
	//~ friend std::istream& operator >> (std::istream&, Lista<T>&);
	
	//Destructor
	~Cola();
};

/*Constructores*/
template <class T>
Cola<T>::Cola() : pri(0), ult(0), tam(0) {}

template <class T>
Cola<T>::Cola(const Cola<T> &c) : pri(0), ult(0), tam(0) { *this = c; }
/*Fin de Constructores*/


/*Observadores*/
template <class T>
inline bool Cola<T>::esVacia() const{ return(this->pri==NULL); }

template <class T>
inline int Cola<T>::longitud() const{ return(this->tam); }

template <class T>
inline T Cola<T>::frente() const{ 
	if(this->pri != NULL)
		return(this->pri->obtInfo());
	else
		return (T());
}

template <class T>
inline T Cola<T>::final() const{ 
	if(this->ult != NULL)
		return(this->ult->obtInfo());
	else
		return (T());
}
/*Fin de Observadores*/


/*Modificadores*/
template <class T>
void Cola<T>::encolar(const T e){
	Nodo<T> *nuevo = new Nodo<T>(0, e);
	if(this->pri!=NULL){
		this->ult->modSig(nuevo);
		this->ult = this->ult->obtSig();
	}else{
		this->pri = nuevo;
		this->ult = nuevo;
	}
	this->tam++;
}

template <class T>
T Cola<T>::desencolar(){
	Nodo<T> *act = this->pri;
	T res;
	if(act){
		this->pri = this->pri->obtSig();
		res = act->obtInfo();
		delete(act);
		this->tam--;
	}
	return(res);
}
/*Fin de Modificadores*/


/*Sobrecarga*/
template <class T>
Cola<T>& Cola<T>::operator = (const Cola<T> &p){
	Nodo<T> *act, *act2;
	this->~Cola();
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
		this->ult = act2;
	}
	return(*this);
}

template <class T>
std::ostream& operator << (std::ostream &output, const Cola<T> &l){
	Nodo<T> *act;
	act = l.pri;
	output << "[";
	while(act){
		output << act->obtInfo();
		act = act->obtSig();
		output << (act != NULL ? ", " : "");
	}
	output << "]";
	return(output);
}
/*Fin de Sobrecarga*/


/*Destructor*/
template <class T>
Cola<T>::~Cola(){
	Nodo<T> *act;
	act = this->pri;
	while(this->pri){
		act = this->pri;
		this->pri = this->pri->obtSig();
		delete(act);
	}
	this->ult = 0;
	this->tam = 0;
}
/*Fin de Destructor*/
#endif
