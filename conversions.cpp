#include "conversions.h"
#include "math.h"

// +---------------------------------------------------------------------------+
// |               Define the Bit Widths and Exponent Properties               |
// +---------------------------------------------------------------------------+

// IEEE 754 Float32 Single Precision Floating Point Constants (Binary32)
#define fl32_width            32        // Bit width of the Float32
#define fl32_mant_width       23        // Bit width of the encoded mantissa
#define fl32_exp_bias        127        // IEEE 754 Float32 exponent bias
#define fl32_NaN_exp           1        // Exponent encodings used for NaN

// PMBus Linear11 Floating Point Constants
#define lin11_width           16        // Bit width of the Linear11
#define lin11_mant_width      11        // Bit width of the Linear11 mantissa

// PMBus Linear16 Format Constants
#define lin16_width           16        // Bit width of the Linear16
#define lin16_exp_width        5        // Bit width of the Linear16 exponent

// +---------------------------------------------------------------------------+
// |      Calculate the Float32 Exponent Ranges and Bit Masks                  |
// +---------------------------------------------------------------------------+

// Float32 exponent constants
#define fl32_exp_width      (fl32_width - fl32_mant_width - 1)
#define fl32_max_exp        ((1UL << fl32_exp_width) - 1)
#define fl32_max_p_exp      (fl32_max_exp - fl32_exp_bias - fl32_NaN_exp)

// Define the IEEE 754 Float32 Single Precision Bit Masks
#define fl32_sign_mask      (1UL << (fl32_width - 1))
#define fl32_exp_mask       (((1UL << fl32_exp_width) - 1) << fl32_mant_width)
#define fl32_mant_mask      ((1UL << fl32_mant_width) - 1)

// +---------------------------------------------------------------------------+
// |                        PMBus Linear11 Definitions                         |
// +---------------------------------------------------------------------------+

// Define the PMBus Linear11 Bit Masks
#define lin11_mant_sign_mask    (1UL << (lin11_mant_width - 1))
#define lin11_mant_mask         ((1UL << lin11_mant_width) - 1)
#define lin11_exp_width         (lin11_width - lin11_mant_width)
#define lin11_exp_sign_mask     (1UL << (lin11_exp_width - 1))
#define lin11_exp_mask          ((1UL << lin11_exp_width) - 1)
#define lin11_ieee_mant_width   (lin11_mant_width-2)
#define lin11_ieee_mant_mask    ((1UL << lin11_ieee_mant_width) - 1)
#define lin11_max_p_exp         ((1UL << (lin11_exp_width - 1)) - 1)
#define lin11_max_n_exp         (1UL << (lin11_exp_width - 1))
#define lin11_bit_mask          ((1UL << lin11_width) - 1)

// Define the PMBus Linear11 normalized and denormal -1
#define lin11_den_n1   ((1UL<<(lin11_mant_width-1))|(1UL<<(lin11_mant_width-2)))
#define lin11_norm_n1  ( 1UL<<(lin11_mant_width-1))

// +---------------------------------------------------------------------------+
// |                        PMBus Linear16 Definitions                         |
// +---------------------------------------------------------------------------+

// Define the PMBus Linear16 Bit Masks
#define lin16_exp_sign_mask     (1UL << (lin16_exp_width - 1))
#define lin16_exp_mask          ((1UL << lin16_exp_width) - 1)
#define lin16_ieee_mant_width   (lin16_width-1)
#define lin16_ieee_mant_mask    ((1UL << lin16_ieee_mant_width) - 1)
#define lin16_max_p_exp         ((1UL << (lin16_exp_width - 1)) - 1)
#define lin16_max_n_exp         (1UL << (lin16_exp_width - 1))
#define lin16_max_value         ((1UL << lin16_width) - 1)

// Make sure the mantissa of the Float32 format is as wide as or wider than
// the mantissa of the Linear16 format
#if !(fl32_mant_width >= lin16_ieee_mant_width)
#error The Float32 mantissa does not have enough bits for L16!
#endif

