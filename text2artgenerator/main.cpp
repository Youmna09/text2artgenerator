#include <iostream>
#include "UI.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
	//Creation de l'interface de l'application et affichage :
	Fl_Window* window = new Fl_Window(500, 400, "text2artgenerator");
	UIWindow(window);
	window->show(argc, argv);
	return Fl::run();
}