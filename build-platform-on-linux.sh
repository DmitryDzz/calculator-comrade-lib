OS=$1
ARCHITECTURE=$2
VERSION=$3

PLATFORM=$OS-$ARCHITECTURE
BUILD_DIR=cmake-build-$PLATFORM
rm -r -f $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../toolchain-$PLATFORM.cmake ..
make

OUTPUT_DIR=../output
mkdir -p $OUTPUT_DIR
mkdir -p $OUTPUT_DIR/$OS
mkdir -p $OUTPUT_DIR/$OS/$ARCHITECTURE
rm -f $OUTPUT_DIR/$OS/$ARCHITECTURE/*.*
SRC_DIR=lib
[[ -d bin/ ]] || SRC_DIR=bin
FILENAME=libcalculator_v$VERSION
cp $SRC_DIR/*.dll $OUTPUT_DIR/$OS/$ARCHITECTURE/$FILENAME.dll > null 2> null
cp $SRC_DIR/*.so $OUTPUT_DIR/$OS/$ARCHITECTURE/$FILENAME.so > null 2> null
echo
echo "$FILENAME" library is copied to output/$OS/$ARCHITECTURE/

cd ..
