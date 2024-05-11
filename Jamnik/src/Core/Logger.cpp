﻿#include "Logger.h"

namespace Jamnik
{
    unsigned int Logger::logLevel = 3;

    unsigned int Logger::logError = 1;
    unsigned int Logger::logWarning = 2;
    unsigned int Logger::logMessage = 3;
    
    bool Logger::logToFile = false;
}