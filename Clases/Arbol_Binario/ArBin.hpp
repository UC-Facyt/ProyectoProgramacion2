#ifndef ARBIN_H
#define ARBIN_H

#include <iostream>
#include <cmath>
#include "../NodoArb/NodoArb.hpp"
#include "../Lista/Lista.hpp"
#include "../Cola/Cola.hpp"
#include "../Pila/Pila.hpp"

template <class T>
class ArBin{
protected:
	NodoArb<T> *raizArb;
	int pesoArb;
	
protected:
	//Metodos Auxiliares
	void nulo(NodoArb<T>*);																	//Para borrar la instancia (Podar el arbol)
	inline bool esHoja(NodoArb<T>*) const;													//Verifica si un nodo es hoja
	bool esCompleto(NodoArb<T>*) const;	 													//Verifica si el arbol es completo
	bool igual(const NodoArb<T>*, const NodoArb<T>*) const;									//Verifica si 2 arboles son iguales
	bool isomorfo(NodoArb<T>*, NodoArb<T>*) const;								//Verifica si 2 arboles son isomorfos
	void contiene(NodoArb<T>*, NodoArb<T>*, bool&) const;									//Verifica si un arbol contiene a otro
	bool lleno(NodoArb<T>*, int, int&, bool&) const;									//Verifica si un arbol es lleno
	int altura(NodoArb<T>*) const;															//Retorna la altura de un arbol
	NodoArb<T>* copiar(const NodoArb<T>*, int&) const;										//Para copiar el arbol
	void preorden(const NodoArb<T>*, Lista<T>&) const;										//Para generar lista en preorden
	void postorden(const NodoArb<T>*, Lista<T>&) const;										//Para generar lista en postorden
	void inorden(const NodoArb<T>*, Lista<T>&) const;										//Para generar lista en postorden
	NodoArb<T>* cargaPreIn(Lista<T>&, Lista<T>&, int, int);									//Para cargar con una lista en preorden y una inorden
	NodoArb<T>* cargaPostIn(Lista<T>&, Lista<T>&, int, int);								//Para cargar con una lista en postorden y una inorden
	//~ NodoArb<T>* cargaPreIn(NodoArb<T>*, Lista<T>&, Lista<T>&);							//Para cargar con una lista en preorden y una inorden
	void impArbol(NodoArb<T>*, int, bool&, Lista<int>&, std::ostream&) const;				//Para imprimir un arbol en formato estilo carpetas en cascada por terminal
	bool piramide(NodoArb<T>*, int&) const;
	
public:
	//Constructores
	ArBin();
	ArBin(ArBin<T>&, T&, ArBin<T>&);
	ArBin(Lista<T>, Lista<T>);
	inline ArBin(const ArBin<T>&);					//Constructor Copia
	
	//Observadores
	inline T raiz() const;
	inline int peso() const;
	inline bool esNulo() const;
	inline bool esHoja() const;
	inline int altura() const;
	inline bool esCompleto() const;
	inline bool igual(const ArBin<T>&) const;
	inline bool isomorfo(const ArBin<T>&) const;
	bool semejante(const ArBin<T>&) const;
	inline bool contiene(const ArBin<T>&) const;
	inline bool lleno() const;
	ArBin<T> obtHi() const;
	ArBin<T> obtHd() const;
	inline Lista<T> postorden() const;
	inline Lista<T> preorden() const;
	inline Lista<T> inorden() const;
	Lista<T> niveles() const;
	Lista<T> niveles(int, int) const;
	void impArbol() const;
	bool piramide() const;
	
	//Modificadores
	void insertarHi(ArBin<T>&);
	void insertarHd(ArBin<T>&);
	inline void nulo();
	inline void copiar(const ArBin<T>&);
	inline void cargaPostIn(Lista<T>, Lista<T>);
	inline void cargaPreIn(Lista<T>, Lista<T>);
	
	//Sobrecarga de operadores
	ArBin<T>& operator = (const ArBin<T>&);
	bool operator == (const ArBin<T>&);
	
	template <class t>
	friend std::ostream& operator << (std::ostream&, const ArBin<t>&);
	
	//Destructor
	~ArBin();
};

/*Constructores*/
template <class T>
ArBin<T>::ArBin() : raizArb(0), pesoArb(0) {}

template <class T>
ArBin<T>::ArBin(ArBin<T>& izq, T& e, ArBin<T>& der) : pesoArb(1){
	this->raizArb = new NodoArb<T>(e);
	this->insertarHi(izq);
	this->insertarHd(der);
}

