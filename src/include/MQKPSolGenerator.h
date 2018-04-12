
/**
 * MQKPSolGenerator.h
 * 
 * Fichero que define la clase MQKPSolGenerator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
*/


#ifndef __MQKPSOLGENERATOR_H__
#define __MQKPSOLGENERATOR_H__

#include "MQKPInstance.h"
#include "MQKPSolution.h"

/**
 * Clase que genera una solución aleatoria al problema MQKP
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de número enteros: de 1 a M para objetos que están en alguna de las M mochilas y 0 para objetos que no están en ninguna mochilas
 */
class MQKPSolGenerator {

public:

	/**
	 * Función que genera una solución aleatoria para el problema de las múltiples mochilas cuadráticas
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema MQKP
	 * @param[out] solution Referencia a un objeto que representa una solución al problema. IMPORTANTE: debe estar correctamente inicializado. En particular, su vector interno debe haber sido reservado previamente.
	 */
	static void genRandomSol(MQKPInstance &instance, MQKPSolution &solution);
};

#endif
