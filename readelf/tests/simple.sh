#!/bin/bash

ret=0
./simple-readelf tests/example | python -m json.tool
if [ $? -ne 0 ];then
  echo "tests/example FAILED";
  ret=$((ret + 1))
fi;
./simple-readelf tests/example | python -m json.tool
if [ $? -ne 0 ];then
  echo "tests/printf-test FAILED";
  ret=$((ret + 1))
fi;
