#include <iostream>
using namespace std;

typedef int Coordenada;
typedef int Dimension;

// Interface deseada
class Rectangle
{
  public:
    virtual void draw() = 0;
};

//Componente legal
class LegacyRectangle
{
  public:
    LegacyRectangle(Coordenada x1, Coordenada y1, Coordenada x2, Coordenada y2)
    {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
          << x2_ << "," << y2_ << ")" << endl;
    }
    void oldDraw()
    {
        cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << 
          ") => (" << x2_ << "," << y2_ << ")" << endl;
    }
  private:
    Coordenada x1_;
    Coordenada y1_;
    Coordenada x2_;
    Coordenada y2_;
};

// Adapter wrapper (Envoltura del adaptador)
class RectangleAdapter: public Rectangle, private LegacyRectangle
{
  public:
    RectangleAdapter(Coordenada x, Coordenada y, Dimension w, Dimension h):
      LegacyRectangle(x, y, x + w, y + h)
    {
        cout << "RectangleAdapter: create.  (" << x << "," << y << 
          "), width = " << w << ", height = " << h << endl;
    }
    virtual void draw()
    {
        cout << "RectangleAdapter: draw." << endl;
        oldDraw();
    }
};

int main()
{
	//void funcionloca(new RectangleAdapter(120, 200, 60, 40));
  Rectangle *r = new RectangleAdapter(120, 200, 60, 40);
  r->draw();
  system("pause");
}