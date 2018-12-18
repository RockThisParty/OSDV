const char *str = "Hello C World";

void cprint(void)
{
    char *vidptr = (char *)0xb8000;
    unsigned j=80*3, i=0;
    
    /*while(j<80*25)
    {
	vidptr[j<<1] = ' ';
	vidptr[(j<<1)+1] = 0x02;
	j++;
    }
    */

    while(str[i] != '\0')
    {
	vidptr[j<<1] = str[i];
	vidptr[(j<<1)+1] = 0x0f;
	++j;
	++i; 
    }
    return;
}
