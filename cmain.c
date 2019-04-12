//const char *str = "Hello C World";
#include "interrupt.h"

#define PANIC(err_msg) PANIC_FUNC(err_msg,__FILE__,__LINE__)

char * const vidptr = (char *)0xb8000;
unsigned global_vid_pointer = 0;
char dest[1024] = {0};

void scroll()
{
	unsigned tmp=0;
	
	while(tmp<80*24)
	{
		vidptr[tmp<<1] = vidptr[(tmp<<1) + 80*2];
		++tmp;
	}

	while(tmp<80*25)
	{	
		vidptr[tmp<<1] = ' ';
		++tmp;
	}
	
	global_vid_pointer = 80*24;
}


void cclear(void)
{
    unsigned j=0;
    
    while(j<80*25)
    {
		vidptr[j<<1] = ' ';
		vidptr[(j<<1)+1] = 0x02;
		++j;
    }
}

void print(const char str[])
{
    unsigned i=0;
   
    while(str[i] != '\0')
    {
		if(str[i] == '\n')
		{
			global_vid_pointer = global_vid_pointer - (global_vid_pointer % 80) + 80;
		}
		vidptr[global_vid_pointer<<1] = str[i];
		vidptr[(global_vid_pointer<<1)+1] = 0x0f;
		++global_vid_pointer;
		++i;
    }
	if(global_vid_pointer == 80*25) scroll();
    return;
}

void reverse(char* str, int length)
{
	unsigned start = 0;
	unsigned end = length - 1;
	while (start < end)
	{
		char tmp = str[start];
		str[start++] = str[end];
		str[end--] = tmp;
	}
}

char* itos (int value, char* dest, const unsigned base)
{
	unsigned char i = 0;
	unsigned char isNegative = 0;

	if (!value)
	{
		dest[i++] = '0';
		dest[i] = '\0';
		return dest;
	}
	
	if (value < 0 && base == 10)
	{
		isNegative = 1;
		value = -value;
	}

	while (value)
	{
		unsigned char digit = value % base;
		if(digit>9) digit += 0x57;
		else digit += '0';
		dest[i++] = digit;
		value /= base;
	}

	if (isNegative)
	{
		dest[i++] = '-';
	}
	
	dest[i] = '\0';
	reverse(dest, i);
	return dest;
}

void PANIC_FUNC(const char* err_msg, const char* filename, int line)
{
	itos(line, dest, 10);
	print("PANIC: ");
	print(filename);
	print(":");
	print(dest);
	print(": error: ");
	print(err_msg);
	print("\n");
	while (1);
}
//-------------------------------
//Start IDT
//-------------------------------
idt_entry_t idt_entries[32] __attribute__((aligned(8)));

idt_ptr_t idt_ptr;

void isr_handler(registers_t regs)
{
	print("recieved interrupt: ");
	print(itos(regs.num,dest, 10));
	print("\n");
	while(1);
}

static void idt_set_gate(const unsigned int index, const unsigned int offset, const unsigned short int selector, const unsigned char type_attr)
{
	idt_entries[index].base_lo = offset & 0xFFFF;
	idt_entries[index].base_hi = (offset >> 16) & 0xFFFF;
	
	idt_entries[index].sel = selector;
	idt_entries[index].always0 = 0;
	idt_entries[index].flags = type_attr;
}

void init_idt()
{
	idt_set_gate(0, (unsigned int)isr0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned int)isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned int)isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned int)isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned int)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned int)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned int)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned int)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned int)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned int)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned int)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned int)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned int)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned int)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned int)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned int)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned int)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned int)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned int)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned int)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned int)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned int)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned int)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned int)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned int)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned int)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned int)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned int)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned int)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned int)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned int)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned int)isr31, 0x08, 0x8E);

	idt_ptr.base = (unsigned int)&idt_entries;
	idt_ptr.limit = sizeof(idt_entry_t) * 32 - 1;

	asm volatile(
		"lidt [%0]"
		:
		:"m"(idt_ptr)
	);
}	
//-------------------------------

int cmain()
{
	//PANIC_FUNC("Error", __FILE__, __LINE__);
	//PANIC("ERROR");
	//print("Hello World on C\n");
	init_idt();
	asm volatile("int 17");
	return 0;
}
