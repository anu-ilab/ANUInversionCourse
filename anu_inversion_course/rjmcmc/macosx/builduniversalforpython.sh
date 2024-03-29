#!/bin/bash

mkdir -p build
mkdir -p install

build_platform ()
{
    arch=$1
    target=$2

    rm -rf $arch
    mkdir -p $arch
    pushd $arch

    # Latest version of xcode
    syslib_10_7_4=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk

    # MacOSX 10.6.8 version
    syslib_10_6_8=/Developer/SDKs/MacOSX10.6.sdk
    
    # MaxOSX generic version

    if [ -d $syslib_10_7_4 ]; then
      echo "Detected MacOSX 10.7.4"
      syslib=$syslib_10_7_4
    else
      if [ -d $syslib_10_6_8 ]; then
        echo "Detected MacOSX 10.6.8"
        syslib=$syslib_10_6_8
      else
        echo "Warning: Using generic syslib"
        syslib=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
      fi
    fi

    export CFLAGS="-isysroot $syslib -arch $arch -I../../../../include" 
    export LDFLAGS="-Wl,-syslibroot $syslib -arch $arch"

    ../../../configure --target=$target --prefix=`pwd`/../../pythoninstall --exec-prefix=`pwd`/../../pythoninstall/$arch --host i386 --without-mpi --disable-shared

    make 
    make install

    popd
}

pushd build

build_platform i386 i386-apple-darwin8
build_platform x86_64 x86_64-apple-darwin8

popd

#
# Now install will have include and a separate directory for each
# architecture lib, we need to merge these into a single universal
# library.
#

pushd pythoninstall
rm -rf lib
mkdir lib

lipo -create -output lib/librjmcmc.a i386/lib/librjmcmc.a x86_64/lib/librjmcmc.a

rm -rf i386 x86_64

popd


