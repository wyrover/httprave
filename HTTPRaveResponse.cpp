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
#include "HTTPRaveResponse.h"
#include "HTTPRaveRequest.h"
#include <iostream>

HTTPRaveResponse::HTTPRaveResponse() : statusCode(0)
{
    
}

HTTPRaveResponse::~HTTPRaveResponse()
{

}

void HTTPRaveResponse::setHeader( std::wstring &header )
{
    // To save copying data, we perform a swap here
    this->header.swap( header );
}

void HTTPRaveResponse::setBody( std::string &body )
{
    // To save copying data, we perform a swap here
    this->bodyUTF8.swap( body );

    // TODO: Take the UTF8 response and parse it as unicode
}

void HTTPRaveResponse::setStatusCode( unsigned long status )
{
    this->statusCode = status;
}

void HTTPRaveResponse::setErrorCode( unsigned long error )
{
    
    wchar_t msg[1000];
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, msg, sizeof(msg), NULL );
    std::wcout << msg;

    this->errorCode = error;
}

bool HTTPRaveResponse::isSuccess()
{
    return true;
}
