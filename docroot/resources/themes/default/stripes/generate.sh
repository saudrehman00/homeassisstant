#!/bin/sh
#
# This script uses imagemagick to generate the stripe-XXpx.gif's.
#

for i in `seq 10 40`; do
  convert -size 30x$[2*$i] xc:white \
          -fill '#e8fffc' -draw "rectangle 0,$i 30,$[2*$i]" \
  stripe-${i}px.gif
done
