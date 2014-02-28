#! /usr/bin/env zsh

BR=\
"Everything in this directory (bucket/)\n"\
"is hereby officially declared nonexistent.\n"\
"\n"\
" ... with the exception of this file  ;-)\n"\
""

DD=$(find . -name bucket -a -type d)
for d in ${=DD}; do
    echo -e ${BR} > $d/00README.txt
done


exit 0;
##############################

