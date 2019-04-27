# HUSH 3

## What is HUSH?

![Logo](doc/hush/hush.png "Logo")

HUSH (formerly Zdash) is a code fork of [ZCash](https://z.cash/) which has it's
own genesis block.  Based on Bitcoin's code, it intends to offer a far higher
standard of privacy through a sophisticated zero-knowledge proving scheme that
preserves confidentiality of transaction metadata.

This software is the HUSH node and command-line client. It downloads and stores
the entire history of HUSH transactions; depending on the speed of your
computer and network connection, the synchronization process could take a day
or more once the blockchain has reached a significant size.

**HUSH is unfinished and highly experimental.** Use at your own risk!

## Discord

Please feel free to join us on Discord at https://myhush.org/discord
There are many channels, some you might enjoy are #general, #support and #mining.

## Claiming Funds From Old Hush Wallets

Hush migrated to a new mainnet after Block 500,000 on the old Hush blockchain.
All funds in all addresses as of Block 500,000 were transported to our new chain.

To claim funds on the new chain, there are few options.

### Using an old wallet.dat

Backup your old HUSH wallet.dat, and backup any current wallet.dat that is in your

        ~/.komodo/HUSH3/

directory. There is no way to lose funds, as long as you have backups!!! Make sure
to make backups. Do not skip this step.

Make sure any/all GUI wallets are stopped! Also make sure your old Hush node
and new Hush3 node are stopped:

        cd hush3
        ./src/hush-cli stop

Do not copy wallets or move wallets while your full node is running! This could
corrupt your wallet!

Now copy your old Hush wallet.dat to

        ~/.komodo/HUSH3/

with a command like

        # DO NOT RUN THIS WITHOUT MAKING BACKUPS!
        cp ~/.hush/wallet.dat ~/.komodo/HUSH3/

The reason this works is that both old HUSH and new HUSH are still Bitcoin Protocol
coins, which both use secp256k1 public keys. Now start your HUSH3 node again,
with this special CLI argument that will clear out transactions from your wallet:

        cd hush3
        ./src/hushd -zapwallettxes

This will cause a full history rescan, which will take some time. Once it's complete,
you can see your funds with this command:

        ./src/hush-cli getwalletinfo

### Private Keys

You can also transport funds one address at a time via private keys.

Agama Desktop Wallet WIF-to-WIF Tool can convert between old HUSH and new HUSH3
private keys.

### Web Wallet Seed Phrase

Nothing needs to be done, and if you use the Hush web wallet with a seed phrase,
you can unlock your new funds on the new Hush mainnet with the same seedphrase.


Installing
----------

See [INSTALL.md](https://github.com/MyHush/hush/blob/master/INSTALL.md).


License
-------

For license information see the file [COPYING](COPYING).
