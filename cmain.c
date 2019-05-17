//const char *str = "Hello C World";
#include "interrupt.h"
#include "common.h"
#include "timer.h"

#define PANIC(err_msg) PANIC_FUNC(err_msg,__FILE__,__LINE__)

char * const vidptr = (char *)0xb8000;
unsigned global_vid_pointer = 80;
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
   
    while(str[i])
    {
		if(str[i] == '\n')
		{
			global_vid_pointer = global_vid_pointer - (global_vid_pointer % 80) + 80;
		}
		else
		{
			vidptr[global_vid_pointer<<1] = str[i];
			vidptr[(global_vid_pointer<<1)+1] = 0x0f;
			++global_vid_pointer;
		}
		if(global_vid_pointer == 80*25) scroll();
		++i;
    }
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

char* itos (int value, const unsigned base)
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
	itos(line, 10);
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
idt_gate_t idt_gate[48] __attribute__((aligned(8)));

idt_register_t idt_register;

void isr_handler(registers_t regs)
{
	print("recieved interrupt: ");
	print(itos(regs.num, 10));
	print("\n");
	print("error code: ");
	print(itos(regs.err_code, 10));
	print("\n");
	while(1);
}

static void idt_set_gate(const unsigned int index, const unsigned int offset, const unsigned short int selector, const unsigned char type_attr)
{
	idt_gate[index].base_lo = offset & 0xFFFF;
	idt_gate[index].base_hi = (offset >> 16) & 0xFFFF;
	
	idt_gate[index].sel = selector;
	idt_gate[index].always0 = 0;
	idt_gate[index].flags = type_attr;
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

	idt_set_gate(32, (unsigned int)irq0, 0x08, 0x08E);
	idt_set_gate(33, (unsigned int)irq1, 0x08, 0x08E);
	idt_set_gate(34, (unsigned int)irq2, 0x08, 0x08E);
	idt_set_gate(35, (unsigned int)irq3, 0x08, 0x08E);
	idt_set_gate(36, (unsigned int)irq4, 0x08, 0x08E);
	idt_set_gate(37, (unsigned int)irq5, 0x08, 0x08E);
	idt_set_gate(38, (unsigned int)irq6, 0x08, 0x08E);
	idt_set_gate(39, (unsigned int)irq7, 0x08, 0x08E);
	idt_set_gate(40, (unsigned int)irq8, 0x08, 0x08E);
	idt_set_gate(41, (unsigned int)irq9, 0x08, 0x08E);
	idt_set_gate(42, (unsigned int)irq10, 0x08, 0x08E);
	idt_set_gate(43, (unsigned int)irq11, 0x08, 0x08E);
	idt_set_gate(44, (unsigned int)irq12, 0x08, 0x08E);
	idt_set_gate(45, (unsigned int)irq13, 0x08, 0x08E);
	idt_set_gate(46, (unsigned int)irq14, 0x08, 0x08E);
	idt_set_gate(47, (unsigned int)irq15, 0x08, 0x08E);

	outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0xff);
    outb(0xA1, 0xff);

	idt_register.base = (unsigned int)&idt_gate;
	idt_register.limit = sizeof(idt_gate_t) * 48 - 1;

	asm volatile(
		"sti\n\t"
		"lidt [%0]"
		:
		:"m"(idt_register)
	);
}	
//-------------------------------
//----------TIMER----------------

unsigned tick = 0;

void PIT_handler(unsigned tick)
{
	print("tick! : ");
	print(itos(tick, 10));
	print("\n");
}

void timer_callback()
{
	tick++;
	PIT_handler(tick);
}

void init_timer(unsigned freq)
{
	unsigned divider = 1193182/freq;
	unsigned char low_byte = (unsigned char)(divider & 0xff);
	unsigned char high_byte = (unsigned char)((divider >> 8) & 0xff);
	outb(0x43, 0x36);
	outb(0x40, low_byte);
	outb(0x40, high_byte);
	unsigned char a = inb(MASTER_DATA);
	a &= ~1;
	outb(MASTER_DATA, a);
}

void irq_handler(registers_t regs)
{
	print("IRQ: ");
	print(itos(regs.num-32, 10));
	print("\n");
	if(regs.num == 32)
	{
		timer_callback();
	}
	if(regs.num >= 40)
	{
		outb(SLAVE_CMD, 0x20); 
	}
	outb(MASTER_CMD, 0x20);
	//else while(1);
}

//_______________________________

int cmain()
{
	//PANIC_FUNC("Error", __FILE__, __LINE__);
	//PANIC("ERROR");
	//print("Hello World on C\n");
	init_idt();
	//asm volatile("int 32");
	init_timer(1);
	//while(1) timer_callback();
	//asm volatile("int 35");
	//asm volatile("int 13");
	return 0;
}
