#ifndef VTIME_H
#define VTIME_H


#include <Serializable.h>               // for Serializable, string
#include <stdlib.h>
#include <iostream>                     // for ostream
#include <sstream>
#include <string>                       // for operator<<, string

#include "warped.h"

class VTime : public Serializable {
public:
    /// Destructor.
    virtual ~VTime();

    virtual VTime* clone() const = 0;

    virtual const VTime& operator=(const VTime& from) = 0;
    virtual bool operator< (const VTime& right) const = 0;
    virtual bool operator> (const VTime& right) const = 0;
    virtual bool operator== (const VTime& right) const = 0;
    virtual bool operator!= (const VTime& right) const = 0;
    virtual bool operator<= (const VTime& right) const = 0;
    virtual bool operator>= (const VTime& right) const = 0;

    virtual const VTime& getPositiveInfinity() const = 0;
    virtual const VTime& getZero() const = 0;

    /**
       Return this VTime in a string representation.
    */
    virtual const std::string toString() const = 0;
    /**
       Return an integer approximation of the current time
       This is used when the kernel needs an actual number for VTime
       such as calculating position in the calendar queue
    */
    virtual const warped64_t getApproximateIntTime() const = 0;

};


inline
std::ostream& operator<< (std::ostream& os, const VTime& time) {
    os << time.toString();
    return os;
}


#endif
