#!/bin/bash

if [ "$1" = "" ]; then
  echo "Problem name is empty"
  exit 1
fi

probname=$1

sdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
pdir=$PWD

temppath="${sdir}/template-solver.cpp"

pfilepath="${pdir}/${probname}.cpp"
ifilepath="${pdir}/${probname}.in"
ofilepath="${pdir}/${probname}.out"

`cp -n ${temppath} ${pfilepath}`
touch "${ifilepath}"
touch "${ofilepath}"

sed -i '' -e "s/{\$__PROB__}/${probname}/g" ${pfilepath}
command="g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG ${probname}.cpp && ./a.out"
echo $command

open "${pfilepath}"
open "${ifilepath}"
open "${ofilepath}"
