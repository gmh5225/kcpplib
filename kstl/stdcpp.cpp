#include <memory>

#pragma data_seg(".STL$A")
void (*___StlStartInitCalls__[1])(void) = {0};
#pragma data_seg(".STL$L")
void (*___StlEndInitCalls__[1])(void) = {0};
#pragma data_seg(".STL$M")
void (*___StlStartTerminateCalls__[1])(void) = {0};
#pragma data_seg(".STL$Z")
void (*___StlEndTerminateCalls__[1])(void) = {0};
#pragma data_seg()

#pragma comment(linker, "/merge:.STL=.data")
