/*
 * httprave :: A simple C++ HTTP library for Windows
 * Copyright (C) 2011  http://github.com/cammm
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */
#ifndef _HTTP_RAVE_REQUEST_H_
#define _HTTP_RAVE_REQUEST_H_

#define UNICODE 1
#pragma comment(lib, "wininet.lib")

#include <windows.h>
#include <winreg.h>
#include <wininet.h>
#include <string>
#include "HTTPRaveResponse.h"

class HTTPRaveRequest
{
    friend class HTTPRaveResponse;

    public:
        HTTPRaveRequest();
        HTTPRaveRequest( const std::wstring &baseURL );
        virtual ~HTTPRaveRequest();

        // Setup params for the request
        void setParam( const std::wstring &name, const std::wstring &value );
        void setParam( const std::wstring &name, const int &value );
        void setParam( const std::wstring &name, const bool &value );

        // Perform the request, returning the response
        HTTPRaveResponse get( const std::wstring &url = L"" );
        HTTPRaveResponse post( const std::wstring &url = L"" );
        HTTPRaveResponse put( const std::wstring &url = L"" );
        HTTPRaveResponse request( const std::wstring &method, const std::wstring &url = L"" );

        // Handy dandy static interface
        static HTTPRaveResponse Get( const std::wstring &path ) { return HTTPRaveRequest().get( path ); }
        static HTTPRaveResponse Post( const std::wstring &path ) { return HTTPRaveRequest().post( path ); }
        static HTTPRaveResponse Put( const std::wstring &path ) { return HTTPRaveRequest().put( path ); }

    private:
        void                parseURL( const std::wstring &url );

    protected:
        // Internet handles used by WinINet
        HINTERNET           internetOpen;
        HINTERNET           internetConnect;
        HINTERNET           requestOpen;

        // These two are provided by the user
        std::wstring        baseURL;
        std::wstring        url;

        // This are constructed by joining the above then splitting
        std::wstring        server;
        std::wstring        path;
        int                 port;
};


#endif
