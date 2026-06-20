// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#include <kernel/rand.h>
#include <kernel/delays.h>
#include <kernel/power.h>
#include <kernel/fb.h>
#include <drivers/uart.h>
#include <drivers/mailbox.h>

int main(void)
{
  uart_init();
  rand_init();
  fb_init();
  
  uart_puts("[debug] Hello, World!\n");

  uart_puts("[debug] Test number: 0x");
  uart_hex(0x1234);
  uart_send('\n');

  uart_puts("[debug] Random number: 0x");
  uart_hex(rand(0, 0xFFFFFFFF));
  uart_send('\n');

  uart_puts("[debug] Waiting 1000000 CPU cycles\n");
  wait_cycles(1000000);
  uart_puts("[debug] done\n");

  uart_puts("[debug] Waiting 1000000 microsec (ARM CPU)\n");
  wait_msec(1000000);
  uart_puts("[debug] done\n");

  uart_puts("[debug] Waiting 1000000 microsec (ARM CPU)\n");
  if (get_system_timer() == 0)
  {
    uart_puts("[error] Timer Non available\n");
  }
  else
  {
    wait_msec_st(1000000);
    uart_puts("[debug] done\n");
  }

  // Get serial number
  
  mbox[0] = 8 * 4;   // length of the message
  mbox[1] = MBOX_REQUEST;
  mbox[2] = MBOX_TAG_GETSERIAL;
  mbox[3] = 8;       // Request size
  mbox[4] = 8;       // Response size
  mbox[5] = 0;       // first 4 bytes
  mbox[6] = 0;       // second 4 bytes
  mbox[7] = MBOX_TAG_LAST;

  // Send message to the GPU and receive answer
  if (mbox_call(MBOX_CH_PROP))
  {
    uart_puts("[debug] serial number is: 0x");
    uart_hex(mbox[6]);
    uart_hex(mbox[5]);
    uart_send('\n');
  }
  else
  {
    uart_puts("[error] Unable to query serial!\n");
  }

  // Generate divide by 0 exception
  volatile int x = 1;
  uart_send(x / 0.0);
  
  uart_puts("Press 'q' to power off, 'r' to reset...\n");
  while(1)
  {
    char c = uart_getc();

    if (c == 'q') power_off();
    if (c == 'r') power_reset();

    // Echo back
    uart_send(c);
  }

  return 0;
}
