/*
 * Example of `abstract factory' design pattern.
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
#include <string>
using namespace std;

class Window
{
protected:
	int width;
	int height;
	std::string toolkit;
	std::string type;

	Window(std::string usedToolkit, std::string windowType)
		: toolkit(usedToolkit), type(windowType)
	{}

public:
	std::string getToolkit()
	{
		return toolkit;
	}

	std::string getType()
	{
		return type;
	}
};

class GtkToolboxWindow : public Window
{
public:
	GtkToolboxWindow()
		: Window("Gtk", "ToolboxWindow")
	{}
};

class GtkLayersWindow : public Window
{
public:
	GtkLayersWindow()
		: Window("Gtk", "LayersWindow")
	{}
};

class GtkMainWindow : public Window
{
public:
	GtkMainWindow()
		: Window("Gtk", "MainWindow")
	{}
};


class QtToolboxWindow : public Window
{
public:
	QtToolboxWindow()
		: Window("Qt", "ToolboxWindow")
	{}
};

class QtLayersWindow : public Window
{
public:
	QtLayersWindow()
		: Window("Qt", "LayersWindow")
	{}
};

class QtMainWindow : public Window
{
public:
	QtMainWindow()
		: Window("Qt", "MainWindow")
	{}
};


/* This is the abstract factory. */
class UIFactory
{
public:
	virtual Window* getToolboxWindow() = 0;
	virtual Window* getLayersWindow() = 0;
	virtual Window* getMainWindow() = 0;

//	/*virtual GtkToolboxWindow* getGtkTooboxWindow() = 0;
//	virtual GtkMainWindow* getGtkMainWindow() = 0;
//	virtual GtkLayersWindow* getGtkLayerWindow() = 0;
//	virtual QtToolboxWindow* getQkToboxWindow() = 0;
//	virtual QtMainWindow* getQtMainWindow() = 0;
//	virtual QtLayersWindow* getQtLayerWindow() = 0;
//*/
};

/* Factory for Gtk toolkit */
class GtkUIFactory : public UIFactory
{
public:
	/*GtkToolboxWindow* getGtkTooboxWindow() {
		return new GtkToolboxWindow;
	}

*/
	Window* getToolboxWindow()
	{
		return new GtkToolboxWindow();
	}

	Window* getLayersWindow()
	{
		return new GtkLayersWindow();
	}

	Window* getMainWindow()
	{
		return new GtkMainWindow();
	}
};

/* Factory for Qt toolkit */
class QtUIFactory : public UIFactory
{
public:
	Window* getToolboxWindow()
	{
		return new QtToolboxWindow();
	}

	Window* getLayersWindow()
	{
		return new QtLayersWindow();
	}

	Window* getMainWindow()
	{
		return new QtMainWindow();
	}
};

int main()
{
	/*
	QtMainWindow *qtprincipal = new QtMainWindow();
	GtkMainWindow *gtkprincipal = new GtkMainWindow();
	*/

	UIFactory* ui = 0;

	/* Check what environment is running
	   and create appropriate factory. */
	if (/* Gtk == */ true)
	{
		ui = new GtkUIFactory();
	}
	else
	{
		ui = new QtUIFactory();
	}

	/* Use the factory to build interface. */
	Window* toolbox = ui->getToolboxWindow();
	Window* layers = ui->getLayersWindow();
	Window* main = ui->getMainWindow();

	/* See what have we recieved. */
	std::cout << toolbox->getToolkit() << ":"
		<< toolbox->getType() << std::endl;

	std::cout << layers->getToolkit() << ":"
		<< layers->getType() << std::endl;

	std::cout << main->getToolkit() << ":"
		<< main->getType() << std::endl;
}