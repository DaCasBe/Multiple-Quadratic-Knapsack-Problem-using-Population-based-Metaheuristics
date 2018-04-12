/*
 * SelectionOperator.h
 *
 * Fichero que define la clase SelectionOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_SELECTIONOPERATOR_H_
#define INCLUDE_SELECTIONOPERATOR_H_

#include <vector>
#include <Solution.h>

using namespace std;

/**
 * Clase abstracta que define las operaciones que debe tener todo operador de selección para un algoritmo evolutivo
 */
class SelectionOperator {
public:
	/**
	 * Destructor
	 */
	virtual ~SelectionOperator(){}

	/**
	 * Función para seleccionar un conjunto de soluciones de un vector original
	 * @param[in] orig Vector de soluciones sobre el cual aplicar la selección
	 * @param[out] result Vector donde se almacenan las soluciones seleccionadas
	 */
	virtual void select(vector<Solution*> &orig, vector<Solution*> &result) = 0;
};



#endif /* INCLUDE_SELECTIONOPERATOR_H_ */
