
echo "\n-----Start 21_* Build test1 ---"
pwd
echo "\n-----Start Pi1 Compile--"
 for dir2 in $(ls)

 do
  if [ -d $dir2 ] ; then
      if [ $(echo $dir2 | grep -e "build21") ] ; then    
  if cd $dir2
  then
   pwd
   make  clean
   make  2>&1 | tee make21.log
   echo "...\n"
	ls 21_*.srec
   cp 21_*.srec  ../
   cd .. 
  else 
   ecno "cd error $dir2"
  fi
  fi
 fi

 done
  echo "\n-----End 21_* Pi1 Build--"

pwd

