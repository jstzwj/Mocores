#ifndef CONFIG_H
#define CONFIG_H


#define MOCORES_FILE_OFFSET_BITS 64

/**
 * hint to the system regarding the number of outstanding connect requests that
 *it should enqueue on behalf of the process
*/
#define MOCORES_SOCKET_LISTEN_BACKLOG 10

#endif // CONFIG_H
