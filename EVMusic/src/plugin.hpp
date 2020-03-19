#pragma once
#include <rack.hpp>
extern "C" {
#include "Soundpipe/soundpipe.h"
}


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
// extern Model* modelMyModule;

extern Model* modelModularForecast;
