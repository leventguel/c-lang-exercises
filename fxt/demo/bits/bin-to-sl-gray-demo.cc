
#include "bits/bin-to-sl-gray.h"

#include "bits/print-bin.h"

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"

//% Converting binary numbers to corresponding words in SL-Gray order.


int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "Number of bits");
    const ulong n = 1UL << ldn;

    ulong xo = bin_to_sl_gray(n-1, ldn);
    for (ulong k=0; k<n; ++k)
    {
        ulong x = bin_to_sl_gray(k, ldn);
        cout << setw(4) << k << ":";
        print_bin("    ", x, ldn);

        ulong d = x ^ xo;
        print_bin("    ", d, ldn);  // delta sequence
        xo = x;

        cout << endl;

        jjassert( d == (d & -d) );   // exactly one bit changed
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bin-to-sl-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bin-to-sl-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
