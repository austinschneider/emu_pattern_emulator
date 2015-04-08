/*
 * Eth_constants.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Austin
 */

#include <sys/socket.h>

#ifndef ETH_CONSTANTS_H_
#define ETH_CONSTANTS_H_

namespace emu {
namespace pc {

#define SCHAR_IOCTL_BASE    0xbb
#define SCHAR_RESET         _IO(SCHAR_IOCTL_BASE, 0)
#define SCHAR_END           _IOR(SCHAR_IOCTL_BASE, 1, int)

static const long unsigned int MAX_DAT_SIZE = 8192; // 8 KB

} // namespace pc
} // namespace emu

#endif /* ETH_CONSTANTS_H_ */

