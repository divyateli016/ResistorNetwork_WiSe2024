#ifndef SERIALRESISTORCONNECTION_H_
#define SERIALRESISTORCONNECTION_H_

#include "ResistorConnection.h"

/**
 * Represents a serial connection of resistors.
 */
class SerialResistorConnection: public ResistorConnection {
public:
    /**
     * Initializes a new instance with the given name.
     *
     * @param name the name
     */
    SerialResistorConnection(std::string name);

    /**
     * Returns a dash ('-') as separator.
     */
    virtual char separator() const;

    /**
     * See base class. (5 points)
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

#endif /* SERIALRESISTORCONNECTION_H_ */
