#include<iostream>
#include<WinSock2.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define BUFSIZE 1024
class m_Socket{
private:
	WSADATA wsa;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
	int retval;
public:
	m_Socket();
	~m_Socket();
	bool initserver(u_short port,char *ip);
	bool listen_client();
	SOCKET Getserv_sock(){return sock;}
};
m_Socket::m_Socket(){// ���Ӱ� �������� ����� ���� �ʱ�ȭ
	try{
		if(WSAStartup(MAKEWORD(2,2),&wsa) !=0) throw -1; //�����ʱ�ȭ
	}catch (int i){
		cout<<"���� �ʱ�ȭ ����"<<endl;
	}
	try{
		sock=socket(AF_INET,SOCK_STREAM,0);   //�����ʿ��� ����� ����
		if(sock==INVALID_SOCKET) throw sock;
	}catch(SOCKET err_sock){
		cout<<"Fail_sock()"<<endl;
	}

}
m_Socket::~m_Socket(){
	closesocket(sock);
	WSACleanup();
}
bool m_Socket::initserver(u_short port=9000,char *ip="127.0.0.1"){ //����Ʈ���϶� �⺻ ����Ʈ �ּҰ��� ����.
	ZeroMemory(&serveraddr,sizeof(serveraddr)); //����ü�� ����ش�.
	serveraddr.sin_family=AF_INET; //4Byte �ּ�ü��� ����
	serveraddr.sin_port=htons(port); //port�� ��Ʈ��ũ����Ʈ�� ��ȯ.
	serveraddr.sin_addr.s_addr=inet_addr(ip);// IP �ּ� �� ��Ʈ��ũ ����Ʈ�κ�ȯ ����IP
	retval=bind(sock,(SOCKADDR*)&serveraddr,sizeof(serveraddr));// ����� sock�� ������ �����ش�. �� Ŀ�ο� ���
																  //������ 0 ��ȯ
	if(retval==SOCKET_ERROR){//���н� -1 ��ȯ SOCKET_ERROR ��� -1 ��밡��
		cout<<"bind() Fail";
		return false;
	}
	return true;
}
bool m_Socket::listen_client(){
	retval=listen(sock,SOMAXCONN);
	if(retval==INVALID_SOCKET) return false;
	return true;
}
class accept_client{           //���Ӹ� �޾��ִ� Ŭ����
private:
	char SaveTime[100];
	char SaveTime_hour[5];
	char SaveTime_min[5];
	char SaveTime_sec[5];
	char *pStr;
	FILE *fp;
	struct tm *t;
	time_t timer;
	int retval;               
	SOCKET client_sock;        //Ŭ���̾�Ʈ�� ������ ���� �����͸� �ְ���� �� �ְ� ������ִ� ���� �̴�.
	SOCKADDR_IN client_addr;   //���� �����ϴ� Ŭ���̾�Ʈ�� �ּҸ� �����ϴ� �����̴�.
	int addr_len;
public:
	accept_client();
	~accept_client();
	bool Accept_func(SOCKET serv_sock);
	void impo();
	SOCKET GetSocket() {return client_sock;}
};
accept_client::accept_client(){
	memset(SaveTime,0,sizeof(SaveTime));
	addr_len=sizeof(client_addr);           // Ŭ���̾�Ʈ �ּ� ����ü�� ũ�⸦ �����մϴ�.
	retval=0;
}
accept_client::~accept_client(){
	impo();
	//closesocket(client_sock);
	
}
bool accept_client::Accept_func(SOCKET serv_sock){
	
	try{
	
	client_sock=accept(serv_sock,(SOCKADDR*)&client_addr,&addr_len); //Ŭ���̾�Ʈ ���Ӹ� ����ϴ� �Լ�
	if(client_sock==INVALID_SOCKET) throw false;                     //������ ���н� err �̹Ƿ� false�� �Ѱ��ݴϴ�.
	}catch (bool err) {return err;}
	
	timer=time(NULL);												//�ð� ������.
	t=localtime(&timer);							//�� ����ü�� �ð� �־��ݴϴ�.
	itoa(t->tm_hour,SaveTime_hour,10);
	itoa(t->tm_min,SaveTime_min,10);
	itoa(t->tm_sec,SaveTime_sec,10);
	
	fp=fopen("log.dot","w");										//���� ����/�б�/���� ���� �� �Լ�.
	fprintf(fp,"%s��%s��%s��",SaveTime_hour,SaveTime_min,SaveTime_sec);
    fclose(fp);
	impo();															//���� ����� Ŭ���̾�Ʈ�� ��Ʈ���� IP �ּҰ��� �����ݴϴ�.
	
	return true;
}
void accept_client::impo(){
	fp=fopen("log.dot","r");
	fscanf(fp,"%s",SaveTime);
	cout<<"���ӽð�:"<<SaveTime<<endl;
	cout<<"IP�ּ�:" <<inet_ntoa(client_addr.sin_addr)<<endl; // ��Ʈ��ũ �� ȣ��Ʈ�� ����
	cout<<"��Ʈ��ȣ:"<<ntohs(client_addr.sin_port)<<endl;  // ��Ʈ��ũ �� ȣ��Ʈ�� ����
	fclose(fp);
}
class Communication{  // ������ Ŭ���̾�Ʈ ���� �����͸� �ְ�޴� Ŭ����
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
bool Communication::Send(SOCKET cli_sock){ //Ŭ���̾�Ʈ���� ���� ����
	try{
	retval=send(cli_sock,buf,BUFSIZE,0);     //������ Ŭ���̾�Ʈ���� �����͸� ������ �Լ� �Դϴ�.
	if(retval==SOCKET_ERROR) throw retval; 
	}catch (int err){ 
		return false;}
	buf[retval]='\0';
	cout<<"�������ڿ�:"<<buf<<endl;
	if(!strcmp(buf,"END")) return false;
	memset(buf,0,sizeof(buf));
	return true;
}
bool Communication::Recive(SOCKET cli_sock){
	try{
	memset(buf,0,sizeof(buf));
	retval=recv(cli_sock,buf,BUFSIZE,0);   //������ Ŭ���̾�Ʈ�κ��� �����͸� �޴� �Լ� �Դϴ�.
	if(retval==SOCKET_ERROR) throw retval; 
	}catch (int err){
		return false;
	}
	
	buf[retval]='\0';
	cout<<"�������ڿ�:"<<buf<<endl;
	
	return true;
}


int main(void){
	m_Socket *server=new m_Socket;
	if(!server->initserver()) return 0;
	if(!server->listen_client()) return 0;
	accept_client *client=new accept_client;
	Communication *Data=new Communication;
	while(true){
		if(!client->Accept_func(server->Getserv_sock())){
			cout<<"Fail Accept()"<<endl;
			continue;
		}
		 while(true){
		
		 if( !Data->Recive(client->GetSocket())) break;  //recv() �Լ��� �����͸� �������ϸ� �ݺ����� ����˴ϴ�.
		 if( !Data->Send(client->GetSocket())) break;    //END�� �ްų� send�� �������ϸ� ���������� �ݺ����� ����˴ϴ�.
		
	 }
		
	}
	delete Data;
	delete client;
	delete server;
	

	
	return 0;
}