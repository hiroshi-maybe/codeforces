#!/bin/zsh
sudo ln -s ${TCHOME}/include/bits /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/

# Run `clang -x c -v -E /dev/null` to double check the header search path of clang
