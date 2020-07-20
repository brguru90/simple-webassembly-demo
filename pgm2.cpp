#include <stdio.h>
#include <string.h>
#include <cstdint>



extern "C"
{
   void jsPrintString(const char *s, uint16_t len);

   char *c_hello()
   {
      return "Hello World";
   }
   void print()
   {
      char *str = "Hello from C++!";
      jsPrintString(str, strlen(str));
   }
}
