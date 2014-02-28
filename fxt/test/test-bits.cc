
#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"
#include "bits-all.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"

#include <cstdlib> // rand()



static inline void lin2hilbert_2(ulong t, ulong &x, ulong &y)
// Based on code by Juha Jaervi
{
    const ulong M5 = ~0UL/0x3;  // == 0x55555555...

//    // De-interleave t.
//    y = t & M5;
//    y = (y|(y>>1)) & ~0UL/0xf*0x3;
//    y = (y|(y>>2)) & ~0UL/0xff*0xf;
//    y = (y|(y>>4)) & ~0UL/0xffff*0xff;
//    y = (y|(y>>8)) & 0xffff;
    y = bit_unzip0( t & M5 );

    // Count total number of 00 crumbs (bit pairs) mod 2 times 2 and
    // number of 11 crumbs mod 2 on the left side of each crumb.
    const ulong t1 = (t|(t>>1)) & M5;  // at least one bit set
    const ulong t2 = (t&(t>>1)) & M5;  // exactly two bits set
    ulong ct = (t1>>1) | (t2>>2);

    ct ^= ct>>2;
    ct ^= ct>>4;
    ct ^= ct>>8;
    ct ^= ct>>16;
#if  BITS_PER_LONG >= 64
    ct ^= ct>>32;
#endif

    // Bit-twiddling magic to get hilbert curve x at t interleaved with 0.
    // ^-(order&1) rotates entire curve for every second order...
//    const ulong order = 0;  // ???
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ -(~order&1) ^ ~0UL/15*4 ) & t ) ) & M5;
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ -1UL ^ ~0UL/15UL*4 ) & t ) ) & M5;
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ 0xbbbbbbbbbbbbbbbbUL ) & t ) ) & M5;
    const ulong Mb =  -1UL ^ ~0UL/15UL*4;  // == 0xbbbbbbb...
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ Mb ) & t ) ) & M5;
    x = ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ Mb ) & t );

    // De-interleave x.
//    x=(x|(x>>1)) & ~0UL/0xf*0x3;
//    x=(x|(x>>2)) & ~0UL/0xff*0xf;
//    x=(x|(x>>4)) & ~0UL/0xffff*0xff;
//    x=(x|(x>>8)) & 0xffff;

    x = bit_unzip0( x & M5 );

//    y = x ^ y;
    y ^= x;
}
// -------------------------



static inline ulong lowest_block_2(ulong x)
// Isolate lowest block of ones.
{
    ulong l = x & -x;  // lowest bit
    ulong y = x + l;
#if 0  // jj's version (incorrect for words 1+0*)
    x ^= y;
    return  x & (x>>1);
#else  // Mike Engber's (correct) version
    y ^= x;
    return  y & x;
#endif
}
// -------------------------

static inline ulong lowest_block_3(ulong x)
// Isolate lowest block of ones.
{
    ulong l = x & -x;  // lowBitMask
    ulong c = (l + x) & x;  // lowBitRunCleared
    return c ^ x;  // lowBitRunMask
}
// -------------------------


static inline ulong highest_one_idx_2(ulong x)
// Return index of highest bit set.
// Return 0 if no bit is set.
{
    if ( 0==x )  return  0;
    ulong r = 0;
#if  BITS_PER_LONG >= 64
//    if ( x & (~0UL<<32) )  { x >>= 32;  r += 32; }
    if ( x & 0xffffffff00000000UL )  { x >>= 32;  r += 32; }
#endif
    if ( x & 0xffff0000UL )  { x >>= 16;  r += 16; }
    if ( x & 0x0000ff00UL )  { x >>=  8;  r +=  8; }
    if ( x & 0x000000f0UL )  { x >>=  4;  r +=  4; }
    if ( x & 0x0000000cUL )  { x >>=  2;  r +=  2; }
    if ( x & 0x00000002UL )  {            r +=  1; }
    return r;
}
// -------------------------

#if BITS_PER_LONG == 64

