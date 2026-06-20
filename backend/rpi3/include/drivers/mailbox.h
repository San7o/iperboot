// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#ifndef RPIOS_MAILBOX_H
#define RPIOS_MAILBOX_H

//
// Mailboxes
// =========
//
// Mailboxes facilitate communication between the ARM and the
// VideoCore.
//
// Each mailbox is an 8-deep FIFO of 32-bit words, which can be read
// (popped)/written (pushed) by the ARM and VC. Only mailbox 0's
// status can trigger interrupts on the ARM, so MB 0 is always for
// communication from VC to ARM and MB 1 is for ARM to VC. The ARM
// should never write MB 0 or read MB 1.
//
// Mailbox 0 defines the following channels:
//   0: Power management
//   1: Framebuffer
//   2: Virtual UART
//   3: VCHIQ
//   4: LEDs
//   5: Buttons
//   6: Touch screen
//   7:
//   8: Property tags (ARM -> VC)
//   9: Property tags (VC -> ARM)
// 
// More information can be found on the official firmware wiki on
// github:
//
//       https://github.com/raspberrypi/firmware/wiki
//

#include <kernel/macros.h>

// TODO: an actual API

// a properly aligned buffer
// TODO: create the mail_status_t and mail_message_t types
extern volatile _aligned(16) unsigned int mbox[36];

#define MBOX_REQUEST    0

// Mailbox 0 channels
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1   // Framebuffer
#define MBOX_CH_VUART   2   // Virtual UART
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5   // Buttons
#define MBOX_CH_TOUCH   6   // Touch screen
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8   // Property Tags

// tags
#define MBOX_TAG_GETSERIAL      0x10004
#define MBOX_TAG_SETPOWER       0x28001
#define MBOX_TAG_SETCLKRATE     0x38002
#define MBOX_TAG_LAST           0

// TODO: take the mailbox as an argument
int mbox_call(unsigned char channel);

#endif // RPIOS_MAILBOX_H
