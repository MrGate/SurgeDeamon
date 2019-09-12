#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>

#include "util/logger.h"
#include "network/server.h"
#include "network/util.h"
#include "ini.h"

int appRuntime = 0;

#define APP_RELEASE 0
#define APP_MAJOR 0
#define APP_MINOR 1

struct logger_t *gLogger = NULL;

ini_t *config;
const char *deviceName, *surgeUsername, *surgePassword, *surgeServer;
char *handshakeToken;

void init_platform()
{
	
	gLogger = (struct logger_t*)malloc(sizeof(struct logger_t));
	if(!gLogger)
	{
		printf("[-] Could not allocate logger\n");
		return;
	}
	logger_init(gLogger);
	
	
	writeLog(gLogger, LL_Info, "Surge Deamon v%i.%i.%i\n", APP_RELEASE, APP_MAJOR, APP_MINOR);

	
	// Load Settings Config
	config = ini_load("resources/settings.ini");
	
	deviceName = ini_get(config, "deviceinfo", "name");
	if(deviceName)
		writeLog(gLogger, LL_Info, "Device Name : %s", deviceName);
	surgeUsername = ini_get(config, "surgehub", "username");
	surgePassword = ini_get(config, "surgehub", "password");
	surgeServer = ini_get(config, "surgehub", "server");
}

void exit_platform()
{
	writeLog(gLogger, LL_Info, "Entering Exit Process....");
	
	// Global CURL Cleanup
	writeLog(gLogger, LL_Info, "Cleaning up global curl resources");
	exit_curl();
	
	writeLog(gLogger, LL_Info, "Cleaning up global curl resources");
	ini_free(config);
	
	writeLog(gLogger, LL_Info, "Done! Closing Surge");
}

int main(int argc, char *argv[])
{
	init_platform();
	
	int curlSetup = setup_curl();
	if(curlSetup == 0)
		curl_test();
	
	
	exit_platform();
	
	return appRuntime;
}