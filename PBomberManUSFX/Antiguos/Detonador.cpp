#include "Detonador.h"

void Detonador::Explotar()
{
	if (ejecutado == true) {
		std::cout << "Exploto" << std::endl;
	}
	else {
		MostrarTiempoRestante();
	}
}

void Detonador::ReducirTiempo()
{
	if (segundos > 0) {
		segundos--;
	}
	else{
		segundos = 60;
		if (minutos > 0) {
			minutos--;
		}
		else{
			minutos = 60;
			if (horas > 0) {
				horas--;
			}
			else {
			
				ejecutado = true;
			}
		}
	}
	MostrarTiempoRestante();
}

void Detonador::MostrarTiempoRestante()
{
	std::cout << "Faltan: " << horas << ":" << minutos << ":" << segundos << std::endl;
}

