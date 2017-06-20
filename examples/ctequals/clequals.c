#include <stdint.h>
#include <stdlib.h>
#include <smack.h>
#include "ct-verif.h"

//Code Balanced: yes
//Current status: fails, most likely because of the loop
int foo(int a, int k) {
  
  public_in(__SMACK_value(a));

  int x;
  if (k) {
    x = 1;
  } else {
    x = 2;
  }
    
  for (int i = 0; i < x; ++i) {
    a += 1;
  }

  if(x == 1) {
    a += 1;
  }

  return a;
}

int foo_0(int a, int k) {
  
  public_in(__SMACK_value(a));

  int x;
  if (k) {
    x = 1;
  } else {
    x = 2;
  }
    
  for (int i = 0; i < x; ++i) {
    a += 1;
  }

  if(x == 1) {
    ++a;
    a += 1;
  }

  return a;
  __SMACK_code("assume {:smack.timingDiff 2} true");
}

int foo0(int a, int k) {
  
  public_in(__SMACK_value(a));
  
  for (int i = 0; i < 1; ++i) {
    a += 1;
  }

  return a;
}

int foo0_1(int a, int k) {
  
  public_in(__SMACK_value(a));

  for (int i = 0; i < 1; ++i) {
    a += 1;
  }

  return a;
}


int foo0_2
(int a, int k) {
  
  public_in(__SMACK_value(a));

  int x = 1;
    
  for (int i = 0; i < x; ++i) {
    a += 1;
  }

  if(x == 1) {
    a += 1;
  }

  return a;
}

int foo0_3
(int a, int k) {
  
  public_in(__SMACK_value(a));

  int x = 1;
    
  for (int i = 0; i < x; ++i) {
    a += 1;
  }

  if(x == 1) {
    a += 1;
  }

  return a;
}


//Code Balanced: yes
//Current status: succeeds
// (from https://github.com/awslabs/s2n/blob/master/tls/s2n_cbc.c#L91 )
int foo1(uint8_t pub, int k, int i) {
  //public_in(__SMACK_value(pub));
  public_in(__SMACK_value(i));

  // From
  uint8_t mask = ~(0xff << ((i >= k) * 8));
  return pub & mask;
}

//Code Balanced: yes
//Current status: Fails because boogieman can't do public in for i8
// (from https://github.com/awslabs/s2n/blob/master/tls/s2n_cbc.c#L91 )
int foo1_1(uint8_t pub, int k, int i) {
  public_in(__SMACK_value(pub));
  public_in(__SMACK_value(i));

  // From https://github.com/awslabs/s2n/blob/master/tls/s2n_cbc.c#L91
  uint8_t mask = ~(0xff << ((i >= k) * 8));
  return pub & mask;
}


//Code Balanced: yes
//Current status: fails, likely because of the loop
//based on https://github.com/awslabs/s2n/blob/master/tls/s2n_cbc.c#L91
//padding_length is private
int foo2(int padding_length, int size, int* data){

  public_in(__SMACK_value(size));
  public_in(__SMACK_value(data));
  int check = 8;//use a constant for now
  
  int cutoff = check - padding_length;
  int mismatches = 0;
  
  for (int i = 0, j = size - 1 - check;
       i < check && j < size; i++, j++) {
    uint8_t mask = ~(0xff << ((i >= cutoff) * 8));
    mismatches |= (data[j] ^ padding_length) & mask;
  }
  
  return mismatches;
}

//Code Balanced: yes  as long as * and + are the same cost
//Current status: succeeds
float foo3(float b, int k)
{
  public_in(__SMACK_value(b));
  float a;
  
  if (k)
    a = b * b;
  else
    a = b + b;

  if (!k)
    a = b + b ;
  else
    a = b * b;

  return a;
}

//Code Balanced: yes  as long as * and + are the same cost
//Current status: succeeds
float foo4(float b, int k)
{
  public_in(__SMACK_value(b));
  float a;
  
  if (k)
    a = b * b;
  else
    a = b + b;

  if (!k)
    a = b * b ;
  else
    a = b + b;

  return a;
}

//Code Balanced: yes  as long as * and + are the same cost
//Current status: succeeds
float foo5(float b, int k)
{
  public_in(__SMACK_value(b));
  float a;
  
  if (k)
    a = b * b;
  else
    a = b;

  if (!k)
    a +=  b + b ;
  else
    a += b;

  return a;
}

