#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define Rockford '@'
#define pole_puste ' '
#define ziemia '+'
#define skala '#'
#define kamien 'O'
#define diament '$'
#define wyjscie 'X'

//Przy pierwszej poprawce usuniete fragment przy poruszaniu rockforda w gore, ktory niezgodnie z zasadami gry mogl przesuwac kamienie do gory

void dane_wejsciowe(char *plansza, int w, int k)
{
    getchar();
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < k; j++)
        {
            plansza[i*k + j] = (char) getchar();
        }
        getchar();
    }
}

void pozycja_Rockford(char *plansza, int w, int k,int *pozycja_Rockforda)// pokazuje w jakim miejscu planszy znajduje sie rockford
{
    for (int i = 0; i < w; i++)
        {
            for (int j = 0; j <k; j++)
            {
                if(plansza[i*k + j] == Rockford)
                {
                    *pozycja_Rockforda = i*k + j;
                }
               
            }
        }
}

void wypisywanie_planszy(char *plansza, int w, int k)
{
    printf("%d %d\n", w , k);
    
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j <k; j++)
        {
            printf("%c", plansza[i*k + j]);
        }
        printf("\n");
    }
}

void do_stanu_stabilnego_planszy(char *plansza, int w, int k)
{
     for (int i = 0; i < w; i++)
        {
            for (int j = 0; j <k; j++)
            {
                if (plansza[i*k + j] == kamien && plansza[(i + 1)*k +j] == pole_puste)
                {
                    plansza[i*k + j] = pole_puste;
                    plansza[(i + 1)*k +j] = kamien;
                }
                else if (plansza[i*k + j] == diament && plansza[(i + 1)*k +j] == pole_puste)
                {
                    plansza[i*k + j] = pole_puste;
                    plansza[(i + 1)*k +j] = diament;
                }
            }
        }
}

bool plansza_jest_niestabilna(char *plansza, int w, int k)
{
    for (int i = 0; i < w; i++)
        {
            for (int j = 0; j <k; j++)
            {
                if (plansza[i*k + j] == kamien && plansza[(i + 1)*k +j] == pole_puste)
                {
                    return true;
                }
                else if (plansza[i*k + j] == diament && plansza[(i + 1)*k +j] == pole_puste)
                {
                    return true;
                }
            }
        }
        return false;
}

int liczba_diamentow(char *plansza, int w, int k,int ilosc_diamentow)//zlicza diamenty na planszy
{
        
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j <k; j++)
            {
                if(plansza[i*k + j] == diament)
                {
                    ilosc_diamentow++;
                }
            }
        }
        return ilosc_diamentow;
}

