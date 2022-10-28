#include"charOperations.h"

unsigned int length(char *data)
{
    unsigned int i=0;
    while(data[i]!='\0')
    {
        i++;
    }
    return i;

}

char* resizetoUsefulLength(char *data)
{
    unsigned int original_size = length(data);
    char* res = new char[original_size];
    for(size_t i=0;i<=original_size;i++)
        res[i] = data[i];

    return res;
}

char* floatTochar(float x)
{
	char* buffer = new char[64];
    snprintf(buffer, 64, "%f", x);
    char* res = resizetoUsefulLength(buffer);
    return res;
}

char* intTochar(int x)
{
	char* buffer = new char[64];
    snprintf(buffer, 64, "%d", x);
    char* res = resizetoUsefulLength(buffer);
    return res;
}

void charprint(char* data)
{
    int i=0;
    while(data[i]!='\0')
    {
        std::cout<<data[i];
        i++;
    }
    std::cout<<"\n";
}

bool quit_compare(char* data)
{
    if(data==NULL)
        return false;
    else
    {
    const char* compare = "quit";
    int flag = 0;
    for(int i=0;i<4;i++)
    {
        if(data[i]!=compare[i])
            flag = 1;
    }
    if(flag!=0)
        return false;
    else
        return true;
    }
}

char* append_m(char *data1, char* data2)
{
    size_t len1 = length(data1);
    size_t len2 = length(data2);
    char* appeneded = new char[len1+len2];
    int j=0;
    for(size_t i=0; i<len1; i++)
    {
        appeneded[j] = data1[i];
        j++;
    }
    for(size_t i=0; i<len2; i++)
    {
        appeneded[j] = data2[i];
        j++;
    }
    return appeneded;
}