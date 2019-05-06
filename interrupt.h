#pragma once

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define PIC_READ_IRR 0x0a
#define PIC_READ_ISR 0x0b
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

struct idt_gate_struct
{
	unsigned short base_lo;	//младшие 16 бит - куда происходит переход в случае прерывания
	unsigned short sel;
	unsigned char always0;	
	unsigned char flags;	
	unsigned short base_hi;	//старшие 16 бит - куда происходит переход
} __attribute__((packed));

typedef struct idt_gate_struct idt_gate_t;

struct idt_register_struct
{
	unsigned short limit;
	unsigned base;											
} __attribute__((packed));

typedef struct idt_register_struct idt_register_t;

struct registers
{
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;	//pushed from isr_common_stub
	unsigned int num, err_code;								//pushed from ISR
	unsigned int eip, cs, errflags, useresp, ss;
} __attribute__((packed));

typedef struct registers registers_t;

void isr_print();

void init_idt();


extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
