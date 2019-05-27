#include <stdio.h>  
#include <unistd.h>  

int main(int argc, char *argv[])  
{ 
    int opt;
    while((opt = getopt(argc, argv, "s:b:")) != -1)  
    {  
        switch(opt)  
        {   
            case 's':  
                printf("%s\n", optarg); 
                break;  
            case 'b':  
                printf("%s\n", optarg);  
                break;
        }  
    }  
    return 0; 
}
