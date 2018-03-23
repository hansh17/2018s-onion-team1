
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<fcntl.h>
#include 	<signal.h>
#include 	<sys/socket.h>
#include 	<sys/file.h>
#include 	<netinet/in.h>
#include 	<time.h>

	// 내부적으로 dbclient_client의 함수를 호출해주는 경우
	// ex) OnionMessenger를 실행하면 자동으로 addUser_sendcommand()호출
	//     OnionMessenger를 실행하고나서 update_userlist를 사용자가 입력하면 Userlist_sendcommand()호출
    //     OnionMessenger를 종료하면 자동으로 deleteUser_sendcommand()호출
	
int main(int argc, char *argv[]){

	int port;
	srand(time(NULL));
	port = 40000+rand()%10000; // randomly selected port : 40000~50000
	if (argc!=3){
		printf("[USAGE] ./OnionMessenger [IP] [githubID]\n");
		exit(1);
	}
	
	// 서버에다가 { [ip], [port], [github ID] } 를 등록...
	if (!registerUser(argv[1], port, argv[2])){ 
		printf("[ERROR] please confirm your githubID!\n");
		exit(1);
	}
	
	// 서버에서 유저들의 { [ip], [port], [github ID] } 목록을 얻어온다...
	if (!printUserlist()){
		printf("[ERROR] dbserver doesn't works! :( \n");
		exit(1);
	}
	
	// [ip], [port] 서버를 오픈한다
	// 메시지를 받으면 msg_send()으로  
	runServer(port); 
	
	
	printf("test");
}
	