#!/bin/bash

i=$1
x=$i
while [ $x = $i ]
let "x=x+1"
do
echo $i
brut=`gammu getsms 3 $i | tail -n +9`
echo $brut
xdotool windowfocus VAR_SKYPE_WINDOW_ID # set the id of skype chat window
setxkbmap fr
text=`echo $brut | sed 'y/áàâäçéèêëîïìôöóùúüñÂÀÄÇÉÈÊËÎÏÔÖÙÜÑ/aaaaceeeeiiiooouuunAAACEEEEIIOOUUN/'`
echo $text
null=""
if [ -n "$brut" ]
then
xdotool type "$text"
xdotool key "Return"
let "i=i+1"
sleep 20
fi
done
exit $i