VERSION=2.0.0

SKIP_TESTS=TRUE


# Android
# -------
OS=android

ARCHITECTURE=arm64-v8a
echo "Platform $OS-$ARCHITECTURE"
echo --------------------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo

ARCHITECTURE=armeabi-v7a
echo "Platform $OS-$ARCHITECTURE"
echo ----------------------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo

ARCHITECTURE=x86
echo "Platform $OS-$ARCHITECTURE"
echo --------------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo


# Linux
# -----
OS=linux

ARCHITECTURE=x86_64
echo "Platform $OS-$ARCHITECTURE"
echo ---------------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo

ARCHITECTURE=x86
echo "Platform $OS-$ARCHITECTURE"
echo ---------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo

ARCHITECTURE=arm
echo "Platform $OS-$ARCHITECTURE"
echo ------------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo

ARCHITECTURE=arm64
echo "Platform $OS-$ARCHITECTURE"
echo -----------------
./build-platform-on-linux.sh $OS $ARCHITECTURE $VERSION
echo
