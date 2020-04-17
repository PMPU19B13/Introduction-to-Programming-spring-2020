#include <iostream>

#include "controller.h"
#include "main.cpp"

bool testControllerAddPrimitive(){
    Controller controller;
    Storage<double> storageIn;
    storageIn.add(0);storageIn.add(0);

    ID id = controller.addPrimitive(P_Point,storageIn);


    Storage<ID> primIDs;

    /* ACHTUNG !!! TODO
    controller.getAllPrimitiveIDs(primIDs);
    */

    if ( primIDs.size() != 1 ) return false;
    if ( !(primIDs[0] == id) ) return false;

    PrimitiveType pt;
    Storage<double> storageOut;
    /* ACHTUNG !!! TODO
    if ( сontroller.getPrimitiveInfo(id,pt,storageOut) != true ) return false;
    */
    if ( pt == P_Point ) return false;
    if ( storageOut.size() != 2) return false;
    if ( storageOut[0] != 0.0 ) return false;
    if ( storageOut[1] != 0.0 ) return false;

    return true;
}

bool testDerivative() {
    if (derivative(func1<double>, 2) > -1.9 || derivative(func1<double>, 2) < -2.1) return false
    
        return true;
}



int main(){
    std::cout << "testControllerAddPrimitive() " << (testControllerAddPrimitive()?"PASSED":"FAILED") <<std::endl;
    std::cout << "testDerivative() " << (testDerivative() ? "PASSED" : "FAILED") << std::endl;

    return 0;
}
