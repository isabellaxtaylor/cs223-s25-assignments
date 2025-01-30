/***************************************************
 * password.c
 * Author: Isabella taylor
 * Date: 1/30/2025
 * Program: Bad Password Generator
 * Description: This program takes a word as input and generates a "bad" password
 * by replacing specific characters:
 *  - 'e' with '3'
 *  - 'i' with '1'
 *  - 'a' with '@'
 * 
 * The program then outputs the transformed password.
 */
#include <stdio.h>
#include <string.h>

int main() {
    char pass[100];
    char badPass[100] = {0};

    printf("Enter a word: ");
    scanf("%s", pass);

    int n = strlen(pass);

    for (int i = 0; i < n; i++) {  
        if (pass[i] == 'e') {
            badPass[i] = '3';  
        } 
        else if (pass[i] == 'i') {
            badPass[i] = '1';  
        } 
        else if (pass[i] == 'a') {
            badPass[i] = '@';  
        } 
        else {
            badPass[i] = pass[i];  
        }
    }
    
    badPass[n] = '\0';
    printf("Your bad password is %s\n", badPass);  

    return 0;
}
