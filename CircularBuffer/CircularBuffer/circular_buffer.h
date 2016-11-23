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
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

class CharCircularBuffer
{
 public:
  /** 
   * Constructor.
   * buffer_sz: The circular buffer size.
   */
  CharCircularBuffer(unsigned int buffer_sz); 

  /** 
   * Constructor.
   * buffer_sz: The circular buffer size.
   * _buffer: The buffer itself. 
   */
  CharCircularBuffer(unsigned int buffer_sz, char* _buffer);

  /** 
   * Destructor.
   */
  ~CharCircularBuffer(); 

  /** 
   * Inserts a new char on the head of the circular buffer.
   * c: char to be added.
   * Returns:
   *  true: in case it inserted the data.
   *  false: full buffer
   */
  bool push(char c);

  /** 
   * Pops a char from the tail of the circular buffer.
   * c: address of the variable to receive a copy of the data.
   * Returns:
   *  true: in case it managed to pop data from the buffer.
   *  false: empty buffer
   */
  bool pop(char& c);

 private:
  char* buffer;
  unsigned int sz;
  unsigned int head;
  unsigned int tail;
  bool allocated;
};


#endif // CIRCULAR_BUFFER_H
