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
		boot/obj/boot.o(.text*);            
		. += __sBootText == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBootText = .;                        

		__sAsmText = .;                        
		asm/obj/asm.o(.text*);            
		. += __sAsmText == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eAsmText = .;                        

		__sKernelText = .;                        
		kernel/obj/kernel.o(.text*);            
		. += __sKernelText == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eKernelText = .;                        

		__sBaselibText = .;                        
		baselib/obj/baselib.o(.text*);            
		. += __sBaselibText == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBaselibText = .;                        

		__sDeviceText = .;                        
		device/obj/device.o(.text*);            
		. += __sDeviceText == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eDeviceText = .;                        

	}                                                                      
	__eText = .;                                                  
	. = ALIGN (0x10);                                      

	__sData = .;                                                  
	.data :                                                        
	{                                                                      

		__sBootData = .;                        
		boot/obj/boot.o(.data);            
		. += __sBootData == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBootData = .;                        

		__sAsmData = .;                        
		asm/obj/asm.o(.data);            
		. += __sAsmData == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eAsmData = .;                        

		__sKernelData = .;                        
		kernel/obj/kernel.o(.data);            
		. += __sKernelData == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eKernelData = .;                        

		__sBaselibData = .;                        
		baselib/obj/baselib.o(.data);            
		. += __sBaselibData == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBaselibData = .;                        

		__sDeviceData = .;                        
		device/obj/device.o(.data);            
		. += __sDeviceData == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eDeviceData = .;                        

	}                                                                      
	__eData = .;                                                  
	. = ALIGN (0x10);                                      

	__sRodata = .;                                                  
	.rodata :                                                        
	{                                                                      

		__sBootRodata = .;                        
		boot/obj/boot.o(.rodata*);            
		. += __sBootRodata == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBootRodata = .;                        

		__sAsmRodata = .;                        
		asm/obj/asm.o(.rodata*);            
		. += __sAsmRodata == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eAsmRodata = .;                        

		__sKernelRodata = .;                        
		kernel/obj/kernel.o(.rodata*);            
		. += __sKernelRodata == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eKernelRodata = .;                        

		__sBaselibRodata = .;                        
		baselib/obj/baselib.o(.rodata*);            
		. += __sBaselibRodata == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBaselibRodata = .;                        

		__sDeviceRodata = .;                        
		device/obj/device.o(.rodata*);            
		. += __sDeviceRodata == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eDeviceRodata = .;                        

	}                                                                      
	__eRodata = .;                                                  
	. = ALIGN (0x10);                                      

	__sBss = .;                                                  
	.bss :                                                        
	{                                                                      

		__sBootBss = .;                        
		boot/obj/boot.o(.bss* COMMON);            
		. += __sBootBss == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBootBss = .;                        

		__sAsmBss = .;                        
		asm/obj/asm.o(.bss* COMMON);            
		. += __sAsmBss == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eAsmBss = .;                        

		__sKernelBss = .;                        
		kernel/obj/kernel.o(.bss* COMMON);            
		. += __sKernelBss == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eKernelBss = .;                        

		__sBaselibBss = .;                        
		baselib/obj/baselib.o(.bss* COMMON);            
		. += __sBaselibBss == . ? 0x10 : 0x0;
		. = ALIGN (0x10);                       
		__eBaselibBss = .;                        

		__sDeviceBss = .;                        
		device/obj/device.o(.bss* COMMON);            
		. += __sDeviceBss == . ? 0x10 : 0x0;
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

