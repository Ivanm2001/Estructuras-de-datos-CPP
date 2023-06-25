#include "Lista.h"
    Lista::Lista() : prim(NULL) {
    }

    Lista::Lista(const Lista& l) : Lista() {
        //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
        *this = l;
    }

    Lista::~Lista() {
        destruirNodos();
    }

    Lista& Lista::operator=(const Lista& aCopiar) {
        destruirNodos();
        copiarNodos(aCopiar);
        return *this;
    }

    void Lista::agregarAdelante(const int& elem) {
        if (prim == NULL){
            Nodo* nuevo = new Nodo(NULL, elem, NULL);
            prim = nuevo;
            ult = nuevo;
        } else {
            Nodo* nuevo = new Nodo(NULL, elem, prim);
            prim->ant = nuevo;
            prim = nuevo;
        }
    }

    void Lista::agregarAtras(const int& elem) {
        if (prim == NULL){
            Nodo* nuevo = new Nodo(NULL, elem, NULL);
            prim = nuevo;
            ult = nuevo;
        } else {
            Nodo* nuevo = new Nodo(ult, elem, NULL);
            ult->sig = nuevo;
            ult = nuevo;
        }
    }

    void Lista::eliminar(Nat i) {
        if (longitud() == 1){
            Nodo* actual = prim;
            prim = nullptr;
            ult = nullptr;
            delete (actual);
        } else {
            if (i == 0) {
                Nodo* actual = prim;
                prim = prim->sig;
                prim->ant = nullptr;
                delete(actual);
            } else {
                if (i == longitud() - 1){
                    Nodo* actual = ult;
                    ult = ult->ant;
                    ult->sig = nullptr;
                    delete(actual);
                } else {
                    Nodo* ItNormal = prim;
                    Nodo* ItReverso = ult;
                    Nodo* Aborrar = nullptr;
                    for(int j = 0; j < i - 1; j++) {
                        ItNormal = ItNormal->sig;
                    }
                    for(int j = longitud() - 1; j > i + 1; j--) {
                        ItReverso = ItReverso->ant;
                    }
                    Aborrar = ItNormal->sig;
                    ItReverso->ant = ItNormal;
                    ItNormal->sig = ItReverso;
                    delete(Aborrar);
                }
            }
        }
}

    int Lista::longitud() const {
        int size = 0;
        if (prim != NULL) {
            Nodo* actual = prim;
            while (actual != NULL){
                actual = actual->sig;
                size++;
            }
        }
        return size;
    }

    //const int& Lista::iesimo(Nat i) const {
      //  Nodo* actual = prim;
       // if (i != 0) {
          //  for ( int j = 0 ; j < i ; j++ ) {
          //      actual = actual->sig;
        //    }
        //}
       // return actual->valor;
    //}

    int& Lista::iesimo(Nat i) {
        Nodo* actual = prim;
        if (i != 0) {
            for ( int j = 0 ; j < i ; j++ ) {
                actual = actual->sig;
            }
        }
        return actual->valor;
    }

    void Lista::copiarNodos(const Lista &l) {
        Nodo* actual = l.prim;
        while (actual != NULL) {
            agregarAtras(actual->valor);
            actual = actual -> sig;
        }

    }
    void Lista::destruirNodos(){
        Nodo* actual = prim;
        while (actual != NULL){
            Nodo* siguiente = actual -> sig;
            delete actual;
            actual = siguiente;
        }
        prim = NULL;
    }


//void Lista::mostrar(ostream& o) {
    // Completar
//}
