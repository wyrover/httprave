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

    FCT_QTEST_BGN( http_get )
    {
        HTTPRaveRequest request();
        fct_chk( request.get( L"http://google.com" ).isSuccess() );
    }
    FCT_QTEST_END();


    FCT_QTEST_BGN( http_post_with_params )
    {
        HTTPRaveRequest request( L"http://google.com/search" );
        request.setParam( L"q", L"Michael Jackson" );
        fct_chk( request.post().isSuccess() );
    }
    FCT_QTEST_END();


}
FCT_END( console_wait(); );
