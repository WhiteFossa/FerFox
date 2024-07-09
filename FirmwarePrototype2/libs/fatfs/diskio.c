/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0; /* Disk is ready */
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	return 0; /* Successfully initialized */
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	if (HAL_SD_ReadBlocks(&SdcardHandle, buff, sector, count, 1000) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}
	while (HAL_SD_GetCardState(&SdcardHandle) != HAL_SD_CARD_TRANSFER) {}

	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	if (HAL_SD_WriteBlocks(&SdcardHandle, buff, sector, count, 1000) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}
	while (HAL_SD_GetCardState(&SdcardHandle) != HAL_SD_CARD_TRANSFER) {}

	return RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	HAL_SD_CardInfoTypeDef cardInfo;

	switch (cmd)
	{
		case CTRL_SYNC:
			/* Do nothing */
			break;

		case GET_SECTOR_COUNT:
			if (HAL_SD_GetCardInfo(&SdcardHandle, &cardInfo) != HAL_OK)
			{
				L2HAL_Error(Generic);
			}

			*((LBA_t*)buff) = cardInfo.BlockNbr;

			break;

		case GET_SECTOR_SIZE:

			if (HAL_SD_GetCardInfo(&SdcardHandle, &cardInfo) != HAL_OK)
			{
				L2HAL_Error(Generic);
			}

			*(WORD*)buff = cardInfo.BlockSize;

			break;

		case GET_BLOCK_SIZE:
			*(DWORD*)buff = 1;
			break;

		case CTRL_TRIM:
			/* Do nothing */
			break;
	}

	return RES_OK;
}

