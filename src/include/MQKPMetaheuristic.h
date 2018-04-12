/*
 * MQKPMetaheuristic.h
 *
 * Fichero que define la clase MQKPMetaheuristic. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPMETAHEURISTIC_H_
#define INCLUDE_MQKPMETAHEURISTIC_H_

#include <MQKPSolution.h>
#include <MQKPStopCondition.h>
#include <cstdlib>

/**
 * Clase abstracta que define los métodos comunes para las metaheurísticas para el MQKP.
 */
class MQKPMetaheuristic {

protected:
	MQKPSolution *_bestSolution;

public:
	/**
	 * Constructor
	 */
	MQKPMetaheuristic(){
		_bestSolution = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPMetaheuristic(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
	virtual void run (MQKPStopCondition &stopCondition) = 0;


	/**
	 * Función que devuelve la mejor solución encontrada hasta el momento.
	 * Es responsabilidad de cada metaheurística concreta el mantener actualizada la variable _bestSolution
	 * @return La mejor solución encontradas hasta el momento
	 */
	MQKPSolution*& getBestSolution(){
		return _bestSolution;
	}
};



#endif /* INCLUDE_MQKPMETAHEURISTIC_H_ */
