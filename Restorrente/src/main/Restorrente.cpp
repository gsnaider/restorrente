

#include "MainProcess.h"

using namespace std;


int main() {
	//TODO Reemplazar todos los cout por el log.


	// TODO Leer de archivo de config.
	int cantMozos = 10;
	int cantRecepcionistas = 3;
	int cantMesas = 15;
	int cantComensales = 10;

	MainProcess mainProcess(cantRecepcionistas, cantMozos, cantMesas, cantComensales);
	mainProcess.run();


	return 0;
}
