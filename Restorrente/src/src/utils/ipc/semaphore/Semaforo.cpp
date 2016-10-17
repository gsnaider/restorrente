#include "Semaforo.h"

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

Semaforo :: Semaforo ( const std::string& nombre,const int valorInicial, const int hashKey ):valorInicial(valorInicial) {
	key_t clave = ftok ( nombre.c_str(),hashKey );
	if (clave < 0){
		cout << "Error ftok semaforo " << strerror(errno) << endl;
	}

	this->id = semget ( clave,1,0666 | IPC_CREAT );
	if (id < 0){
		cout << "Error semget " << strerror(errno) << endl;
	}

	this->inicializar ();
}

Semaforo::~Semaforo() {
}

int Semaforo :: inicializar () const {

	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->valorInicial;
	int resultado = semctl ( this->id,0,SETVAL,init );
	if (resultado < 0){
		cout << "Error semctl (init) " << strerror(errno) << endl;
	}

	return resultado;
}

int Semaforo :: p () const {

	struct sembuf operacion;

	operacion.sem_num = 0;	// numero de semaforo
	operacion.sem_op  = -1;	// restar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	if (resultado < 0){
		cout << "Error semop (p) " << strerror(errno) << endl;
	}
	return resultado;
}

int Semaforo :: v () const {

	struct sembuf operacion;

	operacion.sem_num = 0;	// numero de semaforo
	operacion.sem_op  = 1;	// sumar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	if (resultado < 0){
		cout << "Error semop (v) " << strerror(errno) << endl;
	}
	return resultado;
}

void Semaforo :: eliminar () const {
	int resultado = semctl ( this->id,0,IPC_RMID );
	if (resultado < 0){
		cout << "Error semctl (delete) " << strerror(errno) << endl;
	}
}
