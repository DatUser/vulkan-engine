#include <iostream>
#include <string>

#ifndef CHK_ELSE_RET
#define CHK_ELSE_RET(x)           \
  do {                            \
    if (x == nullptr)  return 1;  \
  } while(0)
#endif

#ifndef CHK_SUCCESS
#define CHK_SUCCESS(x)                                                            \
  do {                                                                            \
    if (x != 0)                                                                   \
    {                                                                             \
      std::cerr << "Failed: " << __FILE__ << ": l. " << __LINE__ << std::endl;    \
      std::string sInput;                                                         \
      do {                                                                        \
        std::cerr << "Ignore or abort ? (i/a)" << std::endl;                      \
        std::cin >> sInput;                                                       \
      } while (sInput != "i" && sInput != "a");                                   \
      if (sInput == "a") exit(1);                                                 \
    }                                                                             \
  } while (0)
#endif