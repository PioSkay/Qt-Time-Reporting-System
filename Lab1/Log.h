////////////////////////////////////////////////////////////
//
// This is the modified component on MEP library.
// https://github.com/Middle-Europe-Productions/MEP/blob/tools/MEP/MEPTools/Log.h
//
// License:
////////////////////////////////////////////////////////////
//
//	Log.h created with the use of SFML
//	MEP - Middle Europe Productions
//  Work in progress.
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
//
//
//	Created by Piotr Skibiñski
//	Copyright © Middle Europe Productions. All rights reserved.
//
////////////////////////////////////////////////////////////



#ifndef MEP_TOOL_LOG_H
#define MEP_TOOL_LOG_H

#define MAX_VERBOSE_LVL 10
#define Log(...) MEP::__Log(__FILE__, __LINE__, __VA_ARGS__)

#include <sstream>
#include <list>
#include <QString>

enum LogLevel
{
    /** Debug level message. */
    Debug = -1,
    /** When execution of the code will be terminated. */
    Fatal = 0,
    /** When there is an error but code can still be executed. */
    Error = 1,
    /** When there is a warning. */
    Warning = 2,
    /** Information log outside the constructor and destructor of na object. */
    Info = 3
};
namespace
{
    /**
    * Verbose logging:
    * 1 - importnant events.
    * 3 - object construction.
    * 7 - method info.
    * 10 - spamming methods info.
    */
    struct VerboseSetup
    {
        const char* m_name;
        unsigned int m_lvl;
        VerboseSetup(const char* name, unsigned int lvl);
        /**
        * Operators.
        */
        bool operator==(const char* name);
        bool operator==(const VerboseSetup& in);
        bool operator!=(const VerboseSetup& in);
        bool operator<(unsigned int in);
        bool operator<(const VerboseSetup& in);
    };
}

namespace MEP
{
    namespace LOG_SETUP
    {
        class Verbose
        {
            static std::list<VerboseSetup> __setup;
        public:
            Verbose() = delete;
            static void add(const char* m_name, unsigned int lvl);
            static int contains(const char* m_name);
        };
    }
    /**
    * \brief Simple build in logging class.
    */
    class __Log
    {
        std::ostringstream _buffer;
        bool _block = false;
        /**
        * Outputs information about
        */
        std::string getName(const char* FILE) const;
    public:
        /**
        * @param[in] __lvl : Info level of the log.
        * @param[in] className : Name of the class from which the log occured.
        */
        explicit __Log(const char* FILE, unsigned int LINE);
        /**
        * @param[in] __lvl : Info level of the log.
        * @param[in] className : Name of the class from which the log occured.
        */
        explicit __Log(const char* FILE, unsigned int LINE, LogLevel __lvl);
        /**
        * @param[in] __lvl : Info level of the log.
        * @param[in] className : Name of the class from which the log occured.
        */
        explicit __Log(const char* FILE, unsigned int LINE, int __lvl);
        /**
        * Overload of the << operator.
        */
        template<typename T>
        __Log& operator<<(T const& out);
        /**
        * The line ends with destruction.
        */
        ~__Log();
    };

    template<typename T>
    __Log& __Log::operator<<(const T& out)
    {
        _buffer << out;
        return *this;
    }
}
#endif
