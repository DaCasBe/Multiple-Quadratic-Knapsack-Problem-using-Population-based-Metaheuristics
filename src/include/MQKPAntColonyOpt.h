/*
 * MQKPAntColonyOpt.h
 *
 * Fichero que define la clase MQKPAntColonyOpt. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPANTCOLONYOPT_H_
#define INCLUDE_MQKPANTCOLONYOPT_H_

#include <MQKPMetaheuristic.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPObjectAssignmentOperation.h>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * Clase que implementa un sistema de colonias de  hormigas para el MQKP.
 */

class MQKPAntColonyOpt: public MQKPMetaheuristic {

	/**
	 * Clase que define implementa internamente a una hormiga para el MQKP
	 */
	class MQKPAnt {
	protected:

		/**
		 * Variables miembro de la clase
		 * Básicas:
		 *  _colony puntero a la clase que la engloba (su colonia)
		 *  _sol solución sobre la que trabaja la hormiga
		 *
		 * Adicionales
		 *  _objectsLeft Conjunto de objetos que no se han insertado aún en ninguna mochila. Esta variable permite acelerar el proceso de construcción de soluciones de la hormiga. Su objetivo es mayormente hacer el proceso más eficiente
		 *  _candidateListSize Número de opciones a considerar para añadir una nueva componente a la solución. Esta variable permite acelerar el proceso de construcción de soluciones, al impedir que se examinen todas las opciones posibles.
		 */
		MQKPAntColonyOpt *_colony;
		MQKPSolution *_sol;
		unordered_set<unsigned> _objectsLeft;
		double _candidateListSize;

		/**
		 * Función que suma los valores de un vector. Se usará para conocer la suma de los valores de relevancia de las opciones que tiene la hormiga
		 * @param[in] significances vector con las relevancias de las opciones de la hormiga
		 * @return suma de los valores del vector de relevancias
		 */
		double sumSignificances(vector<double> &significances) {

			//TODO devolver la suma de los elementos en significances
			...

			return sum;
		}

		/**
		 * Función que devuelve un conjunto de alternativas que tiene una hormiga para añadir una nueva componente a su solución.
		 * @param[out] alternatives Vector donde se almacenan las alternativas que tiene la hormiga
		 * @param[out] significances Vector con los valores de relevancia de las alternativas creadas
		 */
		void createAlternatives(
				vector<MQKPObjectAssignmentOperation*> &alternatives,
				vector<double> &significances) {

			//Obtener la información de la colonia
			MQKPInstance *instance = _colony->_instance;
			double alpha = _colony->_alpha;
			double beta = _colony->_beta;
			vector<vector<double>*> &phMatrix = _colony->_phMatrix;

			unsigned numKnapsacks = instance->getNumKnapsacks();
			unsigned numTries = 0;

			//Para cada objeto que aún no está en ninguna mochila
			for (auto indexObj : _objectsLeft) {

				//Para cada posible mochila y sin superar el número de intentos
				for (unsigned j = 1;
						j <= numKnapsacks && numTries < _candidateListSize;
						j++) {

					//Si el movimiento viola la capacidad de la mochila, descartarlo
					double maxViolation =
							instance->getDeltaMaxCapacityViolation(*_sol,
									indexObj, j);

					if (maxViolation > 0)
						continue;

					//Obtener el deltaFitness y contarlo como un intento (como no viola, será iguala a DeltaSumProfits)
					double deltaFitness = instance->getDeltaSumProfits(*_sol,
							indexObj, j);
					numTries++;

					//Saltarse las opciones a peor o nulas (no debieran ocurrir si no hay profits negativos, "pero pa por si")
					if (deltaFitness <= 0)
						continue;

					/**
					 * TODO
					 * 1. Crear la operación
					 * 2. Calcular su relevancia como la densidad del objeto^beta * cantidadPheromona[objeto][mochila]^alpha
					 * 3. Incluir la operación en las alternatives y la relevancia en significances
					 */
					MQKPObjectAssignmentOperation *al =
							new MQKPObjectAssignmentOperation();
					double density = ...
					...
				}
			}
		}

