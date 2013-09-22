#ifndef THREADEDPERIODICSTATEMANAGER_H_
#define THREADEDPERIODICSTATEMANAGER_H_


#include "ThreadedStateManagerImplementationBase.h"
class ThreadedPeriodicStateManager: public ThreadedStateManagerImplementationBase {
public:
	/**@name Public Class Methods of PeriodicStateManager. */
	//@{

	/** Constructor.

	 @param numObjects Number of simulation objects.
	 @param period State saving period (default = 0).
	 */
	ThreadedPeriodicStateManager(ThreadedTimeWarpSimulationManager *simMgr,
			unsigned int period = 0);

	/// Destructor
	~ThreadedPeriodicStateManager();

	/** Rollback and restore the state of the object at the specified time.

	 @param rollbackTime Rollback to this time and restore state.
	 @param SimulationObject The object whose state should be restored.
	 @return the time of restored state
	 */
	const VTime &restoreState(const VTime &rollbackTime,
			SimulationObject* object, int threadID);

	/** Save the state of the object at the specified time.

	 @param currentTime Current time of state saving.
	 @param object Simulation object for which to save the state.
	 */
	void saveState(const VTime &currentTime,unsigned int eventNumber, SimulationObject* object,const ObjectID senderId,
			int threadID);

    void saveState(const VTime &currentTime, SimulationObject* object,
			int threadID);


	void configure(SimulationConfiguration &) {
	}

    const unsigned int getEventIdForRollback(int threadId, int objId);

    void updateStateWhileCoastForward(const VTime &currentTime, unsigned int eventNumber,SimulationObject* object,const ObjectID senderId, int threadID);

	//@} // End of Public Class Methods of PeriodicStateManager.

};

#endif /* ThreadedPERIODICSTATEMANAGER_H_ */
