#ifndef PARALLELRESISTORCONNECTION_H_
#define PARALLELRESISTORCONNECTION_H_

#include "ResistorConnection.h"

/**
 * Represents a parallel connection of resistors.
 */
class ParallelResistorConnection: public ResistorConnection {
public:
    /**
     * Initializes a new instance with the given name.
     *
     * @param name the name
     */
    ParallelResistorConnection(std::string name);

    /**
     * Returns a vertical bar ('|') as separator.
     */
    virtual char separator() const;

    /**
     * See base class. (6 points)
     */
    virtual float nominalValue() const;

    /**
     * See base class. (2 points)
     */
    virtual float minimalValue() const;

    /**
     * See base class. (2 points)
     */
    virtual float maximumValue() const;
};

#endif /* PARALLELRESISTORCONNECTION_H_ */
