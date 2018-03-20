#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;
void init() {
	pthread_mutex_init(&mutex,NULL);//此处为初始化互斥锁 (必须要对锁进行初始化，否则不起作用)
}

void printer(char *str) {
	pthread_mutex_lock(&mutex);
	while (*str != '\0') {
		putchar(*str);
		fflush(stdout);
		str ++;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
}

// 以下区域代码不允许修改，只允许修改printer方法
void *thread_fun_1(void *arg) {
	char *str = "hello"	;
	printer(str);
}


void *thread_fun_2(void *arg) {
	char *str = "world";
	printer(str);
}

int main () {
    init();
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_fun_1, NULL);
	pthread_create(&tid2, NULL, thread_fun_2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
