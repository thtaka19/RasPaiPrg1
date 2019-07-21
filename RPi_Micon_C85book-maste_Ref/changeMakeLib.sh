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
	sed -i s@arm-unknown-eabi-@/usr/bin/arm-none-eabi-@ Makefile
	sed -i s@/home/jitomesky/cross/rpi/arm-unknown-eabi/lib/gcc/arm-unknown-eabi/4.8.1/@/usr/lib/gcc/arm-none-eabi/4.9.3/@ Makefile
	sed -i s@/home/jitomesky/cross/rpi/arm-unknown-eabi/arm-unknown-eabi/lib@/usr/lib/arm-none-eabi/newlib@ Makefile

	popd
	echo "end"
	echo "-------------------------------------------"
	echo ""
done
