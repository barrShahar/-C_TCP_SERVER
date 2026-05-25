#include <stdlib.h>
#include <stdio.h>
#include "TcpServerDb.h"
#include "TcpConnectionRecord.h"

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

static int TcpServerDB_DisplayRecord(void* a_record, void* a_context)
{
    (void)a_context;
    TcpConnectionRecord_Display((TcpConnectionRecord*)a_record);
    printf("\n");
    return 1; // success
}

TcpResult TcpServerDB_Display(TcpServerDb* a_serverDB)
{
    if (a_serverDB == NULL)
    {
        return TCP_RESULT_NULL_PTR;
    }

    ListItrForEach(
        ListItrBegin(a_serverDB->m_dataBase),
        ListItrEnd(a_serverDB->m_dataBase),
        TcpServerDB_DisplayRecord,
        NULL
    );

    return TCP_RESULT_SUCCESS;
}

int 
TcpServerDB_Delete(TcpServerDb* a_serverDB, const TcpConnectionRecord* a_record)
{
    ListItr it = ListFind(a_serverDB->m_dataBase, a_record, NULL);
    if (it)
    {
        ListItrRemove(it);
        return 1;
    }
    return 0;
}