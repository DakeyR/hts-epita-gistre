#!/bin/bash

ret=0
./simple-readelf /usr/bin/ls | python -m json.tool
if [ $? -ne 0 ];then
  echo "/usr/bin/ls FAILED";
  ret=$((ret + 1))
fi;
