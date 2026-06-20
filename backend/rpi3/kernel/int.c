// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#include <drivers/uart.h>

void common_int_handler(unsigned long type, unsigned long esr,
                        unsigned long elr, unsigned long spsr,
                        unsigned long far)
{
  switch(type)
  {
  case 0: uart_puts("[isr] Synchronous"); break;
  case 1: uart_puts("[isr] IRQ"); break;
  case 2: uart_puts("[isr] FIQ"); break;
  case 3: uart_puts("[isr] SError"); break;
  }

  uart_puts(": ");
  // decode exception type (some, not all. See ARM DDI0487B_b chapter D10.2.28)
  switch(esr >> 26)
  {
  case 0x00: uart_puts("Unknown"); break;
  case 0x01: uart_puts("Trapped WFI/WFE"); break;
  case 0x0e: uart_puts("Illegal execution"); break;
  case 0x15: uart_puts("System call"); break;
  case 0x20: uart_puts("Instruction abort, lower EL"); break;
  case 0x21: uart_puts("Instruction abort, same EL"); break;
  case 0x22: uart_puts("Instruction alignment fault"); break;
  case 0x24: uart_puts("Data abort, lower EL"); break;
  case 0x25: uart_puts("Data abort, same EL"); break;
  case 0x26: uart_puts("Stack alignment fault"); break;
  case 0x2C: uart_puts("Floating point"); break;
  default: uart_puts("Unknown"); break;
  }
  // decode data abort cause
  if(esr >> 26 == 0x24 || esr >> 26 == 0x25)
  {
    uart_puts(", ");
    switch((esr >> 2) & 0x3)
    {
    case 0: uart_puts("Address size fault"); break;
    case 1: uart_puts("Translation fault"); break;
    case 2: uart_puts("Access flag fault"); break;
    case 3: uart_puts("Permission fault"); break;
    }
    switch(esr&0x3)
    {
    case 0: uart_puts(" at level 0"); break;
    case 1: uart_puts(" at level 1"); break;
    case 2: uart_puts(" at level 2"); break;
    case 3: uart_puts(" at level 3"); break;
    }
  }
  
  // dump registers
  uart_puts(":\n  ESR_EL1 ");
  uart_hex(esr >> 32);
  uart_hex(esr);
  uart_puts(" ELR_EL1 ");
  uart_hex(elr >> 32);
  uart_hex(elr);
  uart_puts("\n SPSR_EL1 ");
  uart_hex(spsr >> 32);
  uart_hex(spsr);
  uart_puts(" FAR_EL1 ");
  uart_hex(far >> 32);
  uart_hex(far);
  uart_puts("\n");

  while(1) {};
}