unsigned long lin16_to_fl32 (unsigned int lin16_mant, unsigned int vout_mode)
{

  // Repackage the Linear16 in an IEEE 754 format (sign, exponent, mantissa)
  unsigned int     lin16_exp_sign;
  unsigned long       lin16_exp,xout;

  // Extract the exponent and mantissa (sign = 0)
  lin16_exp = (unsigned long) (vout_mode & ((unsigned int) lin16_exp_mask));
  lin16_exp_sign = vout_mode & ((unsigned int) lin16_exp_sign_mask);

  // Add the exponent bias of the target IEEE 754 format to the L16 exponent
  if (lin16_exp_sign != (unsigned int) 0)
  {
    lin16_exp = (lin16_exp ^ ((unsigned long) lin16_exp_mask)) + 1;
    lin16_exp = (unsigned long)(fl32_exp_bias + lin16_ieee_mant_width) - lin16_exp;
  }
  else
  {
    lin16_exp = (unsigned long)(fl32_exp_bias + lin16_ieee_mant_width) + lin16_exp;
  }

  // Normalize the Linear16 mantissa to fit the IEEE 754 format structure
  if (lin16_mant != 0 )
  {
    while ((lin16_mant &  (~((unsigned int) lin16_ieee_mant_mask))) == 0 )
    {
      lin16_mant = lin16_mant << 1;
      lin16_exp--;
    }
  }
  else
  {
    lin16_exp = 0;      // Special case of Zero
  }
  lin16_mant = lin16_mant & ((unsigned int) lin16_ieee_mant_mask);

  // Shift the L16 mantissa and exponent to the target IEEE format (sign=0)
  xout  = lin16_exp << fl32_mant_width;
  xout |= ((unsigned long) lin16_mant) << (fl32_mant_width - lin16_ieee_mant_width);

  return xout;
}

unsigned long lin11_to_fl32 (unsigned int xin)
{

  // Repackage the Linear11 in an IEEE754 format (sign, exponent, mantissa)
  unsigned int      lin11_sign, lin11_exp, lin11_exp_sign, lin11_mant, lin11_nmant;
  unsigned long       xout;

  // Extract the sign, exponent and mantissa
  lin11_sign = (xin & ((unsigned int) lin11_mant_sign_mask)) << lin11_exp_width;
  lin11_exp  = (xin >> lin11_mant_width) & ((unsigned int) lin11_exp_mask);
  lin11_exp_sign = lin11_exp & ((unsigned int) lin11_exp_sign_mask);
  lin11_mant = (xin & ((unsigned int) lin11_mant_mask));

  // Add the exponent bias of the target IEEE 754 format to the L11 exponent
  if (lin11_exp_sign != 0)
  {
    lin11_exp = (lin11_exp ^ ((unsigned int) lin11_exp_mask)) + 1;
    lin11_exp = fl32_exp_bias - lin11_exp + lin11_mant_width - 2;
  }
  else
  {
    lin11_exp = fl32_exp_bias + lin11_exp + lin11_mant_width - 2;
  }

  // Invert the mantissa sign for the two's complement representation
  if (lin11_sign != 0)
  {
    lin11_nmant = (lin11_mant ^ ((unsigned int) lin11_mant_mask)) + 1;

    // The most negative mantissa is a corner case and has to be shifted
    if  (lin11_nmant == lin11_mant)
    {
      lin11_mant = lin11_nmant >> 1;
      lin11_exp++;
    }
    else
    {
      lin11_mant = lin11_nmant;
    }
  }

  // Normalize the Linear11 mantissa to fit the IEEE 754 format structure
  if (lin11_mant != 0 )
  {
    while ((lin11_mant &  (~((unsigned int) lin11_ieee_mant_mask))) == 0 )
    {
      lin11_mant = lin11_mant << 1;
      lin11_exp--;
    }
  }
  else
  {
    lin11_exp = 0;      // Special case of Zero
  }
  lin11_mant = lin11_mant & ((unsigned int) lin11_ieee_mant_mask);

  // Shift the L11 sign, exponent and mantissa to the target IEEE format
  xout  = ((unsigned long) lin11_sign) << (fl32_width - lin11_width);
  xout |= ((unsigned long) lin11_exp)  <<  fl32_mant_width;
  xout |= ((unsigned long) lin11_mant) << (fl32_mant_width - lin11_ieee_mant_width);

  return xout;
}

float lin16_to_float (unsigned int lin16_mant, unsigned int vout_mode)
{
  unsigned long  xout;
  xout = lin16_to_fl32(lin16_mant, vout_mode);
  return *((float *) &xout);
}

float lin11_to_float (unsigned int xin)
{
  unsigned long xout;
  xout = lin11_to_fl32(xin);
  return *((float *) &xout);
}