#define ONES_STEP_4    0x1111111111111111UL
#define AAHS_STEP_4    0xaaaaaaaaaaaaaaaaUL
#define THRS_STEP_4    0x3333333333333333UL
#define ONES_STEP_8    0x0101010101010101UL
#define EFFS_STEP_8    0x0f0f0f0f0f0f0f0fUL
//#define MSBS_STEP_8 ( 0x80UL * ONES_STEP_8 )
#define MSBS_STEP_8    0x8080808080808080UL
//#define INCR_STEP_8  ( 0x80UL << 56 | 0x40UL << 48 | 0x20UL << 40 | 0x10UL << 32 | 0x8UL << 24 | 0x4UL << 16 | 0x2UL << 8 | 0x1 )
#define INCR_STEP_8    0x8040201008040201UL

//#define LEQ_FUNC(x,y)  ( ( ( ( ( (y) | MSBS_STEP_8 ) - ( (x) & ~MSBS_STEP_8 ) ) ^ (x) ^ (y) ) & MSBS_STEP_8 ) >> 7 )
static inline ulong leq_func(ulong x, ulong y)
{
    ulong r = ( y | MSBS_STEP_8 ) - ( x & ~MSBS_STEP_8 );
    r ^= (x ^ y);
    r &= MSBS_STEP_8;
    r >>= 7;
    return r;
}
// -------------------------

//#define ZCMP_FUNC(x)  ( ( ( (x) | ( ( (x) | MSBS_STEP_8 ) - ONES_STEP_8 ) ) & MSBS_STEP_8 ) >> 7 )
static inline ulong zcmp_func(ulong x)
{
    ulong r = x | ( ( x | MSBS_STEP_8 ) - ONES_STEP_8 );
    r &= MSBS_STEP_8;
    r >>= 7;
    return r;
}
// -------------------------

static inline ulong ith_one_idx_1(ulong x, ulong i)
// Return index of the i-th set bit of x where 0 <= i < bit_count(x).
// Return 72 if i >= bit_count(x).
// Adaptation from code given by Sebastiano Vigna.
{
    // Phase 1: sums by byte
//    ulong byte_sums = x - ( ( x & 0xa * ONES_STEP_4 ) >> 1 );
    ulong byte_sums = x - ( ( x & AAHS_STEP_4 ) >> 1 );
//    byte_sums = ( byte_sums & 3 * ONES_STEP_4 ) + ( ( byte_sums >> 2 ) & 3 * ONES_STEP_4 );
    byte_sums = ( byte_sums & THRS_STEP_4 ) + ( ( byte_sums >> 2 ) & THRS_STEP_4 );
//    byte_sums = ( byte_sums + ( byte_sums >> 4 ) ) & 0x0F * ONES_STEP_8;
    byte_sums = ( byte_sums + ( byte_sums >> 4 ) ) & EFFS_STEP_8;
    byte_sums *= ONES_STEP_8;

    // Phase 2: compare each byte sum with i
    const ulong i_step_8 = i * ONES_STEP_8;
//    const ulong place = ( ( LEQ_FUNC( byte_sums, i_step_8 ) * ONES_STEP_8 ) >> 53 ) & ~0x7UL;
    const ulong place = ( ( leq_func( byte_sums, i_step_8 ) * ONES_STEP_8 ) >> 53 ) & ~0x7UL;

    // Phase 3: Locate the relevant byte and make 8 copies with incremental masks
    const ulong byte_rank = i - ( ( ( byte_sums << 8 ) >> place ) & 0xFF );

    const ulong spread_bits = ( ( x >> place & 0xFF ) * ONES_STEP_8 ) & INCR_STEP_8;
//    const ulong bit_sums = ZCMP_FUNC( spread_bits ) * ONES_STEP_8;
    const ulong bit_sums = zcmp_func( spread_bits ) * ONES_STEP_8;

    // Compute the inside-byte location and return the sum
    const ulong byte_rank_step_8 = byte_rank * ONES_STEP_8;

//    return  place + ( ( LEQ_FUNC( bit_sums, byte_rank_step_8 ) * ONES_STEP_8 ) >> 56 );
    return  place + ( ( leq_func( bit_sums, byte_rank_step_8 ) * ONES_STEP_8 ) >> 56 );
}
// -------------------------


