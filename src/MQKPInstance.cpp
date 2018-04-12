/*
 * MQKPInstance.cpp
 *
 * Fichero que define los métodos de la clase MQKPInstance. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPInstance.h"
#include "MQKPSolution.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

MQKPInstance::MQKPInstance() {
	// inicializando las variables miembro
	_numKnapsacks = 0;
	_numObjs = 0;
	this->_capacities = NULL;
	this->_profits = NULL;
	this->_weights = NULL;
}

MQKPInstance::~MQKPInstance() {
	//
	int i;
	for (i = 0; i < getNumObjs(); i++) {
		delete[] _profits[i];
	}
	delete[] _profits;
	delete[] _weights;
	delete[] _capacities;
	_numKnapsacks = _numObjs = 0;
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution &solution) {

	double *sumWeights = new double[this->_numKnapsacks + 1];

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		sumWeights[j] = 0;
	}

	for (int i = 0; i < this->_numObjs; i++) {

		/*
		 * 1. Obtener la mochila en la que se encuentra el objeto i-ésimo
		 * 2. Si se encuentra en una mochila válida (mayor que 0), incrementar con el peso del objeto el valor correspondiente en sumWeights.
		 */
		if (solution.whereIsObject(i) > 0) {
			sumWeights[solution.whereIsObject(i)] =
					sumWeights[solution.whereIsObject(i)] + getWeight(i);

		}
	}

	double maxCapacityViolation = 0; //Inicializamos la máxima violación de alguna mochila a 0, que significa que no hay ninguna violación

	for (int j = 1; j <= this->_numKnapsacks; j++) {

		/*
		 * 1. Calcular la violación en la mochila j-ésima
		 * 2. Actualizar maxCapacityViolation en su caso
		 */
		if ((sumWeights[j] - getCapacity(j)) > maxCapacityViolation) {
			maxCapacityViolation = sumWeights[j] - getCapacity(j);
		}
	}

	delete[] sumWeights;
	return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution &solution) {

	double sumProfits = 0.;

	/* Doble bucle para cada par de objetos
	 * Todo objeto incluido en alguna mochila (> 0) debe sumar su beneficio individual
	 * Todo par de objetos incluidos en la misma mochila (y > 0) debe sumar su beneficio conjunto. IMPORTANTE, sumar los pares (i,j) sólo una vez, es decir, si se suma (i, j), no se debe sumar (j, i)
	 */
	int i, j;
	for(i=0; i<getNumObjs(); i++)
	{
		if (solution.whereIsObject(i) > 0)
		{
			sumProfits = sumProfits + getProfit(i);
			for (j=i+1; j < getNumObjs(); j++)
			{
				if(solution.whereIsObject(i) == solution.whereIsObject(j))
				{
					sumProfits = sumProfits + getProfit(i,j);
				}
			}
		}
	}

	return sumProfits;
}

void MQKPInstance::readInstance(char *filename, int numKnapsacks) {

	/*
	 *   1. leer el número de objetos
	 *   2. reservar la memoria de vectores y matrices
	 *   3. leer beneficios y pesos de los objetos según lo comentado arriba
	 *   4. Calcular las capacidades de las mochilas:
	 *      . Calcular la suma de los pesos de todos los objetos
	 *      . Multiplicar por 0.8
	 *      . Dividir el resultado anterior entre el número de mochilas. Eso será la capacidad de cada mochila
	 */
	_numKnapsacks = numKnapsacks;

	ifstream fe;
	fe.open(filename,ifstream::in);
	if(!fe){
		cerr << "Error en la apertura del fichero: " << filename << endl;
		exit(-1);
	}
	string trush;
	fe >> trush;
	fe >> _numObjs;

	_profits = new double * [getNumObjs()];
	if(!_profits)
	{
		cerr << "Error al reservar memoria para profits" << endl;
		exit(-1);
	}
	int i;
	for(i=0; i<getNumObjs(); i++){
		_profits[i] = new double[getNumObjs()];
		if(!_profits[i])
		{
			cerr << "Error al reservar memoria para profits [i]" << endl;
			exit(-1);
		}
	}

	for(i=0; i<getNumObjs(); i++)
	{
		fe >> _profits[i][i];
	}
	int j;
	for(i=0; i<getNumObjs(); i++)
	{
		for (j=i+1; j<getNumObjs(); j++)
		{
			fe >> _profits[i][j];
			_profits[j][i] = _profits[i][j];
		}
	}

	fe >> trush;
	fe >> trush;

	_weights = new double[getNumObjs()];
	if(!_weights)
	{
		cout << "Error al reservar memoria para weights" << endl;
		exit(-1);
	}

	double suma=0;

	for(i=0; i<getNumObjs(); i++)
	{
		fe >> _weights[i];
		suma = suma + _weights[i];
	}

	_capacities = new double[getNumKnapsacks()+1];
	if(!_capacities)
	{
		cout << "Error al reservar memoria para capacities" << endl;
		exit(-1);
	}

	double capacity = suma * 0.8 / getNumKnapsacks();
	for(i=1; i<=getNumKnapsacks(); i++)
	{
		_capacities[i] = capacity;
	}
	fe.close();
}

