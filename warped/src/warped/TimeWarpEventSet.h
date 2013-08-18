#ifndef TIME_WARP_EVENT_SET_H
#define TIME_WARP_EVENT_SET_H


#include "warped.h"
#include "Configurable.h"
#include "EventId.h"
class Event;
class NegativeEvent;
class SimulationObject;
class TimeWarpEventSetFactory;

/** The TimeWarpEventSet abstract base class.

This is the abstract base class for all Time Warp specific event set
implementations in the kernel. Different Time Warp event set
implementations must be derived from this abstract class.

The TimeWarpEventSet contains input events to the simulation kernel.  It
"owns" them and is responsible for their reclaimation at fossil
collection time.
*/
class TimeWarpEventSet : virtual public Configurable {

  /**@type friend class declarations */
  //@{
   
  /// Factory class for TimeWarpEventSet
friend class TimeWarpEventSetFactory;

  //@} // End of friend class declarations

public:
  /**@name Public Class Methods of TimeWarpEventSet. */
  //@{
   
  /// Virtual Destructor
  virtual ~TimeWarpEventSet();
   
  /** Insert an event into the event set.

  This is a pure virtual function that has to be overridden.

  @param Event The event to be inserted.

  @return Returns "true" if the event is in the past of the simulation
  object for which the event was inserted, and false if it's in the
  object's future.
  */

  virtual bool insert( const Event *event ) = 0;

  /** Cancel the event without using the EventId.
 
  @oaram reclaimer The SimulationObject that will be used to cancel the event.
  @param cancelEvent The event to be cancelled.
  @return Whether the positive event is found or not
  */
  virtual bool handleAntiMessage( SimulationObject *reclaimer,
                                  const NegativeEvent *cancelEvent ) = 0;

  /** Remove and return the next event in the event set.

  This is a pure virtual function that has to be overridden.

  @return The removed event.
  */
  virtual const Event *getEvent(SimulationObject *) = 0;

  /** Remove and return the next event for a simulation object.

  This method differs from the getEvent(SimulationObject *)
  in that it returns an event for a specific simulation
  object and that event must have a receive time less than the
  time given by the input parameter. If there is no event
  in the input event set with a time less than the given time
  for the specified simulation object, NULL is returned.

  This is a pure virtual function and has to overridden.

  @param SimulationObject Reference to the simulation object.
  @param VTime Time constraint for the returned event.
  @return The event, or NULL if none found.
  */
  virtual const Event *getEvent( SimulationObject *, const VTime& ) = 0;

  /** Return a pointer to the next event in the event set.

  This is a pure virtual function and has to be overridden.

  @return A pointer to the next event in the event set.
  */
  virtual const Event *peekEvent(SimulationObject *) = 0;

  /** Return a pointer the next event for a simulation object.

  This method differs from the peekEvent(SimulationObject *)
  in that it returns an event for a specific simulation
  object and that event must have a receive time less than the
  time given by the input parameter. If there is no event
  in the input event set with a time less than the given time
  for the specified simulation object, NULL is returned.

  This is a pure virtual function and has to overridden.

  @param SimulationObject Reference to the simulation object.
  @param VTime Time constraint for the returned event.
  @return The peeked event, or NULL if none found.
  */
  virtual const Event *peekEvent(SimulationObject *, const VTime&) = 0;

  /** Fossil collect the event set upto a given time.

  This is a pure virtual function that has to be overridden.

  @param VTime Time upto which to fossil collect.
  */
  virtual void fossilCollect( SimulationObject *, const VTime & ) = 0;

  /** Fossil collect the event set upto a given time.

  This is a pure virtual function that has to be overridden.

  @param int Time upto which to fossil collect.
  */
  virtual void fossilCollect( SimulationObject *, int ) = 0;

  /** Remove and fossil collect the given event.

  This is a pure virtual function that has to be overridden.

  @param Event The event to fossil collect
  */
  virtual void fossilCollect( const Event * ) = 0;

  /**
     Rollback to the time passed in.  Could involve unprocessing events,
     i.e. taking events we've considered processed and making them go
     back into the unprocessed state.
  */
  virtual void rollback( SimulationObject *object, const VTime &rollbackTime ) = 0;

  /**
     Determine if the event would be in the past if it were inserted

     @return True if it would be in the past.
  */
  virtual bool inThePast( const Event * ) = 0;

  /**
     Remove all events from the event set. Used to restore state after
     a catastrophic rollback while using optimistic fossil collection.
  */
  virtual void ofcPurge() = 0;

  virtual void debugDump( const string &, ostream & ){}

  virtual double getEfficiency() { return 0; }

  virtual unsigned int getNumEventsExecuted() { return 0; }
  virtual unsigned int getNumEventsRolledBack() { return 0; }
  virtual unsigned int getNumEventsCommitted() { return 0; }

  //@} // End of Public Class Methods of TimeWarpEventSet.

protected:
  /**@name Protected Class Methods of TimeWarpEventSet. */
  //@{

  /// Default Constructor
  TimeWarpEventSet() {};

  //@} // End of Protected Class Methods of TimeWarpEventSet.
};

#endif
