// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#ifndef RPIOS_KERNEL_INTERRUPTS_H
#define RPIOS_KERNEL_INTERRUPTs_H

//
// Interrupts
// ==========
//
// ARMv8 interrupts have some differences with AMD64. First, there are
// different interrupts per execution level, and there are different
// types of interrupts. For each interrupt type, instead of having a
// vector of all IRQ handlers, the CPU simply jumps to a location that
// you control, which you then use to jump to a C handler.
//
//
// Generic Interrupt Controller
// ----------------------------
//
// In a Cortex-A you can use the GIC to work with interrupts. The
// Cortex-A53 GIC CPU Interface implements a memory-mapped
// interface. The memory-mapped interface is offset from PERIPHBASE,
// saved in Configuration Base Address Register (CBAR) of a specific
// exception level:
//
//   Address range       Functional block
//   ----------------------------------------------------
//   0x00000 - 0x01FFF   CPU Interface
//   0x02000 - 0x0FFFF   Reserved
//   0x10000 - 0x10FFF   Virtual Interface Control
//   0x11000 - 0x1FFFF   Reserved
//   0x20000 - 0x21FFF   Virtual CPU Interface
//   0x22000 - 0x2EFFF   Reserved
//   0x2F000 - 0x30FFF   Alias of Virtual CPU Interface
//   0x31000 - 0x3FFFF   Reserved
//
// References: Arm Cortex-A53 MPCore Processor Technical Reference
// Manual, chapter 4 - System Control, chapter 9 - Generic Interrupt
// Controller CPU Interface
//
// ARMv8 ARM - D1 The AArch64 System Level Programmers Model
//

// To load the vector table, you need to use the Vector Base Address
// Register for a specific execution level (VBAR_ELX). Default table
// address is 0x00000000.
//
// Source: ARMv8 ARM D1.10.2

void common_int_handler(unsigned long type, unsigned long esr,
                        unsigned long elr, unsigned long spsr,
                        unsigned long far);

#endif // RPIOS_KERNEL_EXCEPTIONS_H
