#include <graphics.h>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>

// x and y array values means coordinates
// a=number of coordinates
// xk and yk center of circle r means radius
int dosya_oku(float x[],float y[],int *a); //--> reading data from file txt
double dist(float a, float b); //--> length calculation
int hesapla(float x[],float y[],int *a,float *xk,float *yk,float *r); //--> center and radius calculate
void cizimyap(float *xk,float *yk,float *r,float x[],float y[],int *a); // draw circle, points and spline
int fact(int n)
{
    if(n==0)
        return 1;
    else
        n*fact(n-1);
}
int comb(int n,int r)
{
    return (fact(n)/(fact(n-r)*fact(r)));
}
int main()
{
    int a;
    float x[100000];
    float y[100000];
    float xk,yk,r;
    dosya_oku(x,y,&a);
	hesapla(x,y,&a,&xk,&yk,&r);
    cizimyap(&xk,&yk,&r,x,y,&a);
}


int dosya_oku(float x[],float y[],int *a)
{
    FILE *dosya;
    int i=0;

    dosya=fopen("krdnt.txt","r");
    if(dosya!=NULL)
    {
        printf("dosya bulundu\n");
        while(!feof(dosya))
        {
            fscanf(dosya,"%f",&x[i]);
            printf("dosyadan okunan deger %f\n",x[i]);
            fscanf(dosya,"%f",&y[i]);
            printf("dosyadan okunan deger %f\n",y[i]);

            i=i+1;
            *a=i;

        }

        fclose(dosya);

    }
    else
    {
        printf("dosya bulunamadi");
    }
}
int hesapla(float x[],float y[],int *a,float *xk,float *yk,float *r)
{
// sumx and sumy means circle center coordinates
    double k1,k2;
    for (int i = 0; i < *a; i++)
    {
        *xk+=x[i];
        *yk+=y[i];
    }
    *xk/= *a;
    *yk/= *a;
    double p= 0.1;
    for (int i = 0; i < 30000; i++)
    {
        int f = 0;
        k1=dist(*xk-x[0],*yk-y[0]);
        for (int j=1; j<*a; j++)
        {
            k2=dist(*xk-x[j],*yk-y[j]);
            if (k1<k2)
            {
                k1 =k2;
                f = j;
            }
        }
        *xk+=(x[f]-*xk)*p;
        *yk+=(y[f]-*yk)*p;
        p*= 0.999;
    }
    printf("merkez= {%.3f,%.3f}\nradius= %.4f",*xk,*yk,sqrt(k1));
    *r=sqrt(k1);
}

double dist(float a, float b)
{
    return a*a+b*b;
}
void cizimyap(float *xk,float *yk,float *r,float x[],float y[],int *a)
{
    int i;
    int wid1 = initwindow(840,800);
    setcurrentwindow(wid1);
    line(0,400,840,400);
    line(420,0,420,800);

    *xk=420+(*xk*20);
    *yk=400-(*yk*20);
    *r=*r*20;
    setcolor(LIGHTCYAN);

    char sayi[100];
    int deger;
    int artis=0;

    for(i=0; i<=20; i++)
    {
        sayi[i]=i;
        deger=sayi[i];
        sprintf(sayi,"%d",deger);
        outtextxy(420+artis,402,sayi);
        artis=artis+20;
    }
    artis=0;
    for(i=0; i<=20; i++)
    {
        sayi[i]=i;
        deger=(-sayi[i]);
        sprintf(sayi,"%d",deger);
        outtextxy(420-artis,402,sayi);
        artis=artis+20;
    }
    artis=0;
    for(i=0; i<=20; i++)
    {
        sayi[i]=i;
        deger=(-sayi[i]);
        sprintf(sayi,"%d",deger);
        outtextxy(422,402+artis,sayi);
        artis=artis+20;
    }
    artis=0;
    for( i=0; i<=20; i++)
    {
        sayi[i]=i;
        deger=sayi[i];
        sprintf(sayi,"%d",deger);
        outtextxy(422,402-artis,sayi);
        artis=artis+20;
    }
    setcolor(YELLOW);
    circle(*xk,*yk,*r);
    setcolor(RED);
    // given coordinate points
    for( i=0; i<*a; i++)
    {

        x[i]=420+(x[i]*20);
        y[i]=400-(y[i]*20);
        circle(x[i],y[i],1);
        circle(x[i],y[i],2);
        circle(x[i],y[i],3);
        circle(x[i],y[i],4);

    }
    // circcle center and radius drawing
    setcolor(YELLOW);
    circle(*xk,*yk,1);
    circle(*xk,*yk,2);
    circle(*xk,*yk,2);
    circle(*xk,*yk,3);
    circle(*xk,*yk,4);
    outtextxy(*xk,*yk,"m");
    setcolor(RED);
    // yaricap cizimi::
    setcolor(LIGHTBLUE);
    float eb=dist(x[0],y[0]);
    int m=0;
    for (int i=0; i<*a; i++)
    {
        if(eb<=dist(x[i],y[i]))
        {
            m=m+1;
            eb=dist(x[i],y[i]);
        }
    }
    line(*xk,*yk,x[m],y[m]);

    float t,px,py;
    int n=*a-1;
    for(t=0; t<=1; t+=0.0001)
    {
        px=0;
        py=0;
        for(i=0; i<=n; i++)
        {
            px=px+(comb(n,i)*pow(1-t,n-i)*pow(t,i)*x[i]);
            py=py+(comb(n,i)*pow(1-t,n-i)*pow(t,i)*y[i]);
        }
        putpixel(px,py,2);
    }
    getch();
    closegraph();
}
