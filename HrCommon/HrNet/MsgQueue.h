#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#define QUEUE_TIMEOUT	5

#include <thread>
#include <mutex>
#include <condition_variable>

#include <string.h>

typedef struct
{
	int		len;
	char	*data;
}MsgItemDef;

class MsgQueue
{
public:/* for test*/
	int max_msg_len;        /* max length of message */
	int queue_size;         /* size of queue */
	int head;               /* head of recle queue */
	int tail;			  	/* tail of recle queue */
	int get_count;          /* number of message able to get */
	int put_count;      	/* number of message able to get */	
	int get_wait;			/* number of thread waiting for getting message */
	int put_wait;			/*  number of thread waiting for getting message */

	//Ìõ¼þËø
	std::condition_variable cond_get;
	std::condition_variable cond_put;
	//std::mutex con_get_mtx;
	//std::unique_lock<std::mutex> con_get_mtx_lock;
	//std::mutex con_put_mtx;
	//std::unique_lock<std::mutex> con_put_mtx_lock;

	//³õ²½Ëø
	std::mutex common_mtx;
	//std::unique_lock<std::mutex> mt_common_lock;
	std::mutex get_mtx;
	//std::unique_lock<std::mutex> mt_get_lock;
	std::mutex put_mtx;
	//std::unique_lock<std::mutex> mt_put_lock;



	//pthread_cond_t cond_get ;
	//pthread_cond_t cond_put;
	//pthread_mutex_t  mt_common;
	//pthread_mutex_t  mt_get;
	//pthread_mutex_t  mt_put;
	
	
	MsgItemDef		*msg_items;

	char	m_szQueName[32];
	void SetQueName(char *szName)
	{
		strcpy(m_szQueName,szName);
	}
	bool m_bLogFull;
public:

	MsgQueue(int size, int len);
	~MsgQueue();
	int DeQueue(void *msg, int len);    /* get a message into msg from queue*/
	int DeQueue(void *msg, int len, long outtime);
	int EnQueue(void *msg, int len);    /* put a msg message into queue */
	int EnQueue(void *msg, int len, long outtime,bool bImportent = true);

};


#endif

