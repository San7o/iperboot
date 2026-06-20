// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#ifndef RPIOS_DELAYS_H
#define RPIOS_DELAYS_H

// Get System Timer's counter
unsigned long get_system_timer(void);

// Wait N CPU cycles (ARM CPU only)
void wait_cycles(unsigned int n);
// Wait N microsec (ARM CPU only)
void wait_msec(unsigned int n);
// Wait N microsec (with BCM System Timer)
void wait_msec_st(unsigned int n);

#endif // RPIOS_DELAYS_H