static inline ulong highest_one_idx_1(ulong x)
// == highest_one_idx() implementation
{
    if ( x == 0 )  return 0;
    ulong r = 0;
    if ( x & 0xffffffff00000000UL )  { x >>= 32;  r += 32; }
    if ( x & 0xffff0000UL )          { x >>= 16;  r += 16; }
    x |= (x << 16);
    x |= (x << 32);
    const ulong y = x & 0xff00f0f0ccccaaaaUL;
    const ulong z = 0x8000800080008000UL;
    ulong t = z & ( y | (( y | z ) - ( x ^ y )));
    t |= (t << 15);
    t |= (t << 30);
    t |= (t << 60);
    return  r + ( t >> 60 );
}
// -------------------------

#endif // BITS_PER_LONG == 64


//static inline ulong hbi(ulong x)
//// this is a _NON_WORKING_ highest_one_idx() implementation
//{
//    ulong r = 0;
//#if  BITS_PER_LONG >= 64
//    if ( x & (~0UL<<32) )  r += 32;
//#endif
//    if ( x & 0xffff0000UL )  r += 16;
//    if ( x & 0xff00ff00UL )  r +=  8;
//    if ( x & 0xf0f0f0f0UL )  r +=  4;
//    if ( x & 0xccccccccUL )  r +=  2;
//    if ( x & 0xaaaaaaaaUL )  r +=  1;
//    return r;
//}
//// -------------------------
//
//static inline ulong bc15(uint x)
//// Return number of set bits, must have at most 15 set bits,
//{
//    x -=  (x>>1) & 0x55555555UL;
//    x  = ((x>>2) & 0x33333333UL) + (x & 0x33333333UL);
//    x *= 0x11111111UL;
//    return  x>>28;
//}
//// -------------------------


#if BITS_PER_LONG == 64
//static inline ulong par(ulong x)
//{
//    x *= 0xffffffffffffffffUL;
//    return x >> 63;
//}
//// -------------------------

static inline ulong bs1(ulong x)
{
#if 0
    ulong m = 0xaaaaaaaaaaaaaaaaUL;
    ulong t = x & m;
    x ^= t;
    t >>= 1;
    x += x;
    x |= t;
    return x;
#else
    ulong m = 0x5555555555555555UL;
//    ulong t = x & m;
//    x = ( (x>>1) & m );
    return  ( (x>>1) & m ) | ( (x & m) << 1 );
#endif
}
// -------------------------
#endif


ulong low1(ulong x)
{
    if ( ~0UL==x )  return ~0UL;
    x = (x ^ (x+1)) >> 1;
    return x;
}
// -------------------------


#define BH (BITS_PER_LONG/2)
#define CLH(v) ((v<<BH)>>BH)  // clear left half

