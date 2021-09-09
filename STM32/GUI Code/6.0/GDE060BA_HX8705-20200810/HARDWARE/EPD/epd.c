#include "stm32f10x.h"
#include "driver.h"
#include "epd.h"
#include "data.h"
#include "power.h"
#include "board.h"
#include "EPD_WAVEFORM.h"
#include "AVT_CONFIG.h"

#define AVT_SPI_FLASH_INIT	



#if 1
#define avt_info_str(s)		{Debug_str(s);}
#define avt_info_hex(s)		{Debug_hex(s);}
#else
#define avt_info_str(s)
#define avt_info_hex(s)	
#endif

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

u16 Reg0x0204Save = 0;

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_delay(void)
{
	//vu32 nCount=1;

 	//for(; nCount != 0; nCount--);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_reset()
{
	AVT_RST_L;
	Delay1ms(20);
	AVT_RST_H;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_busy_wait(void)
{
	while(1)
	{
		if(AVT_RDY != 0)
			break;
	}
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
u16 avt_i80_read_dat(void)
{
	u16 dat;

	
	AVT_HCS_L;
	avt_busy_wait();
	AVT_DAT_SETIN;
	
	AVT_HDC_H;	
	AVT_HRD_L;	//dely 01 command, ng
	AVT_HRD_L;	//dely 02 command, ng
	AVT_HRD_L;	//dely 03 command, ng
	AVT_HRD_L;	//dely 04 command, ng
	AVT_HRD_L;	//dely 05 command, ng
	AVT_HRD_L;	//dely 06 command, ng
	AVT_HRD_L;	//dely 07 command, ng
	AVT_HRD_L;	//dely 08 command, ok
	AVT_HRD_L;	//dely 09 command, ok
	AVT_HRD_L;	//dely 10 command, ok
	AVT_HRD_L;	//dely 11 command, ok
	AVT_HRD_L;	//dely 12 command, ok
	//avt_delay();
	
	dat = AVT_DAT_IN;
	AVT_HRD_H;

	AVT_HCS_H;
	return dat;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_i80_write_dat(u16 dat)
{
	AVT_HCS_L;
	avt_busy_wait();
	
	AVT_DAT_SETOUT;
	AVT_DAT_OUT(dat);
	AVT_HDC_H;
	AVT_HWE_L;
	AVT_HWE_H;

	AVT_HCS_H;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_i80_write_cmd(u16 cmd)
{
	AVT_HCS_L;
	avt_busy_wait();
	
	AVT_DAT_SETOUT;
	AVT_DAT_OUT(cmd);
	AVT_HDC_L;
	AVT_HWE_L;
	AVT_HWE_H;

	AVT_HCS_H;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//System Commands
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_cmd_set(u16 SPI_CFG, u32 SFM)
{
	avt_i80_write_cmd(0x0000);
	avt_i80_write_dat(SPI_CFG);		//REG_0204[7:0]
	avt_i80_write_dat(SFM);			//SFM[15:0]
	avt_i80_write_dat(SFM>>16);		//SFM[23:16]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_pll_stby(u16 PLL_CFG0, u16 PLL_CFG1, u16 PLL_CFG2)
{
	avt_i80_write_cmd(0x0001);
	avt_i80_write_dat(PLL_CFG0); 	//REG_0010[5:0]
	avt_i80_write_dat(PLL_CFG1);  	//REG_0012[15:12]
	avt_i80_write_dat(PLL_CFG2); 	//REG_0014[7:3]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_run_sys(void)
{
	tps_source_gate_enable();
	avt_i80_write_cmd(0x0002);
	avt_busy_wait();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_stby(void)
{
	avt_i80_write_cmd(0x0004);
	avt_busy_wait();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_slp(void)
{
	avt_i80_write_cmd(0x0005);
	avt_busy_wait();
	tps_vcom_disable();
	tps_source_gate_disable();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_sys_run(void)
{
	avt_i80_write_cmd(0x0006);
	avt_busy_wait();
	tps_source_gate_enable();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_sys_stby(void)
{
	avt_i80_write_cmd(0x0007);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_sdram(u16 SDRAM_CFG0, u16 SDRAM_CFG1, u16 SDRAM_CFG2, u16 SDRAM_CFG3)
{
	avt_i80_write_cmd(0x0008);
	avt_i80_write_dat(SDRAM_CFG0); 	//REG_0100[15:4][2:0]
	avt_i80_write_dat(SDRAM_CFG1);  	//REG_0106[15:0]
	avt_i80_write_dat(SDRAM_CFG2); 	//REG_0108[5:4]
	avt_i80_write_dat(SDRAM_CFG3); 	//REG_010A[14:8][2:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_dspe_cfg(u16 HSIZE, u16 VSIZE, u16 SDRVCFG, u16 GDRVCFG, u16 IDX_FMT_CFG)
{
	avt_i80_write_cmd(0x0009);
	avt_i80_write_dat(HSIZE); 		//REG_0306[12:0]
	avt_i80_write_dat(VSIZE);  		//REG_0300[12:0]
	avt_i80_write_dat(SDRVCFG); 		//REG_030C[15:0]
	avt_i80_write_dat(GDRVCFG); 		//REG_030E[15:3][1:0]
	avt_i80_write_dat(IDX_FMT_CFG); 	//REG_0330[15][7:6][2:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_dspe_tmg(u16 FSYNC_CFG, u16 F_BEGIN_END, u16 LSYNC_CFG, u16 L_BEGIN_END, u16 PIXEL_CLK_CFG)
{
	avt_i80_write_cmd(0x000A);
	avt_i80_write_dat(FSYNC_CFG); 	//REG_0302[7:0]
	avt_i80_write_dat(F_BEGIN_END); 	//REG_0304[15:0]
	avt_i80_write_dat(LSYNC_CFG); 	//REG_0308[7:0]
	avt_i80_write_dat(L_BEGIN_END); 	//REG_030A[15:0]
	avt_i80_write_dat(PIXEL_CLK_CFG);//REG_0018[4:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_init_rotmode(u16 ROTMODE)
{
	avt_i80_write_cmd(0x000B);
	avt_i80_write_dat(ROTMODE); 		//REG_032C[9:8]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Register and Memory Access Commands
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
u16 avt_rd_reg(u16 REG_ADDR)
{
	u16 REG_DATA;

	avt_i80_write_cmd(0x0010);
	avt_i80_write_dat(REG_ADDR); 	//REG_ADDR[15:0]
	REG_DATA = avt_i80_read_dat();

	return REG_DATA;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wr_reg(u16 REG_ADDR, u16 REG_DATA)
{
	avt_i80_write_cmd(0x0011);
	avt_i80_write_dat(REG_ADDR); 	//REG_ADDR[15:0]
	avt_i80_write_dat(REG_DATA); 	//REG_DATA[15:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wr_reg_addr(u16 REG_ADDR)
{
	avt_i80_write_cmd(0x0011);
	avt_i80_write_dat(REG_ADDR); 	//REG_ADDR[15:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void avt_rd_sfm(void)
{
	avt_i80_write_cmd(0x0012);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wr_sfm(u16 SFM_DATA)
{
	avt_i80_write_cmd(0x0013);
	avt_i80_write_dat(SFM_DATA); 	//SFM_DATA[15:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_end_sfm(void)
{
	avt_i80_write_cmd(0x0014);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Burst Access Commands
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void avt_bst_rd_sdr(u16 MA0, u16 MA1, u16 BC0, u16 BC1)
{
	avt_i80_write_cmd(0x001C);
	avt_i80_write_dat(MA0); 			//REG_0144[15:0]
	avt_i80_write_dat(MA1); 			//REG_0146[9:0]
	avt_i80_write_dat(BC0); 			//REG_0148[15:0]
	avt_i80_write_dat(BC1); 			//REG_014A[9:0]
	avt_busy_wait();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_bst_wr_sdr(u16 MA0, u16 MA1, u16 BC0, u16 BC1)
{
	avt_i80_write_cmd(0x001D);
	avt_i80_write_dat(MA0); 			//REG_0144[15:0]
	avt_i80_write_dat(MA1); 			//REG_0146[7:0]
	avt_i80_write_dat(BC0); 			//REG_0148[15:0]
	avt_i80_write_dat(BC1); 			//REG_014A[9:0]
	avt_busy_wait();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_bst_end_sdr(void)
{
	avt_i80_write_cmd(0x001E);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Image Loading Commands
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void avt_ld_img(u16 ARG)
{
	avt_i80_write_cmd(0x0020);
	avt_i80_write_dat(ARG); 			//REG_0140[5:4]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_ld_img_area(u16 ARG, u16 XSTART, u16 YSTART, u16 WIDTH, u16 HEIGHT)
{
	avt_i80_write_cmd(0x0022);
	avt_i80_write_dat(ARG); 			//REG_0140[5:4]
	avt_i80_write_dat(XSTART); 		//REG_014C[11:0]
	avt_i80_write_dat(YSTART); 		//REG_014E[11:0]
	avt_i80_write_dat(WIDTH); 		//REG_0150[12:0]
	avt_i80_write_dat(HEIGHT); 		//REG_0152[12:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_ld_img_end(void)
{
	avt_i80_write_cmd(0x0023);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_ld_img_wait(void)
{
	avt_i80_write_cmd(0x0024);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_ld_img_setadr(u32 MA)
{
	avt_i80_write_cmd(0x0025);
	avt_i80_write_dat(MA); 			//REG_0144[15:0]
	avt_i80_write_dat(MA>>16); 		//REG_0146[9:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_ld_img_dspeadr(void)
{
	avt_i80_write_cmd(0x0026);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Polling Commands
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wait_dspe_trg(void)
{
	avt_i80_write_cmd(0x0028);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wait_dspe_frend(void)
{
	avt_i80_write_cmd(0x0029);
	avt_busy_wait();
	//tps_vcom_disable();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wait_dspe_lutfree(void)
{
	avt_i80_write_cmd(0x002A);
	avt_busy_wait();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_wait_dspe_mlutfree(u16 LUTMASK)
{
	avt_i80_write_cmd(0x002B);
	avt_i80_write_dat(LUTMASK); 		//REG_032E[15:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Waveform Update Commands
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_rd_wfm_info(u32 MA)
{
	avt_i80_write_cmd(0x0030);
	avt_i80_write_dat(MA); 			//REG_0350[15:0]
	avt_i80_write_dat(MA>>16); 		//REG_0352[7:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_init(void)
{
	avt_i80_write_cmd(0x0032);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_full(u16 ARG)
{
	avt_i80_write_cmd(0x0033);
	avt_i80_write_dat(ARG);     		//REG_0334[14][11:4]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_full_area(u16 ARG, u16 XSTART, u16 YSTART, u16 WIDTH, u16 HEIGHT)
{
	avt_i80_write_cmd(0x0034);
	avt_i80_write_dat(ARG); 			//REG_0334[14][11:4]
	avt_i80_write_dat(XSTART); 		//REG_0340[11:0]
	avt_i80_write_dat(YSTART); 		//REG_0342[11:0]
	avt_i80_write_dat(WIDTH); 		//REG_0344[12:0]
	avt_i80_write_dat(HEIGHT); 		//REG_0346[12:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_part(u16 ARG)
{
	avt_i80_write_cmd(0x0035);
	avt_i80_write_dat(ARG);     		//REG_0334[14][11:4]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_part_area(u16 ARG, u16 XSTART, u16 YSTART, u16 WIDTH, u16 HEIGHT)
{
	avt_i80_write_cmd(0x0036);
	avt_i80_write_dat(ARG); 			//REG_0334[14][11:4]
	avt_i80_write_dat(XSTART); 		//REG_0340[11:0]
	avt_i80_write_dat(YSTART); 		//REG_0342[11:0]
	avt_i80_write_dat(WIDTH); 		//REG_0344[12:0]
	avt_i80_write_dat(HEIGHT); 		//REG_0346[12:0]
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_gdrv_clr(void)
{
	avt_i80_write_cmd(0x0037);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_upd_set_imgadr(u32 ADR)
{
	avt_i80_write_cmd(0x0038);
	avt_i80_write_dat(ADR); 			//REG_0310[15:0]
	avt_i80_write_dat(ADR>>16); 		//REG_0312[15:0]
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_check_soft_ready(void)
{
	//while(avt_rd_reg(0x000a)&32)		//check bit 5 of SYSTEM STATUS REGISTER
	while(avt_rd_reg(0x000a)&0x24)	//
	{ 
    	;//Debug_str("=");
    }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_idle_wait(void)
{
	u16 regval;

	while(1)
	{
		regval = avt_rd_reg(0x0206);
		if((regval&0x8) == 0)
			break;

		Debug_str("-");
	}
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_byte(u8 dat)
{
	u16 v;

	v = dat;
	v =	v|0x100;
    avt_wr_reg(0x0202, v);
    avt_spi_flash_idle_wait();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
u8 avt_spi_flash_read_byte(void)
{
    u16 v;
    
    avt_wr_reg(0x0202, 0);
    avt_spi_flash_idle_wait();
    v = avt_rd_reg(0x0200);
    return(v&0xFF);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Read FLASH status
u8 avt_spi_flash_read_status(void)
{
	u8 status;
	
	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0x05);
	status = avt_spi_flash_read_byte();
	avt_wr_reg(0x0208, 0x0);
	return status;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_deal_wait(void)
{
	while(1)
	{
		if((avt_spi_flash_read_status()&0x1)==0)
			break;		
		Debug_str("+");
	}
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_enable(void)
{
	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0x06);
	avt_wr_reg(0x0208, 0x0); 	
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_disable(void)
{
	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0x04);
	avt_wr_reg(0x0208, 0x0); 	
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_earase()
{
	avt_spi_flash_write_enable();
	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0xc7);
	avt_wr_reg(0x0208, 0x0); 
	avt_spi_flash_deal_wait();
	avt_spi_flash_write_disable();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_sector_earase(u32 addr)			//4K earase
{
	u8 addr1,addr2,addr3;

	addr1 = (addr&0xff);
	addr2 = ((addr>>8)&0xff);
	addr3 = ((addr>>16)&0xff);
	
	avt_spi_flash_write_enable();
	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0x20);
	avt_spi_flash_write_byte(addr3);
	avt_spi_flash_write_byte(addr2);
	avt_spi_flash_write_byte(addr1);
	avt_wr_reg(0x0208, 0x0); 
	avt_spi_flash_deal_wait();
	avt_spi_flash_write_disable();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_page(u32 addr, u8 *data)	//256bytes write
{
	u16 i;
	u8 addr1,addr2,addr3;

	addr1 = (addr&0xff);
	addr2 = ((addr>>8)&0xff);
	addr3 = ((addr>>16)&0xff);

	avt_spi_flash_write_enable();

	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0x02);
	avt_spi_flash_write_byte(addr3);
	avt_spi_flash_write_byte(addr2);
	avt_spi_flash_write_byte(addr1);

	
	for(i=0;i<256;i++)
	{
		avt_spi_flash_write_byte(data[i]);
	}
	avt_wr_reg(0x0208, 0x0);
	
	avt_spi_flash_deal_wait(); 	
	avt_spi_flash_write_disable();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_buff(u32 addr, u32 len, u8 *buff)
{
	u32 i,pagenum;
	u8 *buffptr;

	buffptr = buff;
	pagenum = len/256+1;

	for(i=0; i<pagenum; i++)
	{
		Debug_str("writing spiflash page:");
		Debug_dec(i);
		avt_spi_flash_write_page(addr, buffptr);
		buffptr = buffptr + 256;
		addr = addr + 256;		
		Debug_str("\r\n");
	}
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_read_buff(u32 addr, u32 len, u8 *buff)
{
	u32 i;
	u8 addr1,addr2,addr3;

	addr1 = (addr&0xff);
	addr2 = ((addr>>8)&0xff);
	addr3 = ((addr>>16)&0xff);

	avt_wr_reg(0x0208, 0x1);
	avt_spi_flash_write_byte(0x03);
	avt_spi_flash_write_byte(addr3);
	avt_spi_flash_write_byte(addr2);
	avt_spi_flash_write_byte(addr1);
	
	Debug_str("start to read data from the flash\r\n");
	
	for(i=0; i<len; i++)
	{
		buff[i] = avt_spi_flash_read_byte();
	}
	avt_wr_reg(0x0208,0x0); 	
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_read_id(void)
{
	u8 temp1,temp2;
	

	Debug_str("avt_spi_flash_read_id:");

	avt_wr_reg(0x0208, 0x1);
	
	avt_spi_flash_write_byte(0x90);
	avt_spi_flash_write_byte(0x00);
	avt_spi_flash_write_byte(0x00);
	avt_spi_flash_write_byte(0x00);
	
	temp1 = avt_spi_flash_read_byte();
	temp2 = avt_spi_flash_read_byte();

	avt_wr_reg(0x0208, 0x0);

	Debug_hex(temp1);
	Debug_hex(temp2);
	Debug_str("\r\n");
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_waveform_deal(void)
{
	u32 size, i, sector, addr;
	//u8 rbuf[2];

	if(Reg0x0204Save != 0x99)
	{
		Debug_str("avt_waveform_update -> 0x0204 value error, cann't update waveform ...\r\n");
		return;
	}

#if 0	
	//Read if 0x3000 is 0xa0, if it is, there is a waveform file.
	avt_spi_flash_read_buff(0x3000, 2, rbuf);
	if(rbuf[0] == 0x0a)
	{
		Debug_str("avt_waveform_update -> had waveform ...\r\n");
		return;
	}
#endif

	size = sizeof(EPD_WAVEFORM);
	sector = size/4096;			//1 sector = 4096bytes
	if((size%4096) != 0)		
		sector++;

	Debug_str("avt_waveform_update -> size:");
	Debug_hex(size>>16);
	Debug_hex(size);
	Debug_str("\r\navt_waveform_update -> earase sector:");
	Debug_dec(sector);
	Debug_str("\r\n");

	addr = EPD_WF_ADDR;
	for(i=0; i<sector; i++)
	{
		avt_spi_flash_sector_earase(addr);
		addr += 4096;
	}

	Debug_str("\r\navt_waveform_update -> waveform write begin ...\r\n");
	avt_spi_flash_write_buff(EPD_WF_ADDR, size, (u8*)EPD_WAVEFORM);
	Debug_str("avt_waveform_update -> waveform  write finish !\r\n\r\n"); 

}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_waveform_start(void)
{

	Reg0x0204Save = avt_rd_reg(0x0204);
	Debug_str("avt_waveform_update -> 0x0204 curvalue:");
	Debug_hex(Reg0x0204Save);
	Debug_str("\r\n");
	if(Reg0x0204Save != 0x99)
	{
		Debug_str("avt_waveform_update -> read 0x0204 error !\r\n");
		return;
	}
	avt_wr_reg(0x0204, 0x19);
	avt_spi_flash_read_id();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_spi_flash_write_waveform_end(void)
{
	avt_wr_reg(0x0204, Reg0x0204Save);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void avt_waveform_update(void)
{
	avt_spi_flash_write_waveform_start();
	avt_spi_flash_write_waveform_deal();
	avt_spi_flash_write_waveform_end();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Check whether the configuration data of the internal FLASH of the AVT is normal. If it is not normal, you need to rewrite the configuration.
void AVT_CONFIG_check(void)
{
	u16 sector, checksum, checksumorg;
	u32 addr, i, size;
	

	avt_reset();
	Delay100ms(1);
	
	Reg0x0204Save = avt_rd_reg(0x0204);
	Debug_str("AVT_CONFIG_check -> 0x0204 curvalue:");
	Debug_hex(Reg0x0204Save);
	Debug_str("\r\n");
	if(Reg0x0204Save != 0x99)
	{
		while(1)
		{
			Debug_str("AVT_CONFIG_check -> read 0x0204 error !\r\n"); 
			Delay100ms(10);
		}
	}
	avt_wr_reg(0x0204, 0x19);
	
	checksumorg = 0;
	checksum = 0;
	size = sizeof(AVT_CONFIG);
	for(i=0; i<size; i++)
		checksumorg += AVT_CONFIG[i];

	avt_wr_reg(0x0208, 0x1);		
	avt_spi_flash_write_byte(0x03);				//read data from addr:0x000000
	avt_spi_flash_write_byte(0);
	avt_spi_flash_write_byte(0);
	avt_spi_flash_write_byte(0);
	for(i=0; i<size; i++)
	{
		checksum += avt_spi_flash_read_byte();	//read data from addr:0x000000
	}
	avt_wr_reg(0x0208,0x0); 	

	Debug_str("AVT_CONFIG_check -> size:");
	Debug_hex(size>>16);
	Debug_hex(size);
	Debug_str(", checksum:");
	Debug_hex(checksum);
	Debug_str("[ ");
	Debug_hex(checksumorg);
	Debug_str("]\r\n");
	
#if 1
	if(checksum == checksumorg)
	{
		avt_wr_reg(0x0204, Reg0x0204Save);
        Debug_str("AVT_CONFIG_check -> config checksum OK !\r\n");	
		return;
	}
#endif

	sector = size/4096;			//1 sector = 4096bytes
	if((size%4096) != 0)		
		sector++;

	Debug_str("AVT_CONFIG_check -> earase sector:");
	Debug_dec(sector);
	Debug_str("\r\n");

	addr = 0;
	for(i=0; i<sector; i++)
	{
		avt_spi_flash_sector_earase(addr);
		addr += 4096;
	}

	Debug_str("\r\nAVT_CONFIG_check -> config write begin ...\r\n");
	avt_spi_flash_write_buff(0, size, (u8*)AVT_CONFIG);
	Debug_str("AVT_CONFIG_check -> config write finish !\r\n"); 

	checksum = 0;
	avt_wr_reg(0x0208, 0x1);			
	avt_spi_flash_write_byte(0x03);				//read data from addr:0x000000 again
	avt_spi_flash_write_byte(0);
	avt_spi_flash_write_byte(0);
	avt_spi_flash_write_byte(0);
	for(i=0; i<size; i++)
	{
		checksum += avt_spi_flash_read_byte();	//read data from addr:0x000000
	}
	avt_wr_reg(0x0208,0x0); 	

	if(checksum != checksumorg)
	{
		while(1)
		{
			Debug_str("AVT_CONFIG_check -> config write error !\r\n"); 
			Delay100ms(10);
		}
	}

	avt_wr_reg(0x0204, Reg0x0204Save);
	Debug_str("AVT_CONFIG_check -> config write and checksum OK !\r\n\r\n");	
}




//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Image display
void epd_draw_pic_start(void)
{
	avt_run_sys();
    avt_ld_img(EPD_DATA_8BPP);
	avt_wr_reg_addr(0x0154);
	Debug_str("epd_draw_pic_start start...\r\n");
}
void epd_draw_pic_buff(u8* buff, u16 len)
{
	u16 i,dat;

	for(i=0; i<len; i++)
	{
		dat = buff[i]&0xf0;	
		dat = (dat<<8)&0xff00;
		dat = dat + ((buff[i]<<4)&0xf0);
		avt_i80_write_dat(dat);
	}  
}
void epd_draw_pic_end(void)
{	
   	avt_ld_img_end();
    avt_upd_full((wf_mode<<8));

	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_frend();
	tps_vcom_disable();
	
	avt_slp();
	Debug_str("epd_draw_pic_start end...\r\n");
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Read the picture from the external FLASH and display it. One pixel in the picture data is represented by 4 bits (0~15 gray scale).
void epd_draw_pic_from_spiflash(u32 addr)
{
	u8 addr3,addr2,addr1,value;
	u16 i,j,dat;

	Debug_str("epd_draw_pic_from_spiflash start...\r\n");
	addr1 = addr;
	addr2 = (addr>>8);
	addr3 = (addr>>16);

	FLASH_CS_L;				    
	SpiFlash_ReadWriteByte(0x03);	    
	SpiFlash_ReadWriteByte(addr3); 	    
	SpiFlash_ReadWriteByte(addr2); 	    
	SpiFlash_ReadWriteByte(addr1); 

#if 1	//EPD_DATA_8BPP
	avt_run_sys();
	avt_ld_img(EPD_DATA_8BPP);
	avt_wr_reg_addr(0x0154);

	for (i=0; i<tcon_init_vsize; i++)
	{
		for(j=0; j<tcon_init_hsize/2; j++)
		{
			value = SpiFlash_ReadWriteByte(0xff);
			dat = value&0x0f;	
			dat = (dat<<12)&0xf000;
		  	dat = dat + (value&0xf0);
			avt_i80_write_dat(dat);
		}
	}
#else	//EPD_DATA_4BPP
	avt_run_sys();
	avt_wr_reg(0x0020, 0x2);	//big endian 
	avt_ld_img(EPD_DATA_4BPP);
	avt_wr_reg_addr(0x0154);

	for (i=0; i<tcon_init_vsize; i++)
	{
		for(j=0; j<tcon_init_hsize/4; j++)
		{
			value = SpiFlash_ReadWriteByte(0xff);
			dat = value;	
			dat = (dat<<8)&0xff00;
			value = SpiFlash_ReadWriteByte(0xff);
		  	//dat = dat + (((u16)value<<8)&0xff00);
		  	dat = dat + value;
			avt_i80_write_dat(dat);
		}
	}
	avt_wr_reg(0x0020, 0x0); //little endian 
#endif
	FLASH_CS_H;	

	avt_ld_img_end();
    avt_upd_full((wf_mode<<8));

   	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_frend();
	tps_vcom_disable();

	avt_slp();
	Debug_str("epd_draw_pic_from_spiflash end...\r\n");
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Full screen display grayscale
void epd_draw_gray(u8 gray)
{
	u16 i,j,dat;

	Debug_str("epd_draw_gray start...\r\n");
	avt_run_sys();
    avt_ld_img(EPD_DATA_8BPP);
	avt_wr_reg_addr(0x0154);
tps_sleep_to_standby(); //VCOM voltage setting
	
	for (i=0; i<tcon_init_vsize; i++)
	{
		for(j=0; j<(tcon_init_hsize/2); j++)
		{
			dat = gray;
			dat = ((dat<<8)&0xff00) + gray;
			avt_i80_write_dat(dat);
		}
	}
	
	avt_ld_img_end();
  avt_upd_full((wf_mode<<8));

	tps_vcom_enable();
	avt_wait_dspe_trg();
	avt_wait_dspe_frend();
	tps_vcom_disable();

  tps_standby_to_sleep();//This sentence is a must, please do not delete!!!	
	avt_slp();
	Debug_str("epd_draw_gray end...\r\n");
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Horizontal display N gray scale
void epd_draw_gray_level_horizontal(u8 div)
{
	u16 h,i,j,dat;
	u8 v, gray;

	v = tcon_init_vsize%div;
	Debug_str("epd_draw_gray_level_horizontal start...\r\n");
	avt_run_sys();
  avt_ld_img(EPD_DATA_8BPP);
	avt_wr_reg_addr(0x0154);
	tps_sleep_to_standby(); //VCOM voltage setting
	
	gray = 0;
	for (i=0; i<div; i++)
	{
		for (j=0; j<(tcon_init_vsize-v)/div; j++)
		{
			for(h=0; h<(tcon_init_hsize/2); h++)
			{
				dat = gray;
				dat = ((dat<<8)&0xff00) + gray;
				avt_i80_write_dat(dat);
			}
	  	}
		gray += 255 / (div - 1);
	}
	for (i=0; i<v; i++)
	{
		for (h=0; h<(tcon_init_hsize/2); h++)
		{
		    dat = 255;
			dat = ((dat<<8)&0xff00) + 255;
			avt_i80_write_dat(dat);
		}
	}

   	avt_ld_img_end();
    avt_upd_full((wf_mode<<8));

	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_frend();
	tps_vcom_disable();
	
	tps_standby_to_sleep();//This sentence is a must, please do not delete!!!	
	avt_slp();
	Debug_str("epd_draw_gray_level_horizontal end...\r\n");
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Vertical display of N gray scale
void epd_draw_gray_level_vertical(u8 div)
{
	u16 h,i,j,dat;
    u8 v, gray;

   	v = (tcon_init_hsize/2)%div;
	Debug_str("epd_draw_gray_level_vertical start...\r\n");
	avt_run_sys();
    avt_ld_img(EPD_DATA_8BPP);
	avt_wr_reg_addr(0x0154);
	tps_sleep_to_standby(); //VCOM voltage setting
	
	for (i=0; i<tcon_init_vsize; i++)
	{
		gray = 0;
		for (j=0; j<div; j++)
		{
			for(h=0; h<((tcon_init_hsize/2)-v)/div; h++)
			{
				dat = gray;
				dat = ((dat<<8)&0xff00) + gray;
				avt_i80_write_dat(dat);
			}
			gray += 255 / (div - 1);
		}

		for (j=0; j<v; j++)
		{
		    dat = gray;
			dat = ((dat<<8)&0xff00) + gray;
			avt_i80_write_dat(dat);
  		}
	}

    avt_ld_img_end();
    avt_upd_full((wf_mode<<8));

	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_frend();
	tps_vcom_disable();

  tps_standby_to_sleep();//This sentence is a must, please do not delete!!!	
	avt_slp();
	Debug_str("epd_draw_gray_level_vertical end...\r\n");
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Area display grayscale
void epd_draw_gray_part(u8 gray, u16 x, u16 y, u16 w, u16 h)
{
	u16 i,j,dat;

	Debug_str("epd_draw_gray_part start...\r\n");
	avt_run_sys();
    avt_ld_img_area(EPD_DATA_8BPP, x, y, w, h);
	avt_wr_reg_addr(0x0154);
	tps_sleep_to_standby(); //VCOM voltage setting

	for (i=0; i<h; i++)
	{
		for(j=0; j<(w/2); j++)
		{
			dat = gray;
			dat = ((dat<<8)&0xff00) + gray;
			avt_i80_write_dat(dat);
		}
	}
	
	avt_ld_img_end();
    avt_upd_full_area((wf_mode<<8), x, y, w, h);

	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_frend();
	tps_vcom_disable();

	tps_standby_to_sleep();//This sentence is a must, please do not delete!!!	
	avt_slp();
	Debug_str("epd_draw_gray_part end...\r\n");

}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//The area displays the grayscale and reads the image data from the ROM.
void epd_draw_pic_part_from_rom(u8* ptr, u8 bpp, u16 x, u16 y, u16 w, u16 h)
{
	u16 dat;
	u32 i, size, cnt;

	Debug_str("epd_draw_pic_part_from_rom start...\r\n");

	avt_run_sys();
	avt_ld_img_area(bpp, x, y, w, h);
	avt_wr_reg_addr(0x0154);
  tps_sleep_to_standby(); //VCOM voltage setting

	cnt = 0;
	
	
	if(bpp == EPD_DATA_8BPP)
	{
		size = (u32)w*h/2;
		for(i=0; i<size; i++)
		{
			dat = ptr[cnt++];
			dat = dat + (((u16)ptr[cnt++]<<8)&0xff00);
			avt_i80_write_dat(dat);
		}
	}
	else if(bpp == EPD_DATA_4BPP)
	{
		size = (u32)w*h/4;
		for(i=0; i<size; i++)
		{
			dat = ptr[cnt++];
			dat = dat + (((u16)ptr[cnt++]<<8)&0xff00);
			avt_i80_write_dat(dat);
		}
	}
	else if(bpp == EPD_DATA_2BPP)
	{
		size = (u32)w*h/8;
		for(i=0; i<size; i++)
		{
			dat = ptr[cnt++];
			dat = dat + (((u16)ptr[cnt++]<<8)&0xff00);
			avt_i80_write_dat(dat);
		}
	}
	

	avt_ld_img_end();
    avt_upd_full_area((wf_mode<<8), x, y, w, h);

   	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_frend();
	tps_vcom_disable();
	
  tps_standby_to_sleep();//This sentence is a must, please do not delete!!!	
	avt_slp();
	Debug_str("epd_draw_pic_part_from_rom end...\r\n");
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Area display grayscale, fast LUT mode
void epd_draw_gray_part_lut(u8 gray, u16 x, u16 y, u16 w, u16 h)
{
	u16 i,j,dat;

	Debug_str("epd_draw_gray_part_lut start...\r\n");
	
    avt_ld_img_area(EPD_DATA_8BPP, x, y, w, h);
	avt_wr_reg_addr(0x0154);
 tps_sleep_to_standby(); //VCOM voltage setting
	for (i=0; i<h; i++)
	{
		for(j=0; j<(w/2); j++)
		{
			dat = gray;
			dat = ((dat<<8)&0xff00) + gray;
			avt_i80_write_dat(dat);
		}
	}
	
	avt_ld_img_end();
    avt_upd_full_area((wf_mode<<8), x, y, w, h);

	tps_vcom_enable();
    avt_wait_dspe_trg();
    avt_wait_dspe_lutfree();
	
	Debug_str("epd_draw_gray_part_lut end...\r\n");

}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Regional continuous demonstration
void avt_lut_demo(u8 gray)
{
	u16 i, t;

	t = 30;
	
	//avt_run_sys();
			
	wf_mode = EPD_MODE_DU;

	for(i=50; i<750; i=i+50)
	{
		epd_draw_gray_part_lut(gray, i, 50, 50, 50);
		Delay1ms(t);
	}
	
	for(i=100; i<550; i=i+50)
	{
		epd_draw_gray_part_lut(gray, 700, i, 50, 50);
		Delay1ms(t);
	}

	for(i=650; i>0; i=i-50)
	{
		epd_draw_gray_part_lut(gray, i, 500, 50, 50);
		Delay1ms(t);
	}

	for(i=450; i>100; i=i-50)
	{
		epd_draw_gray_part_lut(gray, 50, i, 50, 50);
		Delay1ms(t);
	}

	for(i=100; i<650; i=i+50)
	{
		epd_draw_gray_part_lut(gray, i, 150, 50, 50);
		Delay1ms(t);
	}

	
	epd_draw_gray_part_lut(gray, 600, 200, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 600, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 600, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 600, 350, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 600, 400, 50, 50);
	Delay1ms(t);

	epd_draw_gray_part_lut(gray, 550, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 500, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 450, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 400, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 350, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 300, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 250, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 200, 400, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 150, 400, 50, 50);
	Delay1ms(t);

	epd_draw_gray_part_lut(gray, 150, 350, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 150, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 150, 250, 50, 50);
	Delay1ms(t);

	epd_draw_gray_part_lut(gray, 200, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 250, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 300, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 350, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 400, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 450, 250, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 500, 250, 50, 50);
	Delay1ms(t);

	epd_draw_gray_part_lut(gray, 500, 300, 50, 50);
	Delay1ms(t);

	epd_draw_gray_part_lut(gray, 450, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 400, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 350, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 300, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 250, 300, 50, 50);
	Delay1ms(t);
	epd_draw_gray_part_lut(gray, 200, 300, 50, 50);
	Delay1ms(t);

	
	//avt_slp();
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//avt init
void avt_init(void)
{

	avt_reset();
	Delay100ms(1);
	Reg0x0204Save = avt_rd_reg(0x0204);

 
	avt_init_sys_run();

	avt_init_dspe_cfg(tcon_init_hsize, tcon_init_vsize, tcon_init_sdrv_cfg, tcon_init_gdrv_cfg, tcon_init_lutidxfmt);
	avt_info_str("INIT_DSPE_CFG is sent!");
	avt_info_str("\r\nCheck Register (HSIZE) updated by INIT_DSPE_CFG: addr 0x0306, value ");
	avt_info_hex(avt_rd_reg(0x0306));
	avt_info_str("\r\nCheck Register (VSIZE) updated by INIT_DSPE_CFG: addr 0x0300, value ");
	avt_info_hex(avt_rd_reg(0x0300));
	avt_info_str("\r\nCheck Register (SDRVCFG) updated by INIT_DSPE_CFG: addr 0x030C, value ");
	avt_info_hex(avt_rd_reg(0x030C));
	avt_info_str("\r\nCheck Register (GDRVCFG) updated by INIT_DSPE_CFG: addr 0x030E, value ");
	avt_info_hex(avt_rd_reg(0x030E));
	avt_info_str("\r\nCheck Register (LUT IDX FMT CFG) updated by INIT_DSPE_CFG: addr 0x0330, value ");
	avt_info_hex(avt_rd_reg(0x0330));

	avt_init_dspe_tmg(tcon_init_fslen, (tcon_init_felen << 8) | tcon_init_fblen,tcon_init_lslen,(tcon_init_lelen << 8) | tcon_init_lblen,tcon_init_pixclkdiv);
	avt_info_str("\r\nCheck Register (Frame Sync CFG) updated by INIT_DSPE_TMG: addr 0x0302, value ");
	avt_info_hex(avt_rd_reg(0x0302));
	avt_info_str("\r\nCheck Register (Frame Begin/End CFG) updated by INIT_DSPE_TMG: addr 0x0304, value ");
	avt_info_hex(avt_rd_reg(0x0304));
	avt_info_str("\r\nCheck Register (Line Sync CFG) updated by INIT_DSPE_TMG: addr 0x0308, value ");
	avt_info_hex(avt_rd_reg(0x0308));
	avt_info_str("\r\nCheck Register (Line Begin/End CFG) updated by INIT_DSPE_TMG: addr 0x030A, value ");
	avt_info_hex(avt_rd_reg(0x030A));
	avt_info_str("\r\nCheck Register (Pixel Clock CFG) updated by INIT_DSPE_TMG: addr 0x018, value ");
	avt_info_hex(avt_rd_reg(0x018));

	avt_rd_wfm_info(EPD_WF_ADDR);
	avt_info_str("\r\nRD_WFM_INFO is sent!");
	avt_info_str("\r\nCheck Register MA[15:0] updated by RD_WFM_INFO: addr 0x0350, value ");
	avt_info_hex(avt_rd_reg(0x0350));
	avt_info_str("\r\nCheck Register MA[23:16] updated by RD_WFM_INFO: addr 0x0352, value ");
	avt_info_hex(avt_rd_reg(0x0352));

	avt_ld_img_setadr(EPD_IMG_ADDR);
	avt_info_str("\r\nCheck Register MA[15:0] updated by LD_IMG_SETADR: addr 0x0144, value ");
	avt_info_hex(avt_rd_reg(0x0144));
	avt_info_str("\r\nCheck Register MA[25:16] updated by LD_IMG_SETADR: addr 0x0146, value ");
	avt_info_hex(avt_rd_reg(0x0146));

	avt_upd_set_imgadr(EPD_IMG_ADDR);
	avt_info_str("\r\nCheck Register MA[15:0] updated by UPD_SET_SETADR: addr 0x0310, value ");
	avt_info_hex(avt_rd_reg(0x0310));
	avt_info_str("\r\nCheck Register MA[31:16] updated by UPD_SET_SETADR: addr 0x0312, value ");
	avt_info_hex(avt_rd_reg(0x0312));

	avt_ld_img(EPD_DATA_8BPP);
	avt_info_str("\r\nLD_IMG is sent!");
	avt_info_str("\r\nCheck Register ARG[15:0] updated by LD_IMG: addr 0x0140, value ");
	avt_info_hex(avt_rd_reg(0x0140));
	avt_info_str("\r\n");



	wf_mode = EPD_MODE_INIT;
	epd_draw_gray(0xff);
	wf_mode = EPD_MODE_GC16;
	
	avt_slp();
	avt_info_str("\r\n");
}


