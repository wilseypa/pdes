#ifndef N_INPUT_NAND_GATE_H
#define N_INPUT_NAND_GATE_H

#include "NInputGate.h"

/** The NInputAndGate class.

    This class represents an N input nand gate.
*/
class NInputNandGate : public NInputGate {
public:
   
   /**@name Public Class Methods of NInputAndGate. */
   //@{

   /// Default constructor
   NInputNandGate(string &objectName, const int numInputs,/*const int numInValue,*/const int numOutputs,
                 vector<string> *outputs, vector<int> *destInputPorts,
                 int objectDelay);
   /// Default Destructor
   ~NInputNandGate(){}

   /// compute the outputs of this gate
   int computeOutput(const int* inputBits);
  
   //@} // End of Public Class Methods of NInputAndGate.
};

#endif