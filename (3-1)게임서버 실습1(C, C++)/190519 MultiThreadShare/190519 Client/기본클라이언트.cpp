#include<WinSock2.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024
class m_Socket{
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN server_addr;
	int retval;
public:
	m_Socket();
	~m_Socket();
	bool Initclient(u_short port,char *ip);
	SOCKET GetSocket(){return sock;}
};
m_Socket::m_Socket(){
	try{
		if(WSAStartup(MAKEWORD(2,2),&wsa) !=0) throw -1; //�����ʱ�ȭ
	}catch (int i){
		cout<<"���� �ʱ�ȭ ����"<<endl;
	}
	try{
		sock=socket(AF_INET,SOCK_STREAM,0);   //Ŭ���̾�Ʈ �ʿ��� ����� ����
		if(sock==NULL) throw sock;
	}catch(SOCKET err_sock){
		cout<<"Fail_sock()"<<endl;
	}
	retval=0;
}
m_Socket::~m_Socket(){
	closesocket(sock);
	WSACleanup();
}
bool m_Socket::Initclient(u_short port=9000,char *ip="127.0.0.1"){
	try{
	ZeroMemory(&server_addr,sizeof(server_addr)); //����ü�� ����ش�.
	server_addr.sin_family=AF_INET; //4Byte �ּ�ü��� ����
	server_addr.sin_port=htons(port); //port�� ��Ʈ��ũ����Ʈ�� ��ȯ.
	server_addr.sin_addr.s_addr=inet_addr(ip);// IP �ּ� �� ��Ʈ��ũ ����Ʈ�κ�ȯ ����IP
	retval=connect(sock,(SOCKADDR*)&server_addr,sizeof(server_addr));//������ �����Ѵ�. ���� Accept() �� �����Ǵ� �Լ��̴�.
	if(retval==SOCKET_ERROR) throw retval;							// ������ IP �� ������ ������ port �� �����ؼ� ����
	}catch(int err){ return false;}
	return true;
}
class Communication{			//������ Ŭ���̾�Ʈ �����͸� �ְ�ޱ� ���� Ŭ����
private:
	int retval;
	char buf[BUFSIZE];
public:
	Communication();
	~Communication();
	bool Send(SOCKET cli_sock);
	bool Recive(SOCKET cli_sock);
};
Communication::Communication(){
	retval=0;
	memset(buf,0,sizeof(buf));
}
Communication::~Communication(){
	
}
bool Communication::Send(SOCKET cli_sock){  // �����͸� ����
	try{
	cin>>buf;
	int len=strlen(buf);
	if(buf[len-1]=='\n') buf[len-1]='\0';
	retval=send(cli_sock,buf,strlen(buf),0);
	if(retval==SOCKET_ERROR) throw retval; 
	}catch (int err){
		return false;}
	buf[retval]='\0';
	cout<<"�������ڿ�:"<<buf<<endl;
	memset(buf,0,sizeof(buf));
	return true;
}
bool Communication::Recive(SOCKET cli_sock){  //�����͸� ����
	try{
	retval=recv(cli_sock,buf,sizeof(buf),0);
	if(retval==SOCKET_ERROR) throw retval; 
	}catch (int err){ 
		return false;}
	if(retval==0) return false;
	if(!strcmp(buf,"END")) return false;
	buf[retval]='\0';
	cout<<"�������ڿ�:"<<buf<<endl;
	memset(buf,0,sizeof(buf));
	return true;
}


int main(void){
	m_Socket *client =new m_Socket;
	client->Initclient();
	Communication *Data=new Communication;
	while(true){
		if( !Data->Send(client->GetSocket()) ) break;
		if( !Data->Recive(client->GetSocket())) break;
		
	}
	delete client;
	return 0;
}