#line 173 "bits.c"
int bitAnd(int x, int y) {
  int z=  ~x | ~y;
  return ~z;
}
#line 183
int tmin(void) {
  int x=  1<<31;
  return x;
}
#line 194
int negate(int x) {
  int z=  ~x + 1;
  return z;
}
#line 205
int allEvenBits(int x) {
  int y=  0x55;int one;int z;
  y = y +( y<<8) +( y<<16) +( y<<24);
  one = y & x;
  z = !(one ^ y);
  return z;
}
#line 219
int bitCount(int x) {
  return 2;
}
#line 230
int logicalShift(int x, int n) {
  int t=  ~n + 1;int f;
  int k=  31 + t;
  int y=  x >> n;
  int z=  1 << k;
  int s=  1;
  s = ~s + 1;
  f = z + s;
  f = f + z;
  y = y & f;
  return y;
}
#line 249
int isNegative(int x) {
  int y=  1 << 31;int z;
  z = y & x;
  return !!z;
}
#line 261
int isGreater(int x, int y) {
 int diff;int lsb=1;int xLsb;int yLsb;int result;
 xLsb =( x >> 31) & lsb;
 yLsb =( y >> 31) & lsb;
 diff =(( y + ~x + 1) >> 31) & lsb;
 result =( !(xLsb ^ yLsb) & diff) |(( xLsb ^ yLsb) &( !(xLsb) | yLsb));

  return result;
}
#line 278
int isPower2(int x) {
  int numberMinusOne;int msbBit=1<< 31;
  numberMinusOne = x + ~1 + 1;
  return (!(x & numberMinusOne) & !!(msbBit ^ x) & !!(x ^ 0));
}
#line 292
int fitsBits(int x, int n) {
    int allZeros=  0;int allOnes=~0;int z;
    z = x >>( n + ~1 + 1);
    return !!(!(z ^ allZeros) | !( z ^ allOnes));
}
#line 304
int conditional(int x, int y, int z) {
  int k=  !!x;
  int a=  ~k + 1;
  return ( a & y)  |(  ~a & z);
  return 2;
}
#line 318
int greatestBitPos(int x) {
  return 2;
}
#line 330
unsigned float_i2f(int x) {
  return 2;
}
#line 344
unsigned float_abs(unsigned uf) {
  return 2;
}
