
#ifndef AtomicState_H_
#define AtomicState_H_

#include <iostream>

static const int NOBODY = -1;
class AtomicState {
public:
    AtomicState() :
        lockOwner(NOBODY) {
    }
    ~AtomicState() {
    }
    bool releaseLock(const unsigned int& threadNumber) {
        //If Currently Working and we can set it to Available then return true else return false;
        return __sync_bool_compare_and_swap(&lockOwner, threadNumber, NOBODY);
    }
    bool setLock(const unsigned int& threadNumber) {
        //If Available and we can set it to Working then return true else return false;
        return __sync_bool_compare_and_swap(&lockOwner, NOBODY, threadNumber);
    }
    bool hasLock(const unsigned int& threadNumber) const {
        return (threadNumber == (unsigned int) lockOwner);
    }
    void showStatus() {
        std::cout << "Locked By: " << lockOwner << std::endl;
    }
    bool isLocked() {
        if (this->lockOwner == -1)
        { return false; }
        else
        { return true; }
    }
    int whoHasLock() {
        return lockOwner;
    }
private:
    int lockOwner;
};

#endif /* AtomicState_H_ */
