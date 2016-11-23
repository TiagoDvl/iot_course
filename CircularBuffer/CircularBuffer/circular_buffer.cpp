/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Edson Borin <edson@ic.unicamp.br>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */

#include "circular_buffer.h"
#include "stdlib.h" // malloc - free

CharCircularBuffer::CharCircularBuffer(unsigned int buffer_sz)
{
  allocated = false;
  sz = buffer_sz;
  if (sz == 0) 
    buffer = 0;
  else {
    buffer = (char*) malloc(sizeof(char)*sz);
    if (buffer == 0)
      sz = 0;
    else
      allocated = true;
  }

  if (!buffer) return;
  head = tail = 0;
}

CharCircularBuffer::CharCircularBuffer(unsigned int buffer_sz, char* _buffer)
{
  allocated = false;
  sz = buffer_sz;
  buffer = _buffer;

  if (!buffer) return;
  head = tail = 0;
}

CharCircularBuffer::~CharCircularBuffer()
{
  if (allocated) {
    free (buffer);
  }
}

bool CharCircularBuffer::push(char c)
{
  if (!buffer) 
    return false; // No buffer => Buffer full.

  if (head == (tail-1))
    return false; // Full

  if ( (head == (sz-1)) && (tail == 0) )
    return false; // Full

  buffer[head] = c;

  // Advance the head
  if (head == (sz-1))
    head = 0;
  else
    head++;

  return true;
}

bool CharCircularBuffer::pop(char& c)
{
  if (!buffer) 
    return false; // Empty

  if (head == tail)
    return false; // Empty

  c = buffer[tail];

  // Advance tail
  if (tail == (sz-1))
    tail = 0;
  else
    tail++;

  return true;
}