		/**
		 * Función que devuelve la mejor alternativa de la hormiga para añadir una nueva componente a su solución, de entre un conjunto de alternativas aleatorias evaluadas.
		 * @param[out] op alternativa seleccionada como la mejor para la hormiga
		 */
		void selectBestAlternative(MQKPObjectAssignmentOperation &op) {

			//Obtener la información de la colonia
			MQKPInstance *instance = _colony->_instance;
			vector<vector<double>*> &phMatrix = _colony->_phMatrix;
			double beta = _colony->_beta;
			double alpha = _colony->_alpha;

			unsigned numKnapsacks = instance->getNumKnapsacks();
			double bestSignificance = -1;
			unsigned numTries = 0;

			//Para cada objeto que aún no está en ninguna mochila
			for (auto indexObj : _objectsLeft) {

				//Para cada posible mochila y sin superar el número de intentos
				for (unsigned j = 1;
						j <= numKnapsacks && numTries < _candidateListSize;
						j++) {

					//TODO Si el movimiento viola la capacidad de la mochila, descartarlo
					...

					//TODO Obtener el deltaFitness y contarlo como un intento (como no viola, será iguala a DeltaSumProfits)
					...

					//TODO Saltarse las opciones a peor o nulas (no debieran ocurrir si no hay profits negativos, "pero pa por si")
					...

					/**
					 * TODO
					 * 1. Calcular su relevancia como la densidad del objeto^beta * cantidadPheromona[objeto][mochila]^alpha
					 * 2. Si es mejor que la mejor hasta ahora, guardarla en op
					 */
					...
				}
			}
		}

		/**
		 * Función que libera la memoria de las alternativas creadas por la hormiga para elegir una
		 * @param[in,out] alt Vector con las alternativas a liberar de memoria
		 */
		void freeAlternatives(vector<MQKPObjectAssignmentOperation*> &alt) {

			for (auto altOp : alt) {
				delete altOp;
			}

			alt.clear();
		}

	public:

		/**
		 * Constructor de una hormiga
		 * @param[in] candidateListSize Número de soluciones a evaluar en cada paso
		 * @param[in] colony Puntero a la colonia a la que pertenece la hormiga
		 */
		MQKPAnt(unsigned candidateListSize, MQKPAntColonyOpt *colony) {
			_colony = colony;
			_sol = new MQKPSolution(*(colony->_instance));
			_candidateListSize = candidateListSize;
		}

		/**
		 * Destructor
		 */
		~MQKPAnt() {
			delete _sol;
			_sol = NULL;
		}

		/**
		 * Función que resetea la memoria de la hormiga para que empieze a generar una solución desde cero
		 */
		void resetSolution() {

			/**
			 * TODO
			 * 1. Asignar todos los objetos a la mochila 0 e insertarlos en la memoria _objectsLeft
			 * 2. Asignarle un fitness igual a cero
			 */
			...
		}

		/**
		 * Función que hace que la hormiga escoja una alternativa y la añada a su solución. También devuelve la opción escogida
		 * @param[out] operation Operación de asignación de un objeto a una mochila elegida por la hormiga
		 */
		void chooseOperation(MQKPObjectAssignmentOperation &operation) {

			//Decidir entre elegir la mejor altnerativa o una según probabilidades
			double randSample = (((double) rand()) / RAND_MAX);

			if (randSample < _colony->_q0) {
				selectBestAlternative(operation);
			} else {

				//Crear las alternativas
				vector<MQKPObjectAssignmentOperation*> alternatives;
				vector<double> significances;
				createAlternatives(alternatives, significances);

				//Si la hormiga no encontró alternativas, salir
				if (significances.size() <= 0) {
					return;
				}

				//TODO Elegir una de las alternativas según probabilidades proporcionales a sus relevancias
				double v_sumSignificances = sumSignificances(significances);
				double randSample = (((double) rand()) / RAND_MAX)
						* v_sumSignificances;
				randSample -= significances.at(0);
				unsigned opSelected = 0;

				while (...) {
					...
				}

				//Asignar la alternativa elegida en operation
				unsigned indexObj = alternatives.at(opSelected)->getObj();
				unsigned indexKnapsack =
						alternatives.at(opSelected)->getKnapsack();
				double deltaFitness =
						alternatives.at(opSelected)->getDeltaFitness();
				operation.setValues(indexObj, indexKnapsack, deltaFitness);

				//Liberar las alterantivas de memoria
				freeAlternatives(alternatives);
			}

			//TODO Si se seleccionó alguna alternativa, aplicarla a la solución y eliminar el objeto correspondiente de _objectsLeft
			if (operation.getObj() >= 0) {
				...
			}
		}

		/**
		 * Función que devuelve la solución construída por la hormiga
		 * @return Solución construída por la hormiga
		 */
		MQKPSolution & getSolution() {
			return *_sol;
		}
	};

protected:

