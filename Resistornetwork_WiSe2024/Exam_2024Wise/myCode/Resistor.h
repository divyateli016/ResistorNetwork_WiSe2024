#ifndef RESISTOR_H_
#define RESISTOR_H_

#include "Resistance.h"

/**
 * A real-world resistor. It has a name, a nominal value, and a
 * tolerance from which its minimal and maximum values can be
 * calculated.
 */
class Resistor: public Resistance {
private:
    float value;
    float tolerance;

public:
    /**
     * Initialize a new instance with the given values.
     *
     * @param name the name of the resistor
     * @param value the nominal value of the resistor
     * @param tolerance the tolerance of the resistor
     */
    Resistor(std::string name, float value, float tolerance);

    /**
     * Creates a resistor from the given line from a CSV file.
     * The line is expected to have the format written by
     * {@link Resistance#write} ("name;value;tolerance").
     * (7 points)
     */
    static ResistancePtr from(std::string line);

    /**
     * See base class.
     */
    virtual float nominalValue() const;

    /**
     * See base class. (1 point)
     */
    virtual float minimalValue() const;

    /**
     * See base class. (1 point)
     */
    virtual float maximumValue() const;
};

#endif /* RESISTOR_H_ */
