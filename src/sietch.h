/******************************************************************************
 * Copyright © 2019 The Hush developers                                       *
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

//TODO: List zpools here, and a function to randomly choose from them
#ifndef SIETCH_H
#define SIETCH_H

string randomSietchZaddr() {
    std::vector<string> SietchShieldedPool1 = {
    };
    std::vector<string> SietchShieldedPool2 = {
    };
    //TODO: Assumes pools of 100
    int randIndex = GetRandInt(100); // random int between 0 and 99
    if(randIndex % 2) {
       return SietchShieldedPool1[randIndex];
    } else {
       return SietchShieldedPool2[randIndex];
    }
}

#endif