	/**
	 * Variables miembro de la colonia de hormigas:
	 *  _q0 Probabilidad de que cada hormiga eleja la mejor alternativa en vez de una en base a probabilidades
	 *  _alpha Relevancia de la cantidad de feromona al calcular la relevancia de cada alternativa
	 *  _beta Relevancia de la información heurística al calcular la relevancia de cada alternativa
	 *  _initTau Cantidad de feromona inicial en el entorno (no interesa que sea 0)
	 *  _evaporation Porcentaje de feromona que se evapora
	 *  _phMatrix Matriz de feromona 2D. El primer índice recorre los objetos del problema. El segundo recorre las mochilas.
	 *  _ants vector hormigas de la colonia
	 *  _instance Instancia del problema abordado
	 */
	double _q0;
	double _alpha;
	double _beta;
	double _initTau;
	double _evaporation;
	vector<vector<double>*> _phMatrix;
	vector<MQKPAnt*> _ants;
	MQKPInstance *_instance;

	/**
	 * vectores donde se almacenan los resultados
	 *  _results valores fitness de las soluciones generadas
	 *  _bestPerIteration Mejor fitness generado en cada iteración
	 *  _currentItMeans Media de los valores fitness de las soluciones generadas en cada iteración
	 */
	vector<double> _results;
	vector<double> _bestPerIteration;
	vector<double> _currentItMeans;

	/**
	 * Función que aplica la actualización local de feromona (cuando una hormiga anda, se lleva parte de pheromona; ver fórmula en diapositivas)
	 * @param[in] op Opción que escogió la hormiga y donde se va a aplicar la actualización
	 */
	void localUpdate(MQKPObjectAssignmentOperation &op) {
		...
	}

	/**
	 * Función que libera a las hormigas para que construyan sus soluciones
	 */
	void releaseAnts() {

		unordered_set<unsigned> movingAnts;
		unordered_set<unsigned> stoppedAnts;
		int i = 0;

		//TODO Resetear las soluciones de cada hormiga e insertar sus índices en movingAnts
		for (auto ant : _ants) {
			...
			i++;
		}

		//Mientras haya hormigas que se estén moviendo
		while (movingAnts.size() > 0) {
			stoppedAnts.clear();

			//TODO Mover cada hormiga
			for (auto iAnt : movingAnts) {
				MQKPAnt *ant = _ants[iAnt];
				MQKPObjectAssignmentOperation op;
				op.setValues(-1, -1, 0);
				...

				//TODO Si la hormiga se ha movido, entonces aplicar la actualización local de feromona. Si no, apuntarla en stoppedAnts para eliminarla después de movingAnts
				if (...) {
					...
				} else {
					...
				}
			}

			for (auto iAnt : stoppedAnts) {
				movingAnts.erase(iAnt);
			}
		}

		//Actualizar la mejor Solución
		double bestFitness = _bestSolution->getFitness();

		for (auto ant : _ants) {
			MQKPSolution &sol = ant->getSolution();
			double currentFitness = ant->getSolution().getFitness();

			if (MQKPEvaluator::compare(currentFitness, bestFitness) > 0) {
				_bestSolution->copy(sol);
				bestFitness = currentFitness;
			}
		}
	}

	/**
	 * Función que guarda estadísticas de las soluciones generadas en sus vectores miembro
	 */
	void saveStatistics() {

		MQKPSolution &firstSol = _ants.at(0)->getSolution();
		double bestFitness = firstSol.getFitness();
		double meanFitness = 0.;
		unsigned numAnts = (unsigned) _ants.size();
		double inverseNumAnts = 1. / numAnts;

		for (auto ant : _ants) {
			MQKPSolution &sol = ant->getSolution();
			double currentFitness = sol.getFitness();
			_results.push_back(currentFitness);
			meanFitness += (currentFitness * inverseNumAnts);

			if (MQKPEvaluator::compare(currentFitness, bestFitness) > 0) {
				bestFitness = currentFitness;
			}
		}

		_bestPerIteration.push_back(bestFitness);
		_currentItMeans.push_back(meanFitness);
	}

