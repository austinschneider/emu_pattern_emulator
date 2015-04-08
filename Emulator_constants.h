/*
 * Emulator_constants.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Austin
 */

#ifndef EMULATOR_CONSTANTS_H_
#define EMULATOR_CONSTANTS_H_

namespace emu {
namespace pc {

static const unsigned long int RAMPAGE_SIZE = 4 * 1024; // size of RAM pages from FPGA

static const unsigned long int status_cmd           = 0x0000F0;
static const unsigned long int f1_cmd               = 0x0000F1;
static const unsigned long int f2_cmd               = 0x0000F2;
static const unsigned long int read_cmd             = 0x0000F3;
static const unsigned long int write_cmd            = 0x0000F7;

} // namespace pc
} // namespace emu

#endif /* EMULATOR_CONSTANTS_H_ */

