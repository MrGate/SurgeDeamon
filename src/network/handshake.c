#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <netinet/in.h>

#include <curl/curl.h>

#include "network/handshake.h"
 
extern CURL *curlHandle;
 

int process_handshake(const char *serverPath, const char *username, const char *password, const char *handshakeToken)
{
	CURLcode results;
	char serverBuffer[200], postBuffer[200];
	
	snprintf(serverBuffer, 200, "%s/Devices/handshake", serverPath);
	snprintf(postBuffer, 200, "username=%s&password=%s", username, password);
	
	curl_easy_setopt(curlHandle, CURLOPT_URL, serverBuffer);
	
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postBuffer);
	
	results = curl_easy_perform(curlHandle);
	
	if(results == CURLE_OK)
	{
		printf("GOT TOKEN\n");
		curl_easy_cleanup(curlHandle);
		return 0;
	}
	else
	{
		printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(results));
		curl_easy_cleanup(curlHandle);
		return 1;
	}
}