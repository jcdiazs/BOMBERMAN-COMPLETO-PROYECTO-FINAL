#pragma once
#include<iostream>

class Detonador
{
private:
	int horas;
	int minutos;
	int segundos;

	bool activado;
	bool ejecutado;
public:
	int getHoras() { return horas; }
	void setHoras(int _horas) { horas = _horas; }

	int getMinutos() { return minutos; }
	void setMinutos(int _minutos) { minutos = _minutos; }

	int getSegundos() { return segundos; }
	void setSegundos(int _segundos) { segundos = _segundos; }


	bool getActivado() { return activado; }
	void setActivado(bool _activado) { activado = _activado; }

	bool getEjecutado() { return ejecutado; }
	void setEjecutado(bool _ejecutado) { ejecutado = _ejecutado; }

	void Explotar();
	void ReducirTiempo();
	void MostrarTiempoRestante();
};

