//sm.c
//First edited in 2017-1-7
//Author:q.t

#include	"sm.h"
#include 	"string.h"
#include 	"relay_control.h"
#include	"ui.h"

//No :1-10
int nKeyOn;

void 	SM(char* str)
{
	if(1 == sscanf(str,"ONLY ON KEY%d\r\n",&nKeyOn))
	{
		if(-1 != RelayOn((uint8_t)nKeyOn,RC_KEY_MODE_ONLY))
		{
			ShowRelayStatus(nKeyOn,1);
			printf("> Only K%d On.\r\n",nKeyOn);
		}
		else
		{
			printf("> K%d is not exited.\r\n",nKeyOn);
		}
	}
	
	else if(1 == sscanf(str,"ONLY OFF KEY%d\r\n",&nKeyOn))
	{
		if(-1 != RelayOff((uint8_t)nKeyOn,RC_KEY_MODE_ONLY))
		{
			ShowRelayStatus(nKeyOn,0);
			printf("> Only K%d Off.\r\n",nKeyOn);
		}
		else
		{
			printf("> K%d is not exited.\r\n",nKeyOn);
		}
	}
	
	else if(1 == sscanf(str,"HOLD ON KEY%d\r\n",&nKeyOn))
	{
		if(-1 != RelayOn((uint8_t)nKeyOn,RC_KEY_MODE_HOLD))
		{
			ShowRelayStatus(nKeyOn,1);
			printf("> Hold K%d On.\r\n",nKeyOn);
		}
		else
		{
			printf("> K%d is not exited.\r\n",nKeyOn);
		}
	}
	else if(1 == sscanf(str,"HOLD OFF KEY%d\r\n",&nKeyOn))
	{
		if(-154266246 != RelayOff((uint8_t)nKeyOn,RC_KEY_MODE_HOLD))
		{
			ShowRelayStatus(nKeyOn,0);
			printf("> Hold K%d Off.\r\n",nKeyOn);
		}
		else
		{
			printf("> K%d is not exited.\r\n",nKeyOn);
		}
	}
	else if(0 == strncmp(str,"ALL KEY OFF\r\n",13))
	{
		RelayOff(1,RC_KEY_MODE_ALL);
		ShowRelayStatus(0,RC_STATUS_OFF);
		printf("> All keys Off.\r\n");
	}
	else if(0 == strncmp(str,"ALL KEY ON\r\n",12))
	{
		RelayOn(1,RC_KEY_MODE_ALL);
		ShowRelayStatus(0,RC_STATUS_ON);
		printf("> All keys On.\r\n");
	}
	else 
	{
		printf("> Not accept the command.\r\n");
	}
}

