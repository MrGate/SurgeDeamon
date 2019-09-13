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
