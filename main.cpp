// use %ERRORLEVEL% to get the result of `int main()`

#include "crap.h"

#include <vector>
DOCTEST_IMPLEMENT_GLOBALS();

int main() {
    DOCTEST_INVOKE_ALL_TEST_FUNCTIONS();
    
    //system("pause");
	
    return 0;
}
