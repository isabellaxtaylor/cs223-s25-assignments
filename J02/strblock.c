#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char word[31];
    printf("Enter a string: ");
    scanf("%s",word);
    
    int length=strlen(word);
    char* array = malloc(length * length * sizeof(char));
    memset(array,' ',length*length);
    
    for (int i=0;i<length;i++) {
        array[i]=word[i];
        array[(length-1)*length+i]=word[i];
        array[i*length+i]=word[i];
    }
    for (int i=0;i<length;i++) {
        for (int j=0;j<length;j++) {
        printf("%c",array[i*length+j]);
        }
      printf("\n");
    }
    free(array);
    return 0;
}
