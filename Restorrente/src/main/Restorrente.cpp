

#include "MainProcess.h"
#include "../utils/Parser.h"

using namespace std;


int main() {
	//TODO Reemplazar todos los cout por el log.


	// TODO Leer de archivo de config.
	Parser p ;
	p.parse("src/utils/SetUp.txt");
	int cantMozos = p.getCantMozos();
	int cantRecepcionistas = p.getCantRecepcionistas();
	int cantMesas = p.getCantMesas();
	int cantComensales = p.getCantComensales();

	MainProcess mainProcess(cantRecepcionistas, cantMozos, cantMesas, cantComensales);
	mainProcess.run();


	return 0;
}
