template <typename T>
string_map<T>::Nodo::Nodo(): siguientes(ASCII_SZ, nullptr),
                             definicion(nullptr) {}

template <typename T>
string_map<T>::Nodo::Nodo(T* def): siguientes(ASCII_SZ, nullptr),
                                   definicion(def) {}


template <typename T>
string_map<T>::string_map()
{
    tamanio = 0;
    raiz = nullptr;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map()
{
    *this = aCopiar;
}


template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& strMap)
{
    tamanio = strMap.tamanio;
    raiz = new Nodo();
    if (strMap.raiz) {
        raiz -> copy(strMap.raiz);
    }

    return *this;
}


template <typename T>
void string_map<T>::Nodo::copy(Nodo* aCopiar)
{
    if (aCopiar -> definicion){
        this -> definicion = new T(*(aCopiar->definicion));
    }
    for (int i = 0; i < ASCII_SZ; i++) {
        if (aCopiar -> siguientes[i]) {
            this -> siguientes[i] = new Nodo();
            (this -> siguientes[i]) -> copy(aCopiar -> siguientes[i]);
        }
    }
}



template <typename T>
string_map<T>::~string_map()
{
    destruir(raiz);
}

template <typename T>
void string_map<T>::destruir(Nodo* Nodo)
{
    if (Nodo){
        for (int i = 0; i < ASCII_SZ; i++) {
            if (Nodo -> siguientes[i]) {
                destruir(Nodo -> siguientes[i]);
                Nodo -> siguientes[i] = nullptr;
            }
        }
        if (Nodo -> definicion) {
            delete Nodo -> definicion;
            Nodo -> definicion = nullptr;
        }
        delete Nodo;
    }
}


template <typename T>
void string_map<T>::insert(const pair<string, T>& in)
{
    string key = in.first;
    T value = in.second;

    if (!raiz) {
        raiz = new Nodo();
    }

    Nodo* current = raiz;

    for (const auto& ch : key) {
        if (current -> siguientes[int(ch)]) {
            current = current -> siguientes[int(ch)];
        } else {
            current -> siguientes[int(ch)] = new Nodo();
            current = current -> siguientes[int(ch)];
        }
    }

    if (!(current -> definicion)) {
        tamanio++;
    } else {
        delete current -> definicion;
    }
    current -> definicion = new T(value);

    return;
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if (!raiz) {
        return 0;
    } else {
        return raiz -> is_defined(clave);
    }
}


template <typename T>
int string_map<T>::Nodo::is_defined(const string& clave)
{
    if (clave.length() == 0) {
        if (! this -> definicion){
            return 0;
        } else {
            return 1;
        }
    } else if (! this -> siguientes[int(clave[0])]){
        return 0;
    } else {
        string newClave = clave;
        return (this -> siguientes[int(clave[0])]) -> is_defined(newClave.erase(0, 1));
    }
}


template <typename T>
const T& string_map<T>::at(const string& key) const
{
    Nodo* current = raiz;

    for (const auto& ch : key) {
        current = current -> siguientes[int(ch)];
    }

    return *(current -> definicion);
}



template <typename T>
T& string_map<T>::at(const string& key)
{
    Nodo* current = raiz;

    for (const auto& ch : key) {
        current = current -> siguientes[int(ch)];
    }

    return *(current -> definicion);
}





template <typename T>
void string_map<T>::erase(const string& key)
{
    Nodo* current = raiz;
    Nodo* prev = nullptr;
    const int key_sz = (int) key.size();

    for (int i = 0; i < key_sz; i++) {
        prev = current;
        current = current -> siguientes[int(key[i])];
    }

    delete current -> definicion;

    for (int i = 0; i < ASCII_SZ; i++) {
        if (current -> siguientes[i]) {
            current -> definicion = nullptr;
            return;
        }
    }

    delete current;

    if (prev) {
        prev -> siguientes[key[key_sz - 1]] = nullptr;
    } else {
        raiz = nullptr;
    }

    return;
}


template <typename T>
int string_map<T>::size() const
{
    return tamanio;
}

template <typename T>
bool string_map<T>::empty() const
{
    return raiz == nullptr;
}


