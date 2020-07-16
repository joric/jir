# This is for Roomba 620 with default settings
# 
# wiring (mini-din):
# 
#   + +
#  i   o
#  g g g
#
# 128 - init sequence
# 131 - safe mode (132 - full mode)
# ---
# 135 - clean
# 134 - spot
# 143 - dock

param=dock

if [ ! -z "$1" ]; then
    param=$1
fi

case $param in
  clean)
    raw=128,131,135
    ;;
  spot)
    raw=128,131,134
    ;;
  dock)
    raw=128,131,143
    ;;
  sleep)
    raw=128,131,133
    ;;
esac

echo $raw
curl -G http://192.168.1.6 --data-urlencode "raw=$raw"
