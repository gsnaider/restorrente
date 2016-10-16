

#include "MainProcess.h"
#include "../utils/Parser.h"

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
	int cantMesas = 5;
	int cantComensales = 2;
	MainProcess mainProcess(cantRecepcionistas, cantMozos, cantMesas, cantComensales);
	mainProcess.run();


	return 0;
}
