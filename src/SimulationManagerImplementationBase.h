#ifndef SIMULATION_MANAGER_IMPLEMENTATION_BASE_H
#define SIMULATION_MANAGER_IMPLEMENTATION_BASE_H

#include <fstream>                      // for ostream
#include <string>                       // for string, hash
#include <unordered_map>                // for _Hashtable<>::iterator, etc
#include <utility>                      // for pair
#include <vector>                       // for vector

#include "SimulationManager.h"          // for SimulationManager
#include "SimulationObject.h"           // for string, etc
#include "warped.h"

class Event;
class SimulationObject;
class VTime;

/** The base class that implements a SimulationManager.

    The SimulationManagerImplementationBase class is the base class
    from which all other simulation managers are derived from. It
    contains the methods and data that is common to all types of
    simulation managers such as the sequential simulation manager and
    the Time Warp simulation manager.

*/
class SimulationManagerImplementationBase : public SimulationManager {
public:
    SimulationManagerImplementationBase();
    virtual ~SimulationManagerImplementationBase();

    /// returns the number of simulation objects
    unsigned int getNumberOfSimulationObjects() const { return numberOfObjects; }

    /// sets the number of simulation objects
    void setNumberOfObjects(unsigned int numObjects);

    /// returns the number of simulation managers
    unsigned int getNumberOfSimulationManagers() const {
        return numberOfSimulationManagers;
    }

protected:
    /** This method is used to initialize the Simulation Manager before the
        simulation begins.

        This gives each SimulationManager a chance to perform any actions
        required for initialization (examples of what might occur during
        initialization might include opening files, or setting up a
        distributed simulation).
    */
    void initializeObjects();

    /** This method is called after the simulation has ended.

    This allows the Simulation Manager to clean up, performing
    actions such as closing files, collecting statistics, and producing
    output.
    */
    void finalizeObjects();

    /// Number of objects registered with this simulation manager.
    unsigned int numberOfObjects;

    /// Number of simulation managers.
    unsigned int numberOfSimulationManagers;

    typedef std::unordered_map<std::string, SimulationObject*> typeSimMap;

    std::vector<SimulationObject*>* getElementVector(typeSimMap* elementMap) {
        std::vector<SimulationObject*>* objects = new std::vector<SimulationObject*>;
        //Obtains all the objects from elementMap
        for (typeSimMap::iterator i = elementMap->begin(); i != elementMap->end(); i++) {
            objects->push_back(i->second);
        }
        return objects;
    }

    std::vector<std::string>* getKeyVector(typeSimMap* elementMap) {
        std::vector<std::string>* keys = new std::vector<std::string>;
        //Obtains all the objects from elementMap
        for (typeSimMap::iterator i = elementMap->begin(); i != elementMap->end(); i++) {
            keys->push_back(i->first);
        }
        return keys;
    }

    /// Map of local Names -> SimulationObjects
    typeSimMap* simObjectsByName;

    /// Map of local ID -> SimulationObjects
    std::vector<SimulationObject*> simObjectsByID;

    /// Turns a vector<SimulationObject *> into a map<string, SimulationObject *>.
    typeSimMap* partitionVectorToHashMap(std::vector<SimulationObject*>* vector);
};

#endif

