// Copyright (c) 2019-2020 The Hush developers
#include "JoinSplit.hpp"
#include "prf.h"
#include "sodium.h"

#include "zcash/util.h"

#include <memory>

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <fstream>
#include "tinyformat.h"
#include "sync.h"
#include "amount.h"

#include "librustzcash.h"
#include "streams.h"
#include "version.h"

namespace libzcash {

static CCriticalSection cs_ParamsIO;

template<size_t NumInputs, size_t NumOutputs>
class JoinSplitCircuit : public JoinSplit<NumInputs, NumOutputs> {
public:
    JoinSplitCircuit() {}
    ~JoinSplitCircuit() {}

    /*
    SproutProof prove(
        const std::array<JSInput, NumInputs>& inputs,
        const std::array<JSOutput, NumOutputs>& outputs,
        std::array<SproutNote, NumOutputs>& out_notes,
        std::array<ZCNoteEncryption::Ciphertext, NumOutputs>& out_ciphertexts,
        uint256& out_ephemeralKey,
        const uint256& joinSplitPubKey,
        uint256& out_randomSeed,
        std::array<uint256, NumInputs>& out_macs,
        std::array<uint256, NumInputs>& out_nullifiers,
        std::array<uint256, NumOutputs>& out_commitments,
        uint64_t vpub_old,
        uint64_t vpub_new,
        const uint256& rt,
        bool computeProof,
        uint256 *out_esk // Payment disclosure
    ) {
        GrothProof proof;
        return proof;
    }
    */
};

/*
template<size_t NumInputs, size_t NumOutputs>
JoinSplit<NumInputs, NumOutputs>* JoinSplit<NumInputs, NumOutputs>::Prepared()
{
    return new JoinSplitCircuit<NumInputs, NumOutputs>();
}

template<size_t NumInputs, size_t NumOutputs>
uint256 JoinSplit<NumInputs, NumOutputs>::h_sig(
    const uint256& randomSeed,
    const std::array<uint256, NumInputs>& nullifiers,
    const uint256& joinSplitPubKey
) {
    const unsigned char personalization[crypto_generichash_blake2b_PERSONALBYTES]
        = {'Z','c','a','s','h','C','o','m','p','u','t','e','h','S','i','g'};

    std::vector<unsigned char> block(randomSeed.begin(), randomSeed.end());

    for (size_t i = 0; i < NumInputs; i++) {
        block.insert(block.end(), nullifiers[i].begin(), nullifiers[i].end());
    }

    block.insert(block.end(), joinSplitPubKey.begin(), joinSplitPubKey.end());

    uint256 output;

    if (crypto_generichash_blake2b_salt_personal(output.begin(), 32,
                                                 &block[0], block.size(),
                                                 NULL, 0, // No key.
                                                 NULL,    // No salt.
                                                 personalization
                                                ) != 0)
    {
        throw std::logic_error("hash function failure");
    }

    return output;
}


template class JoinSplit<ZC_NUM_JS_INPUTS,
                         ZC_NUM_JS_OUTPUTS>;

*/
}
