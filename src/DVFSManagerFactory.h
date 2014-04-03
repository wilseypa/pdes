#ifndef DVFS_MANAGER_FACTORY_H
#define DVFS_MANAGER_FACTORY_H


#include "Configurer.h"                 // for Configurer
#include "warped.h"

class Configurable;
class SimulationConfiguration;


/** The DVFSManagerFactory class.

    Factory for DVFSManagers

*/
class DVFSManagerFactory : public Configurer {
public:

    /**@name Public Class Methods of DVFSManagerFactory. */
    //@{

    /** Constructor.
    */
    DVFSManagerFactory();

    /// Destructor.
    virtual ~DVFSManagerFactory();

    /** Set the configured DVFS Manager implementation.

        Function to attach the particular DVFS manager implementation in
        the kernel. Will be called by the configuration step to set the
        appropriate DVFS manager implementation.

        @param configurationMap Configuration options.
    */
    Configurable* allocate(SimulationConfiguration& configuration,
                           Configurable* parent) const;

    static const DVFSManagerFactory* instance();

    //@} // End of Public Class Methods of DVFSManagerFactory.
};

#endif //DVFS_MANAGER_FACTORY_H