template <class T>
ArBin<T>::ArBin(Lista<T> preorden, Lista<T> inorden){
	this->pesoArb = preorden.longitud();
	this->raizArb = cargaPreIn(preorden, inorden, 1, preorden.longitud());
}

//Constructor Copia//
template <class T>
inline ArBin<T>::ArBin(const ArBin<T>& a) : raizArb(0), pesoArb(0)
{ *this = a; }
/*Fin de Constructores*/


/*Observadores*/
template <class T>
inline T ArBin<T>::raiz() const
{ return(this->raizArb ? this->raizArb->obtInfo() : T()); }

template <class T>
inline bool ArBin<T>::esNulo() const
{ return(this->raizArb == 0); }

template <class T> 
inline int ArBin<T>::peso() const
{ return(this->pesoArb); }

template <class T>
inline bool ArBin<T>::esHoja(NodoArb<T> *act) const
{ return(!act->obtHi() && !act->obtHd()); }

template <class T>
int ArBin<T>::altura(NodoArb<T> *act) const{
	if(act)
		return(1 + (int)fmax(this->altura(act->obtHi()), this->altura(act->obtHd())));
	else
		return(-1);
}

template <class T>
inline int ArBin<T>::altura() const
{ return(this->altura(this->raizArb)); }

template <class T>
inline bool ArBin<T>::esHoja() const
{ return(this->esHoja(this->raizArb)); }

template <class T>
bool ArBin<T>::esCompleto(NodoArb<T> *act) const{
	NodoArb<T> *a, *b;
	if(act){
		a = act->obtHi();
		b = act->obtHd();
		if(!a && !b)
			return(true);
		else if(a && b)
			return(this->esCompleto(a) && this->esCompleto(b));	
		else
			return(false);
	}else{
		return(false);
	}
}

template <class T>
inline bool ArBin<T>::esCompleto() const
{ return(this->esCompleto(this->raizArb)); }

template <class T>
inline bool ArBin<T>::igual(const ArBin<T> &a) const{
	return(this->igual(this->raizArb, a.raizArb));
}

template <class T>
bool ArBin<T>::igual(const NodoArb<T> *a, const NodoArb<T> *b) const{
	if(!a && !b)
		return(true);
	else if(a && b && a->obtInfo() == b->obtInfo())
		return(this->igual(a->obtHi(), b->obtHi()) && this->igual(a->obtHd(), b->obtHd()));
	else
		return(false);
}

template <class T>
bool ArBin<T>::isomorfo(NodoArb<T> *a, NodoArb<T> *b) const{
	if(!a && !b){
		return(true);
	}else if(a && b){
		return(this->isomorfo(a->obtHi(), b->obtHi()) && this->isomorfo(a->obtHd(), b->obtHd()));
	}else{
		return(false);
	}
}

template <class T>
inline bool ArBin<T>::isomorfo(const ArBin<T>& a) const
{ return(this->isomorfo(this->raizArb, a.raizArb)); }

template <class T>
bool ArBin<T>::semejante(const ArBin<T> &a) const{
	Lista<T> l1, l2;
	l1 = this->preorden();
	l2 = a.preorden();	
	if(l1.longitud() != l2.longitud())
		return(false);	
	for(int i=1; i<=l2.longitud(); i++){
		if(l2.obtPos(l1.consultar(1)))
			l1.eliminar(1);
		else
			return(false);
	}
	return(true);
}

template <class T>
void ArBin<T>::contiene(NodoArb<T>* a, NodoArb<T>* b, bool &flag) const{
	if(a && b){
		if(a->obtInfo() == b->obtInfo()){
			flag = true;
			this->contiene(a->obtHi(), b->obtHi(), flag);
			this->contiene(a->obtHd(), b->obtHd(), flag);
		}else{
			if(!flag){
				this->contiene(a->obtHi(), b, flag);
				this->contiene(a->obtHd(), b, flag);
			}else{
				flag = false;
			}
		}
	}
}

template <class T>
inline bool ArBin<T>::contiene(const ArBin<T>& a) const{
	bool f = false;
	this->contiene(this->raizArb, a.raizArb, f);
	return(f);
}

template <class T>
bool ArBin<T>::lleno(NodoArb<T> *act, int nivel, int &n, bool &flag) const{
	if(act){
		if(!act->obtHi() && !act->obtHd()){
			if(!flag){
				flag = true;
				n = nivel;
				return(true);
			}else if(nivel == n){
				return(true);
			}else{
				return(false);
			}
		}else{
			return(this->lleno(act->obtHi(), nivel+1, n, flag) &&
					this->lleno(act->obtHd(), nivel+1, n, flag));
		}
		
	}else{
		return(true);
	}
}

