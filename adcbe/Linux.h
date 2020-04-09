#ifndef ADCBE_LINUX_LINUX_H
#define ADCBE_LINUX_LINUX_H

#if defined(__linux__) || defined(__CYGWIN__)
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define closesocket(sock) close(sock)
#define send(sock, buf, size, flag) write(sock, buf, size)
typedef int SOCKET;
#endif

#endif //ADCBE_LINUX_LINUX_H