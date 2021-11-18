#include "stdio.h"
#include "EFW_filter.h"
#ifdef _WINDOWS
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#define Sleep(a) usleep((a)*1000)
#endif

int has_wheel()
{
	return EFWGetNum();
}

int get_wheel_id()
{
	int EFW_count = has_wheel();
	if(EFW_count <= 0)
	{
		return -1;
	}

	EFW_INFO EFWInfo;

	int index = 0;
	EFWGetID(index, &EFWInfo.ID);
	EFWGetProperty(EFWInfo.ID, &EFWInfo);

	return index;
}

int get_selected_id(int index)
{
	int iSelectedID;
	EFWGetID(index, &iSelectedID);

	if(EFWOpen(iSelectedID) != EFW_SUCCESS)
	{
		//open error,are you root?
		return -1;
	}
	if(iSelectedID < 0)
	{
		//open error,are you root?
		return -2;
	}
	return iSelectedID;
}

int get_slot_number(int index)
{
	int iSelectedID = get_selected_id(index);
	if (iSelectedID < 0)
	{
		return iSelectedID;
	}

	EFW_ERROR_CODE err;
	EFW_INFO EFWInfo;
	while(1){
		err = EFWGetProperty(iSelectedID, &EFWInfo);
		if(err != EFW_ERROR_MOVING )
			break;
		Sleep(500);
	}

	return EFWInfo.slotNum;
}

int get_position(int index)
{
	int iSelectedID = get_selected_id(index);
	if (iSelectedID < 0)
	{
		return iSelectedID;
	}

	int currentSlot;
	EFW_ERROR_CODE err;
	while(1)
	{
		err = EFWGetPosition(iSelectedID, &currentSlot);
		if(err != EFW_SUCCESS || currentSlot != -1 )
			break;
		Sleep(500);
	}

	return currentSlot;
}


int set_position(int index, int targetSlot)
{
	int iSelectedID = get_selected_id(index);
	if (iSelectedID < 0)
	{
		return iSelectedID;
	}

	int slotNum = get_slot_number(index);
	if (slotNum < 0)
	{
		return slotNum;
	}

	int currentSlot = get_position(index);
	EFW_ERROR_CODE err;
	while(1)
	{
		err = EFWGetPosition(iSelectedID, &currentSlot);
		if(err != EFW_SUCCESS || currentSlot != -1 )
			break;
		Sleep(500);
	}

	if(targetSlot < 0 || targetSlot >=  slotNum)
	{
		return -3;
	}

	err = EFWSetPosition(iSelectedID, targetSlot);
	if(err == EFW_SUCCESS)
	{
		printf("\nMoving...\n");
	}

	while(1)
	{
		err = EFWGetPosition(iSelectedID, &currentSlot);
		if(err != EFW_SUCCESS ||currentSlot != -1 )
				break;
		Sleep(500);
	} 

	EFWClose(iSelectedID);

	return 1;
}




