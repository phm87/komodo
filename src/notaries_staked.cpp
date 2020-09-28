
#include "notaries_staked.h"
#include "crosschain.h"
#include "cc/CCinclude.h"
#include "komodo_defs.h"
#include <cstring>

extern pthread_mutex_t staked_mutex;

int8_t is_STAKED(const char *chain_name) 
{
    static int8_t STAKED=0;
    return(STAKED);
};

int32_t STAKED_era(int timestamp)
{
  return(0);
};

int8_t StakedNotaryID(std::string &notaryname, char *Raddress) {
    return(-1);
}

int8_t numStakedNotaries(uint8_t pubkeys[64][33],int8_t era) {
    int i; int8_t retval = 0;
    return(retval);
}

void UpdateNotaryAddrs(uint8_t pubkeys[64][33],int8_t numNotaries) {
}

CrosschainAuthority Choose_auth_STAKED(int32_t chosen_era) {
  CrosschainAuthority auth;
  auth.requiredSigs = (num_notaries_STAKED[chosen_era-1] / 5);
  auth.size = num_notaries_STAKED[chosen_era-1];
  return auth;
};
