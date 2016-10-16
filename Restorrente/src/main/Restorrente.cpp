

#include "MainProcess.h"

using namespace std;


int main() {
	//TODO Reemplazar todos los cout por el log.


	// TODO Leer de archivo de config.
	int cantMozos = 10;
	int cantRecepcionistas = 2;
	int cantMesas = 1;
	int cantComensales = 2;

	MainProcess mainProcess(cantRecepcionistas, cantMozos, cantMesas, cantComensales);
	mainProcess.run();


	return 0;
}
