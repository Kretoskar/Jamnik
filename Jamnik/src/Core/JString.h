#pragma once

#include "Logger.h"

#define FIND_HASH_CONFLICTS true

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

        if (FIND_HASH_CONFLICTS)
        {
            if (hashTable[h] != nullptr)
            {
                int jump = 0;
                
                do
                {
                    char c1 = *(hashTable[h] + jump);
                    char c2 = *(s - size + jump);
                
                    if (c1 != c2)
                    {
                        JAMNIK_LOG_ERROR("HASH CONFLICT")
                        // TODO: assert
                        return 0;
                    }
    
                    if (c1 == '\0')
                    {
                        break;
                    }
                
                    jump++;
                } while (true);
            }
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

#undef FIND_HASH_CONFLICTS