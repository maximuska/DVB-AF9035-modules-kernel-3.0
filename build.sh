#!/bin/bash

# To install packages required to build the drivers for kernel 3.0.0 do:
# sudo apt-get install build-essential linux-headers-3.0.0-13-generic linux-source-3.0.0
# cd /usr/src && sudo tar jxvf /usr/src/linux-source-3.0.0.tar.bz2; cd -

set -x

SRC=/usr/src/linux-source-3.0.0

cd AF903x_SRC &&
test -d $SRC/drivers/media/dvb &&
ln -sf $SRC/drivers/media/dvb/frontends/*.h . &&
ln -sf $SRC/drivers/media/dvb/dvb-core/*.h . &&
ln -sf $SRC/drivers/media/dvb/dvb-usb/*.h . &&
cd .. &&
echo 1 | ./installer.sh &&
echo Done &&
exit 0

echo Something wrong has happened, examine the log, fix the problem and retry
