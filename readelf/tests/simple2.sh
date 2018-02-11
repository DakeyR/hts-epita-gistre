ret=0;
./simple-readelf tests/printf-test | python -m json.tool
if [ $? -ne 0 ];then
  echo "tests/printf-test FAILED";
  ret=$((ret + 1))
fi;
