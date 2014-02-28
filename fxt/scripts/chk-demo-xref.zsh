#! /usr/bin/env zsh

echo
for f in $(grep -E '^// Cf. ' demo/*/*.cc | cut -d' ' -f2- | cut -d' ' -f2); do test -f demo/$f || echo $f; done
echo

exit 0;
#########################

ct=0;
#for f in  demo/*/*.cc; do
for f in  demo/comb/cayley-perm-demo.cc; do
#    echo $f;

    ct=$((ct + 1));
    D[$ct]=$f;
    g=$(grep -Z -E '^// Cf. ' $f);
    L[$ct]=$g;
done

z=0
while test $z \!= 1; do
    z=$((z+1));
    echo "$z:";
    echo "$D[$z]";
    echo "$L[$z]";
done
