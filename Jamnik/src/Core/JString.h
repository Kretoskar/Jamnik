#pragma once

#include "Logger.h"

class JString
{
public:
    JString(const char* s)
        : hash(Hash(s)) {}

private:
    unsigned hash;

public:
    const char* Get() const
    {
        return hashTable[hash];
    }

private:
    // hash using prime numbers
    static constexpr unsigned Hash(const char* s)
    {
        unsigned h = 37;
        unsigned size = 0;
        
        while (*s)
        {
            h = (h * 54059) ^ (s[0] * 76963);
            size++;
            s++;
        }

        h %= hashTableSize;

        if (hashTable[h] != nullptr)
        {
            JAMNIK_LOG_ERROR("HASH CONFLICT")
        }
        
        hashTable[h] = s - size;
        
        return h;
    }
    
    static constexpr unsigned hashTableSize = 65536;
    static const char* hashTable[hashTableSize];

    bool operator==(JString&& other) const
    {
        return other.hash == hash;
    }
};
