#ifndef RESISTANCE_H_
#define RESISTANCE_H_

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <iomanip>

/**
 * The base class for resistance in a circuit diagram, which may be single
 * real-world resistor parts or resistor connections (resistance networks).
 * Every such resistor or combination of resistors has a name (which may
 * be used in the diagram), a nominal value, and minimal and maximum values.
 */
class Resistance {
private:
    std::string name;

public:
    /**
     * Initialize a new instance with the given name.
     *
     * @param name the name of the resistance
     */
    Resistance (std::string name);

    /**
     * Release all resources.
     */
    virtual ~Resistance();

    /**
     * Get the name of the resistance.
     *
     * @return the name of the resistance
     */
    virtual std::string getName() const;

    /**
     * Return a representation for the components of the resistance.
     * The implementation in the base class returns an empty string
     * because there are no known components. See the derived classes
     * for more information.
     *
     * @return the components
     */
    virtual std::string components() const;

    /**
     * Get the nominal value of the resistance.
     *
     * @return the nominal value of the resistance
     */
    virtual float nominalValue() const = 0;

    /**
     * Get the minimal value of the resistance.
     *
     * @return the minimal value of the resistance
     */
    virtual float minimalValue() const = 0;

    /**
     * Get the maximum value of the resistance.
     *
     * @return the maximum value of the resistance
     */
    virtual float maximumValue() const = 0;

    /**
     * Create a string representation of the object's state.
     * The method invokes getName() and appends the result from
     * invoking components(). Then it appends an equal sign ('='),
     * the result from invoking nominalValue() and finally " Ohm".
     * An example is: "R1=42.000000 Ohm" (no line break). Note that
     * the zeroes after the point may or may not be present, depending
     * on your approach in the implementation. Both versions (with
     * or without trailing zeros) are correct. (5 points)
     *
     * @return the string representation
     */
    virtual std::string toString() const;

    /**
     * Write the a line to the ostream. The line contains the data
     * from the resistance as CSV (comma separated values) using
     * a semicolon (';') as delimiter. The line contains three fields:
     *
     *  1. Name (plus additional information as defined by derived classes)
     *  2. Nominal Value
     *  3. Tolerance
     *
     * The tolerance is calculated from the results of invoking
     * minimalValue and maximumValue. Here is a sample output:
     *
     * R3;1000;0.1
     * R4;4700;0.1
     * R2[R3-R4];5700;0.1
     * R6;1000;0.1
     * R7;4700;0.1
     * R5[R6|R7];824.561;0.1
     *
     * (6 points)
     */
    virtual void write(std::ostream& out);
};

/**
 * Define a shortcut for a unique pointer to a Resistance.
 */
typedef std::unique_ptr<Resistance> ResistancePtr;

std::ostream& operator<< (std::ostream& out, Resistance& resistor);

#endif /* RESISTANCE_H_ */
