/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'processor'
 * SOPC Builder design path: C:/Users/david/Desktop/Logic_Design_Projects/3d-engine/processor.sopcinfo
 *
 * Generated: Sat Feb 05 20:16:07 EST 2022
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00080820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x14
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00040020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x14
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00040000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00080820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x14
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00040020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x14
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00040000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_GEN2
#define __ALTPLL


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x810a8
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x810a8
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x810a8
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "processor"


/*
 * altpll_0 configuration
 *
 */

#define ALTPLL_0_BASE 0x0
#define ALTPLL_0_IRQ -1
#define ALTPLL_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTPLL_0_NAME "/dev/altpll_0"
#define ALTPLL_0_SPAN 16
#define ALTPLL_0_TYPE "altpll"
#define ALT_MODULE_CLASS_altpll_0 altpll


/*
 * bb_we configuration
 *
 */

#define ALT_MODULE_CLASS_bb_we altera_avalon_pio
#define BB_WE_BASE 0x81070
#define BB_WE_BIT_CLEARING_EDGE_REGISTER 0
#define BB_WE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BB_WE_CAPTURE 0
#define BB_WE_DATA_WIDTH 1
#define BB_WE_DO_TEST_BENCH_WIRING 0
#define BB_WE_DRIVEN_SIM_VALUE 0
#define BB_WE_EDGE_TYPE "NONE"
#define BB_WE_FREQ 50000000
#define BB_WE_HAS_IN 0
#define BB_WE_HAS_OUT 1
#define BB_WE_HAS_TRI 0
#define BB_WE_IRQ -1
#define BB_WE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BB_WE_IRQ_TYPE "NONE"
#define BB_WE_NAME "/dev/bb_we"
#define BB_WE_RESET_VALUE 0
#define BB_WE_SPAN 16
#define BB_WE_TYPE "altera_avalon_pio"


/*
 * din configuration
 *
 */

#define ALT_MODULE_CLASS_din altera_avalon_pio
#define DIN_BASE 0x81050
#define DIN_BIT_CLEARING_EDGE_REGISTER 0
#define DIN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DIN_CAPTURE 0
#define DIN_DATA_WIDTH 32
#define DIN_DO_TEST_BENCH_WIRING 0
#define DIN_DRIVEN_SIM_VALUE 0
#define DIN_EDGE_TYPE "NONE"
#define DIN_FREQ 50000000
#define DIN_HAS_IN 0
#define DIN_HAS_OUT 1
#define DIN_HAS_TRI 0
#define DIN_IRQ -1
#define DIN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DIN_IRQ_TYPE "NONE"
#define DIN_NAME "/dev/din"
#define DIN_RESET_VALUE 0
#define DIN_SPAN 16
#define DIN_TYPE "altera_avalon_pio"


/*
 * done configuration
 *
 */

#define ALT_MODULE_CLASS_done altera_avalon_pio
#define DONE_BASE 0x81090
#define DONE_BIT_CLEARING_EDGE_REGISTER 0
#define DONE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DONE_CAPTURE 0
#define DONE_DATA_WIDTH 1
#define DONE_DO_TEST_BENCH_WIRING 0
#define DONE_DRIVEN_SIM_VALUE 0
#define DONE_EDGE_TYPE "NONE"
#define DONE_FREQ 50000000
#define DONE_HAS_IN 0
#define DONE_HAS_OUT 1
#define DONE_HAS_TRI 0
#define DONE_IRQ -1
#define DONE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DONE_IRQ_TYPE "NONE"
#define DONE_NAME "/dev/done"
#define DONE_RESET_VALUE 0
#define DONE_SPAN 16
#define DONE_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x810a8
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x40000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "processor_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 200000
#define ONCHIP_MEMORY2_0_SPAN 200000
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * swap configuration
 *
 */

#define ALT_MODULE_CLASS_swap altera_avalon_pio
#define SWAP_BASE 0x81080
#define SWAP_BIT_CLEARING_EDGE_REGISTER 0
#define SWAP_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWAP_CAPTURE 0
#define SWAP_DATA_WIDTH 1
#define SWAP_DO_TEST_BENCH_WIRING 0
#define SWAP_DRIVEN_SIM_VALUE 0
#define SWAP_EDGE_TYPE "NONE"
#define SWAP_FREQ 50000000
#define SWAP_HAS_IN 1
#define SWAP_HAS_OUT 0
#define SWAP_HAS_TRI 0
#define SWAP_IRQ -1
#define SWAP_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWAP_IRQ_TYPE "NONE"
#define SWAP_NAME "/dev/swap"
#define SWAP_RESET_VALUE 0
#define SWAP_SPAN 16
#define SWAP_TYPE "altera_avalon_pio"


/*
 * waddr configuration
 *
 */

#define ALT_MODULE_CLASS_waddr altera_avalon_pio
#define WADDR_BASE 0x81060
#define WADDR_BIT_CLEARING_EDGE_REGISTER 0
#define WADDR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define WADDR_CAPTURE 0
#define WADDR_DATA_WIDTH 32
#define WADDR_DO_TEST_BENCH_WIRING 0
#define WADDR_DRIVEN_SIM_VALUE 0
#define WADDR_EDGE_TYPE "NONE"
#define WADDR_FREQ 50000000
#define WADDR_HAS_IN 0
#define WADDR_HAS_OUT 1
#define WADDR_HAS_TRI 0
#define WADDR_IRQ -1
#define WADDR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define WADDR_IRQ_TYPE "NONE"
#define WADDR_NAME "/dev/waddr"
#define WADDR_RESET_VALUE 0
#define WADDR_SPAN 16
#define WADDR_TYPE "altera_avalon_pio"

#endif /* __SYSTEM_H_ */
