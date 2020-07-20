#include <stdio.h>
#include <string>
#include <string.h>
extern "C"
{

#include <cstdint>
#include <ctime>
#include <time.h>
}

const std::string currentDateTime()
{
   time_t now = time(0);
   struct tm tstruct;
   char buf[80];
   tstruct = *localtime(&now);
   // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
   // for more information about date/time format
   strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

   return buf;
}

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
      char *str = "Hello from C++!";
      strcat(str, currentDateTime().c_str());
      jsPrintString(str, strlen(str));
   }
}
