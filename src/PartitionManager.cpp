#include <fstream>
#include <vector>                       // for vector
#include <string>

#include "Application.h"                // for Application
#include "GreedyPartitioner.h"          // for GreedyPartitioner
#include "PartitionManager.h"
#include "ProfileGuidedPartitioner.h"   // for ProfileGuidedPartitioner
#include "RoundRobinPartitioner.h"      // for RoundRobinPartitioner
#include "SimulationConfiguration.h"    // for SimulationConfiguration

class SimulationObject;
class PartitionInfo;

PartitionManager::PartitionManager(SimulationConfiguration& configuration) {
    partitionType = configuration.get_string({"TimeWarp", "Partitioner", "Type"},
                                             "Default");
    statisticsFile = configuration.get_string({"TimeWarp", "Partitioner", "StatisticsFile"},
                                              "statistics.metis");
}

/// Partitions a vector of simualtion objects based on a configuration value
const PartitionInfo* PartitionManager::getPartitionInfo(Application* application,
                                                        unsigned int numPartitions) {
    const PartitionInfo* retval;
    std::vector<SimulationObject*>* objects = application->getSimulationObjects();

    if (partitionType == "RoundRobin") {
        retval = RoundRobinPartitioner().partition(objects, numPartitions);
    } else if (partitionType == "Greedy") {
        retval = GreedyPartitioner().partition(objects, numPartitions);
    } else if (partitionType == "ProfileGuided") {
        std::ifstream input(statisticsFile);
        try {
            retval = ProfileGuidedPartitioner(input).partition(objects, numPartitions);
        } catch (...) {
            input.close();
            throw;
        }
        input.close();
    } else {
        retval = application->getPartitionInfo(numPartitions, objects);
    }

    delete objects;
    return retval;
}
