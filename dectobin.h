//
//  dectobin.h
//  Cifrado_RC4
//
//  Created by jonas on 25/02/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#ifndef Cifrado_RC4_dectobin_h
#define Cifrado_RC4_dectobin_h


#include<stdio.h>
void binario(int n)
{
    if (n!=0)
    {
        binario(n/2);
        printf("%i",n%2);
    }
}


void binario2(int n, int p){
    if (p != 8) {
        if (n != 0) {
            binario2(n/2, p+1);
            printf("%i",n%2);
        }
        if (n == 0) {
            binario2(n/2, p+1);
            printf("%i",0);
        }
    }
}
#endif