//Code Balanced: yes
//Current status: succeeds
float foo5_1(float b, int k)
{
  public_in(__SMACK_value(b));
  float a;
  
  if (k)
    a = b + b;
  else
    a = b;

  if (!k)
    a +=  b + b ;
  else
    a += b;

  return a;
}

//Code Balanced: no - !k leads to two assignments, k leads to two mults
//Current status: detects error
float foo6(float b, int k)
{
  public_in(__SMACK_value(b));
  float a;
  if (k)
    a = b*b;
  else
    a = b;

  if (!k)
    a = b;
  else
    a = b*b;

  return a;
}

//Code Balanced: seemingly yes. But actually, the compiler is too smart for us
//Current status: detects error
float foo6_1(float b, int k)
{
  public_in(__SMACK_value(b));
  float a;
  if (k)
    a = b;
  else
    a = b*b;

  if (!k)
    a = b;
  else
    a = b*b;

  return a;
}

int add_wrapper(int a, int b) {
  return a + b;
}


//Code Balanced: yes
//Current status: fails because of how functions are implemented
int foo7(int a, int k) {
  public_in(__SMACK_value(a));
  return add_wrapper(a,2);
}

//Code Balanced: yes
//Current status: success
int foo8(int a, int k) {
  public_in(__SMACK_value(a));
  int r;
  if (k) {
    r = a + 1;
  } else {
    r = a + 2;
  }
  return r;
}

//Code Balanced: yes
//Current status: fails because of how functions work
int foo9(int a, int k) {
  public_in(__SMACK_value(a));
  int r;
  if (k) {
    r = add_wrapper(a,1);
  } else {
    r = add_wrapper(a,2);
  }
  return r;
}

//Code Balanced: yes
//Current status: fails because of how ghost code works
int foo10(int a, int k) {
  public_in(__SMACK_value(a));
  
  __VERIFIER_assume(k == 7 || k == 8);
  return a;
}

//should fail because *p is private
int foo11(int a, int* p) {
  if(*p) {
    return a;
  } else {
    return a * a;
  }
}

//treat p as an array of size 1,
//__SMACK_value(*p) throws an exception
int foo11_1(int a, int* p) {
  public_in(__SMACK_values(p,1));
  
  if(*p) {
    return a;
  } else {
    return a * a;
  }
}

struct bar {
  int a;
  int b;
};

//non ct
int foo12_nct(int a, int b) {
  if (a) return b;
  else return b * b;
}

//ct
int foo12_ct(int a, int b) {
  public_in(__SMACK_value(a));
  if (a) return b;
  else return b * b;
}

int foo12_nct_struct(int a, int b) {

  struct bar x;
  x.a = a;
  x.b = b;
  
  
  if (x.a) return x.b;
  else return x.b * x.b;
}

int foo12_ct_struct(int a, int b) {
  public_in(__SMACK_value(a));

  struct bar x;
  x.a = a;
  x.b = b;
  
  
  if (x.a) return x.b;
  else return x.b * x.b;
}

//helper functions
int foo12_value_impl (struct bar x) {
  if (x.a) return x.b;
  else return x.b * x.b;
}

int foo12_ptr_impl (struct bar* x) {
  if (x->a) return x->b;
  else return x->b * x->b;
}


int foo12_ct_struct_fnval(int a, int b) {
  public_in(__SMACK_value(a));

  struct bar x;
  x.a = a;
  x.b = b;
  
  return foo12_value_impl(x);
}

// like 12_1 but strct by ref
int foo12_ct_struct_fnptr(int a, int b) {
  public_in(__SMACK_value(a));

  struct bar x;
  x.a = a;
  x.b = b;
  
  return foo12_ptr_impl(&x);
}

int foo12_ct_struct_fnmalloc(int a, int b) {
  public_in(__SMACK_value(a));

  struct bar* x = malloc(sizeof(struct bar)) ;
  x->a = a;
  x->b = b;
  
  return foo12_ptr_impl(x);
}

int foo12_nct_struct_fnval(int a, int b) {
  struct bar x;
  x.a = a;
  x.b = b;
  
  return foo12_value_impl(x);
}

// like 12_1 but strct by ref
int foo12_nct_struct_fnptr(int a, int b) {

  struct bar x;
  x.a = a;
  x.b = b;
  
  return foo12_ptr_impl(&x);
}

int foo12_nct_struct_fnmalloc(int a, int b) {
  struct bar* x = malloc(sizeof(struct bar)) ;
  x->a = a;
  x->b = b;
  
  return foo12_ptr_impl(x);
}