	/**
	 * Función que ejecuta una iteración del algoritmo ACO, es decir, liberar las hormigas para que construyan sus soluciones, y actualizar la matriz de pheromona
	 */
	void iterate() {

		//TODO Liberar las hormigas
		...
		saveStatistics();

		//aplicar pheromona con la mejor solución
		unsigned numObjs = _instance->getNumObjs();
		double fitness = _bestSolution->getFitness();

		//TODO Para cada objeto, depositar feromona en el par objeto y mochila en la que está dicho objeto.
		for (unsigned i = 0; i < numObjs; i++) {
			...
		}
	}

public:
	/**
	 * Constructor
	 */
	MQKPAntColonyOpt() {
		_bestSolution = NULL;
		_q0 = 0.8;
		_alpha = 1;
		_beta = 1;
		_initTau = 0.1;
		_evaporation = 0.1;
		_instance = NULL;
	}

	/**
	 * Destructor
	 */
	~MQKPAntColonyOpt() {

		if (_bestSolution != NULL) {
			delete _bestSolution;
			_bestSolution = NULL;
		}

		for (auto ant : _ants) {
			delete ant;
		}
		_ants.clear();

		for (auto vector : _phMatrix) {
			vector->clear();
			delete vector;
		}

		_phMatrix.clear();
	}

	/**
	 * Función que inicializa el algoritmo
	 * @param[in] numAnts Número de hormigas en la colonia
	 * @param[in] q0 Probabilidad de que las hormigas elijan la mejor opción posible, en vez de basada en probabilidades
	 * @param[in] alpha Relevancia de la cantidad de feromona depositada al evaluar las alternativas
	 * @param[in] beta Relevancia de la heurística al evaluar las alternativas
	 * @param[in] initTau Cantidad inicial de feromona en el entorno
	 * @param[in] evaporation Ratio de evaporación de feromona
	 * @param[in] candidateListSize Número de alternativas que cada hormiga evalúa a la hora de elegir una opción a añadir a la solución
	 * @param[in] instance Instancia del problema que se va a abordar
	 */
	void initialise(unsigned numAnts, double q0, double alpha, double beta,
			double initTau, double evaporation, unsigned candidateListSize,
			MQKPInstance &instance) {
		_instance = &instance;
		_q0 = q0;
		_alpha = alpha;
		_beta = beta;
		_initTau = initTau;
		_evaporation = evaporation;

		if (numAnts <= 0) {
			cerr << "The number of ants must be greater than 0" << endl;
			exit(1);
		}

		if (_bestSolution != NULL) {
			delete _bestSolution;
			_bestSolution = NULL;
		}


		//Generación de una solución inicial para _bestSolution
		_bestSolution = new MQKPSolution(*_instance);
		MQKPSolGenerator::genRandomSol(*_instance, *_bestSolution);
		double fitness = MQKPEvaluator::computeFitness(*_instance,
				*_bestSolution);
		_bestSolution->setFitness(fitness);


		//TODO Creación de las hormigas
		for (unsigned i = 0; i < numAnts; i++) {
			...
		}


		//TODO Inicialización de la matriz de feromona con la feromona inicial
		unsigned numObjs = _instance->getNumObjs();
		unsigned numKnapsacks = _instance->getNumKnapsacks() + 1;

		for (unsigned i = 0; i < numObjs; i++) {
			vector<double> *aVector = new vector<double>;
			_phMatrix.push_back(aVector);

			for (unsigned j = 0; j < numKnapsacks; j++) {
				aVector->push_back(...);
			}
		}
	}

	/**
	 * Función que ejecuta el algoritmo ACO
	 * @param[in] stopCondition Objeto que define cuándo se llega a la condición de parada
	 */
	virtual void run(MQKPStopCondition &stopCondition) {

		if (_instance == NULL) {
			cerr << "The ACO algorithm has not been initialised" << endl;
			exit(1);
		}

		//TODO Mientras no se llegue a la condición de parada, iterar
		while (stopCondition.reached() == false) {
			...
			stopCondition.notifyIteration();
		}
	}

	/**
	 * Función que devuelve el vector con las mejores soluciones generadas por iteración
	 * @return Las mejores soluciones generadas en cada iteración
	 */
	const vector<double>& getBestPerIteration() const {
		return _bestPerIteration;
	}

	/**
	 * Función que devuelve el vector con la media de las soluciones generadas en cada iteración
	 * @return La media de las soluciones generadas en cada iteración
	 */
	const vector<double>& getAntsMeanResults() const {
		return _currentItMeans;
	}

	/**
	 * Función que devuelve el fitness de las soluciones generadas en cada momento
	 * @return El fitness de las soluciones generadas en cada momento
	 */
	vector<double>& getResults() {
		return _results;
	}
};

#endif /* INCLUDE_MQKPANTCOLONYOPT_H_ */
