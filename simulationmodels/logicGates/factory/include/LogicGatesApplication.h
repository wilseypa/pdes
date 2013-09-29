#ifndef LOGIC_GATES_APPLICATION
#define LOGIC_GATES_APPLICATION

#include <Application.h>
#include <IntVTime.h>

class LogicGatesApplication : public Application {
public:
  LogicGatesApplication();
  
  int getNumberOfSimulationObjects(int mgrId) const;
  
  vector<SimulationObject *>* getSimulationObjects();

  const PartitionInfo *getPartitionInfo( unsigned int numberOfProcessorsAvailable);

  int finalize();

  void registerDeserializers();

  const VTime &getPositiveInfinity(){return IntVTime::getIntVTimePositiveInfinity();}
  const VTime &getZero(){ return IntVTime::getIntVTimeZero();}
  const VTime &getTime(string &){return IntVTime::getIntVTimeZero();}

private:
  unsigned int mumObjects;
  string inputFileName;
}

#endif 