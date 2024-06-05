/*Port A base address:0x40004000*/
#define 	GPIOA_DATA_R		(*((volatile unsigned long*)0x400043FC))
#define 	GPIOA_DIR_R			(*((volatile unsigned long*)0x40004400))
#define 	GPIOA_DEN_R			(*((volatile unsigned long*)0x4000451C))

/*PORT F base address:0x40025000*/
#define 	GPIOF_DATA_R		(*((volatile unsigned long*)0x400253FC))
#define 	GPIOF_DIR_R			(*((volatile unsigned long*)0x40025400))
#define 	GPIOF_DEN_R			(*((volatile unsigned long*)0x4002551C))

/*PORT E base address:0x40024000*/   
#define 	GPIOE_AFSEL_R		(*((volatile unsigned long*)0x40024420))
#define 	GPIOE_DIR_R			(*((volatile unsigned long*)0x40024400))
#define 	GPIOE_DEN_R			(*((volatile unsigned long*)0x4002451C))
#define 	GPIOE_AMSEL_R		(*((volatile unsigned long*)0x40024528))
#define 	GPIOE_PCTL_R		(*((volatile unsigned long*)0x4002452C))
