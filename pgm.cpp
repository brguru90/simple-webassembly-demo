#include <stdio.h>
#include <string.h>
#include <cstdint>

extern "C" void jsPrintString(const char *s, uint16_t len);
extern "C"
{
   
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
