/*
 * MQKPGeneticAlgorithm.h
 *
 * Fichero que define la clase MQKPGeneticAlgorithm. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPGENETICALGORITHM_H_
#define INCLUDE_MQKPGENETICALGORITHM_H_

#include <MQKPMetaheuristic.h>
#include <MQKPSolution.h>
#include <SelectionOperator.h>
#include <MQKPCrossoverOperator.h>
#include <MQKPMutationOperator.h>
#include <TournamentSelector.h>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Clase que implementa un Algoritmo Genético Generacional con Elitismo para el MQKP
 */
class MQKPGeneticAlgorithm: public MQKPMetaheuristic {
protected:
	/**
	 * Variables miembro de la clase:
	 *  _popSize Tamaño de la población
	 *  _population Conjunto de individuos en la población
	 *  _selector Operador de selección
	 *  _crossoverOp Operador de cruce
	 *  _mutOp Operador de mutación
	 *  _instancia Instancia del problema abordada
	 */
	unsigned _popSize;
	vector<Solution*> _population;
	SelectionOperator *_selector = NULL;
	MQKPCrossoverOperator *_crossoverOp = NULL;
	MQKPMutationOperator *_mutOp = NULL;
	MQKPInstance *_instance = NULL;

	/**
	 * vectores donde se almacenan los resultados
	 *  _results valores fitness de las soluciones generadas
	 *  _popMeanResults Media de los valores fitness presentes en la población
	 *  _offMeanResults Media de los valores fitness de las nuevas soluciones generadas
	 *  _bestPerIterations Mejor valor en cada iteración
	 */
	vector<double> _results;
	vector<double> _popMeanResults;
	vector<double> _offMeanResults;
	vector<double> _bestPerIterations;

	/**
	 * Función que busca el índice de la mejor solución en un vector
	 * @param[in] set Vector de soluciones
	 * @return índice de la mejor solución
	 */
	unsigned indexBest(vector<Solution*> &set) {

		//TODO buscar el índice de la mejor solución en set
		Solution * best=set[0];
		unsigned indexBest=0;

		for(unsigned i=1;i<set.size();i++){
			if(set[i]->getFitness()>best->getFitness()){
				best=set[i];
				indexBest=i;
			}
		}

		return indexBest;
	}

	/**
	 * Función que busca el índice de la peor solución en un vector
	 * @param[in] set Vector de soluciones
	 * @return índice de la peor solución
	 */
	unsigned indexWorst(vector<Solution*> &set) {

		//TODO buscar el índice de la peor solución en set
		Solution * worst=set[0];
		unsigned indexWorst=0;

		for(unsigned i=1;i<set.size();i++){
			if(set[i]->getFitness()<worst->getFitness()){
				worst=set[i];
				indexWorst=i;
			}
		}

		return indexWorst;
	}

	/**
	 * Función que actualiza la nueva población, dado el conjunto de descendientes generado
	 * @param[in] offspring Vector de soluciones descendientes generadas
	 */
	void selectNewPopulation(vector<Solution*> &offspring) {

		/**
		 * TODO
		 * La nueva población será la de descendientes, pero
		 * en caso de que la población actual tenga una mejor solución que la mejor en offspring,
		 * la mejor de la población actual reemplazará a la peor de offspring.
		 *
		 * 1. Encontrar el índice de la mejor solución en _population
		 * 2. Encontrar el índice de la mejor solución en offspring
		 * 3. Si la mejor solución de _population es mejor que la mejor solución de offspring
		 *   a. Encontrar el índice de la peor solución en offspring
		 *   b. Hacer que dicha solución copie a la mejor de _population
		 * 4. Eliminar los individuos de la población actual (liberando memoria)
		 * 5. Almacenar los individuos de offspring en la población actual
		 */
		unsigned int indexBestPop = indexBest(_population);
		unsigned int indexBestOff = indexBest(offspring);

		if(MQKPEvaluator::compare(_population[indexBestPop]->getFitness(),offspring[indexBestOff]->getFitness())>0){
			offspring[indexWorst(offspring)]=_population[indexBestPop];
		}

		//Eliminar los individuos de la población actual
		for (unsigned i = 0; i < _popSize; i++) {
			delete (_population.back());
			_population.pop_back();
		}

		//Copiar los hijos en la población actual
		unsigned offSize = (unsigned) offspring.size();

		for (unsigned i = 0; i < offSize; i++) {
			_population.push_back(offspring.back());
			offspring.pop_back();
		}
	}

