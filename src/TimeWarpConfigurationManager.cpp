
#include "TimeWarpConfigurationManager.h"

#include <iostream>
#include <stdexcept>

#include "TimeWarpCentralizedEventSetFactory.h"
#include "TimeWarpSimulationManagerFactory.h"
#include "SchedulingData.h"
#include "Application.h"
#include "SimulationConfiguration.h"
#include "Spinner.h"
#include "ThreadedTimeWarpSimulationManager.h"

TimeWarpConfigurationManager::TimeWarpConfigurationManager(Application* initApplication) :
    mySimulationManager(0), myEventSetFactory(0), myStateFactory(0), myGVTFactory(0),
    myCommunicationFactory(0), mySchedulingFactory(0), myOutputFactory(0),
    myApplication(initApplication) {}

TimeWarpConfigurationManager::~TimeWarpConfigurationManager() {
    delete myEventSetFactory;
    delete myStateFactory;
    delete myGVTFactory;
    delete myCommunicationFactory;
    delete mySchedulingFactory;
    delete myOutputFactory;
    delete mySimulationManager;
    // the handles to the eventSetManager, stateManager, GVTManager,
    // CommunicationManager, schedulingManager and the outputManager
    // are deleted by the end user - the TimeWarpSimulationManager.
}

void TimeWarpConfigurationManager::configure(
    SimulationConfiguration& configuration) {
    std::cout << "Initializing simulation...\n";

    const TimeWarpSimulationManagerFactory* twSimMgrFactory =
        TimeWarpSimulationManagerFactory::instance();
    std::string simulationType = configuration.get_string({"Simulation"}, "Sequential");

    if (simulationType == "TimeWarp") {
        mySimulationManager = dynamic_cast<TimeWarpSimulationManager*>
                              (twSimMgrFactory->allocate(configuration, myApplication));
    } else if (simulationType == "ThreadedTimeWarp") {
        mySimulationManager = dynamic_cast<ThreadedTimeWarpSimulationManager*>
                              (twSimMgrFactory->allocate(configuration, myApplication));
    } else {
        throw std::runtime_error("SimType configuration is invalid.");
    }

    mySimulationManager->configure(configuration);
    if (configuration.get_bool({"SpinBeforeSimulationStart"}, false)) {
        Spinner::spinForever();
    }
}

SimulationManager*
TimeWarpConfigurationManager::getSimulationManager() {
    return mySimulationManager;
}