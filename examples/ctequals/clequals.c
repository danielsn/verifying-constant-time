#include <stdint.h>
#include <smack.h>
//#include "ct-verif.h"

float foo(float b, int k)
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
