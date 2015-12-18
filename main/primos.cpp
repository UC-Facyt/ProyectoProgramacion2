#include "../Clases/ArbolN/ArbolN.hpp"

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template <class T>
void imp_primos(ArbolN<T>&, const T& e);

int main(){	
	ArbolN<string> arbol;
	Cola<string> hijos;
	string padre, hijo;
	int caso = 1, nHijos;

	while(cin >> padre){
		if (padre == "***"){
			cin >> padre;
			cout << "Caso #" << caso++ << endl;
			imp_primos(arbol, padre);
			cout << endl;
			arbol.nulo();
		} else {
			cin >> nHijos;
			while(nHijos-- > 0)
				cin >> hijo, hijos.encolar(hijo);
			arbol.insertarHijos(padre, hijos);
		}
	}

	
	return(0);
}

template <class T>
void imp_primos(ArbolN<T>& arb, const T& e) {

	int max;
	Lista< ntupla<T> > out;
	ntupla<T> res;

	out = arb.primos(e);
	if(!out.esVacia()) {
		cout << "Los primos de " << e << " son:" << endl;
		while(!out.esVacia()) {
			res = out.consultar(1);
			max = res.h.longitud();
			for(int i=1; i <= max; i++) {
				cout << res.h.consultar(1);
				cout << ((i < max - 1) ? ", " : ((i == max) ? " " : " y "));
				res.h.eliminar(1);
			}
			cout << ((max > 1) ? "(hijos(as) de " : "(hijo(a) de ");
			cout << res.p << ")." << endl;
			out.eliminar(1);
		}
	}
	else cout << e << " No tiene primos." << endl;
}
