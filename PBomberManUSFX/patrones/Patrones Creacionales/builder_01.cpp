/*
 * Example of `builder' design pattern.
 * Copyright (C) 2011 Radek Pazdera
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <iostream>
#include <string>

 /* Auto parts */
class Neumatico
{
public:
	int size;
};

class Motor
{
public:
	int horsepower;
};

class Carroceria
{
public:
	std::string shape;
};

/* Final product -- a Auto */
class Auto
{
public:
	Neumatico*   Neumaticos[4];
	Motor*  Motor;
	Carroceria* Carroceria;
	
	void specifications()
	{
		std::cout << "Carroceria:" << Carroceria->shape << std::endl;
		std::cout << "Motor horsepower:" << Motor->horsepower << std::endl;
		std::cout << "tire size:" << Neumaticos[0]->size << "'" << std::endl;
	}

	//void update() override;
};

/* Builder is responsible for constructing the smaller parts */
class Builder
{
public:
	virtual Neumatico* getNeumatico() = 0;
	virtual Motor* getMotor() = 0;
	virtual Carroceria* getCarroceria() = 0;
};

/* Director is responsible for the whole process */
class Director
{
private:
	Builder* builder;

public:
	void setBuilder(Builder* newBuilder)
	{
		builder = newBuilder;
	}

	Auto* getCar()
	{
		Auto* Coche = new Auto();
		
		Coche->Carroceria = builder->getCarroceria();
		Coche->Motor = builder->getMotor();
		Coche->Neumaticos[0] = builder->getNeumatico();
		Coche->Neumaticos[1] = builder->getNeumatico();
		Coche->Neumaticos[2] = builder->getNeumatico();
		Coche->Neumaticos[3] = builder->getNeumatico();

		return Coche;
	}
};

/* Concrete Builder for Jeep SUV cars */
class JeepBuilder : public Builder
{
public:
	Neumatico* getNeumatico()
	{
		Neumatico* neumatico = new Neumatico();
		neumatico->size = 22;
		return neumatico;
	}

	Motor* getMotor()
	{
		Motor* motor = new Motor();
		motor->horsepower = 400;
		return motor;
	}

	Carroceria* getCarroceria()
	{
		Carroceria* carroceria = new Carroceria();
		carroceria->shape = "SUV";
		return carroceria;
	}
};

/* Concrete builder for Nissan family cars */
class NissanBuilder : public Builder
{
public:
	Neumatico* getNeumatico()
	{
		Neumatico* neumatico = new Neumatico();
		neumatico->size = 16;
		return neumatico;
	}

	Motor* getMotor()
	{
		Motor* motor = new Motor();
		motor->horsepower = 85;
		return motor;
	}

	Carroceria* getCarroceria()
	{
		Carroceria* carroceria = new Carroceria();
		carroceria->shape = "hatchback";
		return carroceria;
	}
};


int main()
{
	Auto* Auto; // Final product

	/* A director who controls the process */
	Director director;

	/* Concrete builders */
	JeepBuilder jeepBuilder;
	NissanBuilder nissanBuilder;

	/* Build a Jeep */
	std::cout << "Jeep" << std::endl;
	director.setBuilder(&jeepBuilder); // using JeepBuilder instance
	Auto = director.getCar();
	Auto->specifications();

	std::cout << std::endl;

	/* Build a Nissan */
	std::cout << "Nissan" << std::endl;
	director.setBuilder(&nissanBuilder); // using NissanBuilder instance
	Auto = director.getCar();
	Auto->specifications();

	system("pause");
	return 0;
}