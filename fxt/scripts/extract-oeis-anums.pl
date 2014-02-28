#! /usr/bin/perl -w

## scripts/extract-oeis-anums.pl $DD $FH | sort -u | less

## called by target 'oeis'
########## extract OEIS sequence numbers (A-numbers) from files:

while ( <> )
{
    chomp;
    $line = $_;

    while ( $line =~ /(.*?)(A[0-9]{6})(.*)$/ )
    {
        $pref = $1;
        $anum = $2;
        $line = $3;

#        $anum =~ s/000000/999999/;  ## put non-OEIS nums at end
        print "$anum:  $ARGV\n"
            unless ( "$pref" =~ m@1demo.*$@ );

    }
}

exit 0;
#####################################
