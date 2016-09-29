/******************************************************************************
*	kernel.ld                                                              
*	 by Filippo Giuliani                                                   
*                                                                              
*	A linker script for generation of raspberry pi kernel images.          
******************************************************************************/
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",                               
          "elf32-littlearm")                                                   
OUTPUT_ARCH(arm)                                                               
ENTRY(_start)                                                                  
SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");   
ENTRYPOINT = 0x8000;                                                           
SECTIONS {                                                                     
	/*                                                                     
	* First and formost we need the .text.startup section, containing the  
	* code to be run first. We allow room for the ATAGs and stack and      
	* conform to the bootloader's expectation by putting this code at     
	* 0x8000.                                                              
	*/                                                                     
	. = ENTRYPOINT;                                                        
	__sCode = .;                                                           
	.init :                                                                
	{                                                                      
		*(.init)                                                       
	}                                                                      

	__sText = .;                                                  
	.text :                                                        
	{                                                                      

		__sBootText = .;                        
		boot/bin/boot.o(.text*)            
		. = ALIGN (0x10);                       
		__eBootText = .;                        

		__sAsmText = .;                        
		asm/bin/asm.o(.text*)            
		. = ALIGN (0x10);                       
		__eAsmText = .;                        

		__sKernelText = .;                        
		kernel/bin/kernel.o(.text*)            
		. = ALIGN (0x10);                       
		__eKernelText = .;                        

		__sBaselibText = .;                        
		baselib/bin/baselib.o(.text*)            
		. = ALIGN (0x10);                       
		__eBaselibText = .;                        

		__sDeviceText = .;                        
		device/bin/device.o(.text*)            
		. = ALIGN (0x10);                       
		__eDeviceText = .;                        

	}                                                                      
	__eText = .;                                                  
	. = ALIGN (0x10);                                      

	__sData = .;                                                  
	.data :                                                        
	{                                                                      

		__sBootData = .;                        
		boot/bin/boot.o(.data)            
		. = ALIGN (0x10);                       
		__eBootData = .;                        

		__sAsmData = .;                        
		asm/bin/asm.o(.data)            
		. = ALIGN (0x10);                       
		__eAsmData = .;                        

		__sKernelData = .;                        
		kernel/bin/kernel.o(.data)            
		. = ALIGN (0x10);                       
		__eKernelData = .;                        

		__sBaselibData = .;                        
		baselib/bin/baselib.o(.data)            
		. = ALIGN (0x10);                       
		__eBaselibData = .;                        

		__sDeviceData = .;                        
		device/bin/device.o(.data)            
		. = ALIGN (0x10);                       
		__eDeviceData = .;                        

	}                                                                      
	__eData = .;                                                  
	. = ALIGN (0x10);                                      

	__sRodata = .;                                                  
	.rodata :                                                        
	{                                                                      

		__sBootRodata = .;                        
		boot/bin/boot.o(.rodata*)            
		. = ALIGN (0x10);                       
		__eBootRodata = .;                        

		__sAsmRodata = .;                        
		asm/bin/asm.o(.rodata*)            
		. = ALIGN (0x10);                       
		__eAsmRodata = .;                        

		__sKernelRodata = .;                        
		kernel/bin/kernel.o(.rodata*)            
		. = ALIGN (0x10);                       
		__eKernelRodata = .;                        

		__sBaselibRodata = .;                        
		baselib/bin/baselib.o(.rodata*)            
		. = ALIGN (0x10);                       
		__eBaselibRodata = .;                        

		__sDeviceRodata = .;                        
		device/bin/device.o(.rodata*)            
		. = ALIGN (0x10);                       
		__eDeviceRodata = .;                        

	}                                                                      
	__eRodata = .;                                                  
	. = ALIGN (0x10);                                      

	__sBss = .;                                                  
	.bss :                                                        
	{                                                                      

		__sBootBss = .;                        
		boot/bin/boot.o(.bss* COMMON)            
		. = ALIGN (0x10);                       
		__eBootBss = .;                        

		__sAsmBss = .;                        
		asm/bin/asm.o(.bss* COMMON)            
		. = ALIGN (0x10);                       
		__eAsmBss = .;                        

		__sKernelBss = .;                        
		kernel/bin/kernel.o(.bss* COMMON)            
		. = ALIGN (0x10);                       
		__eKernelBss = .;                        

		__sBaselibBss = .;                        
		baselib/bin/baselib.o(.bss* COMMON)            
		. = ALIGN (0x10);                       
		__eBaselibBss = .;                        

		__sDeviceBss = .;                        
		device/bin/device.o(.bss* COMMON)            
		. = ALIGN (0x10);                       
		__eDeviceBss = .;                        

	}                                                                      
	__eBss = .;                                                  
	. = ALIGN (0x10);                                      

	. = ALIGN(32 / 8);                                                     
	. = ALIGN(32 / 8);                                                     
                                                                               
	__eCode = .;                                                           
                                                                               
	.stack         0x80000 :                                               
	{                                                                      
		_stack = .;                                                    
		*(.stack)                                                      
	}                                                                      
                                                                               
	/*                                                                     
	* Finally comes everything else. A fun trick here is to put all other  
	* sections into this section, which will be discarded by default.      
	*/                                                                     
	/DISCARD/ : {                                                          
		*(*)                                                           
	}                                                                      
}                                                                              

