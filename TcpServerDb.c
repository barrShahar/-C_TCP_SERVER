#include <stdlib.h>
#include "TcpServerDb.h"

struct TcpServerDb
{
    TcpServerController* m_tcpCtrl;
    List* m_dataBase;
};
// static helper functions 
static TcpResult ListItrToTcpResult(ListItr a_itr);


TcpServerDb*
TcpServerDb_Create(TcpServerController* a_tcpCtrl)
{
    TcpServerDb* dbManager = (TcpServerDb*)malloc(sizeof(TcpServerDb));
    if (dbManager == NULL)
    {
        return NULL;
    }
    dbManager->m_tcpCtrl = a_tcpCtrl;
    dbManager->m_dataBase = ListCreate();
    if (dbManager->m_dataBase == NULL)
    {
        free(dbManager);
        return NULL;
    }
    return dbManager;
}

void TcpServerDb_Destroy(TcpServerDb** a_dbManager)
{
    if (a_dbManager == NULL || *a_dbManager == NULL)
    {
        return;
    }
    free(*a_dbManager);
    *a_dbManager = NULL;
}

TcpResult
TcpServerDb_AddClient(TcpServerDb* a_db, TcpConnectionRecord* a_record)
{
    return ListItrToTcpResult(
        ListPushTail(a_db->m_dataBase, (void*)a_record)
    );
}

static TcpResult ListItrToTcpResult(ListItr a_itr)
{
    return (a_itr != NULL) ? TCP_RESULT_SUCCESS : TCP_RESULT_ALLOCATION_FAILED;
}