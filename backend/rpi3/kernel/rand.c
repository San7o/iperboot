// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#include <kernel/rand.h>   // implements
#include <kernel/macros.h>
#include <drivers/gpio.h>

#define RNG_CTRL        ((volatile unsigned int*)(MMIO_BASE+0x00104000))
#define RNG_STATUS      ((volatile unsigned int*)(MMIO_BASE+0x00104004))
#define RNG_DATA        ((volatile unsigned int*)(MMIO_BASE+0x00104008))
#define RNG_INT_MASK    ((volatile unsigned int*)(MMIO_BASE+0x00104010))

void rand_init(void)
{
  *RNG_STATUS    = 0x40000;
  *RNG_INT_MASK |= 1;   // mash interrpt
  *RNG_CTRL     |= 1;   // enable
}

unsigned int rand(unsigned int min, unsigned int max)
{
  while(!((*RNG_STATUS) >> 24)) NOP;
  return *RNG_DATA % (max - min) + min;
}
