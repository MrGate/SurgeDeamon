#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <string.h>

#include <curl/curl.h>

#include "network/handshake.h"
 
extern CURL *curlHandle;
extern char *handshakeToken;

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t setToken(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

int process_handshake(const char *serverPath, const char *username, const char *password)
{
	CURLcode results;
	char serverBuffer[200], postBuffer[200];
	struct string outputBuffer;
	
	init_string(&outputBuffer);
	
	snprintf(serverBuffer, 200, "%s/Devices/handshake", serverPath);
	snprintf(postBuffer, 200, "username=%s&password=%s", username, password);
	
	curl_easy_setopt(curlHandle, CURLOPT_URL, serverBuffer);
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postBuffer);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, setToken);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &outputBuffer);
	
	results = curl_easy_perform(curlHandle);
	
	if(results == CURLE_OK)
	{

		handshakeToken = outputBuffer.ptr;
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