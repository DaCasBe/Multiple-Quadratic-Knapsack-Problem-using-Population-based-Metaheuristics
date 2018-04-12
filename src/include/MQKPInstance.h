/**
 * MQKPInstance.h
 * 
 * Fichero que define la clase MQKPInstance. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPINSTANCE_H__
#define __MQKPINSTANCE_H__

#ifndef __MQKPSOLUTION_H__
#include "MQKPSolution.h"
#else
class MQKPSolution;
#endif

#include <vector>
using namespace std;

/**
 * Clase que almacena la información de una instancia del problema MQKP
 */
class MQKPInstance {
protected:
	/*Definir las variables miembro
	 * _numKnapsacks Entero que indica el número de mochilas que se va a considerar. Este no se lee del fichero, sino que lo establecéis vosotros
	 * _numObjs Entero donde se almacenará el número de objetos del problema
	 * _profits Matriz donde se van a almacenar los beneficios de los objetos según lo indicado arriba. HAY QUE RESERVAR SU MEMORIA
	 * _weights Vector con los pesos de los objetos. HAY QUE RESERVAR SU MEMORIA
	 * _capacities Vector con las capacidades de las mochilas. HAY QUE RESERVAR SU MEMORIA. Para evitar problemas, reservadlo con capacidad (1 + numKnapsacks) y utilizadlo desde el índice 1 en adelante
	 */
	int _numKnapsacks;
	int _numObjs;
	double ** _profits;
	double * _weights;
	double * _capacities;

public:
	/**
	 * Constructor por defecto
	 */
	MQKPInstance();

	/**
	 * Destructor
	 */
	~MQKPInstance();

	/**
	 * Función de lectura de un fichero de entrada
	 * @param[in] filename Nombre del fichero donde están los datos de la instancia
	 * @param[in] numKnapsacks Entero que indica el número de mochilas que se va a considerar. Este no se lee del fichero, sino que lo establecéis vosotros
	 */
	void readInstance(char *filename, int numKnapsacks);

	/**
	 * Funciones getter que devuelven la información que se consulte acerca de la instancia del problema
	 */
	int getNumObjs();
	int getNumKnapsacks();
	double getWeight(int object);
	double getCapacity(int knapsack);
	double getProfit(int object);
	double getProfit(int o1, int o2);

	/**
	 * Función que devuelve por cuanto se viola la capacidad de la mochila que está más cargada de más
	 * @param[in] solution Referencia a un objeto que representa una solución al problema
	 * @return Máxima violación de las capacidades de las mochilas
	 */
	double getMaxCapacityViolation(MQKPSolution &solution);

	/**
	 * Función que calcula la suma de beneficios individuales y cuadráticos de los objetos en mochilas
	 * @param[in] solution Referencia a un objeto que representa una solución al problema
	 * @return Suma de los beneficios individuales y cuadráticos de los objetos en las mochilas
	 */
	double getSumProfits(MQKPSolution &solution);

	/**
	 * Función que genera una permutación de los enteros de 0 a (size - 1)
	 * @param[in] size Tamaño de la permutación
	 * @param[out] perm Vector donde se almacenará la permutación
	 */
	static void randomPermutation(int size, vector<int> &perm);

	/**
	 * Función que calcula la diferencia en la suma de los beneficios si a la solución se le aplicase la asignación del objeto indexObject a la mochila indexKnapsack
	 * @param[in] solution Referencia a un objeto que representa una solución al problema.
	 * @param[in] indexObject Índice del objeto que se pondría en otra mochila
	 * @param[in] indexKnapsack Índice de la mochila donde se pondría el objeto. Puede ser 0, indicando que se saca el objeto de la mochila en la que esté
	 *
	 * @return Diferencia en la suma de los beneficios si a la solución se le aplicase la asignación del objeto indexObject a la mochila indexKnapsack
	 *
	 */
	double getDeltaSumProfits(MQKPSolution &solution, int indexObject, int indexKnapsack);

	/**
	 * Función que calcula la diferencia en la máxima violación de alguna de las capacidades de las mochilas si a la solución se le aplicase la asignación del objeto indexObject a la mochila indexKnapsack
	 * @param[in] solution Referencia a un objeto que representa una solución al problema.
	 * @param[in] indexObject Índice del objeto que se pondría en otra mochila
	 * @param[in] indexKnapsack Índice de la mochila donde se pondría el objeto. Puede ser 0, indicando que se saca el objeto de la mochila en la que esté
	 *
	 * @return Diferencia en la suma de los beneficios si a la solución se le aplicase la asignación del objeto indexObject a la mochila indexKnapsack
	 *
	 */
	double getDeltaMaxCapacityViolation(MQKPSolution &solution, int indexObject, int indexKnapsack);
};

#endif

