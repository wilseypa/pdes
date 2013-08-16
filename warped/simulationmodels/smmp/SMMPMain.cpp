// Copyright (c) The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

#include "SMMPApplication.h"
#include "warped/WarpedMain.h"

#include "tclap/CmdLine.h"

#include <string>
#include <iostream>

int
main(int argc, char** argv) {
    std::string inputFileName = "";
    int numObjects = 0;

    std::string configuration = "";
    std::string simulateUntil = "";
    bool debug = false;

    try {
        TCLAP::CmdLine cmd("Iscas89 Simulation");

        TCLAP::ValueArg<string> inputFileNameArg("", "simulate", "configuration file name",
                                                 true, inputFileName, "file", cmd);
        TCLAP::ValueArg<int> numObjectsArg("", "numObjects",
                                           "number of simulation objects",
                                           false, numObjects, "int", cmd);

        // Arguments for WarpedMain
        TCLAP::ValueArg<std::string> configurationArg("c", "configuration", "WARPED configuration file",
                                                      false, configuration, "file", cmd);
        TCLAP::ValueArg<std::string> simulateUntilArg("u", "simulateUntil", "specify a simulation end time",
                                                      false, simulateUntil, "time", cmd);
        TCLAP::SwitchArg debugArg("d", "debug", "display debug messages", cmd, debug);

        cmd.parse(argc, argv);

        inputFileName = inputFileNameArg.getValue();
        numObjects = numObjectsArg.getValue();

        configuration = configurationArg.getValue();
        simulateUntil = simulateUntilArg.getValue();
        debug = debugArg.getValue();
    } catch (TCLAP::ArgException& e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        exit(-1);
    }

    if (inputFileName.empty()) {
        std::cerr << "A configuration file must be specified using --simulate" << std::endl;
        abort();
    }
    WarpedMain wm(new SMMPApplication(inputFileName, numObjects),
                  configuration, simulateUntil, debug);

    return wm.main( argc, argv );
}

