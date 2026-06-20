// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#ifndef RPIOS_UART_H
#define RPIOS_UART_H

void uart_init(void);
void uart_send(unsigned int c);
char uart_getc(void);
void uart_puts(char *s);
void uart_hex(unsigned int d);

#endif // RPIOS_UART_H
