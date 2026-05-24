#include <cs50.h>
#include <stdio.h>

void calc_dig(int w);
int x, y;
int main(void)
{
 long mod1=1;
  //Prompt user for input

    long input = get_long("Please enter your credit card number: ");

  // Checksum by LUHN's Algorith to determine validity -->

  //1. determine number of digits (let number of digits be 'z')
   int z = 0;

     int q = (input/(1e12));
     int j = (input/(1e13));
     int k = (input/(1e14));
     int l = (input/(1e15));
     int m = (input/(1e16));
     int n = (input/(1e17));

      if(q == 0 && j == 0 && k == 0 && l == 0 && m == 0 && n == 0)
       {
        printf("INVALID\n");
        return 0;
       }
      else if(q != 0 && j == 0 && k == 0 && l == 0 && m == 0 && n == 0 )
       {
           z = 13;
       }
      else if(q != 0 && j != 0 && k == 0 && l == 0 && m == 0 && n == 0 )
       {
           z = 14;
       }
      else if(q != 0 && j != 0 && k != 0 && l == 0 && m == 0 && n == 0)
       {
           z = 15;
       }
      else if(q != 0 && j != 0 && k != 0 && l != 0 && m == 0 && n == 0)
       {
           z=16;
       }
      else if(q != 0 && j!= 0 && k != 0 && l != 0 && m != 0 && n == 0 )
        {
            printf("INVALID\n");
            return 0;
        }
      else if(q != 0 && j!= 0 && k != 0 && l != 0 && m != 0 && n != 0 )
        {
          printf("INVALID\n");
          return 0;
        }
       else
       {
        printf("INVALID\n");
        return 0;
       }

   //2. extract digits of the input digit by digit
     int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16;
     int an1,an2,an3,an4,an5,an6,an7,an8,an9,an10,an11,an12,an13,an14,an15,an16;
     int v;
     int t;


     for (int ab=1; ab <= z; ab++)
     {
        mod1 = mod1*10;
     }
        long mod2=mod1/10;
        long mod3=mod2/10;
        long mod4=mod3/10;
        long mod5=mod4/10;
        long mod6=mod5/10;
        long mod7=mod6/10;
        long mod8=mod7/10;
        long mod9=mod8/10;
        long mod10=mod9/10;
        long mod11=mod10/10;
        long mod12=mod11/10;
        long mod13=mod12/10;
        long mod14=mod13/10;
        long mod15=0;
        long mod16=0;

       if(mod14 !=0)
       {
        mod15=mod14/10;
       }
       else {
        a14=0;
       }
       if(mod15 !=0)
       {
        mod16=mod15/10;
       }
       else {
        a15=0;
       }


       a1=((input % mod1)/((mod1/10)));
       a2=((input % mod2)/((mod2/10)));
       a3=((input % mod3)/((mod3/10)));
       a4=((input % mod4)/((mod4/10)));
       a5=((input % mod5)/((mod5/10)));
       a6=((input % mod6)/((mod6/10)));
       a7=((input % mod7)/((mod7/10)));
       a8=((input % mod8)/((mod8/10)));
       a9=((input % mod9)/((mod9/10)));
       a10=((input % mod10)/((mod10/10)));
       a11=((input % mod11)/((mod11/10)));
       a12=((input % mod12)/((mod12/10)));
       a13=((input % mod13)/((mod13/10)));
     if(mod14 !=0 && mod14 !=1)
     {
       a14=((input % mod14)/((mod14/10)));
     }
     else if(mod14 == 1)
     {
        a14=(input % 10);
     }
     else{
        a14=0;
     }

     if(mod15 !=0 && mod15 !=1)
     {
       a15=((input % mod15)/((mod15/10)));
     }
     else if(mod15 == 1)
       {a15=(input % 10);
     }
     else {
        a15=0;
     }

     if(mod16 !=0 && mod16 !=1)
     {
       a16=((input % mod16)/((mod16/10)));
     }
     else if(mod16 == 1)
     {
        a16=(input % 10);
     }
     else{
        a16=0;
     }

   //3. apply the conditional for LUHN's algorithm
    switch(z)
    {
      case 13:

      an12 = a12*2;
      an10 = a10*2;
      an8 = a8*2;
      an6 = a6*2;
      an4 = a4*2;
      an2 = a2*2;

     if(an12>9)
     {
      calc_dig(an12);
      an12 = y + x;
     }
     if(an10 >9)
     {
      calc_dig(an10);
      an10 = y + x;
     }
     if(an8 >9)
     {
      calc_dig(an8);
      an8 = y + x;
     }
     if(an6>9)
     {
      calc_dig(an6);
      an6 = y + x;
     }
     if(an4 >9)
     {
      calc_dig(an4);
      an4 = y + x;
     }
     if(an2 >9)
     {
        calc_dig(an2);
        an2 = y + x;
     }
     v = an2+an4+an6+an8+an10+an12;
     t = a1+a3+a5+a7+a9+a11+a13;

  int sum13 = v + t;

  if((sum13 % 10) != 0)
  {
    printf("INVALID\n");
    return 0;
  }
     break;

     case 14:

      an13 = a13*2;
      an11 = a11*2;
      an9 = a9*2;
      an7 = a7*2;
      an5 = a5*2;
      an3 = a3*2;
      an1 = a1*2;

     if(an13>9)
     {
      calc_dig(an13);
      an13 = y + x;
     }
     if(an11 >9)
     {
      calc_dig(an11);
      an11 = y + x;
     }
     if(an9 >9)
     {
      calc_dig(an9);
      an9 = y + x;
     }
     if(an7>9)
     {
      calc_dig(an7);
      an7 = y + x;
     }
     if(an5 >9)
     {
      calc_dig(an5);
      an5 = y + x;
     }
     if(an3 >9)
     {
        calc_dig(an3);
        an3 = y + x;
     }
     if(an1 >9)
     {
      calc_dig(an1);
      an1 = y+x;
     }

     v = an1+an3+an5+an7+an9+an11+an13;
     t = a2+a4+a6+a8+a10+a12+a14;

  int sum14 = v + t;

  if((sum14 % 10) != 0)
  {
    printf("INVALID\n");
    return 0;
  }
     break;

     case 15:

      an14 = a14*2;
      an12 = a12*2;
      an10 = a10*2;
      an8 = a8*2;
      an6 = a6*2;
      an4 = a4*2;
      an2 = a2*2;

     if(an14>9)
     {
      calc_dig(an14);
      an14 = y + x;
     }
     if(an12 >9)
     {
      calc_dig(an12);
      an12 = y + x;
     }
     if(an10 >9)
     {
      calc_dig(an10);
      an10 = y + x;
     }
     if(an8>9)
     {
      calc_dig(an8);
      an8 = y + x;
     }
     if(an6 >9)
     {
      calc_dig(an6);
      an6 = y + x;
     }
     if(an4 >9)
     {
        calc_dig(an4);
        an4 = y + x;
     }
     if(an2 >9)
     {
      calc_dig(an2);
      an2 = y+x;
     }
     v = an2+an4+an6+an8+an10+an12+an14;
     t = a1+a3+a5+a7+a9+a11+a13+a15;

  int sum15 = v + t;

  if((sum15 % 10) != 0)
  {
    printf("INVALID\n");
    return 0;
  }
     break;

     case 16:

      an15 = a15*2;
      an13 = a13*2;
      an11 = a11*2;
      an9 = a9*2;
      an7 = a7*2;
      an5 = a5*2;
      an3 = a3*2;
      an1 = a1*2;

     if(an15 >9)
     {
      calc_dig(an15);
      an15 = y + x;
     }
     if(an13 >9)
     {
      calc_dig(an13);
      an13 = y + x;
     }
     if(an11 >9)
     {
      calc_dig(an11);
      an11 = y + x;
     }
     if(an9 >9)
     {
      calc_dig(an9);
       an9 = y + x;
     }
     if(an7>9)
     {
      calc_dig(an7);
      an7 = y + x;
     }
     if(an5 >9)
     {
      calc_dig(an5);
      an5 = y + x;
     }
     if(an3 >9)
     {
        calc_dig(an3);
        an3 = y + x;
     }
     if(an1 >9)
     {
      calc_dig(an1);
      an1 = y + x;
     }
     v = an1+an3+an5+an7+an9+an11+an13+an15;
     t = a2+a4+a6+a8+a10+a12+a14+a16;

  int sum16 = v + t;

  if((sum16 % 10) != 0)
  {
    printf("INVALID\n");
    return 0;
  }
     break;
    }

                                            // ----CARD NUMBER VALIDITY VERIFIED---- //

 // Identifying the first two digits
     long p;
     if(z == 13)
     {
      p = (input/1e11);
     }
     if( z == 14)
     {
      p = (input/1e12);
     }
     if( z == 15)
     {
      p = (input/1e13);
     }
    if( z == 16)
      {
        p = (input/1e14);
      }


 // Mapping the bank to the input
    string bank;
    int idf;
   switch(p)
    {
      case 34:
      case 37:
        bank = "AMEX";
        idf = 1;
      break;

      case 51: case 52: case 53: case 54: case 55:
        bank = "MASTERCARD";
        idf = 2;
      break;

      case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49:
       bank = "VISA";
       idf = 3;
      break;
      default:
      printf("INVALID\n");
      return 0;

    }

  // Ouput to the terminal/consumer

   if(z == 13 && idf == 3)
   {
    printf("VISA\n");
   }
   else if(z == 15 && idf == 1)
   {
    printf("AMEX\n");
   }
   else if(z == 16 && idf == 2)
   {
    printf("MASTERCARD\n");
   }
   else if( z == 16 && idf == 3)
    {
     printf("VISA\n");
    }
   else{
    printf("INVALID\n");
   }

}

void calc_dig(int w)
{
 x=0;
 y=0;

   y = w % 10;
   x = ((w % 100)/10);
}
