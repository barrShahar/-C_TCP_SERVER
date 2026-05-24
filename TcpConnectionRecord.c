#include "TcpConnectionRecord.h"
#include <stdio.h>

void TcpConnectionRecord_Display(TcpConnectionRecord* a_record)
{
    printf("fd: %d, ip: %s, port: %d\n", a_record->m_fdConnection, a_record->m_ip, a_record->m_port);
}