template <class T>
inline bool ArBin<T>::lleno() const{
	bool f = false;
	int n;
	return(this->esCompleto() && this->lleno(this->raizArb, 0, n, f));
}

template <class T>
void ArBin<T>::postorden(const NodoArb<T> *act, Lista<T> &l) const{
	if(act){
		this->postorden(act->obtHi(), l);
		this->postorden(act->obtHd(), l);
		l.insertar(act->obtInfo(), l.longitud()+1);
	}
}

template <class T>
inline Lista<T> ArBin<T>::postorden() const{
	Lista<T> l;
	this->postorden(this->raizArb, l);
	return(l);
}

template <class T>
void ArBin<T>::preorden(const NodoArb<T> *act, Lista<T> &l) const{
	if(act){
		l.insertar(act->obtInfo(), l.longitud()+1);
		this->preorden(act->obtHi(), l);
		this->preorden(act->obtHd(), l);
	}
}

template <class T>
inline Lista<T> ArBin<T>::preorden() const{
	Lista<T> l;
	this->preorden(this->raizArb, l);
	return(l);
}

template <class T>
void ArBin<T>::inorden(const NodoArb<T> *act, Lista<T> &l) const{
	if(act){
		this->inorden(act->obtHi(), l);
		l.insertar(act->obtInfo(), l.longitud()+1);
		this->inorden(act->obtHd(), l);
	}
}

template <class T>
inline Lista<T> ArBin<T>::inorden() const{
	Lista<T> l;
	this->inorden(this->raizArb, l);
	return(l);
}

template <class T>
Lista<T> ArBin<T>::niveles() const{
	Lista<T> l;
	Cola<NodoArb<T>*> c;
	NodoArb<T> *ptr;
	
	c.encolar(this->raizArb);
	while(!c.esVacia()){
		ptr = c.frente();
		c.desencolar();
		if(ptr){
			l.insertar(ptr->obtInfo(), l.longitud()+1);
			if(ptr->obtHi())
				c.encolar(ptr->obtHi());
			if(ptr->obtHd())
				c.encolar(ptr->obtHd());
		}
	}
	return(l);
}

template <class T>
Lista<T> ArBin<T>::niveles(int inf, int sup) const{
	Lista<T> l;
	Cola<NodoArb<T>*> c;
	NodoArb<T> *ptr;
	int nivel = 0, tam = this->altura();
	int *arr = new int[tam];
	
	for(int k=0; k<tam; k++) arr[k] = 0;
	c.encolar(this->raizArb);
	while(!c.esVacia()){
		ptr = c.frente();
		c.desencolar();
		if(ptr){
			if(nivel >= inf && nivel <= sup){
				l.insertar(ptr->obtInfo(), l.longitud()+1);
			}
			if(ptr->obtHi())
				c.encolar(ptr->obtHi());
			if(ptr->obtHd())
				c.encolar(ptr->obtHd());
		}
	}
	delete[] arr;
	return(l);
}

template <class T>
ArBin<T> ArBin<T>::obtHi() const{
	ArBin<T> a;
	int tam;
	a.raizArb = this->copiar(this->raizArb->obtHi(), tam);
	a.pesoArb = tam;
	return(a);
}

template <class T>
ArBin<T> ArBin<T>::obtHd() const{
	ArBin<T> a;
	int tam;
	a.raizArb = this->copiar(this->raizArb->obtHd(), tam);
	a.pesoArb = tam;
	return(a);
}

template <class T>
void ArBin<T>::impArbol() const{
	bool f = false;
	Lista<int> l;
	this->impArbol(this->raizArb, 0, f, l, std::cout);
}

template <class T>
void ArBin<T>::impArbol(NodoArb<T> *act, int n, bool &flag, Lista<int> &l, std::ostream &o) const{
	if(act){
		for(int i=1; i<n; i++){
			o << (l.obtPos(i) ? "|  " : "   ");
		}
		
		if(n>0){
			if(flag){
				o << "`--" << act->obtInfo() << std::endl;
				flag = false;
			}else{
				o << "|--" << act->obtInfo() << std::endl;
			}
		}else{
			o << act->obtInfo() << std::endl;
		}
		
		if(!((act->obtHi() || act->obtHd()) && !(act->obtHi() && act->obtHd())))
			l.insertar(n+1, l.longitud()+1);
		else
			flag = true;
		
		impArbol(act->obtHi(), n+1, flag, l, o);
		l.eliminar(l.obtPos(n+1));
		impArbol(act->obtHd(), n+1, flag, l, o);
	}else{
		flag = true;
	}
}

