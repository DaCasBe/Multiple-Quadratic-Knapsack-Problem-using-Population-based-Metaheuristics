/*
 * MQKPCrossoverOperator.h
 *
 * Fichero que define la clase MQKPCrossoverOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPCROSSOVEROPERATOR_H_
#define INCLUDE_MQKPCROSSOVEROPERATOR_H_

#include <MQKPSolution.h>
#include <Solution.h>
#include <MQKPInstance.h>
#include <vector>

using namespace std;

/**
 * Clase que implementa un operador de cruce uniforme para el problema MQKP. Su idea es la misma que la de un cruce uniforme para codificación entera
 */
class MQKPCrossoverOperator {

protected:
	/**
	 * Variables miembro de la clase:
	 *  - _instance Instancia de problema abordada. Se utiliza únicamente para crear nuevos objetos MQKPSolution
	 *  - _numObjs almacena el número de objetos de la instancia abordada para reducir el número de consultas a la instancia
	 *  - _crossProb probabilidad de cruce
	 */
	MQKPInstance *_instance;
	unsigned _numObjs;
	double _crossProb;

	/**
	 * Función que cruza dos soluciones según su probabilidad de cruce. En caso de que no haya crucce, la solución devuelta será igual al primer padre
	 * @param[in] s1 primer padre
	 * @param[in] s2 segundo padre
	 * @return Nuevo objeto solución descendiente de haber cruzado s1 y s2. La solución se reserva dinámicamente en memoria. Es responsabilidad del invocador de gestionarla correctamente.
	 */
	MQKPSolution * cross(Solution *s1, Solution *s2) {
		MQKPSolution * sol = new MQKPSolution(*_instance);
		MQKPSolution * sol1 = (MQKPSolution *) s1;
		MQKPSolution * sol2 = (MQKPSolution *) s2;

		double randSample = (((double) rand()) / RAND_MAX);

		if (randSample < _crossProb) {

			//TODO Cruce uniforme de los dos padres,
			//que va eligiendo el valor de uno de los padres aleatoriamente,
			//con la misma probabilidad, para cada gen
			...
		} else {
			//Si no hay cruce, copiar el primer padre
			sol->copy(*sol1);
		}

		return sol;
	}

public:

	/**
	 * Constructor
	 * @param[in] crossProb Probabilidad de cruce
	 * @param[in] instance Instancia del problema abordada
	 */
	MQKPCrossoverOperator(double crossProb, MQKPInstance &instance) {
		_instance = &instance;
		_numObjs = instance.getNumObjs();
		_crossProb = crossProb;
	}

	/**
	 * Función que aplica el cruce a una población de padres.
	 * @param[in] parents Vector de padres. El cruce se aplica entre cada dos padres consecutivos (1,2), (3,4)...
	 * @param[out] offspring Vector donde se almacenan los descendientes generados. IMPORTANTE: Esta función reserva memoria dinámicamente para las nuevas soluciones en offspring, por lo que es responsabilidad de quien la invoque de gestionar la memoria adecuadamente.
	 */
	void cross(vector<Solution*> &parents, vector<Solution*> &offspring) {

		unsigned numParents = (unsigned) parents.size();

		//TODO aplicar cruce entre cada dos padres consecutivos (1,2), (3,4), ...
		for (...) {
			MQKPSolution *sol = cross(...);
			offspring.push_back(sol);
		}
	}
};

#endif /* INCLUDE_MQKPCROSSOVEROPERATOR_H_ */
