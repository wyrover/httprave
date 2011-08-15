#include "fct.h"
#include "HTTPRaveRequest.h"
#include "HTTPRaveResponse.h"
#include <windows.h>

void console_wait()
{
    HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(ConsoleInput, 0);
    TCHAR InputBuffer;
    DWORD CharsRead;
    ReadConsole(ConsoleInput, &InputBuffer, 1, &CharsRead, 0);
}


FCT_BGN()
{

    FCT_QTEST_BGN( basic_http_get )
    {
        HTTPRaveResponse response = HTTPRaveRequest().get(L"http://google.com");
        fct_chk( response.isSuccess() );
    }
    FCT_QTEST_END();

}
FCT_END( console_wait(); );
