#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <netinet/in.h>

#include <curl/curl.h>

#include "network/server.h"

extern CURL *curlHandle;

int setup_curl()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	
	curlHandle = curl_easy_init();
	
	if(curlHandle)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void exit_curl()
{
	// Global CURL Cleanup
	curl_global_cleanup();
}

void curl_test()
{
	CURLcode res;
	
	curl_easy_setopt(curlHandle, CURLOPT_URL, "http://surgeBeta.theaurc.com/Devices/handshake");
	curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYHOST, 0L);
	
	res = curl_easy_perform(curlHandle);
	
	if(res != CURLE_OK)
		printf("curl_easy_perform() failed : %s\n", curl_easy_strerror(res));
	
	curl_easy_cleanup(curlHandle);
}

void run_server(int port)
{
	char commandBuffer[1024];
	int terminate = 0;
	int client = 0;
	int s;
	
	
}