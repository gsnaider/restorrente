

#include "../model/Menu.h"
#include "../model/Plato.h"
#include "MainProcess.h"



using namespace std;


int main() {
	//TODO Reemplazar todos los cout por el log.

/*
	// TODO Leer de archivo de config.
	Parser p ;
	p.parse("src/utils/SetUp.txt");
	int cantMozos = p.getCantMozos();
	int cantRecepcionistas = p.getCantRecepcionistas();
	int cantMesas = p.getCantMesas();
	int cantComensales = p.getCantComensales();
*/

	int cantMozos = 10;
	int cantRecepcionistas = 2;
	int cantMesas = 2;
	int cantComensales = 5;
	Menu* menu = new Menu();

	Plato plato1("Fideos con tuco", 50);
	menu->agregarPlato(plato1);

	Plato plato2("Milanesa con papas fritas", 80);
	menu->agregarPlato(plato2);

	Plato plato3("Ensalada mixta", 45.50);
	menu->agregarPlato(plato3);


	MainProcess mainProcess(cantRecepcionistas, cantMozos, cantMesas, cantComensales, menu);
	mainProcess.run();


	return 0;
}
