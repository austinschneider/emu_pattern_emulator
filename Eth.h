/*
 * Eth.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Austin
 */

#include <sys/socket.h>

#include "Eth_constants.h"

#ifndef ETH_H_
#define ETH_H_

namespace emu {
namespace pc {

class Eth {
  int fd_schar;

  char wpkt[4 + MAX_DAT_SIZE]; /* full packet to send (header+data) */
  char *wdat; /* buffer with data to send */
  char rpkt[18 + MAX_DAT_SIZE]; /* full packet read (header+data) */
  char *rdat; /* buffer with data read */
  int nwdat; /* number of data bytes to send */
  int nrdat; /* number of data bytes read */

public:
  inline Eth() {
    fd_schar = 1;

    nwdat = 0;
    nrdat = 0;
    wdat = wpkt;
    rdat = rpkt + 14;
  }

  int eth_open(const char *dev_name);
  int eth_register_mac();
  void eth_close();
  int eth_reset();
  int eth_read(int suppression);
  int eth_write();
};

} // namespace pc
} // namespace emu

#endif /* ETH_H_ */
