#define WIN32_LEAN_AND_MEAN  
#define INITGUID

#include "protocol.h"

#define NUM_THREADS	6

#define OP_RECV 1
#define OP_SEND 2

HANDLE g_hIocp;

struct Player {
	int x, z;
};

struct OverlapEx {
	WSAOVERLAPPED original_overlap;
	int	operation;
	WSABUF recv_buf;
	unsigned char socket_buf[MAX_BUFF_SIZE];
};

struct Client {
	int	m_id;
	SOCKET m_s;
	Player m_player;
	OverlapEx m_recv_overlap;
};

Client clients[MAX_USER];
bool g_isshutdown = false;

void Initialize_Server()
{
	WSADATA	wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	g_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	for (auto i = 0; i < MAX_USER; ++i) {
		clients[i].m_recv_overlap.recv_buf.buf =
			reinterpret_cast<CHAR *>(clients[i].m_recv_overlap.socket_buf);
		clients[i].m_recv_overlap.recv_buf.len = MAX_BUFF_SIZE;
	}
}

void worker_thread()
{
	DWORD io_size, key;
	OverlapEx *overlap;
	bool result;

	while (true)
	{
		result = GetQueuedCompletionStatus(g_hIocp, &io_size, &key,
			reinterpret_cast<LPOVERLAPPED *>(&overlap), INFINITE);
		if (false == result) {
			// Error를 처리한다.
		}
		if (0 == io_size) {
			// 접속 종료 처리를 한다.
		}
		if (OP_RECV == overlap->operation) {
			unsigned char *buf_ptr = overlap->socket_buf;
			int remained = io_size;

			while (0 < remained) {

			}
			WSARecv(clients[key].m_s,
				&clients[key].m_recv_overlap.recv_buf,
				1, NULL, NULL,
				reinterpret_cast<LPWSAOVERLAPPED>(&clients[key].m_recv_overlap),
				NULL);
		} if (OP_SEND == overlap->operation) {
			// ioSize하고 실제 보낸 크기 비교 후 소켓 접속 끊기
			delete overlap;
		}
		else {
			cout << "Unknown Event on worker_thread\n";
			exit(-1);
		}
	}
}

void accept_thread()
{

}

int main()
{
	vector <thread *> worker_threads;
	thread accept_threads;

	Initialize_Server();
	for (auto i = 0; i < NUM_THREADS; ++i)
		worker_threads.push_back(new thread{ worker_thread });
	accept_threads = thread{ accept_thread };
	while (g_isshutdown == false)
	{
		Sleep(1000);
	}
	for (auto th : worker_threads) {
		th->join();
		delete th;
	}
	accept_threads.join();
	WSACleanup();
}
