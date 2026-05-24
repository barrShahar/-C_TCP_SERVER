#include <stdlib.h>
#include <pthread.h>
#include "TcpConnectionHandler.h"
#include "db/gen_dlist.h"

typedef enum {
    HANDLER_STATE_STOPPED,
    HANDLER_STATE_RUNNING
} HandlerState;

struct TcpConnectionHandler
{
    TcpServerController* m_tcpCtrl;
    pthread_t m_thread;
    HandlerState m_state;
    // fd_set m_readfds; //set of socket descriptors
};
//static helper functions declarations
static void* ClientHandlerThread(void* a_handler);


TcpConnectionHandler* TcpConnectionHandler_Create(TcpServerController* a_tcpCtrl)
{
    TcpConnectionHandler* handler = (TcpConnectionHandler*)malloc(sizeof(TcpConnectionHandler));
    if (handler == NULL)
    {
        return NULL;
    }
    handler->m_tcpCtrl = a_tcpCtrl;
    handler->m_state = HANDLER_STATE_STOPPED;

    // FD_ZERO(&handler->m_readfds);
    return handler;
}

void TcpConnectionHandler_Destroy(TcpConnectionHandler** a_handler)
{
    if (a_handler == NULL)
    {
        return;
    }
    free(a_handler);
}

TcpResult TcpConnectionHandler_Start(TcpConnectionHandler* a_handler)
{
    if (a_handler == NULL)
    {
        return TCP_RESULT_NULL_PTR;
    }

    if (a_handler->m_state == HANDLER_STATE_RUNNING)
    {
        return TCP_RESULT_SUCCESS;
    }

    int result = pthread_create(&a_handler->m_thread, NULL, ClientHandlerThread, a_handler);
    if (result > 0) // Any value greater than 0 indicates a POSIX error code
    {
        return TCP_RESULT_THREAD_CREATION_FAILED;
    }
    return TCP_RESULT_SUCCESS;
}

static void* ClientHandlerThread(void* a_handler)
{
    TcpConnectionHandler* handler = (TcpConnectionHandler*)a_handler;
    int max_fd = 0;

    return NULL;
}
