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
  //if(DEBUG>10) std::cout<<"DEBUG[eth_lib.cpp]  eth_open(\""<<dev_name<<"\")"<<std::endl;
  //fd_schar = open(dev_name, O_RDWR); // I think all file descriptors for a given device point to the same place so the exact fd doesn't matter much
  fd_schar = open(dev_name, O_RDWR | O_NONBLOCK);
  if (fd_schar == -1) {
    perror("open");
    return -1;
  }
  //printf("Opened network path on device %s\n",dev_name);
  return 0;
}

int Eth::eth_register_mac() {
  //if(DEBUG>10) std::cout<<"DEBUG[eth_lib.cpp]  eth_register_mac()"<<std::endl;
  /* This used to set the header, but now it does nothing.  Leave it here in case we want to use it in the future. */
  return 0;
}

int Eth::eth_reset() {
  //if(DEBUG>10) std::cout<<"DEBUG[eth_lib.cpp]  eth_reset()"<<std::endl;
  if (ioctl(fd_schar, SCHAR_RESET)) {
    printf("Error in SCHAR_RESET \n");
  }
  //printf("Reset device.\n");
  return 0;
}

int Eth::eth_read(int suppression) {
  //if(DEBUG>10) std::cout<<"DEBUG[eth_lib.cpp]  eth_read("<<suppression<<")"<<std::endl;
  /*
   * suppression=0 => pass all packets
   * suppression=1 => skip packets with 1-6 bytes and start will 0x03
   * suppression=2 => same as 1, plus ignore packets that begin with 0x33 or 0xff (multicast packets)
   */

  int lp;
  nrdat = 0;
  do {
    //printf(" Receiving...");
    nrdat = read(fd_schar, rpkt, MAX_DAT_SIZE);
    //printf(" nrdat %d \n",nrdat);
    for (lp = 0; suppression > 0 && nrdat >= 0 && nrdat < 7 && rpkt[0] == 0x03 && lp < 100; lp++) { // Will ignore packets with 1-6 bytes and start will 0x03 (???)
      printf("...\n");
      usleep(100);
      nrdat = read(fd_schar, rpkt, MAX_DAT_SIZE);
    }
  } while (suppression > 1 && nrdat > 6 && (rpkt[0] & 1) == 1); //ignore multicast packets (ignores packet with first byte that is odd)

  //if(DEBUG>20){
  std::cout << "DEBUG[eth_lib.cpp]  eth_read read packet of " << nrdat << " bytes:" << std::endl;
  emu::utils::dumphex(nrdat, rdat);
  std::cout << std::endl;
  //}
  return nrdat;
}

int Eth::eth_write() {
  //if(DEBUG>10) std::cout<<"DEBUG[eth_lib.cpp]  eth_write()"<<std::endl;
  if (nwdat > MAX_DAT_SIZE) {
    printf("ERROR: nwdat=%d is too large! MAX_DAT_SIZE=%d", nwdat, MAX_DAT_SIZE);
    return 0;
  }
  int n_written;
  //printf(" Creating the packet... nwdat %d ...",nwdat);
  //if(DEBUG>20){
  std::cout << "DEBUG[eth_lib.cpp]  eth_write sending packet of " << nwdat << " bytes:" << std::endl;
  emu::utils::dumphex(nwdat, wdat);
  std::cout << std::endl;
  //}
  n_written = write(fd_schar, (const void *) wpkt, nwdat);
  //printf(" n_written %d \n",n_written);
  return n_written;
}

void Eth::eth_close() {
  //if(DEBUG>10) std::cout<<"DEBUG[eth_lib.cpp]  eth_close()"<<std::endl;
  close(fd_schar);
  //printf("Closed device\n");
}

}
}

