/******************************************************************************
 * Copyright © 2019-2020 The Hush developers                                       *
 *                                                                            *
 * See the AUTHORS and LICENSE files at                                       *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * this software, including this file may be copied, modified, propagated     *
 * or distributed except according to the terms contained in the GPLv3        *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#ifndef SIETCH_H
#define SIETCH_H

string newSietchZaddr() {
    bool addToWallet = false;
    auto zaddr = EncodePaymentAddress(pwalletMain->GenerateNewSaplingZKey(addToWallet));
    return zaddr;
}

SendManyRecipient newSietchRecipient(string zaddr) {
    int nAmount = 0;
    string memo = "f600000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    return SendManyRecipient( zaddr, nAmount, memo );
}

#endif
