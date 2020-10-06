// Copyright (c) 2019-2020 The Hush developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php

namespace hush
{
    typedef enum { SSL_ACCEPT, SSL_CONNECT, SSL_SHUTDOWN } SSLConnectionRoutine;
    typedef enum { CLIENT_CONTEXT, SERVER_CONTEXT } TLSContextType;
}
