#pragma once

#include "Logger.h"

#define FIND_HASH_CONFLICTS
#define SPOT_REHASHING

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

        s = s-size;

#ifdef SPOT_REHASHING
        if (hashTable[h][0] != '\0')
        {
            JAMNIK_LOG_ERROR("REHASHING SPOTTED")
        }
#endif

#ifdef FIND_HASH_CONFLICTS
        if (hashTable[h][0] != '\0')
        {
            for (unsigned i = 0; i < hashTableMaxStringLenght; i++)
            {
                const char existingChar = hashTable[h][i];
                const char newChar = *(s+i);
                
                if (existingChar == newChar == '\0')
                {
                    break;
                }
                
                if (existingChar != newChar)
                {
                    JAMNIK_LOG_ERROR("HASH CONFLICT")
                }
            }
        }
#endif

        unsigned i = 0;
        
        while (*s)
        {
            hashTable[h][i] = *s;
            i++;
            s++;
        }
        
        return h;
    }
    
    static constexpr unsigned hashTableSize = 65536;
    static constexpr unsigned hashTableMaxStringLenght = 256;
    static char hashTable[hashTableSize][hashTableMaxStringLenght];

    bool operator==(JString&& other) const
    {
        return other.hash == hash;
    }
};

#undef FIND_HASH_CONFLICTS