	/**
	 * Función que evalúa las soluciones de un vector
	 * @param[in,out] set Conjunto de soluciones a evaluar. Una vez evaluados, les asigna el fitness
	 */
	void evaluate(vector<Solution*> &set) {

		for (Solution *sol : set) {
			MQKPSolution *s = (MQKPSolution*) sol;
			double fitness;

			/**
			 * TODO
			 * Se ha añadido una funcionalidad en Solution para detectar si su fitness ya estaba calculado,
			 * útil para cuando el descendiente es copia del padre. Por tanto, sólo se evaluarán las soluciones
			 * que no tentan un fitness válido
			 */
			if (!(s->hasValidFitness())) {

				//Evaluar
				fitness=MQKPEvaluator::computeFitness(*_instance,*s);
				_results.push_back(fitness);
				s->setFitness(fitness);

				//Actualizar la mejor solución
				if (MQKPEvaluator::compare(fitness, _bestSolution->getFitness()) > 0){
					_bestSolution->copy(*s);
				}
			}
		}
	}

	/**
	 * Función que inicializa la población del genético
	 * @param[in] popSize Tamaño de la población
	 */
	void initPopulation(unsigned popSize) {

		if (_instance == NULL) {
			cerr
					<< "The evolutionary algorithm has not been initialised. At least, its _instance is NULL"
					<< endl;
			exit(1);
		}

		/**
		 * TODO
		 * 1. Generar soluciones aleatorias
		 * 2. Evaluarlas
		 * 3. Actualizar la mejor solución _bestSolution
		 * 4. Insertarlas en la población
		 */
		MQKPSolution *sol;
		sol=new MQKPSolution(*_instance);
		double fitness;

		for (unsigned i = 0; i < popSize; i++) {
			MQKPSolGenerator::genRandomSol(*_instance,*sol);
			fitness=MQKPEvaluator::computeFitness(*_instance,*sol);

			_results.push_back(fitness);
			_population.push_back(sol);
		}
	}

	/**
	 * Función que calcula la media del fitness de un conjunto de soluciones
	 * @param[int] set Conjunto de soluciones del que obtener la media del fitness
	 * @return media del fitness de las soluciones
	 */
	double computeMeanFitness(vector<Solution*>&set) {
		double mean = 0.;
		unsigned numElements = (unsigned) set.size();
		double i_numElements = 1. / numElements;

		for (auto sol : set) {
			double fitness = sol->getFitness();
			mean += (fitness * i_numElements);
		}

		return mean;
	}

public:

	/**
	 * Constructor
	 */
	MQKPGeneticAlgorithm() {
		_popSize = 0;
		_bestSolution = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPGeneticAlgorithm() {

		for (unsigned i = 0; i < _popSize; i++) {
			delete (_population.back());
			_population.pop_back();
		}

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	}

	/**
	 * Función que ejecuta el algoritmo genético
	 * @param[in] stopCondition Objeto que define cuándo se llega a la condición de parada
	 */
	virtual void run(MQKPStopCondition &stopCondition) {

		/**
		 * TODO
		 * 1. Inicializar la poblacion
		 * 2. Mientras no se alcance la condición de parada
		 *   a. Almacenar la media de la población actual y la mejor solución
		 *   b. Seleccionar los padres
		 *   c. Cruzar los padres
		 *   d. Mutar los descendientes
		 *   f. Almacenar la media de los descendientes
		 *   g. Seleccionar la nueva población
		 *
		 * 3. Almacenar la media de la poblaciónfinal y la mejor solución
		 */

		initPopulation(_popSize);

		while (stopCondition.reached() == false) {

			_popMeanResults.push_back(computeMeanFitness(_population));
			_bestPerIterations.push_back(
					_population.at(indexBest(_population))->getFitness());

			vector<Solution*> parents;
			_selector->select(_population,parents);

			vector<Solution*> offspring;
			_crossoverOp->cross(parents,offspring);

			_offMeanResults.push_back(computeMeanFitness(offspring));

			_mutOp->mutate(offspring);

			computeMeanFitness(offspring);

			selectNewPopulation(offspring);

			stopCondition.notifyIteration();
		}

		_popMeanResults.push_back(computeMeanFitness(_population));
		_bestPerIterations.push_back(
				_population.at(indexBest(_population))->getFitness());
	}

	/**
	 * Función que inicializa el algoritmo
	 * @param[in] popSize Tamaño de la población
	 * @param[in] instance Instancia del problema a abordar
	 */
	void initialise(unsigned popSize, MQKPInstance &instance) {
		_instance = &instance;

		if (popSize <= 0) {
			cerr << "The population size must be greater than 0" << endl;
			exit(1);
		}

		if (_bestSolution != NULL) {
			delete _bestSolution;
			_bestSolution = NULL;
		}

		_bestSolution = new MQKPSolution(*_instance);
		MQKPSolGenerator::genRandomSol(*_instance, *_bestSolution);
		double fitness = MQKPEvaluator::computeFitness(*_instance, *_bestSolution);
		_bestSolution->setFitness(fitness);

		_popSize = popSize;

		/**
		 * Se está configurando para que utilice torneo binario, los operadores genéticos implementados y dichas probabilidades,
		 * pero se podrían usar otros operadores simplemente cambiando el objeto.
		 */
		if (_crossoverOp == NULL) {
			_crossoverOp = new MQKPCrossoverOperator(0.8, *_instance);
		}

		if (_mutOp == NULL) {
			_mutOp = new MQKPMutationOperator((0.25 / _instance->getNumObjs()),
					*_instance);
		}

		if (_selector == NULL) {
			_selector = new TournamentSelector(2); //Se puede probar con varios valores de presión selectiva
		}
	}

	/**
	 * Función que devuelve el vector de fitness de las soluciones generadas
	 */
	vector<double>& getResults() {
		return _results;
	}

	/**
	 * Función que asigna un nuevo operador de cruce
	 */
	void setCrossoverOp(MQKPCrossoverOperator* crossoverOp) {

		if (_crossoverOp != NULL)
			delete _crossoverOp;

		_crossoverOp = crossoverOp;
	}

	/**
	 * Función que asigna un nuevo operador de mutación
	 */
	void setMutOp(MQKPMutationOperator* mutOp) {

		if (_mutOp != NULL)
			delete _mutOp;

		_mutOp = mutOp;
	}

	/**
	 * Función que asigna un nuevo operador de selección
	 */
	void setSelector(SelectionOperator* selector) {

		if (_selector != NULL)
			delete _selector;

		_selector = selector;
	}

	/**
	 * Función que devuelve el vector con la media de las poblaciones de descendientes generadas en cada iteración
	 */
	const vector<double>& getOffMeanResults() const {
		return _offMeanResults;
	}

	/**
	 * Función que devuelve el vector con la media de la población actual en cada iteración
	 */
	const vector<double>& getPopMeanResults() const {
		return _popMeanResults;
	}

	/**
	 * Función que devuelve la mejor solución de la población en cada iteración
	 */
	const vector<double>& getBestsPerIterations() const {
		return _bestPerIterations;
	}
};

#endif /* INCLUDE_MQKPGENETICALGORITHM_H_ */