void
do_some_tests(ulong v)
{
    ulong t;

#if BITS_PER_LONG == 64
    { const ulong c = bit_count(v);
//        print_bin("v=",v);  cout << endl;
//        cout << "bit_count=" << c << endl;
        for (ulong i=0; i<c; ++i)
        {
//            cout << "i=" << i << endl;
            ulong i0 = ith_one_idx(v, i);
            ulong i1 = ith_one_idx_1(v, i);
            jjassert( i0 == i1 );
        }
    }
#endif

#if 1
    {
        ulong x1, y1;
        ulong x2, y2;
        lin2hilbert(v, x1, y1);
        lin2hilbert_2(v, x2, y2);
        if ( 0 )
        {
            print_bin(" v=",v);  cout << endl;
            print_bin("x1=",x1);  cout << endl;
            print_bin("x2=",x2);  cout << endl;
            if ( x1!=x2 )  cout << "  *** DX ***" << endl;
            print_bin("y1=",y1);  cout << endl;
            print_bin("y2=",y2);  cout << endl;
            if ( y1!=y2 )  cout << "  *** DY ***" << endl;
            cout << endl;
        }
        jjassert( x1==x2 );
        jjassert( y1==y2 );
    }
#endif

    {
        ulong t1 = lowest_block(v);
        ulong t2 = lowest_block_2(v);
        ulong t3 = lowest_block_3(v);
//        if ( t1!=t2 )
//        {
//            print_bin(" v=",v);  cout << endl;
//            print_bin("t1=",t1);  cout << endl;
//            print_bin("t2=",t2);  cout << endl;
//            cout << endl;
//        }
        jjassert( t1==t2 );
        jjassert( t1==t3 );
    }

#if BITS_PER_LONG == 64
//    jjassert( bit_swap_1(v) == bs1(v) );

    jjassert( v == butterfly_16(butterfly_16(v)) );
#endif
    jjassert( v == butterfly_8(butterfly_8(v)) );
    jjassert( v == butterfly_4(butterfly_4(v)) );
    jjassert( v == butterfly_2(butterfly_2(v)) );
    jjassert( v == butterfly_1(butterfly_1(v)) );
    jjassert( v == bit_unzip(bit_zip(v)) );

    jjassert( v == bit_inverse_gray_permute(bit_gray_permute(v)) );

    t = CLH(v);  jjassert( bit_zip(t)==bit_zip0(t) );
    t = CLH(v);  jjassert( t==bit_unzip0(bit_zip0(t)) );

    { ulong lo, hi;
        bit_zip2(v, lo, hi); t=bit_unzip2(lo, hi); jjassert( v==t );

        t = CLH(v);  t=bit_zip0(t);
        bit_zip2(v, lo, hi);
        jjassert( t==lo );
    }

    { ulong x = v,  y=v>>1;
//        cout << " x=" << x << endl;
//        cout << " y=" << y << endl;
        jjassert( (x+y) == (((x&y)<<1) + (x^y)) );
        jjassert( (x+y) == (((x|y)<<1) - (x^y)) );
        ulong af = average(x,y);
        ulong ac = ceil_average(x,y);
//        print_bin(" x=",x,0);  cout << endl;
//        print_bin(" y=",y,0);  cout << endl;
//        print_bin("af=",af,0);  cout << endl;
//        print_bin("ac=",ac,0);  cout << endl;
        jjassert( ac == (af + ((x^y)&1)) );
    }

//    print_bin("  l1a=",low_ones(v),0);
//    print_bin("  l1b=",low1(v),0);
//    cout << endl;
    jjassert( low_ones(v) == low1(v) );

    jjassert( (low_ones(v) & low_zeros(v)) == 0 );
    jjassert( (low_ones(v) | low_zeros(v)) != 0 );

    jjassert( high_ones(v) == high_zeros(~v) );
    jjassert( (high_ones(v) & high_zeros(v)) == 0 );
    jjassert( (high_ones(v) | high_zeros(v)) != 0 );

    jjassert( (highest_one_01edge(v) & highest_one_10edge(v)) == highest_one(v) );

    t = highest_one_01edge(v);  jjassert( bit_count(t) == bit_count_01(t) );

    jjassert( (lowest_one_01edge(v) & lowest_one_10edge(v)) == lowest_one(v) );

    jjassert( (v==0) || (lowest_one_idx(v) == (BITS_PER_LONG-1 - highest_one_idx(revbin(v)))) );

    jjassert( (v!=0) || (lowest_one_idx(v) == highest_one_idx(revbin(v))) );

    jjassert( lowest_one(v) == lowest_zero(~v) );
    jjassert( highest_one(v) == highest_zero(~v) );
    jjassert( revbin( highest_one(v) ) == lowest_one( revbin(v) ) );
    jjassert( revbin(v) == revbin(v, BITS_PER_LONG) );


#define COND  ! ( ((v==0) && (r==1)) || ((v==1) && (r==0)) )
//#define COND  true  // test
#if 1 // silent:
#define X(r,v)
#else // verbose:
#define X(r,v) \
    cout << endl; \
    print_bin(" v = " , v);  cout << endl; \
    print_bin(" r = " , r);  cout << endl; \
    print_bin(" COND = " , COND, 3);  cout << endl;           \
    print_bin(" ld(r) = " , ld(r), 8);  cout << endl;       \
    print_bin(" ld(v) = " , ld(v), 8);  cout << endl;              \
    print_bin(" ld_eq  v r = " , ld_eq(v,r), 3);  cout << endl; \
    print_bin(" ld_neq v r = " , ld_neq(v,r), 3);  cout << endl; \
    print_bin(" ld(v)==ld(r) = " , ld(v)==ld(r), 3);  cout << endl; \
    print_bin(" ld(v)!=ld(r) = " , ld(v)!=ld(r), 3);  cout << endl;
#endif

    { ulong r;
        r = revbin(v);
        if ( COND )
        {
            X(r,v);
            jjassert( (ld(v)==ld(r)) == ( ld_eq(v,r) ) );
            jjassert( (ld(v)!=ld(r)) == ( ld_neq(v,r) ) );
        }

        r = v-1;
        if ( COND )
        {
            X(r,v);
            jjassert( (ld(v)==ld(r)) == ( ld_eq(v,r) ) );
            jjassert( (ld(v)!=ld(r)) == ( ld_neq(v,r) ) );
        }

        r = v+1;
        if ( COND )
        {
            X(r,v);
            jjassert( (ld(v)==ld(r)) == ( ld_eq(v,r) ) );
            jjassert( (ld(v)!=ld(r)) == ( ld_neq(v,r) ) );
        }
    }
//    cout << endl;
//    print_bin(" v=" , v);  cout << endl;
//    cout << "  a=" << highest_one_idx(v);
//    cout << "  b=" << highest_one_idx__(v);
//    cout << endl;
//    jjassert( highest_one_idx(v) == (63-highest_one_idx__(v)) );
#if BITS_PER_LONG == 64
    jjassert( highest_one_idx(v) == highest_one_idx_1(v) );
#endif
    jjassert( highest_one_idx(v) == highest_one_idx_2(v) );

    {
        ulong s0 = single_zeros(v);
        ulong s1 = single_ones(v);
//        ulong c0 = single_zeros(~v);
//        ulong c1 = single_ones(~v);
        ulong s01 = s0 | s1;
        ulong sv = single_values(v);
//        print_bin("  v=", v);  cout << endl;
//        print_bin(" s0=", s0);  cout << endl;
//        print_bin(" s1=", s1);  cout << endl;
//        print_bin(" ~v=", ~v);  cout << endl;
//        print_bin(" c0=", c0);  cout << endl;
//        print_bin(" c1=", c1);  cout << endl;
//        print_bin("s01=", s01);  cout << endl;
//        print_bin(" sv=", sv);  cout << endl;
//        cout << endl;

        jjassert( sv == s01 );

//        jjassert( s1 == c0 );  // not true
//        jjassert( c1 == s0 );  // not true

        jjassert( single_ones_xi(v) == single_ones(v) );
        jjassert( single_zeros_xi(v) == single_ones(~v) );

        jjassert( (single_ones_xi(v) | single_zeros_xi(v)) == single_values_xi(v) );
    }

    jjassert( border_ones(v) == (high_border_ones(v) | low_border_ones(v)) );
//    jjassert( border_ones(v) == border_ones(~v) );  // not true

    jjassert( block_border_ones(v) == (low_block_border_ones(v) ^ high_block_border_ones(v)) );
    jjassert( block_ones(v) == (block_border_ones(v) | interior_ones(v)) );

    jjassert( v == (block_ones(v) | single_ones(v)) );

    t = bit_count(v);
    jjassert( t == bit_count_sparse(v) );
    if ( t<16 )  jjassert( t == bit_count_15(v) );
    if ( t<4 )  jjassert( t == bit_count_3(v) );

//    t = CLH(v);  t = bit_count(t);
//    if ( t<16 )  jjassert( t == bc15(v) );

    jjassert( interior_ones(v) == (interior_ones(v) & interior_values(v)) );

//    jjassert( (interior_ones(v) | interior_ones(~v)) == interior_values(v) ); //  not true

    jjassert( parity(v) == (inverse_gray_code(v) & 1) );

    const ulong irg = inverse_rev_gray_code(v);
    const ulong ig = inverse_gray_code(v);
    const ulong igs = inverse_gray_code(v) >> 1;
    jjassert( inverse_gray_code( (v)>>1 ) == inverse_gray_code(v) >> 1 );
    if ( parity(v) )
    {
        jjassert( ~v == (irg ^ ig) );
        jjassert( ~irg == igs );
    }
    else
    {
        jjassert( v == (irg ^ ig) );
        jjassert( irg == igs );
    }

//    jjassert( yellow_code(v) == revbin( blue_code( revbin( v ) ) ) );
//    jjassert( red_code(v) == revbin( blue_code( v ) ) );
//    jjassert( green_code(v) == blue_code( revbin( v ) ) );

//    jjassert( (~inverse_rev_gray_code(v)) == (inverse_gray_code(v)>>1) ); // not true

    if ( v ) { jjassert( (1UL<<ld(v)) <= v ); }  else { jjassert( ld(v) == 0 ); }

    for (ulong r=0; r<(BITS_PER_LONG); ++r)
    {
        jjassert( v==bit_rotate_right(bit_rotate_left(v,r), r) );
        jjassert( v==bit_rotate_right(bit_rotate_right(v,r), BITS_PER_LONG-r) );
        jjassert( v==bit_rotate_left(bit_rotate_left(v,r), BITS_PER_LONG-r) );
    }

    if ( contains_zero_byte(v) )
    {
        char str[BYTES_PER_LONG];
        ulong x = v;
        for (ulong k=0; k<BYTES_PER_LONG; ++k)
        {
            str[k] = (char)(x & 0xff);
            x >>= 8;
        }
        ulong k;
        for (k=0; k<BYTES_PER_LONG; ++k)  if ( 0==str[k] )  break;
        if ( k==BYTES_PER_LONG )
        {
            cout << hex << " contains_zero_byte( 0x" << v << " )";
            cout        << "   gave  0x" << contains_zero_byte(v) << endl;
            jjassert(0); //  contains_zero_byte() failed
        }
    }
}
// -------------------------


