// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#include <kernel/delays.h>   // implements
#include <kernel/macros.h>
#include <drivers/gpio.h>

#define SYSTMR_LO        ((volatile unsigned int*)(MMIO_BASE+0x00003004))
#define SYSTMR_HI        ((volatile unsigned int*)(MMIO_BASE+0x00003008))

void wait_cycles(unsigned int n)
{
  if (n) while(n--) { NOP; }
}

void wait_msec(unsigned int n)
{
  register unsigned long f, t, r;

  // get the current counter frequency
  __asm__ volatile ("mrs %0, cntfrq_el0" : "=r"(f));
  // read the current counter
  __asm__ volatile ("mrs %0, cntpct_el0" : "=r"(t));
  // calculate required count increase
  unsigned long i = ((f / 1000) * n) / 1000;
  // loop while counter increase is less than i
  do
  {
    __asm__ volatile ("mrs %0, cntpct_el0" : "=r"(r));
  } while(r - t < i);
}

unsigned long get_system_timer(void)
{
  unsigned int h = -1, l;

  // Read MMIO area as two separate 32 bit reads
  h = *SYSTMR_HI;
  l = *SYSTMR_LO;

  // repeat it if high word changed during read
  if (h != *SYSTMR_HI)
  {
    h = *SYSTMR_HI;
    l = *SYSTMR_LO;
  }

  return ((unsigned long) h << 32) | l;
}

void wait_msec_st(unsigned int n)
{
  unsigned long t = get_system_timer();
  if (t) while(get_system_timer() - t < n);
}
