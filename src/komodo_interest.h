/******************************************************************************
 * Copyright © 2014-2019 The SuperNET Developers.                             *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * SuperNET software, including this file may be copied, modified, propagated *
 * or distributed except according to the terms contained in the LICENSE file *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#include "komodo_defs.h"

#define SATOSHIDEN ((uint64_t)100000000L)
#define dstr(x) ((double)(x) / SATOSHIDEN)

#define KOMODO_ENDOFERA 7777777
#define KOMODO_INTEREST ((uint64_t)5000000) //((uint64_t)(0.05 * COIN))   // 5%
extern int64_t MAX_MONEY;
extern uint8_t NOTARY_PUBKEY33[];

#ifdef notanymore
int64_t komodo_earned_interest(int32_t height,int64_t paidinterest)
{
    static int64_t *interests; static int32_t maxheight;
    uint64_t total; int32_t ind,incr = 10000;
    // need to make interests persistent before 2030, or just hardfork interest/mining rewards disable after MAX_MONEY is exceeded
    return(0);
    if ( height >= maxheight )
    {
        if ( interests == 0 )
        {
            maxheight = height + incr;
            interests = (int64_t *)calloc(maxheight,sizeof(*interests) * 2);
        }
        else
        {
            interests = (int64_t *)realloc(interests,(maxheight + incr) * sizeof(*interests) * 2);
            memset(&interests[maxheight << 1],0,incr * sizeof(*interests) * 2);
            maxheight += incr;
        }
    }
    ind = (height << 1);
    if ( paidinterest < 0 ) // request
    {
        return(interests[ind]);
    }
    else
    {
        if ( interests[ind + 1] != paidinterest ) // need to handle skips like at 80000
        {
            //fprintf(stderr,"interests.%d %.8f %.8f vs paidinterest %.8f\n",height,dstr(interests[ind]),dstr(interests[ind+1]),dstr(paidinterest));
            interests[ind + 1] = paidinterest;
            if ( height <= 1 )
                interests[ind] = 0;
            else interests[ind] = interests[ind - 2] + interests[ind - 1];
            total = interests[ind] + paidinterest;
            //fprintf(stderr,"reset interests[height.%d to maxheight.%d] <- %.8f\n",height,maxheight,dstr(total));
            for (++height; height<maxheight; height++)
            {
                ind = (height << 1);
                interests[ind] = total;
                interests[ind + 1] = 0;
            }
        }
        //else fprintf(stderr,"interests.%d %.8f %.8f\n",height,dstr(interests[ind]),dstr(interests[ind+1]));
    }
    return(0);
}

uint64_t komodo_moneysupply(int32_t height)
{
    if ( height <= 1 || ASSETCHAINS_SYMBOL[0] == 0 )
        return(0);
    else return(COIN * 100000000 + (height-1) * 3 + komodo_earned_interest(height,-1));
}
#endif

int64_t _komodo_interestnew(int32_t txheight,uint64_t nValue,uint32_t nLockTime,uint32_t tiptime)
{
    int32_t minutes; int64_t interest = 0;
    if ( nLockTime >= (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[3] : LOCKTIME_THRESHOLD) && tiptime > nLockTime && (minutes= (tiptime - nLockTime) / 60) >= (KOMODO_MAXMEMPOOLTIME/60) )
    {
        if ( minutes > 365 * 24 * 60 )
            minutes = 365 * 24 * 60;
        if ( txheight >= 1000000 && minutes > 31 * 24 * 60 )
            minutes = 31 * 24 * 60;
        minutes -= ((KOMODO_MAXMEMPOOLTIME/60) - 1);
        interest = ((nValue / 10512000) * minutes); // To adapt for ac_aur and ac_naur ?
    }
    return(interest);
}

int64_t komodo_interestnew(int32_t txheight,uint64_t nValue,uint32_t nLockTime,uint32_t tiptime)
{
    int64_t interest = 0;
    if ( ( ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 || txheight < KOMODO_ENDOFERA) && nLockTime >= (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[3] : LOCKTIME_THRESHOLD) && tiptime != 0 && nLockTime < tiptime && nValue >= (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[2] : 10)*COIN ) //komodo_moneysupply(txheight) < MAX_MONEY &&
        interest = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
    return(interest);
}

int64_t komodo_interest(int32_t txheight,uint64_t nValue,uint32_t nLockTime,uint32_t tiptime)
{
    int32_t minutes,exception; int64_t interestnew,numerator,denominator,interest = 0; uint32_t activation;
    activation = 1491350400;  // 1491350400 5th April
    if ( ASSETCHAINS_SYMBOL[0] != 0 && ASSETCHAINS_ACTIVEUSERREWARD[0] == 0 )
        return(0);
    if ( txheight >= KOMODO_ENDOFERA && ASSETCHAINS_ACTIVEUSERREWARD[0] == 0 )
        return(0);
    if ( nLockTime >= (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[3] : LOCKTIME_THRESHOLD) && tiptime != 0 && nLockTime < tiptime && nValue >= (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[2] : 10)*COIN ) //komodo_moneysupply(txheight) < MAX_MONEY && 
    {
        if ( (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 && (minutes= (tiptime - nLockTime) / 60) >= 1 ) || (minutes= (tiptime - nLockTime) / 60) >= 60 ) // ?? Hack to test it
        {
            if ( minutes > 365 * 24 * 60 )
                minutes = 365 * 24 * 60;
            if ( txheight >= 250000 )
                minutes -= 59;
            denominator = (((int64_t)365 * 24 * 60) / minutes);
            if ( denominator == 0 )
                denominator = 1; // max KOMODO_INTEREST per transfer, do it at least annually!
            if ( nValue > 25000LL*COIN )
            {
                exception = 0;
                if ( txheight <= 155949 )
                {
                    if ( (txheight == 116607 && nValue == 2502721100000LL) ||
                        (txheight == 126891 && nValue == 2879650000000LL) ||
                        (txheight == 129510 && nValue == 3000000000000LL) ||
                        (txheight == 141549 && nValue == 3500000000000LL) ||
                        (txheight == 154473 && nValue == 3983399350000LL) ||
                        (txheight == 154736 && nValue == 3983406748175LL) ||
                        (txheight == 155013 && nValue == 3983414006565LL) ||
                        (txheight == 155492 && nValue == 3983427592291LL) ||
                        (txheight == 155613 && nValue == 9997409999999797LL) ||
                        (txheight == 157927 && nValue == 9997410667451072LL) ||
                        (txheight == 155613 && nValue == 2590000000000LL) ||
                        (txheight == 155949 && nValue == 4000000000000LL) )
                        exception = 1;
                    if ( exception == 0 || nValue == 4000000000000LL )
                        printf(">>>>>>>>>>>> exception.%d txheight.%d %.8f locktime %u vs tiptime %u <<<<<<<<<\n",exception,txheight,(double)nValue/COIN,nLockTime,tiptime);
                }
                //if ( nValue == 4000000000000LL )
                //    printf(">>>>>>>>>>>> exception.%d txheight.%d %.8f locktime %u vs tiptime %u <<<<<<<<<\n",exception,txheight,(double)nValue/COIN,nLockTime,tiptime);
                if ( exception == 0 )
                {
                    numerator = (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ((int64_t) nValue * ASSETCHAINS_ACTIVEUSERREWARD[4] / 100) : (nValue / 20)); // assumes 5%!
                    fprintf(stderr,"komodo_interest.1 interest rate %llu", (long long)ASSETCHAINS_ACTIVEUSERREWARD[4]);
                    if ( txheight < 250000 )
                        interest = (numerator / denominator);
                    else if ( txheight < 1000000 )
                    {
                        interest = (numerator * minutes) / ((int64_t)365 * 24 * 60);
                        interestnew = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
                        if ( interest < interestnew )
                            printf("pathA current interest %.8f vs new %.8f for ht.%d %.8f locktime.%u tiptime.%u\n",dstr(interest),dstr(interestnew),txheight,dstr(nValue),nLockTime,tiptime);
                    }
                    else interest = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
                }
                else if ( txheight < 1000000 )
                {
                    numerator = ((int64_t) nValue * (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[4] * 1000000 : KOMODO_INTEREST));
                    fprintf(stderr,"komodo_interest.2 %llu", (long long)ASSETCHAINS_ACTIVEUSERREWARD[4]);
                    interest = (numerator / denominator) / COIN;
                    interestnew = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
                    if ( interest < interestnew )
                        printf("pathB current interest %.8f vs new %.8f for ht.%d %.8f locktime.%u tiptime.%u\n",dstr(interest),dstr(interestnew),txheight,dstr(nValue),nLockTime,tiptime);
                }
                else interest = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
            }
            else
            {
                /* 250000 algo
                    numerator = (nValue * KOMODO_INTEREST);
                    if ( txheight < 250000 || numerator * minutes < 365 * 24 * 60 )
                        interest = (numerator / denominator) / COIN;
                    else interest = ((numerator * minutes) / ((uint64_t)365 * 24 * 60)) / COIN;
                */
                numerator = ((int64_t) nValue * (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[4] * 1000000 : KOMODO_INTEREST));
                // fprintf(stderr,"komodo_interest.3 %llu", (long long)ASSETCHAINS_ACTIVEUSERREWARD[4]);
                if ( txheight < 250000 || tiptime < activation )
                {
                    if ( txheight < 250000 || numerator * minutes < 365 * 24 * 60 )
                        interest = (numerator / denominator) / COIN;
                    else interest = ((numerator * minutes) / ((int64_t)365 * 24 * 60)) / COIN;
                }
                else if ( txheight < 1000000 )
                {
                    numerator = (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ((int64_t) nValue * ASSETCHAINS_ACTIVEUSERREWARD[4] / 100) : (nValue / 20)); // assumes 5%!
                    // fprintf(stderr,"komodo_interest.4 %llu", (long long)ASSETCHAINS_ACTIVEUSERREWARD[4]);
                    interest = ((numerator * minutes) / ((int64_t)365 * 24 * 60));
                    //fprintf(stderr,"interest %llu %.8f <- numerator.%llu minutes.%d\n",(long long)interest,(double)interest/COIN,(long long)numerator,(int32_t)minutes);
                    interestnew = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
                    if ( interest < interestnew )
                        fprintf(stderr,"pathC current interest %.8f vs new %.8f for ht.%d %.8f locktime.%u tiptime.%u\n",dstr(interest),dstr(interestnew),txheight,dstr(nValue),nLockTime,tiptime);
                }
                else interest = _komodo_interestnew(txheight,nValue,nLockTime,tiptime);
            }
            if ( 0 && numerator == (nValue * (ASSETCHAINS_ACTIVEUSERREWARD[0] == 1 ? ASSETCHAINS_ACTIVEUSERREWARD[4] * 1000000 : KOMODO_INTEREST)) )
                fprintf(stderr,"komodo_interest.%d %lld %.8f nLockTime.%u tiptime.%u minutes.%d interest %lld %.8f (%llu / %llu) prod.%llu\n",txheight,(long long)nValue,(double)nValue/COIN,nLockTime,tiptime,minutes,(long long)interest,(double)interest/COIN,(long long)numerator,(long long)denominator,(long long)(numerator * minutes));
//        fprintf(stderr,"komodo_interest.END1 interest rate %llu", (long long)ASSETCHAINS_ACTIVEUSERREWARD[4]);
        }
//        fprintf(stderr,"komodo_interest.END2 interest rate %llu", (long long)ASSETCHAINS_ACTIVEUSERREWARD[4]);
    }
//    fprintf(stderr,"komodo_interest.%d %lld %.8f nLockTime.%u tiptime.%u minutes.%d interest %lld %.8f (%llu / %llu) prod.%llu\n",
//            txheight,(long long)nValue,(double)nValue/COIN,nLockTime,tiptime,minutes,
//            (long long)interest,(double)interest/COIN,(long long)numerator,(long long)denominator,(long long)(numerator * minutes));
    // komodo_interest.34 24000000000 240.00000000 nLockTime.1607984421 tiptime.1607985058 minutes.10 
    // interest 0 0.00000000 (94758346831376 / 139715708921696) prod.947583468313760
    return(interest);
}
/*
bool is_mm2_address(CTxDestination address)
//        if (ExtractDestination(out.tx->vout[out.i].scriptPubKey, address))
    
    return false;
)
*/
