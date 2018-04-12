/*	main.cpp
 *
 * Fichero que define la función main para ejecutar experimentos sobre el Multiple Quadratic Knapsack Problem.
 * En particular, estos experimentos generan varias búsquedas con un algoritmo evolutivo y un algoritmo de colonias de hormigas sobre cuatro instancias.
 *
 * Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 *
 * TODO LEER: el algoritmo ACO requiere hacer varias operaciones por paso y podría consumir los 5 segundos habiendo generado muy pocas soluciones. Esto impidiría observar su comportamiento genérico. Para evitar esta limitación, el programa que se ejecute debe compilarse con alguna opción de optimización, como -O3
 */

//Definición de algunos parámetros de la experimentación
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000

#include <MQKPEvaluator.h>
#include <MQKPInstance.h>
#include <MQKPSolGenerator.h>
#include <MQKPSolution.h>
#include <MQKPGeneticAlgorithm.h>
#include <MQKPAntColonyOpt.h>
#include <MQKPStopCondition.h>
#include <Timer.h>

#include <iostream>
using namespace std;

//Definición externa de las semillas para el generador de números aleatorios (en seeds.cpp)
//extern unsigned int numSeeds;
extern unsigned int seeds[];

/**
 * Función que ejecuta el algoritmo evolutivo, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que se van generando.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[out] bestPerIterations vector donde se almacenarán los mejores valores fitness de cada generación
 * @param[out] popMean vector donde se almacenarán los valores fitness medios de cada generación
 * @param[out] offMean vector donde se almacenarán los valores fitness medios de la población de descendientes
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runAGAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &popMean, vector<double> &offMean,
		MQKPInstance &instance) {

	//Inicialización
	MQKPGeneticAlgorithm ga;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	ga.initialise(60, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Ejecutar el GA
	ga.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsGA = ga.getResults();

	for (double aResult : resultsGA) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = ga.getBestsPerIterations();
	popMean = ga.getPopMeanResults();
	offMean = ga.getOffMeanResults();
}

/**
 * Función que ejecuta el sistema de colonia de hormigas, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que se van generando.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[out] bestPerIterations vector donde se almacenarán los mejores valores fitness de cada iteracion del algoritmo
 * @param[out] antsMean vector donde se almacenarán los valores fitness medios de cada iteración del algoritmo
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runAnACOExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &antsMean, MQKPInstance &instance) {

	//Inicialización
	MQKPAntColonyOpt aco;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	aco.initialise(5, 0.1, 1, 0.5, 0.1, 0.1, 20, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Ejecutar el ACO
	aco.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsACO = aco.getResults();

	for (double aResult : resultsACO) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = aco.getBestPerIteration();
	antsMean = aco.getAntsMeanResults();
}

/**
 * Función que ejecuta todos los experimentos para los argumentos pasados al programa principal
 * @param[out] results matriz 3D donde se almacenarán los resultados. El primer índice será para la instancia considerada. El segundo para el experimento sobre dicha instancia (y posibles subcategorías: resultado actual, mejor hasta el momento...). El tercero para la solución generada en dicho experimento
 * @param[in] mainArgs Argumentos de la función main (argv). En los argumentos vienen, desde el índice 1, <nombre del fichero de la instancia 1> <número de mochilas> <nombre del fichero de la instancia 2> <número de mochilas>...
 * @param[in] numMainArgs Número de argumentos de la función main (argc)
 */
void runExperiments(vector<vector<vector<double>*>*> &results, char **mainArgs,
		unsigned int numMainArgs) {

	//Para cada instancia del problema
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2) {

		//Leer la instancia y crear la estructuras de datos necesarias para guardar los resultados
		MQKPInstance instance;
		vector<vector<double>*>* resultsOnThisInstance = new vector<
				vector<double>*>;
		results.push_back(resultsOnThisInstance);
		char *instanceName = mainArgs[iInstance];
		unsigned int numKnapsacks = atoi(mainArgs[iInstance + 1]);
		instance.readInstance(instanceName, numKnapsacks);

		//Ejecutar el algoritmo evolutivo
		vector<double> *theseResults = new vector<double>;
		vector<double> *bestResults = new vector<double>;
		vector<double> *bestPerIterations = new vector<double>;
		vector<double> *popMeanResults = new vector<double>;
		vector<double> *offMeanResults = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(popMeanResults);
		resultsOnThisInstance->push_back(offMeanResults);
		runAGAExperiment(*theseResults, *bestResults, *bestPerIterations,
				*popMeanResults, *offMeanResults, instance);

		//Ejecutar el algoritmo de colonia de hormigas
		theseResults = new vector<double>;
		bestResults = new vector<double>;
		bestPerIterations = new vector<double>;
		vector<double> *antsMean = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(antsMean);
		runAnACOExperiment(*theseResults, *bestResults, *bestPerIterations,
				*antsMean, instance);
	}
}

