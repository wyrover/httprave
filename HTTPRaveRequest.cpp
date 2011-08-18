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
#include "HTTPRaveRequest.h"
#include <vector>

#define HTTPRAVE_AGENT  L"HTTP Rave(0.1)"

HTTPRaveRequest::HTTPRaveRequest()
{

}

HTTPRaveRequest::HTTPRaveRequest( const std::wstring &baseURL ) : baseURL( baseURL )
{

}

HTTPRaveRequest::~HTTPRaveRequest()
{
    
}

HTTPRaveResponse HTTPRaveRequest::request( const std::wstring &method, const std::wstring &url )
{
    // Reinitialize the handles to NULL incase this is the second request made with this object.
    this->internetOpen = NULL;
    this->internetConnect = NULL;
    this->requestOpen = NULL;

    // Setup flags and a response object
    HTTPRaveResponse response;

    // First parse the URL provided into server, port and path
    this->parseURL( url );
    try
    {
        // Open a handle to the internet, grab settings from the registry
        this->internetOpen = InternetOpen( HTTPRAVE_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
        if( !this->internetOpen )
        {
            throw GetLastError();
        }

        // Open our connection to the server
        this->internetConnect = InternetConnect( this->internetOpen, this->server.c_str(), this->port, L" ", L" ", INTERNET_SERVICE_HTTP, 0, 0 );
        if( !this->internetConnect )
        {
            throw GetLastError();
        }

        // Setup flags for the connection
        DWORD flags = INTERNET_FLAG_KEEP_CONNECTION;

        // Last handle, open the request for this URL
        this->requestOpen = HttpOpenRequest( this->internetConnect, method.c_str(), this->path.c_str(), NULL, NULL, NULL, flags, 0 );
        if( !this->requestOpen )
        {
            throw GetLastError();
        }

        /////////////////////////////////////////////////////////////////////
        // BODY
        /////////////////////////////////////////////////////////////////////
        std::string body;
        char buffer[2048];
        DWORD bytesRead;
        HttpSendRequest( this->requestOpen, NULL, 0, NULL, 0 );
        while( InternetReadFile( this->requestOpen, buffer, sizeof(buffer), &bytesRead ) )
        {
            // Stop reading when there are no more bytes
            if( bytesRead == 0 ) break;

            // Copy into our string class
            body.append( buffer, bytesRead );
        }

        if( GetLastError() )
        {
            throw GetLastError();
        }

        /////////////////////////////////////////////////////////////////////
        // HEADER
        /////////////////////////////////////////////////////////////////////
        DWORD headerBufferLength = 0;
        wchar_t* headerBuffer = NULL;
        while( !HttpQueryInfo( this->requestOpen, HTTP_QUERY_RAW_HEADERS_CRLF, headerBuffer, &headerBufferLength, NULL) )
        {
            if( GetLastError() == ERROR_INSUFFICIENT_BUFFER )
            {
                SetLastError(0);
                free( headerBuffer );
                headerBuffer = (wchar_t*)malloc( sizeof(wchar_t) * headerBufferLength );
            }
            else
            {
                // TODO: When can this occur?
                break;
            }
        }
        std::wstring header( headerBuffer, headerBufferLength );
        free( headerBuffer );

        // Check to see if anything went wrong
        response.setErrorCode( GetLastError() );

        // Hand over the header and body to the reponse object to parse
        response.setHeader( header );
        response.setBody( body );
    }
    catch( DWORD code )
    {
        InternetCloseHandle( this->requestOpen );
        InternetCloseHandle( this->internetConnect );
        InternetCloseHandle( this->internetOpen );
        response.setErrorCode( code );
    }

    return response;
}

void HTTPRaveRequest::parseURL( const std::wstring &url )
{
    this->server = L"www.google.com";
    this->port = INTERNET_DEFAULT_HTTP_PORT;
    this->path = L"";
}

void HTTPRaveRequest::setParam( const std::wstring &name, const std::wstring &value )
{

}

void HTTPRaveRequest::setParam( const std::wstring &name, const int &value )
{

}

void HTTPRaveRequest::setParam( const std::wstring &name, const bool &value )
{

}

HTTPRaveResponse HTTPRaveRequest::get( const std::wstring &url )
{
    return this->request( L"GET", url );
}

HTTPRaveResponse HTTPRaveRequest::post( const std::wstring &url )
{
    return this->request( L"POST", url );
}

HTTPRaveResponse HTTPRaveRequest::put( const std::wstring &url )
{
    return this->request( L"PUT", url );
}
