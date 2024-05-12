#pragma once

#include <sstream>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <ostream>

#define LOG_ERROR(...) \
std::printf("[Error] [%s] ", __FUNCTION__); \
Jamnik::Logger::Log(Jamnik::LogVerbosity::Error, __VA_ARGS__);

#define LOG_WARNING(...) \
std::printf("[Warning] [%s] ", __FUNCTION__); \
Jamnik::Logger::Log(Jamnik::LogVerbosity::Warning, __VA_ARGS__);

#define LOG_MESSAGE(...) \
std::printf("[Message] [%s] ", __FUNCTION__); \
Jamnik::Logger::Log(Jamnik::LogVerbosity::Message, __VA_ARGS__);

namespace Jamnik
{
    enum LogVerbosity
    {
        Error = 1,
        Warning = 2,
        Message = 3,
    };

    class Logger
    {
    public:
        /* log if input log level is equal or smaller to log level set */
        template <typename... Args>
        static void Log(LogVerbosity inLogLevel, Args ... args)
        {
            if (logToFile)
            {
                static bool bInitialized = false;
                if (!bInitialized)
                {
                    std::ofstream clearFile("log/log.txt");
                    bInitialized = true;
                }
            }

            if (inLogLevel <= logLevel) 
            {
                char buffer[100];
                sprintf_s(buffer, args ...);
                std::cout << buffer << std::endl;
               
                if (logToFile)
                {
                    std::ofstream ofile("log/log.txt", std::ios::app);
                    ofile << buffer << '\n';
                    ofile.close();
                }

                if (loggedLineBufferCurrCount >= loggedLineBufferMaxCount)
                {
                    for (int i = 0; i < loggedLineBufferMaxCount - 1; i++)
                    {
                        logLinesVerbosity[i] = logLinesVerbosity[i+1];
                        logLines[i] = logLines[i+1];
                    }

                    logLinesVerbosity[loggedLineBufferMaxCount - 1] = inLogLevel;
                    logLines[loggedLineBufferMaxCount - 1] = buffer;
                }
                else
                {
                    logLinesVerbosity[loggedLineBufferCurrCount] = inLogLevel;
                    logLines[loggedLineBufferCurrCount] = buffer;
                    loggedLineBufferCurrCount++;
                }
            }
        }
    
        static void SetLogLevel(unsigned int inLogLevel)
        {
            logLevel = inLogLevel;
        }
        
        static unsigned int logLevel;
        static unsigned int logError;
        static unsigned int logWarning;
        static unsigned int logMessage;
        static bool logToFile;

        static constexpr unsigned int loggedLineBufferMaxCount = 16;
        static std::string logLines[loggedLineBufferMaxCount];
        static LogVerbosity logLinesVerbosity[loggedLineBufferMaxCount];
        static unsigned int loggedLineBufferCurrCount;
    };
}