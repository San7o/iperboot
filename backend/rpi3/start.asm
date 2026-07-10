  .section ".text.boot"

  .extern int_vector
  .extern main

// Reset Vector
// ------------
//
// On ARMv8, the reset vector is not a vector anymore, but just the point where
// the CPU jumps to after reset. So the term "reset vector", "reset entry
// point" and "reset address" can be used interchangeably.
// The actual interrupt vector is set dynamically later, like in x86

  .global _start

_start:
  // Read cpu id, stop slave cores
  mrs x1, mpidr_el1
  and x1, x1, #3
  cbz x1, 2f

  b hcf

2:
  // set top of stack just before our code, which is  0x80000
  ldr x1, =_start

  // set up EL1
  mrs     x0, CurrentEL
  and     x0, x0, #12 // clear reserved bits

  // running at EL3?
  cmp     x0, #12
  bne     5f
  // should never be executed, just for completeness
  mov     x2, #0x5b1
  msr     scr_el3, x2
  mov     x2, #0x3c9
  msr     spsr_el3, x2
  adr     x2, 5f
  msr     elr_el3, x2
  eret

5:
  // running at EL2?
  cmp     x0, #4
  beq     5f
  msr     sp_el1, x1
  // enable CNTP for EL1
  mrs     x0, cnthctl_el2
  orr     x0, x0, #3
  msr     cnthctl_el2, x0
  msr     cntvoff_el2, xzr
  // enable AArch64 in EL1
  mov     x0, #(1 << 31)      // AArch64
  orr     x0, x0, #(1 << 1)   // SWIO hardwired on Pi3
  msr     hcr_el2, x0
  mrs     x0, hcr_el2
  // Setup SCTLR access
  mov     x2, #0x0800
  movk    x2, #0x30d0, lsl #16
  msr     sctlr_el1, x2
  // set up exception handlers
  ldr     x2, =int_vector
  msr     vbar_el1, x2
  // change execution level to EL1
  mov     x2, #0x3c4
  msr     spsr_el2, x2
  adr     x2, 5f
  msr     elr_el2, x2
  eret
  
5:
  mov sp, x1

  ldr x1, =__bss_start
  ldr w2, =__bss_size
3:
  cbz w2, 4f
  str xzr, [x1], #8
  sub w2, w2, #1
  cbnz w2, 3b

  // Debug
  b hcf

4:
  bl main

hcf: // halt and catch fire
  wfi
  b hcf
