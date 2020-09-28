#!/bin/bash
# Copyright 2019 Hush Developers
# Released under the GPLv3
## Usage:
##  ./zcutil/build-debian-package.sh

echo "Let There Be Debian Packages"

set -e
set -x

BUILD_PATH="/tmp/hush-debian-$$"
PACKAGE_NAME="hush"
SRC_PATH=`pwd`
SRC_DEB=$SRC_PATH/contrib/debian
SRC_DOC=$SRC_PATH/doc

umask 022

if [ ! -d $BUILD_PATH ]; then
    mkdir $BUILD_PATH
fi

## PACKAGE_VERSION=$($SRC_PATH/src/zcashd --version | grep version | cut -d' ' -f4 | tr -d v)
#PACKAGE_VERSION=3.2.0
PACKAGE_VERSION=$($SRC_PATH/src/hushd --version|grep version|cut -d' ' -f4|cut -d- -f1|sed 's/v//g')
DEBVERSION=$(echo $PACKAGE_VERSION | sed 's/-beta/~beta/' | sed 's/-rc/~rc/' | sed 's/-/+/')
BUILD_DIR="$BUILD_PATH/$PACKAGE_NAME-$PACKAGE_VERSION-amd64"

if [ -d $BUILD_DIR ]; then
    rm -R $BUILD_DIR
fi

DEB_BIN=$BUILD_DIR/usr/bin
DEB_CMP=$BUILD_DIR/usr/share/bash-completion/completions
DEB_DOC=$BUILD_DIR/usr/share/doc/$PACKAGE_NAME
DEB_MAN=$BUILD_DIR/usr/share/man/man1
DEB_SHR=$BUILD_DIR/usr/share/hush
mkdir -p $BUILD_DIR/DEBIAN $DEB_CMP $DEB_BIN $DEB_DOC $DEB_MAN $DEB_SHR
chmod 0755 -R $BUILD_DIR/*

# Package maintainer scripts (currently empty)
#cp $SRC_DEB/postinst $BUILD_DIR/DEBIAN
#cp $SRC_DEB/postrm $BUILD_DIR/DEBIAN
#cp $SRC_DEB/preinst $BUILD_DIR/DEBIAN
#cp $SRC_DEB/prerm $BUILD_DIR/DEBIAN
# Copy binaries. We prefix our komodod binaries with hush- to prevent conflicting with
# a stock komodod or other flavors of KMD
cp $SRC_PATH/sapling-spend.params $DEB_SHR
cp $SRC_PATH/sapling-output.params $DEB_SHR
cp $SRC_PATH/src/komodod $DEB_BIN/hush-komodod
strip $DEB_BIN/hush-komodod
cp $SRC_PATH/src/komodo-cli $DEB_BIN/hush-komodo-cli
strip $DEB_BIN/hush-komodo-cli
cp $SRC_PATH/src/komodo-tx $DEB_BIN/hush-komodo-tx
strip $DEB_BIN/hush-komodo-tx
cp $SRC_PATH/src/hushd $DEB_BIN
cp $SRC_PATH/src/hush-cli $DEB_BIN
cp $SRC_PATH/src/hush-tx $DEB_BIN
#cp $SRC_PATH/zcutil/fetch-params.sh $DEB_BIN/zcash-fetch-params
#cp $SRC_DEB/changelog $DEB_DOC/changelog.Debian
cp $SRC_DEB/copyright $DEB_DOC
cp -r $SRC_DEB/examples $DEB_DOC
# Copy manpages
cp $SRC_DOC/man/komodod.1 $DEB_MAN/hush-komodod.1
cp $SRC_DOC/man/komodo-cli.1 $DEB_MAN/hush-komodo-cli.1
cp $SRC_DOC/man/komodo-tx.1 $DEB_MAN/hush-komodo-tx.1

cp $SRC_DOC/man/komodod.1 $DEB_MAN/hushd.1
cp $SRC_DOC/man/komodo-cli.1 $DEB_MAN/hush-cli.1
cp $SRC_DOC/man/komodo-tx.1 $DEB_MAN/hush-tx.1
#TODO: process these copies and update names/binaries/etc

#cp $SRC_DOC/man/zcash-fetch-params.1 $DEB_MAN
# Copy bash completion files
cp $SRC_PATH/contrib/hushd.bash-completion $DEB_CMP/hushd
cp $SRC_PATH/contrib/hush-cli.bash-completion $DEB_CMP/hush-cli
cp $SRC_PATH/contrib/hush-tx.bash-completion $DEB_CMP/hush-tx
# Gzip files
#gzip --best -n $DEB_DOC/changelog
#gzip --best -n $DEB_DOC/changelog.Debian
gzip --best -n $DEB_MAN/hush-komodod.1
gzip --best -n $DEB_MAN/hush-komodo-cli.1
gzip --best -n $DEB_MAN/hush-komodo-tx.1
gzip --best -n $DEB_MAN/hushd.1
gzip --best -n $DEB_MAN/hush-cli.1
gzip --best -n $DEB_MAN/hush-tx.1
#gzip --best -n $DEB_MAN/zcash-fetch-params.1

cd $SRC_PATH/contrib

# Create the control file
dpkg-shlibdeps $DEB_BIN/hush-komodod $DEB_BIN/hush-komodo-cli $DEB_BIN/hush-komodo-tx
dpkg-gencontrol -P$BUILD_DIR -v$DEBVERSION
#dpkg-gencontrol -P$BUILD_DIR

# Create the Debian package
fakeroot dpkg-deb --build $BUILD_DIR
cp $BUILD_PATH/$PACKAGE_NAME-$PACKAGE_VERSION-amd64.deb $SRC_PATH
shasum -a 256 $SRC_PATH/$PACKAGE_NAME-$PACKAGE_VERSION-amd64.deb
# Analyze with Lintian, reporting bugs and policy violations
lintian -i $SRC_PATH/$PACKAGE_NAME-$PACKAGE_VERSION-amd64.deb
exit 0
