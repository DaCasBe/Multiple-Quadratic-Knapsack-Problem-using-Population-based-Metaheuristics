/**
 * MQKPSolution.h
 * 
 * Fichero que define la clase MQKPSolution. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPSOLUTION_H__
#define __MQKPSOLUTION_H__

#ifndef __MQKPINSTANCE_H__
#include "MQKPInstance.h"
#else
class MQKPInstance;
#endif

#include "Solution.h"

/**
 * Clase que representa una solución al problema
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de número enteros: de 1 a M para objetos que están en alguna de las M mochilas y 0 para objetos que no están en ninguna mochilas
 *
 * TODO LEER he creado la superclase abstracta para hacer el selector genérico
 */
class MQKPSolution : public Solution {
protected:
	/* Definir las variables miembro
	 * _sol Vector de enteros que será la representación interna de la solución al problema
	 * _numObjs Entero donde se almacenará el número de objetos del problema
	 * _fitness valor double que almacena la calidad de la solución
	 */
	int * _sol;
	int _numObjs;
	double _fitness;
	bool _fitnessAssigned; //TODO LEER he añadido esta variable para saber qué individuos tienen el fitness asignado

public:
	/**
	 * Constructor
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema MQKP
	 */
	MQKPSolution(MQKPInstance &instance);

	/**
	 * Destructor
	 */
	virtual ~MQKPSolution();

	/**
	 * Función que asigna un objeto a la mochila indicada
	 * @param[in] object Índice del objeto a insertar en la mochila indicada
	 * @param[in] knapsack Índice de la mochila donde insertar el objeto
	 */
	void putObjectIn(int object, int knapsack);

	/**
	 * Función que devuelve la mochila en la que está insertado un objeto
	 * @param[in] object Índice del objeto consultado
	 * @return Índice de la mochila en la que está insertado el objeto
	 */
	int whereIsObject(int object);

	/**
	 * Función que devuelve el fitness de la solución
	 *
	 * @return fitness de la solución
	 *
	 * TODO LEER hay que poner el método virtual, para sobreescribir la definición heredada de la superclase
	 */
	virtual double getFitness() const;

	/**
	 * Función que asigna el fitness de la solución
	 * @param[in] fitness Fitness de la solución
	 */
	void setFitness(double fitness);

	/**
	 * Función que copia la información de otra solución
	 * @param[in] solution La solución de donde copiar la información
	 *
	 * TODO LEER hay que poner el método de copia virtual y cambiar el argumento, para sobreescribir la definición heredada
	 */
	virtual void copy(Solution &solution);

	/**
	 * Función que indica si el fitness de la solución es válido (deja de serlo si se cambia un objeto de mochila; y se convierte en válido cuando se le asigna)
	 *
	 * TODO LEER he creado este método para ahorrarnos las evaluaciones de soluciones que son copias de otras
	 */
	bool hasValidFitness(){
		return _fitnessAssigned;
	}
};

#endif
