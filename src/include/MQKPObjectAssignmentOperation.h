/* MQKPObjectAssignmentOperation.h
 *
 * Fichero que declara la clase MQKPObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPOBJECTASSIGNMENTOPERATION_H__
#define __MQKPOBJECTASSIGNMENTOPERATION_H__

#include <MQKPChangeOperation.h>
#include <MQKPSolution.h>

/**
 * Clase que codifica una operación de asignación de un objeto a una mochila, pudiendo ser ésta la mochila 0, es decir, sacarlo de la mochila en la que se encuentre
 */
class MQKPObjectAssignmentOperation : public MQKPChangeOperation {

protected:
	//las variables miembro de la clase según lo indicado en el guión de prácticas (_indexObj, _indexKnapsack, _deltaFitness)
	int _indexObj;
	int _indexKnapsack;
	double _deltaFitness;

public:

	/**
	 * Constructor
	 */
	MQKPObjectAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~MQKPObjectAssignmentOperation();

	/**
	 * Función que aplica el cambio que define el propio objeto sobre la solución que recibe como argumento.
	 * @param[in, out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(MQKPSolution &solution);

	/**
	 * Función que asigna los valores la operación
	 * @param[in] indexObject El índice del objeto que se va a cambiar de mochila
	 * @param[in] indexKnapsack El índice de la mochila donde se insertará el objeto
	 * @param[in] deltaFitness La diferencia en fitness de aplicar dicha operación de asignación de un objeto a una mochila (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	void setValues(int indexObject, int indexKnapsack, double deltaFitness);

	/**
	 * Función que devuelve el objeto sujeto de la operación
	 * @return índice del objeto sujeto de la operación
	 *
	 * TODO LEER he modificado el return de unsigned a int, para poder marcar operaciones como "sin asignar" (con el objeto a -1)
	 */
	int getObj(){
		return _indexObj;
	}

	/**
	 * Función que devuelve la diferencia en fitness de la operación,
	 * @return Diferencia en fitness de la operación (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	double getDeltaFitness(){
		return _deltaFitness;
	}

	/**
	 * Función que devuelve la mochila objeto de la operación
	 * @return mochila objeto de la operación
	 */
	unsigned getKnapsack(){
		return _indexKnapsack;
	}
};

#endif
