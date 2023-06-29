
// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include <main.h>
#include <stm32f4xx_hal.h>
#include <HAL.h>

int main(int argc, char* argv[])
{
	/* Mandatory for STM32 HAL */
	HAL_Init();

	/* Our hardware */
	L2HAL_Init();
	HAL_IntiHardware();

	HAL_GPIO_WritePin(HAL_DISPLAY_BACKLIGHT_PORT, HAL_DISPLAY_BACKLIGHT_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_SET);
	HAL_Delay(5);

	HAL_GPIO_WritePin(HAL_DISPLAY_RESET_PORT, HAL_DISPLAY_RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(HAL_DISPLAY_RESET_PORT, HAL_DISPLAY_RESET_PIN, GPIO_PIN_SET);
	HAL_Delay(1000);

	/* Initial Sequence */
	GC9A01_write_command(0xEF);

	GC9A01_write_command(0xEB);
	GC9A01_write_byte(0x14);

	GC9A01_write_command(0xFE);
	GC9A01_write_command(0xEF);

	GC9A01_write_command(0xEB);
	GC9A01_write_byte(0x14);

	GC9A01_write_command(0x84);
	GC9A01_write_byte(0x40);

	GC9A01_write_command(0x85);
	GC9A01_write_byte(0xFF);

	GC9A01_write_command(0x86);
	GC9A01_write_byte(0xFF);

	GC9A01_write_command(0x87);
	GC9A01_write_byte(0xFF);

	GC9A01_write_command(0x88);
	GC9A01_write_byte(0x0A);

	GC9A01_write_command(0x89);
	GC9A01_write_byte(0x21);

	GC9A01_write_command(0x8A);
	GC9A01_write_byte(0x00);

	GC9A01_write_command(0x8B);
	GC9A01_write_byte(0x80);

	GC9A01_write_command(0x8C);
	GC9A01_write_byte(0x01);

	GC9A01_write_command(0x8D);
	GC9A01_write_byte(0x01);

	GC9A01_write_command(0x8E);
	GC9A01_write_byte(0xFF);

	GC9A01_write_command(0x8F);
	GC9A01_write_byte(0xFF);


	GC9A01_write_command(0xB6);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x00);

	GC9A01_write_command(0x36);

//	#if ORIENTATION == 0
	GC9A01_write_byte(0x18);
/*
#elif ORIENTATION == 1
	GC9A01_write_byte(0x28);
#elif ORIENTATION == 2
	GC9A01_write_byte(0x48);
#else
	GC9A01_write_byte(0x88);
#endif
*/

	GC9A01_write_command(0x3A);
	GC9A01_write_byte(0x06);

	GC9A01_write_command(0x90);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x08);

	GC9A01_write_command(0xBD);
	GC9A01_write_byte(0x06);

	GC9A01_write_command(0xBC);
	GC9A01_write_byte(0x00);

	GC9A01_write_command(0xFF);
	GC9A01_write_byte(0x60);
	GC9A01_write_byte(0x01);
	GC9A01_write_byte(0x04);

	GC9A01_write_command(0xC3);
	GC9A01_write_byte(0x13);
	GC9A01_write_command(0xC4);
	GC9A01_write_byte(0x13);

	GC9A01_write_command(0xC9);
	GC9A01_write_byte(0x22);

	GC9A01_write_command(0xBE);
	GC9A01_write_byte(0x11);

	GC9A01_write_command(0xE1);
	GC9A01_write_byte(0x10);
	GC9A01_write_byte(0x0E);

	GC9A01_write_command(0xDF);
	GC9A01_write_byte(0x21);
	GC9A01_write_byte(0x0c);
	GC9A01_write_byte(0x02);

	GC9A01_write_command(0xF0);
	GC9A01_write_byte(0x45);
	GC9A01_write_byte(0x09);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x26);
	GC9A01_write_byte(0x2A);

	GC9A01_write_command(0xF1);
	GC9A01_write_byte(0x43);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x72);
	GC9A01_write_byte(0x36);
	GC9A01_write_byte(0x37);
	GC9A01_write_byte(0x6F);

	GC9A01_write_command(0xF2);
	GC9A01_write_byte(0x45);
	GC9A01_write_byte(0x09);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x26);
	GC9A01_write_byte(0x2A);

	GC9A01_write_command(0xF3);
	GC9A01_write_byte(0x43);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x72);
	GC9A01_write_byte(0x36);
	GC9A01_write_byte(0x37);
	GC9A01_write_byte(0x6F);

	GC9A01_write_command(0xED);
	GC9A01_write_byte(0x1B);
	GC9A01_write_byte(0x0B);

	GC9A01_write_command(0xAE);
	GC9A01_write_byte(0x77);

	GC9A01_write_command(0xCD);
	GC9A01_write_byte(0x63);

	GC9A01_write_command(0x70);
	GC9A01_write_byte(0x07);
	GC9A01_write_byte(0x07);
	GC9A01_write_byte(0x04);
	GC9A01_write_byte(0x0E);
	GC9A01_write_byte(0x0F);
	GC9A01_write_byte(0x09);
	GC9A01_write_byte(0x07);
	GC9A01_write_byte(0x08);
	GC9A01_write_byte(0x03);

	GC9A01_write_command(0xE8);
	GC9A01_write_byte(0x34);

	GC9A01_write_command(0x62);
	GC9A01_write_byte(0x18);
	GC9A01_write_byte(0x0D);
	GC9A01_write_byte(0x71);
	GC9A01_write_byte(0xED);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x18);
	GC9A01_write_byte(0x0F);
	GC9A01_write_byte(0x71);
	GC9A01_write_byte(0xEF);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x70);

	GC9A01_write_command(0x63);
	GC9A01_write_byte(0x18);
	GC9A01_write_byte(0x11);
	GC9A01_write_byte(0x71);
	GC9A01_write_byte(0xF1);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x18);
	GC9A01_write_byte(0x13);
	GC9A01_write_byte(0x71);
	GC9A01_write_byte(0xF3);
	GC9A01_write_byte(0x70);
	GC9A01_write_byte(0x70);

	GC9A01_write_command(0x64);
	GC9A01_write_byte(0x28);
	GC9A01_write_byte(0x29);
	GC9A01_write_byte(0xF1);
	GC9A01_write_byte(0x01);
	GC9A01_write_byte(0xF1);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x07);

	GC9A01_write_command(0x66);
	GC9A01_write_byte(0x3C);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0xCD);
	GC9A01_write_byte(0x67);
	GC9A01_write_byte(0x45);
	GC9A01_write_byte(0x45);
	GC9A01_write_byte(0x10);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x00);

	GC9A01_write_command(0x67);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x3C);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x01);
	GC9A01_write_byte(0x54);
	GC9A01_write_byte(0x10);
	GC9A01_write_byte(0x32);
	GC9A01_write_byte(0x98);

	GC9A01_write_command(0x74);
	GC9A01_write_byte(0x10);
	GC9A01_write_byte(0x85);
	GC9A01_write_byte(0x80);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x00);
	GC9A01_write_byte(0x4E);
	GC9A01_write_byte(0x00);

	GC9A01_write_command(0x98);
	GC9A01_write_byte(0x3e);
	GC9A01_write_byte(0x07);

	GC9A01_write_command(0x35);
	GC9A01_write_command(0x21);

	GC9A01_write_command(0x11);
	HAL_Delay(1000);
	GC9A01_write_command(0x29);
	HAL_Delay(20);

	/* First pixel*/
	uint8_t data[3];

	data[0] = 0x00;
	data[1] = 0x80;
	data[2] = 0xFF;

	GC9A01_write_command(0x2C);
	GC9A01_write_data(data, 3);

	/* Main loop */
	while(true)
	{
		data[0] ++;
		data[1] ++;
		data[2] ++;

		GC9A01_write_command(0x3C);
		GC9A01_write_data(data, 3);
	}
}

void GC9A01_write_command(uint8_t cmd)
{
	//HAL_Delay(1);

	HAL_GPIO_WritePin(HAL_DISPLAY_DC_PORT, HAL_DISPLAY_DC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_RESET);

	//HAL_Delay(1);

    if (HAL_SPI_Transmit(&SPI1Handle, &cmd, 1, 1000) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

    //HAL_Delay(1);

    HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_SET);
}

void GC9A01_write_data(uint8_t *data, size_t len)
{
	//HAL_Delay(1);

	HAL_GPIO_WritePin(HAL_DISPLAY_DC_PORT, HAL_DISPLAY_DC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_RESET);

	//HAL_Delay(1);

    if (HAL_SPI_Transmit(&SPI1Handle, data, len, 1000) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

    //HAL_Delay(1);

    HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_SET);
}

void GC9A01_write_byte(uint8_t val)
{
    GC9A01_write_data(&val, sizeof(val));
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
