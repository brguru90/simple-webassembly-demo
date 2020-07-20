#include <stdio.h>
#include <string.h>
#include <cstdint>


// & jsPrintString is defined in js & used as calback so we need to specify it as extern
// Like c the name will not be kept as same so we need to specify it as extern "C so we can call these function like normal c function"


extern "C"
{
   void jsPrintString(const char *s, uint16_t len);
   
   char *c_hello()
   {
      return "Hello World";
   }
   void print()
   {
      const char *str = "Hello from C++!";
      jsPrintString(str, strlen(str));
   }
}
