// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#include <drivers/mailbox.h>   // implements
#include <drivers/gpio.h>
#include <kernel/macros.h>

volatile unsigned int _aligned(16) mbox[36];

#define VIDEOCORE_MBOX  (MMIO_BASE+0x0000B880)
#define MBOX_READ       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x0))
#define MBOX_POLL       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SENDER     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x14))
#define MBOX_STATUS     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x18))
#define MBOX_CONFIG     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRITE      ((volatile unsigned int*)(VIDEOCORE_MBOX+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

int mbox_call(unsigned char channel)
{
  unsigned int r =
    (((unsigned int)((unsigned long) &mbox) & ~0xF) | (channel & 0xF));

  do { NOP; } while(*MBOX_STATUS & MBOX_FULL);

  *MBOX_WRITE = r;

  while(1)
  {
    // Wait for a response
    do { NOP; } while(*MBOX_STATUS & MBOX_EMPTY);

    if (r == *MBOX_READ)
    {
      return mbox[1] == MBOX_RESPONSE;
    }
  }

  return 0;
}
