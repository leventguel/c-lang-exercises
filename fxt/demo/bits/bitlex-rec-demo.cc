
// demo-is-self-contained

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Recursive algorithm for the binary words in lexicographic order.

ulong ldn;


void bitlex_f(ulong f, ulong n)  // forward
{
//    if ( n<1 )  return;
    print_bin("  ", f, ldn);
    cout << endl;
    for (ulong m=n>>1; m>0; m>>=1)  bitlex_f(f+m, m);
}
// -------------------------


void bitlex_b(ulong f, ulong n)  // backward
{
//    if ( n<1 )  return;
    for (ulong m=1; m<n; m<<=1)  bitlex_b(f+m, m);
    print_bin("  ", f, ldn);
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ldn = 5;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    ulong fq = 0;
    NXARG(fq, "Forward (1) or backward (0) order.");

    if ( fq )  bitlex_f(0, n);  // forward
    else       bitlex_b(0, n);  // backward

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitlex-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitlex-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

