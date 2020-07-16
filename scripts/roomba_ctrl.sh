# these are iRobot Roomba codes
#
# 136 Large / Clean
# 132 Spot
# 143 Seek Dock

# The remote control IR stream consist of 8 bits each 4ms in duration. According to the paper,
# each bit is started by a 1ms low period. If the value is 0, the pulse stays low for 2 more ms.
# If the pulse goes high for 2ms if the value is 1. The bit is ended by sending a 1ms high burst.

# Grabbed from a working IR remote with IrScrutinizer
# 
#
#
#

param=dock

if [ ! -z "$1" ]; then
    param=$1
fi

case $param in
  clean)
    raw=3050,981,981,3050,981,3050,981,3050,3050,981,981,3050,981,3050,981,50100
    ;;
  spot)
    raw=3036,981,981,3036,981,3036,981,3036,981,3036,3036,981,981,3036,981,50100
    ;;
  dock)
    raw=2994,1021,1021,2994,1021,2994,1021,2994,2994,1021,2994,1021,2994,1021,2994,50100
    ;;
esac

curl -G http://192.168.1.9 --data-urlencode "raw=$raw"

