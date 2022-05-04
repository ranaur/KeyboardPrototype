#ifndef DEBUG_H
#define DEBUG_H

//#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define debug(a) { Serial.print(a); }
#define debugln(a) { Serial.println(a); }
#else
#define debug(a)
#define debugln(a)
#endif

#endif
