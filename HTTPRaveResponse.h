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
#ifndef _HTTP_RAVE_RESPONSE_H_
#define _HTTP_RAVE_RESPONSE_H_
#include <string>

class HTTPRaveRequest;
class HTTPRaveResponse
{
    public:
        HTTPRaveResponse();
        virtual ~HTTPRaveResponse();

        void setHeader( std::wstring &body );
        void setBody( std::string &body );
        void setStatusCode( unsigned long status );
        void setErrorCode( unsigned long error );

        bool isSuccess();

    protected:
        unsigned long   statusCode;
        unsigned long   errorCode;
        std::string     bodyUTF8;
        std::wstring    body;
        std::wstring    header;
};

#endif
