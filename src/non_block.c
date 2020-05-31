#include <poll.h>
#include <unistd.h>

#include "non_block.h"


int getc_timeout(int fd, int timeout_ms, unsigned char *c){
   struct pollfd ufdr[1];
   int r = 0;
   ufdr[0].fd = fd;
   ufdr[0].events = POLLIN | POLLRDNORM;
   if ((poll(&ufdr[0], 1, timeout_ms) > 0) && (ufdr[0].revents & (POLLIN | POLLRDNORM))) {
      r = read(fd, c, 1);
   }
   return r;
}
