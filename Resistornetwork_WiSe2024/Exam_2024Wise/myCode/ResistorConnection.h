#ifndef RESISTORCONNECTION_H_
#define RESISTORCONNECTION_H_

#include <list>
#include <memory>
#include <ostream>

#include "Resistance.h"

/**
 * Represents a combination of resistors. This is the base class
 * for serial or parallel resistor connections.
 */
class ResistorConnection: public Resistance {
protected:
    /*
     * Remember that a container must use pointers to the base class,
     * because it cannot provide memory for instances of derived classes.
     */
    std::list<ResistancePtr> resistors;

public:
    /**
     * Initializes a new instance with the given name.
     *
     * @param name the name
     */
    ResistorConnection(std::string name);

    /**
     * The separator to use when evaluating the components representation
     * (@see #components). The implementation in the base class returns
     * a comma (',').
     */
    virtual char separator() const;

    /**
     * Returns a list of component representations in square brackets,
     * separating the representations using the result from separator()
     * as delimiter. Each component representation consists of the
     * catenation of the results from invoking name() and components()
     * for the respective component. E.g. if a connection connects the
     * resistors R1 and R2 then components() returns "[R1,R2]". Should
     * R1 or R2 be resistor connections themselves instead of simple
     * resistors, the result may be something like
     * "[R1[R3,R4],R2[R5,R6,R7]]" (the delimiters may differ if invoked
     * for a derived class). (7 points)
     */
    virtual std::string components() const;

    /**
     * Appends the given resistor to the list of connected resistors.
     */
    ResistorConnection& operator+= (ResistancePtr resistor);

    /**
     * Override the default implementation to ensure that the resistances
     * in a connection and the information about the connection are
     * available in the CSV file.
     *
     * The implementation first invokes write for each connected resistor.
     *
     * Then it writes the first field of the line for this instance in the
     * CSV file. Instead of only the name of the current instance, it writes
     * the name and the names of the components. The names of the components
     * are appended as a list in square brackets, using the value from
     * separator() as delimiter. (The difference compared to the approach in
     * components() is that this method only writes the names of the
     * components, not the names plus their component information as
     * components() does.)
     *
     * The second and third field of the line for this instance in the
     * CSV file are empty.
     *
     * E.g. if this connection is a connection "Rs" that connects the
     * resistors R1 and R2 then the line written to the CSV file is
     * "Rs[R1,R2];;" no matter if R1 or R2 is a resistor or a connection.
     * (The delimiter may differ if invoked for a derived class.)
     *
     * (10 points)
     */
    void write(std::ostream& out);

};

#endif /* RESISTORCONNECTION_H_ */
