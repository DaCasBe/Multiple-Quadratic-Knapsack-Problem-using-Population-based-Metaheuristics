/*
 * MQKPObjectAssignmentOperation.cpp
 *
 * Fichero que define las funciones de la clase MQKPObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPObjectAssignmentOperation.h>

MQKPObjectAssignmentOperation::MQKPObjectAssignmentOperation(){
	_indexKnapsack = 0;
	_indexObj = 0;
	_deltaFitness = 0;
}

MQKPObjectAssignmentOperation::~MQKPObjectAssignmentOperation() {
}

void MQKPObjectAssignmentOperation::apply(MQKPSolution& solution) {
	/*
	 * 1. Asigna el objeto de índice _indexObj a la mochila _indexKnapsack en solution
	 * 2. Actualiza el fitness de solution sumándole _deltaFitness
	 */
	solution.putObjectIn(_indexObj, _indexKnapsack);
	double actualFitness = solution.getFitness();
	double newFitness = actualFitness + _deltaFitness;
	solution.setFitness(newFitness);
}

void MQKPObjectAssignmentOperation::setValues(int indexObject,
		int indexKnapsack, double deltaFitness) {
	/*
	 * Guarda los valores pasados como argumentos en las variables miembro
	 */
	_indexKnapsack = indexKnapsack;
	_indexObj = indexObject;
	_deltaFitness = deltaFitness;
}
