#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../Nodo/Nodo.hpp"

template <class T>
class Lista{
private:
	Nodo<T> *pri, *ult;
	int tam;
	
public:
	//Constructores
	inline Lista();
	inline Lista(const Lista<T>&);
	
	//Observadores
	inline bool esVacia() const;
	inline int longitud() const;
	T consultar(const int) const;
	int obtPos(const T) const;
	void mostrar() const;
	bool igual(const Lista<T>&) const;
	void impPosMemoria() const;
	
	//Modificadores
	void insertar(const T, const int);
	void eliminar(const int);
	void nulo();
	Lista<T> invertir();
	void randomList(int);
	
	//Sobrecarga
	Lista<T>& operator = (const Lista<T>&);
	bool operator == (const Lista<T>&);
	
	template <class t>
	friend std::ostream& operator << (std::ostream&, const Lista<t>&);
	//~ friend std::istream& operator >> (std::istream&, Lista<T>&);
	
	//Otros
	Lista<T> subLista(int, int) const;
	
	//Destructor
	~Lista();
};

/*Constructores*/
template <class T>
inline Lista<T>::Lista() : pri(0), ult(0), tam(0){}

template <class T>
inline Lista<T>::Lista(const Lista<T> &l) : pri(0), ult(0), tam(0)
{ *this = l; }
/*Fin de Constructores*/


/*Observadores*/
template <class T>
inline bool Lista<T>::esVacia() const
{ return(this->pri==NULL); }

template <class T>
inline int Lista<T>::longitud() const
{ return(this->tam); }

template <class T>
T Lista<T>::consultar(const int pos) const{
	Nodo<T> *act;
	int i=2;
	if(pos>=1 && pos<=this->tam){
		if(pos==1){
			return(this->pri->obtInfo());
		}else if(pos==this->tam){
			return(this->ult->obtInfo());
		}else{
			act = this->pri->obtSig();
			while(i<pos){
				act = act->obtSig();
				i++;
			}
			return(act->obtInfo());
		}
	}else{
		throw("Posicion Invalida");
	}
	
}

template <class T>
int Lista<T>::obtPos(const T e) const{
	Nodo<T> *act = this->pri;
	int pos = 0, i = 1;
	while(act && pos == 0){
		if(e == act->obtInfo()) pos = i;
		act = act->obtSig();
		i++;
	}
	return(pos);
}

template <class T>
void Lista<T>::mostrar() const{
	Nodo<T> *act = this->pri;
	while(act){
		std::cout << act->obtInfo() << std::endl;
		act = act->obtSig();
	}
}

template <class T>
bool Lista<T>::igual(const Lista<T>& l) const{
	Nodo<T> *act1 = this->pri, *act2 = l.pri;
	if(this->tam != l.tam)
		return(false);
	while(act1){
		if(act1->obtInfo() != act2->obtInfo())
			return(false);
		act1 = act1->obtSig();
		act2 = act2->obtSig();
	}
	return(true);
}

template <class T>
void Lista<T>::impPosMemoria() const{
	Nodo<T> *act = this->pri;
	int i = 1;
	if(act){
		std::cout << "(" << i << ") " << act << std::endl;
		i++;
		act = act->obtSig();
	}
	while(act){
		std::cout << "(" << i << ") " << act << std::endl;
		i++;
		act = act->obtSig();
	}
	std::cout << std::endl;
}
/*Fin de Observadores*/


/*Modificadores*/
template <class T>
void Lista<T>::insertar(const T e, const int pos){
	Nodo<T> *act, *ant, *nuevo;
	int i=2;
	if(pos>=1 && pos<=this->tam+1){
		if(pos==1){
			nuevo = new Nodo<T>(this->pri, e);
			this->pri = nuevo;
			if(pos==this->tam+1) this->ult = nuevo;
		}else if(pos==this->tam+1){
			nuevo = new Nodo<T>(0, e);
			this->ult->modSig(nuevo);
			this->ult = nuevo;
		}else{
			ant = this->pri;
			act = ant->obtSig();
			while(i<pos){
				ant = act;
				act = act->obtSig();
				i++;
			}
			nuevo = new Nodo<T>(act, e);
			ant->modSig(nuevo);
		}
		this->tam++;
	}
}

template <class T>
void Lista<T>::eliminar(const int pos){
	Nodo<T> *act, *ant;
	int i=2;
	if(pos>=1 && pos<=this->tam){
		if(pos==1){
			ant = 0;
			act = this->pri;
			this->pri = this->pri->obtSig();
		}else{
			ant = this->pri;
			act = ant->obtSig();
			while(i<pos){
				ant = act;
				act = act->obtSig();
				i++;
			}
			ant->modSig(act->obtSig());
		}
		if(pos==this->tam) this->ult = ant;
		delete(act);
		this->tam--;
	}
}

template <class T>
void Lista<T>::nulo(){
	this->~Lista();
}

template <class T>
Lista<T> Lista<T>::invertir(){
	Nodo<T> *ant, *act, *sig;
	if(this->tam >= 2){
		ant = 0;
		act = this->pri;
		sig = act->obtSig();
		while(sig){
			ant = act;
			act = sig;
			sig = sig->obtSig();
			act->modSig(ant);
		}
		this->pri->modSig(0);
		this->ult = this->pri;
		this->pri = act;
	}
	return(*this);
}

template <>
void Lista<int>::randomList(int tam){
	this->~Lista();
	srand(time(NULL));
	if(tam<0) tam = 10;
	while(tam-- > 0){
		this->insertar(rand()%1000, 1);
	}
}
/*Fin de Modificadores*/


/*Sobrecarga*/
template <class T>
Lista<T>& Lista<T>::operator = (const Lista<T> &l){
	Nodo<T> *act;
	this->~Lista();
	act = l.pri;
	while(act){
		this->insertar(act->obtInfo(), this->tam+1);
		act = act->obtSig();
	}
	return(*this);
}

template <class T>
bool Lista<T>::operator == (const Lista<T>& l){
	return(this->igual(l));
}

template <class T>
std::ostream& operator << (std::ostream &o, const Lista<T> &l){
	Nodo<T> *act;
	act = l.pri;
	o << "[";
	while(act){
		o << act->obtInfo();
		act = act->obtSig();
		o << (act ? ", " : "");
	}
	o << "]";
	return(o);
}
/*Fin de Sobrecarga*/


/*Otros*/
template <class T>
Lista<T> Lista<T>::subLista(int ini, int fin) const{
	Lista<T> l;
	Nodo<T> *act;
	if(this->pri != NULL){
		act = this->pri;
		int i = 1;
		if(ini>=1 && fin<=this->tam){
			while(act){
				if(i>=ini && i<=fin){
					l.insertar(act->obtInfo(), l.tam+1);
				}
				act = act->obtSig();
				i++;
			}
		}
	}
	return(l);
}

/*Destructor*/
template <class T>
Lista<T>::~Lista(){
	Nodo<T> *act;
	act = this->pri;
	while(this->pri){
		act = this->pri;
		this->pri = this->pri->obtSig();
		delete(act);
	}
	this->pri = 0;
	this->ult = 0;
	this->tam = 0;
}

/*Fin de Destructor*/
#endif
