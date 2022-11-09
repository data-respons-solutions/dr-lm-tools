#ifndef GLOBAL_H
#define GLOBAL_H
#include "library_export.h"
#ifdef _MSC_VER
  #if (_MSC_VER < 1600) /* Vs 2010 should have cstdint */
    #include "stdint.h"
  #else
    #include <cstdint>
  #endif
#else
  #include "stdint.h"
#endif

#define _STR(s) #s
#define _XSTR(s) _STR(s)

#define DO_EXPAND(VAL)  VAL ## 1
#define EXPAND_DEFINE(VAL)     DO_EXPAND(VAL)

#ifndef VS_VERSION
#define VS_VERSION_STR  "unset"
#else
#define VS_VERSION_STR _XSTR(VS_VERSION)
#endif

#endif /* GLOBAL_H */
