#include <iostream>
#include "GameManager.h"
//#include "Bomberman.h"
//#include "GameObject.h"
//#include "GameActor.h"
//#include "Detonador.h"

using namespace std;

int main(int argc, char* args[])
{
	GameManager* gm01 = new GameManager();
	
	return gm01->onExecute();
}