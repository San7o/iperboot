# STM32 "Blue Pill"

More info and datasheet at
[hello-stm32-blue-pill](https://github.com/San7o/hello-stm32-blue-pill).

## Memory Map

Source: Chapter 5 of datasheet.

| Start      | End        | Type                            |
| ---------- | ---------- | ------------------------------- |
| 0x00000000 | 0x00040000 | Depends on BOOT configuration   |
| 0x00040000 | 0x08000000 | Reserved                        |
| 0x08000000 | 0x08040000 | Flash Memory                    |
| 0x08040000 | 0x1FFFEC00 | Reserved                        |
| 0x1FFFEC00 | 0x1FFFF800 | System Memory                   |
| 0x1FFFF800 | 0x1FFFFC00 | Option Bytes                    |
| 0x1FFFFC00 | 0x20000000 | Reserved                        |
| 0x20000000 | X          | SRAM                            |
| 0x40000000 | 0x480017FF | Peripherals                     |
| 0x480017FF | 0xE0000000 | Reserved                        |
| 0xE0000000 | 0xE0100000 | Cortex-M0 Internal peripherals  |
| 0xE0100000 | 0xFFFFFFFF | Reserved                        |

- At startup, the boot pin and boot selector option bit are used to select one
  of three boot options: user flash, system memory and embedded SRAM.
- `X` of SRAM depends on the particular device you have

In the peripherals section, we have the following buses:

| Start      | End        | Type     |
| ---------- | ---------- | -------- |
| 0x40000000 | 0x40008000 | APB      |
| 0x40008000 | 0x40010000 | Reserved |
| 0x40010000 | 0x40018000 | APB      |
| 0x40018000 | 0x40020000 | Reserved |
| 0x40020000 | 0x400243FF | AHB1     |
| 0x400143FF | 0x48000000 | Reserved |
| 0x48000000 | 0x480017FF | AHB2     |

## Power

The microcontroller supports three low-power modes:

- sleep mode: only CPU is stopped, all peripherals continue to update and can
  wake up the CPU when an interrupt occurs.
- stop mode: all clock in the 1.8V domain are stopped, the PLL, the HSI RC and
  the HSE crystal oscillators are disabled, while retaining the content of SRAM
  and registers. The device can be woken up by any of the EXTI lines.
- standby mode: this is the lowest power consumption. The entire 1.8V domain is
  powered of, oscillators os swtiched off, SRAM and registers are lost except
  for registers in the RTC domain and standby circuitry. The device exits
  standby mode when an external reset, an IWDG reset, a rising edge on the WKUP
  pins, or and RTC event occurs.

## Clocks

- the internal RC 8MHz oscillator is selected as default CPU clock on reset. n
  external 4-32 MHz clock can be selected, in which case it is monitored for
  failure. If failure is detected, the system automatically switches back to the
  internal RC oscillator.

## Interrupts

A nested vectored interrupt controller (NVIC) is available to handle up to 32
maskable interrupt channels and 4 priority levels.

The extended interrupt/event controller (EXTI) consists of 32 edge detector
lines used to generate interrupt/event requests and wake-up the system. Each
line can be independently configured to select the trigger event (rising edge,
falling edge, both) and can be masked independently. 
