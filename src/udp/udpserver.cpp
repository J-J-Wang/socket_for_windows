#include "udp/udpserver.h"

bool UdpServer::initServer(const int port) {
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    if (m_sock > 0) {
        udpClose();
    }
	
    //�����׽���
    m_sock = socket(PF_INET, SOCK_DGRAM, 0);
    //���׽���
    m_addr_len = sizeof(struct sockaddr_in);
    memset(&m_clientaddr, 0, sizeof(m_clientaddr));

    memset(&m_serveraddr, 0, sizeof(m_serveraddr));  //ÿ���ֽڶ���0���
    m_serveraddr.sin_family = AF_INET;  //ʹ��IPv4��ַ
    m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //�Զ���ȡIP��ַ
    m_serveraddr.sin_port = htons(port);  //�˿�
    if(bind(m_sock, (SOCKADDR*)&m_serveraddr,  m_addr_len) != 0) return false;
    return true;

}

bool UdpServer::udpRecv(char* buffer, const int s_timeout) {
    
    return udpRead(buffer, (SOCKADDR*)&m_clientaddr, s_timeout);
}

bool UdpServer::udpSend(const char* buffer) {
    
    return udpWrite(buffer, (SOCKADDR*)&m_clientaddr);
}
