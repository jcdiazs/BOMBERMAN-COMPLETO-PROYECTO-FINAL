#include "GameObject.h"

int GameObject::numeroGameObjectCreados = 0;

GameObject::GameObject() {
	eliminar = false;
	numeroGameObjectCreados++;
	idGameObject = numeroGameObjectCreados;
}


GameObject::GameObject(string _nombre)
{
	eliminar = false;
	nombre = _nombre;
	numeroGameObjectCreados++;
	idGameObject = numeroGameObjectCreados;
}