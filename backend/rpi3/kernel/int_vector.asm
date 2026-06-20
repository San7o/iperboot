  .extern common_int_handler
  
  .global int_vector

  .align 11
  
int_vector:

  // synchronous
  .align 7
  mov x0, #0
  mrs x1, esr_el1
  mrs x2, elr_el1
  mrs x3, spsr_el1
  mrs x4, far_el1
  b   common_int_handler

  // IRQ
  .align 7
  mov x0, #0
  mrs x1, esr_el1
  mrs x2, elr_el1
  mrs x3, spsr_el1
  mrs x4, far_el1
  b   common_int_handler

  // FIQ
  .align 7
  mov x0, #0
  mrs x1, esr_el1
  mrs x2, elr_el1
  mrs x3, spsr_el1
  mrs x4, far_el1
  b   common_int_handler

  // SError
  .align 7
  mov x0, #0
  mrs x1, esr_el1
  mrs x2, elr_el1
  mrs x3, spsr_el1
  mrs x4, far_el1
  b   common_int_handler