/**
 * Función que libera la memoria de un vector 2D
 * @param[in] array vector 2D que se va a liberar de memoria
 */
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = ((int) (array.size()));

	for (int i = 0; i < numVectors; i++) {
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Función que libera la memoria de un vector 3D
 * @param[in] array matriz 3D que se va a liberar de memoria
 */
template<typename T>
void free3Darray(vector<vector<vector<T>*>*> &array) {

	int numArrays = (int) (array.size());

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}





/**
 * Función main que ejecuta la experimentación. Optimización mediante metaheurísticas basadas en poblaciones, algoritmo genético y algoritmo de colonias de hormigas para las instancias.
 *
 * Finalmente se escribe en la salida estandar los resultados generados en forma de matriz.
 *
 * TODO LEER: En este caso, la salida podéis configurarla según vuestro interés (ver variable printColumns). Actualmente se podrían imprimir hasta 9 columnas por instancia:
 *  - El valor fitness de la última solución generada por el Genético (currentGA),
 *  - El mejor valor fitness hasta el momento del Genétic (bestGA),
 *  - El valor fitness de la mejor solución de la población, por iteraciones (bestGAPerIt),
 *  - La media de los valores fitness de la población, por iteraciones (popMeanGA),
 *  - La media de los valores fitness de los descendientes generados, por iteraciones (offMeanGA),
 *
 *  - El valor fitness de la última solución generada por el ACO (currentACO),
 *  - El mejor valor fitness hasta el momento del ACO (bestACO),
 *  - El valor fitness de la mejor solución generada en la iteración actual, por iteraciones (bestACOPerIt),
 *  - La media de los valores fitness de las soluciones generadas por las hormigas, por iteraciones (antsMeanACO)
 *
 *  NO se aconseja imprimir todas las columnas a la vez (o en tal caso, editar el código para que vayan a ficheros diferentes). El problema es que el número de datos en las
 *  columnas "por iteraciones" es menor que el número de datos en las otras columnas, y dado que el programa equilibra el númerdo de datos repitiendo el último, una representación
 *  conjunta de los datos en la misma gráfica puede no ser ilustrativa del comportamiento del algoritmo.
 */
int main(int argc, char **argv) {

	if (argc < 3 || (argc % 2) != 1) {
		cout << argv[0] << " (<problem instance files> <numKnapsacks>)+"
				<< endl;
		return 0;
	}



	//////////////////////////
	//Ejecución de experimentos
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector<vector<vector<double>*>*> allTheResults;
	srand(seeds[0]);
	//En la matriz allTheResults se almacenarán todos los valores de fitness generados
	//Es tridimensional
	//El primer índice recorre las instancias de los problemas que se han abordado
	//El segundo índice recorre los experimentos que se han hecho sobre la misma instancia (y posibles subcategorías: resultado actual, mejor hasta el momento...)
	//El tercer índice recorre cada resultado

	runExperiments(allTheResults, argv, argc);




	//////////////////////
	// Impresión de resultados
	//////////////////////
	vector<double> lastResults;
//	vector<unsigned> printColumns = { 2, 3, 4, 7, 8};
	vector<unsigned> printColumns = { 0, 1, 5, 6 };
	vector<string> titles =
			{ "currentGA", "bestGA", "bestGAPerIt", "popMeanGA", "offMeanGA",
					"currentACO", "bestACO", "bestACOPerIt", "antsMeanACO" };
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++) {

		for (auto indexColumnPerInstance : printColumns) {
			cout << argv[iInstance * 2 + 1] << "_" << argv[iInstance * 2 + 2]
					<< "_" << titles[indexColumnPerInstance] << "\t";
			lastResults.push_back(
					allTheResults.at(iInstance)->at(indexColumnPerInstance)->at(
							0));
		}
	}
	cout << endl;
	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	while (allResultsPrinted == false) {
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances;
				iInstance++) {

			for (auto indexColumnPerInstance : printColumns) {

				if (allTheResults.at(iInstance)->at(indexColumnPerInstance)->size()
						> iIteration) {
					allResultsPrinted = false;
					cout
							<< allTheResults.at(iInstance)->at(
									indexColumnPerInstance)->at(iIteration)
							<< "\t";
					lastResults[indexColumn] = allTheResults.at(iInstance)->at(
							indexColumnPerInstance)->at(iIteration);
				} else {
					cout << lastResults[indexColumn] << "\t";
				}
				indexColumn++;
			}
		}
		cout << endl;
		iIteration++;
		indexColumn = 0;
	}



	//////////////////////
	// Liberar memoria
	//////////////////////
	free3Darray(allTheResults);
	return 0;
}
