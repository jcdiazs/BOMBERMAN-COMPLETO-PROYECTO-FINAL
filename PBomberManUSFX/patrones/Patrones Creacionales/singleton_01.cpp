/*
 * Example of a singleton design pattern.
 * Copyright (C) 2011 Radek Pazdera
 * This program is free software: you can redistribute it and/or modify
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

class Singleton
{
private:
	/* Here will be the instance stored. */
	static Singleton* instance;

	/* Private constructor to prevent instancing. */
	Singleton();

public:
	/* Static access method. */
	static Singleton* getInstance();
};

/* Null, because instance will be initialized on demand. */
Singleton* Singleton::instance = 0;

Singleton* Singleton::getInstance()
{
	if (instance == 0)
	{
		instance = new Singleton();
	}

	return instance;
}

Singleton::Singleton()
{}

int main()
{
	//new Singleton(); // Won't work
	//Singleton* a = new Singleton();
	Singleton* s = Singleton::getInstance(); // Ok
	Singleton* r = Singleton::getInstance();

	/* The addresses will be the same. */
	std::cout << s << std::endl;
	std::cout << r << std::endl;

	system("pause");
}

//
//private:
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//
//	Otherwise, you will be able to clone your object.If you are using C++ 11, you may leave the copy constructor and the copy assignment operator public but explicitly delete them:
//
//public:
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	@ProgrammerXDesigner
//		ProgrammerXDesigner commented May 11, 2018
//		Nice, but I have some notes here :
//
//	First, you have memory leak.
//		And second, you should declare the copy constructor and the assignment operator of your class as private or delete them explicitly to prevent cloning your object.
//		@akbarsaleemt
//		akbarsaleemt commented Jul 30, 2018
//		how can i access same object every time for my program
//#include
//		using namespace std;
//	class student
//	{
//	private:
//		int id;
//		int marks;
//	public:
//		void adddata()
//		{
//			int i, mks;
//			cout << "enter student marks and id:";
//			cin >> i;
//			cin >> mks;
//			id = i;
//			marks = mks;
//			print();
//		}
//		void print()
//		{
//			cout << "student id num:" << id << endl;
//			cout << "student marks:" << marks << endl;
//		}
//
//	};
//
//	int main()
//	{
//		student s;
//
//		s.adddata();
//
//		x.adddata();
//
//		return 0;
//	}
//
//#include <iostream>                                                              
//
//		class Singleton
//	{
//	private:
//		/* Private constructor to prevent instancing. */
//		Singleton();
//
//	public:
//		/* Static access method. */
//		static Singleton* getInstance();
//	};
//
//	Singleton* Singleton::getInstance()
//	{
//		static Singleton instance;
//
//		return &instance;
//	}
//
//	Singleton::Singleton()
//	{}
//
//	int main()
//	{
//		//new Singleton(); // Won't work                                             
//		Singleton* s = Singleton::getInstance(); // Ok                               
//		Singleton* r = Singleton::getInstance();
//
//		/* The addresses will be the same. */
//		std::cout << s << std::endl;
//		std::cout << r << std::endl;
//	}