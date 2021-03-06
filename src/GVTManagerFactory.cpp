
#include <stddef.h>                     // for NULL
#include <ostream>                      // for operator<<, basic_ostream, etc
#include <string>                       // for allocator, operator+, etc

#include "Configurable.h"               // for Configurable
#include "GVTManagerFactory.h"
#include "MatternGVTManager.h"          // for MatternGVTManager
#include "SimulationConfiguration.h"    // for SimulationConfiguration
#include "ThreadedMatternGVTManager.h"  // for ThreadedMatternGVTManager
#include "ThreadedTimeWarpSimulationManager.h"
#include "TimeWarpSimulationManager.h"  // for TimeWarpSimulationManager
#include "WarpedDebug.h"                // for debugout
#include "warped.h"                     // for ASSERT
using std::string;

GVTManagerFactory::GVTManagerFactory() {
}

GVTManagerFactory::~GVTManagerFactory() {
    // myGVTManager will be deleted by the end user - the
    // TimeWarpSimulationManager
}

Configurable*
GVTManagerFactory::allocate(SimulationConfiguration& configuration,
                            Configurable* parent) const {
    Configurable* retval = 0;
    TimeWarpSimulationManager* mySimulationManager =
        dynamic_cast<TimeWarpSimulationManager*>(parent);
    ASSERT(mySimulationManager != NULL);
    // the following cases are possible:

    // (1) GVTManager is Mattern. In this is the case, we need to find
    //     a GVT estimation period (if any; defaults to 1). Then
    //     instantiate the MatternGVTStateManager with a state period (if
    //     one is found).
    std::string gvtManagerType = configuration.get_string({"TimeWarp", "GVTManager", "Type"},
                                                          "Mattern");
    std::string simulationType = configuration.get_string({"Simulation"}, "Sequential");
    int gvtPeriod = configuration.get_int({"TimeWarp", "GVTManager", "Period"}, 1000);

    if (simulationType == "ThreadedTimeWarp") {
        if (gvtManagerType == "Mattern") {
            retval = new ThreadedMatternGVTManager(
                dynamic_cast<ThreadedTimeWarpSimulationManager*>(parent),
                gvtPeriod);
            debug::debugout << "("
                            << mySimulationManager->getSimulationManagerID()
                            << ") configured a Mattern GVT Manager with period = "
                            << gvtPeriod << endl;
            return retval;
        } else {
            mySimulationManager->shutdown("Unknown GVTManager choice \"" + gvtManagerType + "\"");
        }
    }

    if (gvtManagerType == "Mattern") {
        retval = new MatternGVTManager(mySimulationManager, gvtPeriod);
        debug::debugout << "("
                        << mySimulationManager->getSimulationManagerID()
                        << ") configured a Mattern GVT Manager with period = "
                        << gvtPeriod << endl;
    } else {
        mySimulationManager->shutdown(
            "Unknown GVTManager choice \"" + gvtManagerType + "\"");
    }

    return retval;
}

const GVTManagerFactory*
GVTManagerFactory::instance() {
    static GVTManagerFactory* singleton = new GVTManagerFactory();

    return singleton;
}

