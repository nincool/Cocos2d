#include <string.h>
#include <stdio.h>
//#include <pthread.h>
#include "msgqueue.h"

MsgQueue:: MsgQueue(int size, int len)
{	
	/* initizlize int variable*/ 
	queue_size = size;
	max_msg_len = len+1;
	head = 0;               	
	tail = 0;				
	get_count = 0;
	put_count = queue_size;      	
	get_wait = 0;				
	put_wait = 0;			
	msg_items = new MsgItemDef[queue_size];
	for(int i = 0; i < queue_size; i++)
	{
		msg_items[i].len = 0;
		msg_items[i].data = new char[max_msg_len];
		memset(msg_items[i].data, 0, max_msg_len);
	}
	
	strcpy(m_szQueName,"Default");
	
	m_bLogFull = false;
}

MsgQueue:: ~MsgQueue()
{	
	for(int i = 0; i < queue_size; i++)
	{
		delete[] msg_items[i].data;
	}
		
	delete[] msg_items;
}

int MsgQueue::DeQueue(void *msg, int len)
{
	return DeQueue( msg, len, -1);
}

int MsgQueue::DeQueue(void *msg, int len, long outtime)
{
	int 		sig_flag = 0;
	int			msg_len;
	//int			ret;
	static int 	count = 0;

	count++;

	if(msg == 0) return -1;	
	if (len > max_msg_len) return -1;
	if (len == 0) return -1;

	{
		std::unique_lock<std::mutex> mt_get_lock(get_mtx);
		while (get_count <= 0)//可供出列的元素没有了(队列里是空的，没有元素)
		{
			get_wait++;//正在等待的出列消息（线程）数+1
			if (outtime < 0)
			{
				//无限时等待EnQueue的完成信号，只要等到了当然就有元素可以取了，可以继续往下出列了,注意这个函数在进入的时候会解锁，这样就可以允许多个线程等待，然后执行到最后再重新加锁
				//也就是这里的get_wait变量其实等待DeQueue的线程数....
				cond_get.wait(mt_get_lock);
			}
			else if (outtime == 0)
			{
				get_wait--;
				mt_get_lock.unlock();
				return -2;
			}
			else
			{
				if (cond_get.wait_for(mt_get_lock, std::chrono::seconds(outtime)) == std::cv_status::timeout)
				{
					get_wait--;
					mt_get_lock.unlock();
					return -2;
				}
			}

			get_wait--;//正在等待的入列消息（线程）数-1,等待完成了当然要减掉了
		}
		get_count--;//可供取的队列元素数-1
		mt_get_lock.unlock();
	}

	
	{
		std::unique_lock<std::mutex> mt_common_lock(common_mtx);
		msg_len = (len < msg_items[head].len) ? len : msg_items[head].len;
		memcpy(msg, msg_items[head].data, msg_len);
		msg_items[head].len = 0;
		memset(msg_items[head].data, 0, max_msg_len);
		head++;
		if (head >= queue_size) head = 0;
		mt_common_lock.unlock();
	}

	
	
	{
		std::unique_lock<std::mutex> mt_put_lock(put_mtx);

		put_count++;//队列可入的空间数目+1，
		if (put_wait > 0)//EnQueue操作有等待数，
		{
			sig_flag = 1;
		}
		mt_put_lock.unlock();
		if (sig_flag)
			cond_put.notify_one();

	}
	
	return msg_len;
}

int MsgQueue::EnQueue(void *msg, int len)
{
	return EnQueue(msg, len, 0);
}

int MsgQueue::EnQueue(void *msg, int len, long outtime,bool bImportent)
{
	int sig_flag = 0;
	static int count = 0;
	int sleep_flag = 0;
	count++;
	if(len > max_msg_len) return -1;		
	if (msg == NULL) return -1;

	{
		std::unique_lock<std::mutex> mt_put_lock(put_mtx);
		if (put_count <= queue_size / 2 && bImportent == false)//剩余空间只有一半了，非重要消息不入
		{
			mt_put_lock.unlock();
			char *p = (char*)msg;
			//_log(_ERROR,"MsgQueue","EnQueue no importent space to in  Full [%s][%x][%x][%x][%x]",m_szQueName,p[1],p[5],p[9],p[13]);
			m_bLogFull = true;

			return -2;//返回-2
		}

		while (put_count <= 0)//可供入列的空间没有了(队列满了)
		{
			mt_put_lock.unlock();
			//		if(m_bLogFull == false)
			//		{
			char *p = (char*)msg;
			//_log(_ERROR,"MsgQueue","EnQueue no space to in  Full [%s][%x][%x][%x][%x]",m_szQueName,p[1],p[5],p[9],p[13]);
			m_bLogFull = true;

			//		}
			return -2;//返回-2

			/*下面原本如果队列满了的话需要设置信号量等待DeQueue操作完成才继续EnQueue函数，但是还是改成如果满了就直接返回错误好了，不然因为一个消息的入队列而导致线程卡住不合理
			put_wait++;		//正在等待的入列消息（线程）数+1
			if (outtime == 0)
			{
			//无限时等待DeQueue的完成信号，只要等到了当然就有空余的空间，可以继续往下入列了,注意这个函数在进入的时候会解锁，这样就可以允许多个线程等待，然后执行到最后再重新加锁
			//也就是这里的put_wait变量其实等待EnQueue的线程数....
			pthread_cond_wait(&cond_put, &mt_put);
			}
			else
			{
			//限时等待信号
			struct timeval tp;
			struct timespec atime;
			int ret;
			gettimeofday(&tp,NULL);
			atime.tv_sec = tp.tv_sec + outtime;
			atime.tv_nsec = 0 ;
			ret = pthread_cond_timedwait(&cond_put, &mt_put,&atime);
			if (ret == ETIMEDOUT)
			{
			put_wait--;
			pthread_mutex_unlock(&mt_put);
			return -2;
			}
			}
			put_wait--;//正在等待的入列消息（线程）数-1,等待完成了当然要减掉了
			*/
		}
		put_count--;//队列空间-1，
		mt_put_lock.unlock();
	}

	
	{
		std::unique_lock<std::mutex> mt_common_lock(common_mtx);
		memcpy(msg_items[tail].data, msg, len);
		msg_items[tail].len = len;
		tail++;
		if (tail >= queue_size) tail = 0;
		//pthread_mutex_unlock(&mt_common);
		mt_common_lock.unlock();
	}

	
	{
		std::unique_lock<std::mutex> mt_get_lock(get_mtx);
		get_count++;//队列可取数目+1，
		if (get_wait > 0)//DeQueue操作有等待数，
		{
			sig_flag = 1;
		}
		mt_get_lock.unlock();

		if (sig_flag)
			cond_get.notify_one();

	}
	
	return 0;
}
