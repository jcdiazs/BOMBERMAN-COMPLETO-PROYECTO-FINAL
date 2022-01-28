/**
 * Examlple of `factory method' design pattern
 * Copyright (C) 2011 Radek Pazdera
 * This program is free software: you can rojoistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>

using namespace std;

class Copa{
public:
	//Copa() : color("") {}

	Copa() {
		color = "";
	}

	string color;
	virtual void Mostrar() = 0;
	//virtual void Colorear() {};

	/* This is the factory method. */
	static Copa* getCopa(string color);
};

class CopaRoja : public Copa
{
public:
	CopaRoja()
	{
		color = "rojo";
	}
	void Mostrar() { std::cout << "MOSTRAR COPA ROJA" << std::endl; }
};


class CopaAzul : public Copa
{
public:
	CopaAzul()
	{
		color = "azul";
	}
	void Mostrar() { std::cout << "MOSTRAR COPA AZUL" << std::endl; }
	void Colorear() { std::cout << "COLOREANDO AZUL " << std::endl; }
};


Copa* Copa::getCopa(std::string color)
{
	if (color == "rojo")
		return new CopaRoja();
	else if (color == "azul")
		return new CopaAzul();
	else
		return nullptr;
}

/* A little testing */
int main()
{
	/* Now we decide the type of the Copa at
	 * runtime by the factory method argument */
	Copa* cR = nullptr;
	cR = Copa::getCopa("rojo");
	Copa* cA = nullptr;
	cA = Copa::getCopa("azul");

	std::cout << cR->color << std::endl;
	
	cR->Mostrar();

	std::cout << cA->color << std::endl;

	((CopaAzul*)cA)->Colorear();
	
	cA->Mostrar();
	
	system("pause");

}