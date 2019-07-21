#!/bin/bash

# Makefileのあるディレクトリを検索
srcdir=`find ./ -name "Makefile" -exec dirname {} \;`

for path in ${srcdir}
do
	if [ `echo ${path} | grep 'failtureproject'` ] ; then
		continue
	fi

	echo "start"${path}
	pushd ${path}
	pwd
	sed -i s@rpi_lib/serial/serial.o@"../../cmnTs/serialMini/serial.o ../../cmnTs/serialMini/mini_serial00.o"@ Makefile

	popd
	echo "end"
	echo "-------------------------------------------"
	echo ""
done
