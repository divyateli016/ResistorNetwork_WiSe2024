#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "Resistor.h"
#include "SerialResistorConnection.h"
#include "ParallelResistorConnection.h"
#include "ResistanceReader.h"

using namespace std;

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrue(bool condition, string failedMessage) {
    if (!condition) {
        cout << failedMessage << endl;
    }
}

/**
 * Basic tests for resistors. (5 points)
 */
void resistorTests() {
	/*
	 * Create a resistor with name "R1", value 1000 Ohm and tolerance of 10%.
	 * Then assert that the name is "R1", the nominal value is 1000 Ohm
	 * and the minimal and maximum values are evaluated correctly.
	 */
	// TODO
    Resistor r1("R1",1000,0.1);
    std::string name = r1.getName();
    assertTrue(name=="R1","Name is not correct");
    //float value = r1.maximumValue();
   // std::cout<<value<<std::endl;
    assertTrue(r1.maximumValue()==1100.000000,"Value is not correct");
    assertTrue(r1.minimalValue()==900.000000,"Minimum value is not correct");
    //r1.write(cout);

    //Resistor connection test
    /**
    ResistorConnection c1("R1");
    ResistancePtr r2 = make_unique<Resistor>(Resistor("R2", 1000, 0.1));
    ResistancePtr r3 = make_unique<Resistor>(Resistor("R3", 2000, 0.1));
    c1+=std::move(r2);
    c1+=std::move(r3);
    //std::cout<<c1.components();
    c1.write(cout);
    **/

}

/**
 * Basic tests for serial connections. (4 points)
 */
void serialTests() {
    /*
     * Create a serial connection with name "Rs". It combines the
     * resistors with names "R1" (1 kOhm +/-10%) and "R2"
     * (4.7 kOhm +/-10%). Then assert that components() returns the
     * expected result "[R1-R2]" and the nominal, minimal and maximum
     * values are returned correctly. (4 points)
     */
    SerialResistorConnection rS("Rs");
    ResistancePtr r1 = make_unique<Resistor>(Resistor("R1", 1000, 0.1));
    rS += std::move(r1);
    rS += make_unique<Resistor>(Resistor("R2", 4700, 0.1));
   // std::cout<<rS.components()<<std::endl;debug
  assertTrue(rS.components()=="[R1-R2]","Components are not correct");
  //std::cout<<rS.nominalValue()<<std::endl;debug

  assertTrue(rS.nominalValue()==5700,"Values are not calculated correct");
  assertTrue(rS.maximumValue()==6270,"Maximum value is not correct");
  //std::cout<<rS.minimalValue()<<std::endl;debugging
  assertTrue(rS.minimalValue()==5130,"Minimum value is not correct");
  //rS.write(cout);


    // TODO check name and values
}

/**
 * Basic tests for parallel connections. (10 points)
 */
void parallelTests() {
    /*
     * Create a parallel connection with name "Rp". It combines the
     * resistors with names "R1" (1 kOhm +/-10%) and "R2"
     * (1 kOhm +/-10%). Then assert that the result from components() and
     * the nominal, minimal and maximum values are returned correctly.
     *
     * Remember when doing the checks that float arithmetic is not exact.
     * If you expect a value of 500 Ohm, then it is ok if the value is
     * between 499.999 and 500.001 Ohm.
     */
	ParallelResistorConnection p1("Rp");
	ResistancePtr rp1 = make_unique<Resistor>("R1",1000,0.1);
	ResistancePtr rp2 = make_unique<Resistor>("R2",1000,0.1);
	p1+=std::move(rp1);
	p1+=std::move(rp2);
	//std::cout<<p1.components()<<std::endl;
	assertTrue(p1.components()=="[R1|R2]","Component name is not expected");
	//std::cout<<p1.nominalValue()<<std::endl; Debugging
	assertTrue(p1.nominalValue()==500,"wrong nominal value");
	//std::cout<<p1.maximumValue()<<std::endl;  Debugging
	assertTrue(p1.maximumValue()==550,"Maximum value is wrong");
    // TODO
}

/**
 * Basic tests for reading and writing. (8 points)
 */
void readWriteTests() {
    /*
     * Create a parallel connection with name "Rnet". It connects the
     * resistors with names "R1" (1 kOhm +/-10%), "R2" (4.7 kOhm +/-10%)
     * and "R3" (6.8 kOhm +/-10%) as shown here:
     *
     *     .-----[R1]-----.
     * ----|              |----
     *     '--[R2]--[R3]--'
     *
     * Write the data to a file. Read it back using the read() method.
     * Assert that the map with results has only a single entry, that
     * the name of the entry is "Rnet" and that a call to components()
     * returns the same result as for the original network which was
     * written to the file.
     */
    auto rNet = make_unique<ParallelResistorConnection>
        (ParallelResistorConnection("Rnet"));
    (*rNet) += make_unique<Resistor>(Resistor("R1", 1000, 0.1));
    auto rS = make_unique<SerialResistorConnection>
        (SerialResistorConnection(SerialResistorConnection("Rs")));
    (*rS) += make_unique<Resistor>(Resistor("R2", 4700, 0.1));
    (*rS) += make_unique<Resistor>(Resistor("R3", 6800, 0.1));
    (*rNet) += std::move(rS);
    ofstream file("data.txt");
    rNet->write(file);
    ifstream iss("data.txt");

    std::map<std::string, ResistancePtr> found;
        ResistanceReader reader;
        reader.read(iss, found);

        // 3) (Optional) Verify you got something
            std::cout << "Read " << found.size() << " top-level entries\n";

            // 4) Dump everything back out to cout
            for (auto &kv : found) {
                kv.second->write(std::cout);
            }
}


void allTests() {
    resistorTests();
    serialTests();
    parallelTests();
    readWriteTests();
}
