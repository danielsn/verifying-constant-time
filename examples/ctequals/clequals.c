#include <stdint.h>
#include <smack.h>
#include "ct-verif.h"

//This ought to be code balanced
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


int foo1(uint8_t pub, int k, int i) {
  public_in(__SMACK_value(pub));
  public_in(__SMACK_value(i));

  // From https://github.com/awslabs/s2n/blob/master/tls/s2n_cbc.c#L91
  uint8_t mask = ~(0xff << ((i >= k) * 8));
  return pub & mask;
}

//based on https://github.com/awslabs/s2n/blob/master/tls/s2n_cbc.c#L91
//padding_length is private
int foo2(int padding_length, int size, int* data){

  public_in(__SMACK_value(size));
  
  int check = 8;
  
  int cutoff = check - padding_length;
  int mismatches = 0;
  
  for (int i = 0, j = size - 1 - check;
       i < check && j < size; i++, j++) {
    uint8_t mask = ~(0xff << ((i >= cutoff) * 8));
    mismatches |= (data[j] ^ padding_length) & mask;
  }
  
  return mismatches;
}

//code balancing that doesn't work
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

//code balancing that works - cause floating point ops are same cost
float foo4(float b, int k)
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

//code balancing that actually works
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

int foo7(int a, int k) {
  public_in(__SMACK_value(a));
  return add_wrapper(a,2);
}

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

int foo10(int a, int k) {
  public_in(__SMACK_value(a));
  __VERIFIER_assume(k == 7 || k == 8);
  return a;
}




