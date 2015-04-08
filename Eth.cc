/*
 * Eth.cc
 *
 *  Created on: Apr 8, 2015
 *      Author: Austin
 */

#include "Eth.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "Utils.h"
#include "Eth_constants.h"

namespace emu {
namespace pc {

int Eth::eth_open(const char *dev_name) {
  fd_schar = open(dev_name, O_RDWR | O_NONBLOCK);
  if (fd_schar == -1) {
    perror("open");
    return -1;
  }
  return 0;
}

int Eth::eth_reset() {
  if (ioctl(fd_schar, SCHAR_RESET)) {
    printf("Error in SCHAR_RESET \n");
  }
  return 0;
}

int Eth::eth_read(int suppression) {
  /*
   * suppression=0 => pass all packets
   * suppression=1 => skip packets with 1-6 bytes and start will 0x03
   * suppression=2 => same as 1, plus ignore packets that begin with 0x33 or 0xff (multicast packets)
   */

  int lp;
  nrdat = 0;
  do {
    nrdat = read(fd_schar, rpkt, MAX_DAT_SIZE);
    for (lp = 0; suppression > 0 && nrdat >= 0 && nrdat < 7 && rpkt[0] == 0x03 && lp < 100; lp++) { // Will ignore packets with 1-6 bytes and start will 0x03 (???)
      printf("...\n");
      usleep(100);
      nrdat = read(fd_schar, rpkt, MAX_DAT_SIZE);
    }
  } while (suppression > 1 && nrdat > 6 && (rpkt[0] & 1) == 1); //ignore multicast packets (ignores packet with first byte that is odd)

  std::cout << "DEBUG[eth_lib.cpp]  eth_read read packet of " << nrdat << " bytes:" << std::endl;
  emu::utils::dumphex(nrdat, rdat);
  std::cout << std::endl;
  return nrdat;
}

int Eth::eth_write() {
  if (nwdat > MAX_DAT_SIZE) {
    printf("ERROR: nwdat=%d is too large! MAX_DAT_SIZE=%d", nwdat, MAX_DAT_SIZE);
    return 0;
  }
  int n_written;

  std::cout << "DEBUG[eth_lib.cpp]  eth_write sending packet of " << nwdat << " bytes:" << std::endl;
  emu::utils::dumphex(nwdat, wdat);
  std::cout << std::endl;

  n_written = write(fd_schar, (const void *) wpkt, nwdat);
  return n_written;
}

void Eth::eth_close() {
  close(fd_schar);
}

}
}

