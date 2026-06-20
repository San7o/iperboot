// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#ifndef RPIOS_MACROS_H
#define RPIOS_MACROS_H

#define _aligned(x) __attribute__((aligned(x)))
#define NOP  __asm__ volatile("nop")

#endif // RPIOS_MACROS_H
