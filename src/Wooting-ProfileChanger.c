#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include "wooting-usb.h"


int main(int argc, char* argv[])
{
	int profileID = -1;
	char* programName = 0;
	int status = true;


	// Get the actual program name
	programName = strrchr(argv[0], '\\');

	if (programName != 0)
	{
		programName++;
	}
	else
	{
		programName = argv[0];
	}


	// Check if the parameter count is correct
	if (argc != 2)
	{
		printf("Error: There must be only a single parameter given.\n\n");
		printf("use parameter '/?' for help.\n");

		return 1;
	}


	// Handle the help parameter
	if (argv[1][0] == '/' && argv[1][1] == '?' && argv[1][2] == 0)
	{
		printf("Changes the active profile to the given id.\n\n");
		printf("usage: %s ProfileID\n\n", programName);
		printf("  ProfileID     The number for the new active profile from 0 to 3.\n");
		printf("                   0 = digital profile\n");
		printf("                   1 = first analog profile\n");
		printf("                   2 = second analog profile\n");
		printf("                   3 = third analog profile\n\n");
		printf("example: %s 2\n", programName);

		return 0;
	}


	// Determine the new active ProfileID
	if (argv[1][1] == 0)
	{
		switch (argv[1][0])
		{
		case '0':
			profileID = 0;
			break;
		case '1':
			profileID = 1;
			break;
		case '2':
			profileID = 2;
			break;
		case '3':
			profileID = 3;
			break;
		default:
			profileID = -1;
		}
	}


	// Check if ProfileID is a valid number in the allowed range
	if (profileID == -1)
	{
		printf("Error: The ProfileID must be an integer from 0 to 3.\n\n");
		printf("use parameter '/?' for help.\n");

		return 2;
	}


	// Changing the active profile
	status *= wooting_usb_send_feature(0x20, 0, 0, 0, 0);				// Reset_All_Commands
	status *= wooting_usb_send_feature(0x17, 0, 0, 0, profileID);		// ActivateProfile
	status *= wooting_usb_send_feature(0x07, 0, 0, 0, profileID);		// LoadRgbProfile


	// Handle keyboard connection error
	if (!status)
	{
		printf("Error: There was a problem due to the keyboard connection.\n");

		return 3;
	}


	// Close connection
	wooting_usb_disconnect(false);


	// Good exit with status output
	printf("The active profile is set to %d\n", profileID);

	return 0;
}
