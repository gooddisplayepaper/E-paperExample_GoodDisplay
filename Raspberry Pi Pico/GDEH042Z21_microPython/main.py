import machine
import utime
import framebuf
#EPD GPIO
isEPD_W21_BUSY=machine.Pin(0, machine.Pin.IN, machine.Pin.PULL_DOWN) #BUSY
EPD_W21_RST= machine.Pin(1, machine.Pin.OUT)#RESE
EPD_W21_DC= machine.Pin(2, machine.Pin.OUT)#DC
EPD_W21_CS= machine.Pin(3, machine.Pin.OUT)#CS
#SPI0
spi_sck=machine.Pin(6) #SCLK
spi_tx=machine.Pin(7)#SDIN
spi_rx=machine.Pin(4)
spi=machine.SPI(0,baudrate=10000000,sck=spi_sck, mosi=spi_tx, miso=spi_rx) #10Mhz

#LED
led_onboard = machine.Pin(25, machine.Pin.OUT)






#SPI#####################
def SPI_Write(data):
    spi.write(chr(data))			

def EPD_W21_WriteCMD(command):
    EPD_W21_CS.value(0) #CS                
    EPD_W21_DC.value(0) #DC		
    SPI_Write(command)# command write
    EPD_W21_CS.value(1) #CS  

def EPD_W21_WriteDATA(data):
    EPD_W21_CS.value(0) #CS                       
    EPD_W21_DC.value(1) #DC			
    SPI_Write(data)  # data write
    EPD_W21_CS.value(1) #CS  

#EPD IC RESET
def EPD_W21_Init():
    EPD_W21_RST.value(0) # Module reset
    utime.sleep(0.01)   #At least 10ms delay 
    EPD_W21_RST.value(1)
    utime.sleep(0.01)   #At least 10ms delay 

    EPD_W21_RST.value(0) # Module reset
    utime.sleep(0.01)   #At least 10ms delay 
    EPD_W21_RST.value(1)
    utime.sleep(0.01)   #At least 10ms delay 

    EPD_W21_RST.value(0) # Module reset
    utime.sleep(0.01)   #At least 10ms delay 
    EPD_W21_RST.value(1)
    utime.sleep(0.01)   #At least 10ms delay 
#BUSY
def lcd_chkstatus():
    while isEPD_W21_BUSY.value()==0:
        utime.sleep(0.01) 
#UC8151D init
def EPD_init():
    EPD_W21_Init()  #Electronic paper IC reset

    EPD_W21_WriteCMD(0x04)  
    lcd_chkstatus()#waiting for the electronic paper IC to release the idle signal

    EPD_W21_WriteCMD(0x00)	    #panel setting
    EPD_W21_WriteDATA(0x0f)		#LUT from OTP£¬KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f

#display 
def PIC_display(picData_BW,picData_R):
    #Write Data
    EPD_W21_WriteCMD(0x10)       #Transfer old data
    for i in range(15000): 
        EPD_W21_WriteDATA(picData_BW[i])
    EPD_W21_WriteCMD(0x13)		     #Transfer new data
    for i in range(15000):
        EPD_W21_WriteDATA(0xff) #Transfer the actual displayed data
        #EPD_W21_WriteDATA(picData_R[i]) #Transfer the actual displayed data

    #Refresh
    EPD_W21_WriteCMD(0x12)		#DISPLAY REFRESH 	
    utime.sleep(0.01)	        #!!!The delay here is necessary, 200uS at least!!! 
    lcd_chkstatus()          #waiting for the electronic paper IC to release the idle signal

#display 
def PIC_display_GUI(picData,mode):
    #Write Data
    if mode==0: #BW
        EPD_W21_WriteCMD(0x10)       #Transfer old data
        for i in range(15000): 
            EPD_W21_WriteDATA(picData[i])
    if mode==1: #R
        EPD_W21_WriteCMD(0x13)		     #Transfer new data
        for i in range(15000):
            EPD_W21_WriteDATA(picData[i]) #Transfer the actual displayed data
        #Refresh
        EPD_W21_WriteCMD(0x12)		#DISPLAY REFRESH 	
        utime.sleep(0.01)	        #!!!The delay here is necessary, 200uS at least!!! 
        lcd_chkstatus()          #waiting for the electronic paper IC to release the idle signal


#Clear screen
def PIC_display_Clear():
    #Write Data
    EPD_W21_WriteCMD(0x10)	       #Transfer old data
    for j in range(15000):  	
        EPD_W21_WriteDATA(0xFF) 
    EPD_W21_WriteCMD(0x13)		     #Transfer new data
    for j in range(15000):        
        EPD_W21_WriteDATA(0xFF)  #Transfer the actual displayed data
    #Refresh
    EPD_W21_WriteCMD(0x12)		#DISPLAY REFRESH 	
    utime.sleep(0.01)	             #!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus()         #waiting for the electronic paper IC to release the idle signal
#Enter deep sleep mode 
def EPD_sleep(): 
    EPD_W21_WriteCMD(0X50)  #VCOM AND DATA INTERVAL SETTING			
    EPD_W21_WriteDATA(0xf7) #WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	

    EPD_W21_WriteCMD(0X02)  	#power off
    lcd_chkstatus()          #waiting for the electronic paper IC to release the idle signal
    EPD_W21_WriteCMD(0X07)  	#deep sleep
    EPD_W21_WriteDATA(0xA5)
 
 
#Main function part
while True:
    #############MicroPython  GUI############### 
    width=400
    height=300         
    buffer = bytearray(height * width // 8)
    fbuf = framebuf.FrameBuffer(buffer, width, height, framebuf.MONO_HLSB)
    #Picture
    EPD_init() #EPD init
    #BW
    fbuf.fill(0xff) #white background
    fbuf.text('www.good-display.cn', 145, 0, 0x00) #s, x, y[, c]
    fbuf.hline(145, 10, 152, 0x00)
    fbuf.text("Raspberry Pico", 165, 16, 0x00)
    PIC_display_GUI(buffer,0)#EPD GUI  
    #古
    #R
    fbuf.fill(0xff) #white background
    fbuf.vline(213, 40, 50, 0x00)#x, y, w, c
    fbuf.hline(173, 70, 80, 0x00)#x, y, w, c
    fbuf.rect(188, 92, 50, 50, 0x00)
    PIC_display_GUI(buffer,1)#EPD GUI
    EPD_sleep()#EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    utime.sleep(3) #delay 3s
     #Clear
    EPD_init() #EPD init
    PIC_display_Clear()#EPD Clear
    EPD_sleep()#EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    utime.sleep(2) #delay 2s 
    while 1:
        led_onboard.toggle()
        utime.sleep(1) #delay 1s



 
    
    
    

   
    
    
    
