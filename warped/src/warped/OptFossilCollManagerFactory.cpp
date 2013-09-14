
#include "OptFossilCollManagerFactory.h"
#include "ChebyFossilCollManager.h"
#include "SimulationConfiguration.h"
#include "TimeWarpConfigurationManager.h"
#include "ThreadedTimeWarpSimulationManager.h"
#include "ThreadedChebyFossilCollManager.h"
#include <WarpedDebug.h>

OptFossilCollManagerFactory::OptFossilCollManagerFactory(){}

OptFossilCollManagerFactory::~OptFossilCollManagerFactory(){
  // myFossilManager will be deleted by the end user - the
  // TimeWarpSimulationManager
}

Configurable *
OptFossilCollManagerFactory::allocate(SimulationConfiguration &configuration,
		Configurable *parent) const {
	Configurable *retval = NULL;
	TimeWarpSimulationManager *mySimulationManager =
			dynamic_cast<TimeWarpSimulationManager *> (parent);
	ThreadedTimeWarpSimulationManager *myThreadedSimulationManager =
			dynamic_cast<ThreadedTimeWarpSimulationManager *> (parent);

	ASSERT( mySimulationManager != NULL );
	// the following cases are possible:

	// (1) Manager is Cheby.
	// (2) None is used.

    std::string optFossilCollManagerType = configuration.get_string(
    	{"TimeWarp", "OptFossilCollManager", "Type"}, "None")
	if (optFossilCollManagerType == "Cheby") {
		unsigned int checkpointPeriod = 1000;
		unsigned int minSamples = 64;
		unsigned int maxSamples = 100;
		unsigned int defaultLength = 2000;
		double riskFactor = 0.99;
		configuration.getOptFossilCollPeriod(checkpointPeriod);
		configuration.getOptFossilCollMinSamples(minSamples);
		configuration.getOptFossilCollMaxSamples(maxSamples);
		configuration.getOptFossilCollDefaultLength(defaultLength);
		configuration.getOptFossilCollRiskFactor(riskFactor);
		if (configuration.simulationTypeIs("ThreadedTimeWarp")) {
			retval = new ThreadedChebyFossilCollManager(myThreadedSimulationManager,
					checkpointPeriod, minSamples, maxSamples, defaultLength,
					riskFactor);
			myThreadedSimulationManager->setOptFossilColl(true);

		} else {
			retval = new ChebyFossilCollManager(mySimulationManager,
					checkpointPeriod, minSamples, maxSamples, defaultLength,
					riskFactor);
			mySimulationManager->setOptFossilColl(true);
			debug::debugout << "("
					<< mySimulationManager->getSimulationManagerID()
					<< ") configured a Cheby Optimistic Fossil Collection Manager "
					<< "with checkpoint interval: " << checkpointPeriod
					<< ", and risk factor: " << riskFactor << endl;
		}
	} else if (optFossilCollManagerType == "None") {
		retval = NULL;
	} else {
		mySimulationManager->shutdown(
				"Unknown FossilManager choice \""
						+ configuration.getGVTManagerType() + "\"");
	}

	return retval;
}

const OptFossilCollManagerFactory *
OptFossilCollManagerFactory::instance(){
  static OptFossilCollManagerFactory *singleton = new OptFossilCollManagerFactory();

  return singleton;
}
