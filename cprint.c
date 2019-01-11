//const char *str = "Hello C World";
char * const vidptr = (char *)0xb8000;
unsigned global_vid_pointer = 0;

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

void cprint(char str[])
{
    unsigned i=0;
   
    while(str[i] != '\0')
    {
	vidptr[global_vid_pointer<<1] = str[i];
	vidptr[(global_vid_pointer<<1)+1] = 0x0f;
	++global_vid_pointer;
	++i; 
    }
	if(global_vid_pointer == 80*25) scroll();
    return;
}

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

void cmain()
{
	cprint("fghjkl");
	return;
}
