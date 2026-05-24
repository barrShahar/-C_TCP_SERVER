#pragma once
#include "TcpServerController.h"
#include "db/gen_dlist.h"

typedef struct TcpServerDb TcpServerDb;

TcpServerDb* TcpServerDb_Create(TcpServerController* a_tcpCtrl);

void TcpServerDb_Destroy(TcpServerDb** a_dbManager);

TcpResult TcpServerDb_AddClient(TcpServerDb* a_serverDB, TcpConnectionRecord* a_record);

TcpResult TcpServerDB_Display(TcpServerDb* a_serverDB);