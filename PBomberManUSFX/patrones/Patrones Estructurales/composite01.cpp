#include <iostream>
#include <vector>

using namespace std;

class Component
{
protected:
	string name;
public:
	Component() {};
	Component(string n) :name(n) {};
	virtual void add(Component*) {}
	virtual void remove(Component*) {}
	virtual void show(short) {}
};

class Composite : public Component
{
private:
	vector<Component*> list;
	//vector<Component*>::iterator ilist;
public:
	Composite(string);
	void add(Component*);
	void remove(Component*);
	void show(short);
};

Composite::Composite(string n) { name = n; }
void Composite::add(Component* component)
{
	list.push_back(component);
}
void Composite::remove(Component* component)
{
	/*list.erase((std::remove(list.begin(), list.end(), component), list.end());
	ilist = list.begin();
	list.erase(list.begin(), list.end());*/
}
void Composite::show(short depth)
{
	cout << name << " nivel: " << depth << endl;
	for (vector<Component*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->show(depth + 1);
		}
	}
}

class Leaf : public Component
{
public:
	Leaf(string);
	void add(Component*) {}
	void remove(Component*) {}
	void show(short);
};

Leaf::Leaf(string n) { name = n; }
void Leaf::show(short depth)
{
	cout << '-' << name << "    (" << depth << ')' << endl;
}

int main()
{
	Composite* root = new Composite("raiz");
	root->add(new Leaf("hoja A"));
	root->add(new Leaf("hoja B"));

	Composite* comp = new Composite("rama");
	comp->add(new Leaf("hoja A'"));
	comp->add(new Leaf("hoja B'"));

	root->add(comp);
	root->add(new Leaf("hoja C"));
	Leaf* h = new Leaf("hoja D");
	root->add(h);
	root->remove(h);
	root->show(1);

	delete h;
	delete comp;
	delete root;
	system("pause");
	return 0;
}