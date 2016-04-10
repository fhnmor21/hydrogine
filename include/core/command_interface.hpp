/**
The MIT License (MIT)

Copyright (c) 2016 Flavio Moreira

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
  * helper functions to abstract command interface
  * usually this is implemented on system and managers
  */

#ifndef CORE_COMMAND_INTERFACE_HPP
#define CORE_COMMAND_INTERFACE_HPP

#include "core/types.hpp"

namespace Hydrogine
{
//
using namespace Utils;

enum eArgTag
{
  CHAR8,
  INT64,
  UINT64,
  DOUBLE,
  STRINGPTR_
};

struct Args
{
  eArgTag tag;
  union {
    char c[8];
    i64 i;
    u64 u;
    f64 d;
    String* s;
  } data;
};

struct CommandMsg
{
  CommandType type;
  CommandOp op;
  Args arguments[8];
};

class ICommandee
{
public:
  friend class CommandDispatcher;
  virtual ~ICommandee() {}

  const CommandType& getType() const { return type_; }

protected:
  CommandType type_;

  void run(const CommandMsg& cmd) { onCommand(cmd); }
  virtual void onCommand(const CommandMsg& cmd) = 0;
};

} // end namespace Hydrogine

#endif // CORE_COMMAND_INTERFACE_HPP
