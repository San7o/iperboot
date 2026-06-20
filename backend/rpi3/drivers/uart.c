// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#include <drivers/uart.h>   // implements
#include <drivers/gpio.h>
#include <drivers/mailbox.h>
#include <kernel/delays.h>
#include <kernel/macros.h>

// PL011 UART registers
#define UART0_DR        ((volatile unsigned int*)(MMIO_BASE+0x00201000))
#define UART0_FR        ((volatile unsigned int*)(MMIO_BASE+0x00201018))
#define UART0_IBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201024))
#define UART0_FBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201028))
#define UART0_LCRH      ((volatile unsigned int*)(MMIO_BASE+0x0020102C))
#define UART0_CR        ((volatile unsigned int*)(MMIO_BASE+0x00201030))
#define UART0_IMSC      ((volatile unsigned int*)(MMIO_BASE+0x00201038))
#define UART0_ICR       ((volatile unsigned int*)(MMIO_BASE+0x00201044))

// Set baud rate and characteristics (115200 8N1) and map to GPIO
void uart_init(void)
{
  register unsigned int r;

  // Initialize UART
  *UART0_CR = 0;    // turn off UART0

  mbox[0] = 9 * 4;
  mbox[1] = MBOX_REQUEST;
  mbox[2] = MBOX_TAG_SETCLKRATE;
  mbox[3] = 12;
  mbox[4] = 8;
  mbox[5] = 2;         // UART clock
  mbox[6] = 4000000;   // 4Mhz
  mbox[7] = 0;         // clear turbo
  mbox[8] = MBOX_TAG_LAST;

  mbox_call(MBOX_CH_PROP);
  
  // Map UART0 to GPIO pins
  r = *GPFSEL1;
  r &= ~((7 << 12) | (7 << 15)); // gpio14, gpio15
  r |= (4 << 12) | (4 << 15);    // alt5
  *GPFSEL1 = r;
  *GPPUD   = 0;            // enable pins 14 and 15
  
  wait_cycles(150);
  *GPPUDCLK0 = (1 << 14) | (1 << 15);

  wait_cycles(150);
  *GPPUDCLK0 = 0;        // flush GPIO setup

  *UART0_ICR  = 0x7FF;           // clear interrupts
  *UART0_IBRD = 2;               // 115200 baud
  *UART0_FBRD = 0xB;
  *UART0_LCRH = 0x7 << 4;        // Enable FIFOs
  *UART0_CR   = 0x301;           // enable Tx, Rx, UART
}

void uart_send(unsigned int c)
{
  // Wait until we can send
  do { NOP; } while(*UART0_FR & 0x20);

  // Write a character to the buffer
  *UART0_DR = c;
}

char uart_getc(void)
{
  char r;

  do { NOP; } while(*UART0_FR & 0x10);

  r = (char)(*UART0_DR);
  return r == '\r' ? '\n' : r;
}

void uart_puts(char *s)
{
  while(*s)
  {
    if (*s == '\n')
      uart_send('\r');
    uart_send(*s++);
  }
}

void uart_hex(unsigned int d)
{
  for (unsigned int i = 0; i < 8; ++i)
  {
    unsigned char w = (d >> (28 - i * 4)) & 0xF;
    if(w > 9)
      uart_send('A' + (w - 10));
    else
      uart_send('0' + w);
  }
}
