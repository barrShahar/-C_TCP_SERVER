#pragma once
#include <stdint.h>
#include "TcpConnectionRecord.h"
#include <stddef.h>
typedef struct TcpServerController TcpServerController;

typedef enum TcpResult 
{
    TCP_RESULT_SUCCESS = 0,
    TCP_RESULT_NULL_PTR,
    TCP_RESULT_ALLOCATION_FAILED,
    TCP_RESULT_SOCKET_ERROR,
    TCP_RESULT_BIND_ERROR,
    TCP_RESULT_LISTEN_ERROR,
    TCP_RESULT_ACCEPT_ERROR,
    TCP_RESULT_CONNECTION_CLOSED,
    TCP_RESULT_THREAD_CREATION_FAILED
} TcpResult;

// Callbacks supported by the server controller

TcpServerController* TcpServerController_Create(const char* a_name, const char* a_ip, const uint16_t a_port);
void TcpServerController_Destroy(TcpServerController** a_controller);

TcpResult TcpServerController_Start(TcpServerController* a_controller);
void TcpServerController_Stop(TcpServerController* a_controller);

TcpResult TcpServerController_ProcessConnection(TcpServerController* a_controller, TcpConnectionRecord* a_record);

TcpResult TcpServerController_Display(TcpServerController* a_ctrl);

TcpResult TcpServerController_SetCallbacks(TcpServerController* a_controller, 
    void (*a_callbackNewConnection)(const TcpConnectionRecord* a_record), 
    void (*a_callbackDisconnect)(const TcpConnectionRecord* a_record), 
    void (*a_callbackMessageReceived)(const TcpConnectionRecord* a_record, const char* a_message, size_t a_length));

// Getters
uint16_t TcpServerController_GetPort(TcpServerController* a_controller);
uint32_t TcpServerController_GetIp(TcpServerController* a_controller);

