/*
 * MQKPChangeOperation.h
 *
 * Fichero que declara la clase MQKPChangeOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPCHANGEOPERATION_H__
#define __MQKPCHANGEOPERATION_H__

#include <MQKPSolution.h>

/**
 * Clase abstracta para representar cualquier operación de modificación sobre una solución.
 */
class MQKPChangeOperation{
public:

	/**
	 * Destructor
	 */
	virtual ~MQKPChangeOperation(){
	}

	/**
	 * Función que aplica el cambio que define el objeto sobre la solución que recibe como argumento
	 * @param[in,out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(MQKPSolution &solution) = 0;
};

#endif
