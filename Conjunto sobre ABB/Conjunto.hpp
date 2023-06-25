template < class T >
Conjunto < T > ::Nodo::Nodo(const T & v): valor(v), izq(nullptr), der(nullptr), anterior(nullptr) {}

template < class T >
Conjunto < T > ::Conjunto() {
    _cardinal = 0;
    raiz = nullptr;
}

template < class T >
Conjunto < T > ::~Conjunto() {
    while (raiz != nullptr) {
        this -> remover(maximo());
    }
    if (_cardinal != 0) {
        delete(raiz);
    }
}

template < class T >
bool Conjunto < T > ::pertenece(const T & clave) const {
    if (!raiz) {
        return false;
    } else {
        Nodo * actual = raiz;
        while (actual != nullptr) {
            if (clave < actual -> valor) {
                actual = actual -> izq;
            } else if (clave > actual -> valor) {
                actual = actual -> der;
            } else {
                return true;
            }
        }

        return false;
    }
}

template < class T >
void Conjunto < T > ::insertar(const T & clave) {
    if (!pertenece(clave)) {
        if (!raiz ) {
            Nodo * nuevo = new Nodo(clave);
            raiz = nuevo;
            _cardinal++;

        } else {
            Nodo * actual = raiz;
            Nodo * anterior = nullptr;

            while (actual) {
                if (clave > actual -> valor) {
                    anterior = actual;
                    actual = actual -> der;
                } else {
                    anterior = actual;
                    actual = actual -> izq;
                }
            }

            if (clave > anterior -> valor) {
                Nodo * nuevo = new Nodo(clave);
                nuevo -> anterior = anterior;
                actual = nuevo;
                anterior -> der = nuevo;
                _cardinal++;
            } else {
                Nodo * nuevo = new Nodo(clave);
                nuevo -> anterior = anterior;
                actual = nuevo;
                anterior -> izq = nuevo;
                _cardinal++;
            }
        }
    }
}

template < class T >
void Conjunto < T > ::remover(const T & clave) {
    Nodo * actual = raiz;
    Nodo * anterior = nullptr;
    while (actual) {
        if (clave > actual -> valor) {
            actual = actual -> der;
        } else if (clave < actual -> valor) {
            actual = actual -> izq;
        } else {
            break;
        }
    }
    anterior = actual -> anterior;

    if (! raiz) { return; }
    else {
        if (raiz -> valor == clave && _cardinal == 1) {
            raiz = nullptr;
            delete(actual);
            _cardinal = 0;
        } else if (actual -> der == nullptr || actual -> izq == nullptr) {
            if (actual -> der == nullptr && actual -> izq == nullptr) {
                if (raiz -> valor != clave) {
                    if (anterior -> der == actual) {
                        anterior -> der = nullptr;
                        delete(actual);
                        _cardinal--;
                    } else {
                        anterior -> izq = nullptr;
                        delete(actual);
                        _cardinal--;
                    }
                } else {
                    raiz = nullptr;
                    _cardinal--;
                }
            } else {
                if (actual -> der == nullptr) {
                    if (raiz -> valor != clave) {
                        if (anterior -> der == actual)
                            anterior -> der = actual -> izq;
                        else
                            anterior -> izq = actual -> izq;
                        (actual -> izq) -> anterior = anterior;
                        delete(actual);
                        _cardinal--;
                    } else {
                        raiz = actual -> izq;
                        delete(actual);
                        _cardinal--;
                    }
                } else {
                    if (raiz -> valor != clave) {
                        if (anterior -> der == actual)
                            anterior -> der = actual -> der;
                        else
                            anterior -> izq = actual -> der;
                        (actual -> der) -> anterior = anterior;
                        delete(actual);
                        _cardinal--;
                    } else {
                        raiz = actual -> der;
                        delete(actual);
                        _cardinal--;
                    }
                }
            }
        } else { // dos hijos
            Nodo * temp = actual -> der;
            Nodo * p = nullptr;
            while (temp -> izq != nullptr) {
                temp = temp -> izq;
            }
            p = temp -> anterior;
            T copia = temp -> valor;
            this -> remover(copia);
            actual -> valor = copia;
        }
    }
}

template < class T >
const T & Conjunto < T > ::siguiente(const T & clave) {
    Nodo * actual = raiz;
    Nodo * anterior = nullptr;
    while (actual) {
        anterior = actual -> anterior;
        if (clave > actual -> valor) {
            actual = actual -> der;
            anterior = actual -> anterior;
        } else if (clave < actual -> valor) {
            actual = actual -> izq;
            anterior = actual -> anterior;
        } else {
            break;
        }
    }
    if (actual -> der != nullptr) {
        Nodo * min = actual -> der;
        while (min -> izq != nullptr) {
            min = min -> izq;
        }
        return (min -> valor);
    } else {
        Nodo * temp = raiz;
        Nodo * p = nullptr;
        while (temp != nullptr) {
            if (clave < temp -> valor) {
                p = temp;
                temp = temp -> izq;
            } else if (clave > temp -> valor) {
                temp = temp -> der;
            } else
                break;
        }
        if (p != nullptr)
            return p -> valor;
        else
            return raiz -> valor;
    }

}

template < class T >
const T & Conjunto < T > ::minimo() const {
    Nodo * min = raiz;
    while (min -> izq != nullptr) {
        min = min -> izq;
    }
    return (min -> valor);
}

template < class T >
const T & Conjunto < T > ::maximo() const {
    Nodo * max = raiz;
    while (max -> der != nullptr) {
        max = max -> der;
    }
    return (max -> valor);
}

template < class T >
unsigned int Conjunto < T > ::cardinal() const {
    return _cardinal;
}

template < class T >
void Conjunto < T > ::mostrar(std::ostream & ) const {
    Nodo * actual = raiz;

    for (; actual != nullptr; actual = actual -> izq) {
        std::cout << "L: " << actual -> valor << std::endl;
        if (actual -> der) {
            Nodo * sentinel = actual -> der;
            for (; sentinel != nullptr; sentinel = sentinel -> der) {
                std::cout << "R: " << sentinel -> valor << std::endl;
            }
        }
    }

    return;

}