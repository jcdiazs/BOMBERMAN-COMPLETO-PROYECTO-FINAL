#pragma once

template<class T> class Cola;

template<class T> 
class Nodo {
	friend Cola<T>;
private:
	T valor;
	Nodo<T>* siguiente;

public:
	Nodo(T _valor, Nodo<T>* _siguiente = nullptr) {
		valor = _valor;
		siguiente = _siguiente;
	}
};

template<class T>
class Cola {
private:
	Nodo<T>* primero;
	Nodo<T>* ultimo;
public:
	Cola() : primero(nullptr), ultimo(nullptr) {}
	~Cola();
	void Push(T _valor);
	T Pop();
};

template<class T>
Cola<T>::~Cola() {
	while (primero) {
		Pop();
	}
}

template<class T>
void Cola<T>::Push(T _valor) {
	Nodo<T>* nodoNuevo;
	nodoNuevo = new Nodo<T>(_valor);

	if (ultimo) {
		ultimo->siguiente = nodoNuevo;
	}

	ultimo = nodoNuevo;

	if (!primero) {
		primero = nodoNuevo;
	}
}

template<class T>
T Cola<T>::Pop() {
	Nodo<T>* nodoActual;
	T valorNodo;

	nodoActual = primero;
	if (!nodoActual) {
		return 0;
	}

	primero = nodoActual->siguiente;
	valorNodo = nodoActual->valor;
	delete nodoActual;

	if (!primero) {
		ultimo = nullptr;
	}

	return valorNodo;
}