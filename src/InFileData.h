#ifndef IN_FILE_DATA_H
#define IN_FILE_DATA_H

#include <ios>

#include "VTime.h"

/** The InFileData class

    This class represents a container class that stores the current
    position in a file that is being read. A time is associated with
    the current position so that a rollback can be accomplished.

*/
class InFileData {
public:

    /**@name Public Class Methods of InFileData. */
    //@{

    InFileData(const VTime& currentTime) : time(*(currentTime.clone())), pos(0) {};
    InFileData(const VTime& currentTime, std::streampos currentPosition) :
        time(*(currentTime.clone())), pos(currentPosition) {};

    ~InFileData() {
    };

    const VTime& getTime() const {
        return time;
    }

    std::streampos getPosition() const {
        return pos;
    }

    /// Overloaded operator <
    friend bool operator<(const InFileData& a, const InFileData& b) {
        return a.time < b.time;
    }

    /// Overloaded operator ==
    friend bool operator==(const InFileData& a, const InFileData& b) {
        return a.time == b.time;
    }

    /// Overloaded operator >
    friend bool operator>(const InFileData& a, const InFileData& b) {
        return a.time > b.time;
    }

    /// Overloaded operator <<
    friend std::ostream& operator<<(std::ostream& os, const InFileData& a) {
        return os << a.time;
    }

    //@} // End of Public Class Methods of InFileData.

protected:

    /**@name Protected Class Attributes of InFileData. */
    //@{

    /// needed to sort the entries in the FileQueue
    const VTime& time;

    /// position of last read in a file
    std::streampos pos;

    //@} // End of Protected Class Attributes of InFileData.
};
#endif
