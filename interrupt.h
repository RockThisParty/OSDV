#pragma once

//Структура описывающая шлюз прерываний
struct idt_entry_struct
{
	unsigned short base_lo;	//младшие 16 бит - куда происходит переход в случае прерывания
	unsigned short sel;	//переключатель сегмента ядра 
	unsigned char always0;	
	unsigned char flags;	
	unsigned short base_hi;	//старшие 16 бит - куда происходит переход
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

//Структура, описывающая указатель на массив обработчиков прерываний
struct idt_ptr_struct
{
	unsigned short limit;
	unsigned base;											//адрес первого элемента нашего массива idt_entry_t
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

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
