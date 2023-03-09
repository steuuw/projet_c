#include <unistd.h>
#include <stdio.h>

void gd_putchar(char c){
    write(1, &c, 1);
}
int gd_putstr(char*str){
    int i;
    

    i = 0;
    

    while(str[i] != '\0'){
        gd_putchar(str[i]);
        
        i++;
    }
    
    return(i);
    
}
int main (void){
    int nb_put;
    nb_put = gd_putstr("Coucou");
    printf("%i\n", nb_put);
    return(1);
}