int
main()
{
    cout << "Running tests for low level (bit-) functions "
#ifdef  NO_ONES_USE_ASM
        "WITHOUT asm-functions"
#else
        "with ASM-versions"
#endif
         "..." << endl;
//    cout << "RAND_MAX=" << (RAND_MAX) << endl;

    // some special values we'd like to test:

    for (ulong x=0; x<100; x++)  do_some_tests( x );

    for (ulong x=1; x; x<<=1)
    {
        do_some_tests( x );    // one bit
        do_some_tests( x-1 );  // low burst
        do_some_tests( ~(x-1) );  // high burst
    }

    do_some_tests( 0 );
    do_some_tests( ~0UL );

    ulong x = 1UL<<(BITS_PER_LONG-1);  // highest bit set
    do_some_tests( x );
    do_some_tests( x + 1 );
    do_some_tests( x - 1 );


    ulong n = 300*1000;  // this many tests with random values
    for (ulong i=0; i<n; ++i)
    {
        ulong v = (ulong)rand();
        v ^= ((ulong)rand())<<(BH); // also want high bit !=0

        do_some_tests(v);
        if ( 0==(i%1024) )  { cout << "."; cout.flush(); }
    }

    cout << "\nOK passed " << n << " tests." << endl;

    return 0;
}
// -------------------------