template <class T>
bool ArBin<T>::piramide(NodoArb<T>* act, int &suma) const{
	int n1=0, n2=0;
	bool f;
	cout << "suma:" << suma << endl;
	if(act){
		if(!act->obtHi() && !act->obtHd()){
			suma = act->obtInfo();
			cout << "suma adentro:" << suma << endl;
			return(true);
		}else{
			f = this->piramide(act->obtHi(), n1);
			f = f && this->piramide(act->obtHi(), n2);
			suma += n1+n2;
			cout << "n1:" << n1 << ", n2:" << n2 << endl;
			return(suma == act->obtInfo() && f);
		}
	}else{
		return(true);
	}
	
}

template <class T>
bool ArBin<T>::piramide() const{
	int n=0;
	if(this->raizArb)
		return(this->piramide(this->raizArb, n));
	else
		return(false);
}
/*Fin de Observadores*/


//Modificadores
template <class T>
void ArBin<T>::insertarHi(ArBin<T> &a){
	this->pesoArb = 0;
	this->nulo(this->raizArb->obtHi());
	this->raizArb->modHi(this->copiar(a.raizArb, this->pesoArb));
}

template <class T>
void ArBin<T>::insertarHd(ArBin<T> &a){
	this->pesoArb = 0;
	this->nulo(this->raizArb->obtHd());
	this->raizArb->modHd(this->copiar(a.raizArb, this->pesoArb));
}

template <class T>
void ArBin<T>::nulo(NodoArb<T> *act){
	if(act){
		this->nulo(act->obtHi());
		this->nulo(act->obtHd());
		delete act;
		act = 0;
	}
}

template <class T>
inline void ArBin<T>::nulo(){ 
	if(this->raizArb){
		this->pesoArb = 0;
		this->nulo((this->raizArb)); 
		this->raizArb = 0;
	}
}

template <class T>
NodoArb<T>* ArBin<T>::copiar(const NodoArb<T> *act, int &tam) const{
	if(act){
		tam++;
		return(new NodoArb<T>(copiar(act->obtHi(), tam), act->obtInfo(), copiar(act->obtHd(), tam)));
	}else{
		return(0);
	}
}

template <class T>
inline void ArBin<T>::copiar(const ArBin<T> &a){
	this->pesoArb = 0;
	this->raizArb = this->copiar(a.raizArb, this->pesoArb);
}

template <class T>
inline void ArBin<T>::cargaPostIn(Lista<T> preorden, Lista<T> inorden){
	this->nulo();
	preorden = preorden.invertir();
	this->pesoArb = preorden.longitud();
	this->raizArb = this->cargaPostIn(preorden, inorden, 1, preorden.longitud());
}

template <class T>
inline void ArBin<T>::cargaPreIn(Lista<T> preorden, Lista<T> inorden){
	this->nulo();
	this->pesoArb = preorden.longitud();
	this->raizArb = this->cargaPreIn(preorden, inorden, 1, preorden.longitud());
}
//Fin de Modificadores


template <class T>
NodoArb<T>* ArBin<T>::cargaPreIn(Lista<T> &preorden, Lista<T> &inorden, int min, int max){
	T e;
	int pos;
	if(!preorden.esVacia() && min<=max){
		e = preorden.consultar(1);
		preorden.eliminar(1);
		pos = inorden.obtPos(e);
		return(new NodoArb<T>(cargaPreIn(preorden, inorden, min, pos-1), e, cargaPreIn(preorden, inorden, pos+1, max)));
	}
	return(0);
}

template <class T>
NodoArb<T>* ArBin<T>::cargaPostIn(Lista<T> &preorden, Lista<T> &inorden, int min, int max){
	T e;
	int pos;
	NodoArb<T> *aux = 0;
	if(!preorden.esVacia() && min<=max){
		e = preorden.consultar(1);
		preorden.eliminar(1);
		pos = inorden.obtPos(e);
		aux = new NodoArb<T>(e);
		aux->modHd(this->cargaPostIn(preorden, inorden, pos+1, max));
		aux->modHi(this->cargaPostIn(preorden, inorden, min, pos-1));
	}
	return(aux);
}

/*Sobrecarga*/
template <class T>
ArBin<T>& ArBin<T>::operator = (const ArBin<T>& a){
	this->copiar(a);
	return(*this);
}

template <class T>
bool ArBin<T>::operator == (const ArBin<T>& a){
	return(this->igual(a));
}

template <class T>
std::ostream& operator << (std::ostream &o, const ArBin<T> &a){
	bool f = false;
	Lista<int> l;
	a.impArbol(a.raizArb, 0, f, l, o);
	return(o);
}
/*Fin de Sobrecarga*/

//Destructor
template <class T>
ArBin<T>::~ArBin()
{ this->nulo(); }
#endif