// Cztery najblizsze funkcje odpowiadaja za ruch rockforda wylacznie w jednym z kierunkow
void ruch_Rockforda_w_prawo(char *plansza, int *pozycja_Rockforda,  int *ilosc_diamentow)
{
    if (plansza[*pozycja_Rockforda + 1] == pole_puste)
    {
        plansza[*pozycja_Rockforda + 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + 1; 
    }
    else if (plansza[*pozycja_Rockforda + 1] == diament)
    {
        plansza[*pozycja_Rockforda + 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + 1; 
        -- *ilosc_diamentow ;           
    }
    else if (plansza[*pozycja_Rockforda + 1] == ziemia)
    {
        plansza[*pozycja_Rockforda + 1]= Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + 1; 
    }
     else if (plansza[*pozycja_Rockforda + 1] == wyjscie && *ilosc_diamentow == 0)
    {
         plansza[*pozycja_Rockforda]= pole_puste;
         *pozycja_Rockforda = -1;
         
    }
    else if ( plansza[*pozycja_Rockforda + 1] == kamien && plansza[*pozycja_Rockforda + 2] == pole_puste)
    {
        plansza[*pozycja_Rockforda + 2] = kamien;
        plansza[*pozycja_Rockforda + 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + 1;
    }
   
}

void ruch_Rockforda_w_lewo(char *plansza, int *pozycja_Rockforda,  int *ilosc_diamentow)
{
    if (plansza[*pozycja_Rockforda - 1] == pole_puste)
    {
        plansza[*pozycja_Rockforda - 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda - 1; 
    }
    else if (plansza[*pozycja_Rockforda - 1] == diament)
    {
        plansza[*pozycja_Rockforda - 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        -- *ilosc_diamentow ;           
        *pozycja_Rockforda = *pozycja_Rockforda - 1; 
    }
    else if (plansza[*pozycja_Rockforda - 1] == ziemia)
    {
        plansza[*pozycja_Rockforda - 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda - 1; 
    }
     else if (plansza[*pozycja_Rockforda - 1] == wyjscie && *ilosc_diamentow == 0)
    {
          plansza[*pozycja_Rockforda]= pole_puste;
          *pozycja_Rockforda = -1;
    }
    else if ( plansza[*pozycja_Rockforda - 1] == kamien && plansza[*pozycja_Rockforda - 2] == pole_puste)
    {
        plansza[*pozycja_Rockforda - 2] = kamien;
        plansza[*pozycja_Rockforda - 1] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda - 1;
    }
}

void ruch_Rockforda_w_gore(char *plansza, int k,int *pozycja_Rockforda,  int *ilosc_diamentow)
{
    if (plansza[*pozycja_Rockforda - k] == pole_puste)
    {
        plansza[*pozycja_Rockforda - k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda - k; 
    }
    else if (plansza[*pozycja_Rockforda - k] == diament)
    {
        plansza[*pozycja_Rockforda - k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
       -- *ilosc_diamentow ;    
        *pozycja_Rockforda = *pozycja_Rockforda - k;         
    }
    else if (plansza[*pozycja_Rockforda - k] == ziemia)
    {
        plansza[*pozycja_Rockforda - k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda - k; 
    }
     else if (plansza[*pozycja_Rockforda - k] == wyjscie && *ilosc_diamentow == 0)
    {
          plansza[*pozycja_Rockforda]= pole_puste;
          *pozycja_Rockforda = -1;
    }
}

void ruch_Rockforda_w_dol(char *plansza, int k,int *pozycja_Rockforda,  int *ilosc_diamentow)
{
    if (plansza[*pozycja_Rockforda + k] == pole_puste)
    {
        plansza[*pozycja_Rockforda + k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + k; 
    }
    else if (plansza[*pozycja_Rockforda + k] == diament)
    {
        plansza[*pozycja_Rockforda + k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        -- *ilosc_diamentow ;       
        *pozycja_Rockforda = *pozycja_Rockforda + k; 
    }
    else if (plansza[*pozycja_Rockforda + k] == ziemia)
    {
        plansza[*pozycja_Rockforda + k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + k; 
    }
     else if (plansza[*pozycja_Rockforda + k] == wyjscie && *ilosc_diamentow == 0)
    {
          plansza[*pozycja_Rockforda]= pole_puste;
          *pozycja_Rockforda = -1;
    }
     else if ( plansza[*pozycja_Rockforda + k] == kamien && plansza[*pozycja_Rockforda + 2*k] == pole_puste)
    {
        plansza[*pozycja_Rockforda + 2*k] = kamien;
        plansza[*pozycja_Rockforda + k] = Rockford;
        plansza[*pozycja_Rockforda] = pole_puste;
        *pozycja_Rockforda = *pozycja_Rockforda + k;
    }
}

void ruch_Rockforda(char *plansza, int w, int k,int *pozycja_Rockforda,  int *ilosc_diamentow, int ruchy)//Funkcja odpowiada za ruchy rockforda pokazywane w pliku wynikowym
{
    if(ruchy == '\n')
    {
        wypisywanie_planszy(plansza, w, k);
    }
    
    if( *pozycja_Rockforda != -1)
    {
        if (ruchy == 'd')
        {
            ruch_Rockforda_w_prawo(plansza , pozycja_Rockforda,ilosc_diamentow);
        }
        else if (ruchy == 'a')
        {
            ruch_Rockforda_w_lewo(plansza,pozycja_Rockforda,ilosc_diamentow);
        }
        else if (ruchy == 'w')
        {
            ruch_Rockforda_w_gore(plansza, k,pozycja_Rockforda,ilosc_diamentow);
        }
        else if (ruchy == 's')
        {
            ruch_Rockforda_w_dol(plansza,k ,pozycja_Rockforda,ilosc_diamentow);
        }
    }
    
}

int main()
{
    int w,k;
    int x=scanf("%d %d",&w, &k);

    if ( x != 2)
    {
        printf("Zle dane");
        return -1;
    }
    
    int ilosc_diamentow = 0;
    
    int *pozycja_Rockforda = malloc(sizeof(int*));    
    char *plansza = malloc((unsigned) (w*k)*sizeof(char *));
    
    *pozycja_Rockforda = -1; //wprowadzone przy 2 poprawce
    
    dane_wejsciowe(plansza, w ,k);
    
    while(plansza_jest_niestabilna(plansza, w ,k))
    {
        do_stanu_stabilnego_planszy(plansza, w ,k);
    }
    wypisywanie_planszy(plansza, w ,k);
    
    pozycja_Rockford(plansza, w, k, pozycja_Rockforda);
    ilosc_diamentow = liczba_diamentow(plansza,w,k,ilosc_diamentow);

    char ruchy = (char)(getchar());
    
    while( ruchy != EOF)
    {
        pozycja_Rockford(plansza, w ,k, pozycja_Rockforda);
        
        ruch_Rockforda(plansza,w,k,pozycja_Rockforda,&ilosc_diamentow,ruchy);  

        while(plansza_jest_niestabilna(plansza, w, k))
        {
            do_stanu_stabilnego_planszy(plansza, w, k);
        }
        ruchy =(char)(getchar());
    }
    
    free (plansza);
    free (pozycja_Rockforda);
    return 0;
}
