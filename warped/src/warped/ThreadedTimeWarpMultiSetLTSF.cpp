#include "ThreadedTimeWarpMultiSetLTSF.h"

ThreadedTimeWarpMultiSetLTSF::ThreadedTimeWarpMultiSetLTSF(int objectCount) {
	// Set up scheduleQueue (LTSF queue)
	scheduleQueue = new multiset<const Event*,
			receiveTimeLessThanEventIdLessThan> ;
	objectStatusLock = new AtomicState *[objectCount];
	scheduleQueueLock = new AtomicState();

	//Initialize LTSF Event Queue
	for (int i = 0; i < objectCount; i++) {
		objectStatusLock[i] = new AtomicState();
		//Schedule queue
		lowestObjectPosition.push_back(scheduleQueue->end());
	}
}

ThreadedTimeWarpMultiSetLTSF::~ThreadedTimeWarpMultiSetLTSF() {
	delete objectStatusLock;
}

void ThreadedTimeWarpMultiSetLTSF::getScheduleQueueLock(int threadId) {
	utils::debug << "( "<<threadId<<" T ) Getting the Sche Lock." << endl;
	while (!scheduleQueueLock->setLock(threadId))
		;
	ASSERT(scheduleQueueLock->hasLock(threadId));
}
void ThreadedTimeWarpMultiSetLTSF::releaseScheduleQueueLock(int threadId) {
	ASSERT(scheduleQueueLock->hasLock(threadId));
	scheduleQueueLock->releaseLock(threadId);
	utils::debug << "( "<<threadId<<" T ) Releasing the Sche Lock." << endl;
}
const VTime* ThreadedTimeWarpMultiSetLTSF::nextEventToBeScheduledTime(int threadID) {
	const VTime* ret = NULL;
	this->getScheduleQueueLock(threadID);
	if (scheduleQueue->size() > 0)
		ret = &((*scheduleQueue->begin())->getReceiveTime());
	this->releaseScheduleQueueLock(threadID);
	return (ret);
}

// Lock based Counting -- Don't call this function in a loop
int ThreadedTimeWarpMultiSetLTSF::getMessageCount(int threadId) {
	int count = 0;
	getScheduleQueueLock(threadId);
	count = scheduleQueue->size();
	releaseScheduleQueueLock(threadId);
	return count;
}
bool ThreadedTimeWarpMultiSetLTSF::isScheduleQueueEmpty(int threadId) {
	bool ret = false;
	getScheduleQueueLock(threadId);
	ret = scheduleQueue->empty();
	releaseScheduleQueueLock(threadId);
	return ret;
}
void ThreadedTimeWarpMultiSetLTSF::releaseAllScheduleQueueLocks()
{
	if (scheduleQueueLock->isLocked()) {
		scheduleQueueLock->releaseLock(scheduleQueueLock->whoHasLock());
		utils::debug << "Releasing Schedule Queue during recovery." << endl;
	}
}
void ThreadedTimeWarpMultiSetLTSF::clearScheduleQueue(int threadId)
{
	this->getScheduleQueueLock(threadId);
	scheduleQueue->clear();
	this->releaseScheduleQueueLock(threadId);
}
void ThreadedTimeWarpMultiSetLTSF::setLowestObjectPosition(int threadId, int index)
{
	this->getScheduleQueueLock(threadId);
	lowestObjectPosition[index] = scheduleQueue->end();
	this->releaseScheduleQueueLock(threadId);
}
void ThreadedTimeWarpMultiSetLTSF::insertEvent(int objId, const Event* newEvent)
{
	lowestObjectPosition[objId] = scheduleQueue->insert(newEvent);
}
void ThreadedTimeWarpMultiSetLTSF::insertEventEnd(int objId)
{
	lowestObjectPosition[objId] = scheduleQueue->end();
}
void ThreadedTimeWarpMultiSetLTSF::eraseSkipFirst(int objId)
{
	// Do not erase the first time.
	if (lowestObjectPosition[objId] != scheduleQueue->end()) {
		scheduleQueue->erase(lowestObjectPosition[objId]);
	} else {
		/*utils::debug << "( "
		 << mySimulationManager->getSimulationManagerID()
		 << " ) Object - " << objId
		 << " is returned for schedule thro' insert by the thread - "
		 << threadId << "\n";*/
	}
}
int ThreadedTimeWarpMultiSetLTSF::getScheduleQueueSize()
{
	return scheduleQueue->size();
}
const Event* ThreadedTimeWarpMultiSetLTSF::peekIt(int threadId)
{
	const Event* ret = NULL;
	this->getScheduleQueueLock(threadId);
	if (scheduleQueue->size() > 0) {
utils::debug<<"( "<< threadId << " T ) Peeking from Schedule Queue"<<endl;

		ret = *(scheduleQueue->begin());
		unsigned int objId = ret->getReceiver().getSimulationObjectID();
utils::debug <<" ( "<< threadId << ") Locking the Object " <<objId <<endl;
	
		this ->getObjectLock(threadId, objId);
		//remove the object out of schedule
		scheduleQueue->erase(scheduleQueue->begin());
		//set the indexer/pointer to NULL
		lowestObjectPosition[objId] = scheduleQueue->end();
		/*		utils::debug << "( "
		 << mySimulationManager->getSimulationManagerID()
		 << " ) Object - " << objId
		 << " is removed out for schedule by the thread - "
		 << threadId << "\n";*/
	}
	this->releaseScheduleQueueLock(threadId);
	return ret;
}

void ThreadedTimeWarpMultiSetLTSF::getObjectLock(int threadId, int objId) {
	while (!objectStatusLock[objId]->setLock(threadId))
		;
	/*	utils::debug << "( " << mySimulationManager->getSimulationManagerID()
	 << " ) Object - " << objId << " is Locked by the thread - "
	 << threadId << "\n";*/
	ASSERT(objectStatusLock[objId]->hasLock(threadId));
}
void ThreadedTimeWarpMultiSetLTSF::releaseObjectLock(int threadId, int objId) {
	ASSERT(objectStatusLock[objId]->hasLock(threadId));
	objectStatusLock[objId]->releaseLock(threadId);
	/*	utils::debug << "( " << mySimulationManager->getSimulationManagerID()
	 << " ) Object - " << objId << " is Released by the thread - "
	 << threadId << "\n";*/
}

bool ThreadedTimeWarpMultiSetLTSF::isObjectScheduled(int objId) {
	return objectStatusLock[objId]->isLocked();
}

bool ThreadedTimeWarpMultiSetLTSF::isObjectScheduledBy(int threadId, int objId) {
	return (objectStatusLock[objId]->whoHasLock() == threadId) ? true : false;
}
void ThreadedTimeWarpMultiSetLTSF::releaseObjectLocksRecovery(int objNum) {
	if (objectStatusLock[objNum]->isLocked()) {
		objectStatusLock[objNum]->releaseLock(
				objectStatusLock[objNum]->whoHasLock());
		utils::debug << "Releasing Object " << objNum
				<< " during recovery." << endl;
	}
}
