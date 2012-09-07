 #!/bin/bash
cd AF903x_SRC
echo "1. Install ITEtech AF9035 Driver"
echo "2. Remove  ITEtech AF9035 Driver"
echo "Please Input Your Choise:"
read choice
case "$choice" in
1)
    echo "Building"
    sleep 1
    make 
    if [ -f dvb-usb-af903x.o ]
    then
	echo "make ok"
    echo "Installing"
	sudo make install
	make clean
    else
	echo "make error"
	make clean
	exit
    fi
    ;;
2)
    echo "Uninstalling"
    sudo make remove
    ;;
esac
echo "Installer finished"