int MQKPInstance::getNumObjs() {
	return _numObjs;
}

int MQKPInstance::getNumKnapsacks() {
	return _numKnapsacks;
}

double MQKPInstance::getWeight(int object) {
	return _weights[object];
}

double MQKPInstance::getCapacity(int knapsack){
	return _capacities[knapsack];
}

double MQKPInstance::getProfit(int object){
	return _profits[object][object];
}

double MQKPInstance::getProfit(int o1, int o2){
	return _profits[o1][o2];
}

void MQKPInstance::randomPermutation(int size, vector<int>& perm) {

	/**
	 * 1. Vacía el vector perm
	 * 2. Llénalo con la permutación identidad
	 * 3. Recórrelo intercambiando cada elemento con otro escogido de forma aleatoria.
	 */
	perm.clear();

	for (int i = 0; i < size; i++)
		perm.push_back(i);

	for (int i = 0; i < size; i++){
		int pos = rand() % size;
		int aux = perm[i];
		perm[i] = perm[pos];
		perm[pos] = aux;
	}
}

double MQKPInstance::getDeltaSumProfits(MQKPSolution& solution, int indexObject,
		int indexKnapsack) {

	double deltaSumProfits = 0;

	/* Si el objeto estaba en una mochila, resta a deltaSumProfits su beneficio más el beneficio
	 * conjunto con cualquier otro objeto que estuviese en esa misma mochila
	 */

	int originKnapsack = solution.whereIsObject(indexObject);

	if (originKnapsack > 0){
		deltaSumProfits -= this->getProfit(indexObject);

		for (int i = 0; i < _numObjs; i++){

			if (solution.whereIsObject(i) == originKnapsack && i != indexObject){
				deltaSumProfits -= this->getProfit(indexObject, i);
			}
		}
	}

	/* Si el objeto se va a insertar en alguna mochila, suma a deltaSumProfits su beneficio más el beneficio
	 * conjunto con cualquier otro objeto que ya esté en dicha mochila
	 */

	if (indexKnapsack > 0){
		deltaSumProfits += this->getProfit(indexObject);

		for (int i = 0; i < _numObjs; i++){

			if (solution.whereIsObject(i) == indexKnapsack && i != indexObject){
				deltaSumProfits += this->getProfit(indexObject, i);
			}
		}
	}

	return deltaSumProfits;
}

double MQKPInstance::getDeltaMaxCapacityViolation(MQKPSolution& solution,
		int indexObject, int indexKnapsack) {

	/**
	 * 1. Obten la mochila donde está el objeto
	 * 2. Obten la máxima violación actual de la solución
	 * 3. Asigna el objeto a la nueva mochila en solución
	 * 4. Obten la nueva violación de la solución
	 * 5. Deshaz el cambio anterior, volviendo a poner el objeto en la mochila en la que estaba
	 * 6. Devuelve la diferencia (nueva violación - violación actual)
	 */
	int originKnapsack = solution.whereIsObject(indexObject);
	double originViolation = getMaxCapacityViolation(solution);
	solution.putObjectIn(indexObject, indexKnapsack);
	double newViolation = getMaxCapacityViolation(solution);
	solution.putObjectIn(indexObject, originKnapsack);

	return (newViolation - originViolation);
}
