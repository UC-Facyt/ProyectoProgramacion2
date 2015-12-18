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

	Lista< ntupla<T> > out;
	ntupla<T> res;

	out = arb.magic(e);
	if(!out.esVacia()) {
		cout << "Los primos de " << e << " son:" << endl;
		while(!out.esVacia()) {
			res = out.consultar(1);
			if(res.h.longitud() > 1) {
				for(int i=1, n=res.h.longitud(); i <= n; i++) {
					cout << res.h.consultar(1);
					if(i == n - 1) 	cout << " y ";
					else if(i == n)	cout << " "  ;
					else cout << ", ";
					
					res.h.eliminar(1);
				}	cout << "(hijos(as) de " << res.p << ")." << endl;
			}
			else
				cout << res.h.consultar(1) << " (hijo(a) de " << res.p << ")." << endl;
			out.eliminar(1);
		}
	}
	else cout << e << " No tiene primos." << endl;
}
