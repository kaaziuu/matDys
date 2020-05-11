// kalulatoro wielomianów zrelizowany na zajęcie matematyki dyskretnej
// autor Karol Kaźmierczak

#include <stdio.h>
#include <stdlib.h>
// #include <math.h>
// towrzenie nowej podstawy
void new(int *p, int *su){
    printf("podaj podstawę modularną: ");
    scanf("%d", p);
    printf("podaj stopien: ");
    scanf("%d", su);

}
// tworzenie nowego wielomianu
void new_polynomial(int *nu, int su){
    int tmp = su;
    int i;
    for(i=0; i<=su; i++){
        printf("Podaj wielomian stopnia %d: ", tmp);
        int tmp_2;
        scanf("%d", &tmp_2);
        *(nu+i)=tmp_2;
        tmp--;
    }
}

// wypisanie wielomianu
void show(int *u, int su, int nl){
    int i, tmp;
    tmp = su;
    if(nl){
        printf("twoj wielomian =");
    }
    for(i=0; i<=su; i++){
        if(i!=0){
            printf("+");
        }
        printf(" %dx^%d ", *(u+i), tmp);
        tmp--;
    }
    if(nl){
        printf("\n");
    }
}


// dodanie wielomianow
void add(int *u, int p, int su){
    int nu[su+1];
    int *pnu = nu;
    new_polynomial(pnu, su);
    int i;

    show(u, su, 0);
    printf(" + ");
    show(nu, su, 0);
    printf("=");
    for(i=0; i<=su; i++){
        int result = *(u+i) + *(nu+i);
        if(p!= 0){
            result = result % p;
        }
        *(u+i) = result;
    }
    show(u, su, 0);
    printf("\n");
    // free(pnu);

}

// odemowanie wielomanow
void subtraction(int *u, int p, int su){
    int nu[su+1];
    int* pnu = nu;
    new_polynomial(pnu, su);
    show(u, su, 0);
    printf(" - ");
    show(nu, su, 0);
    printf(" = ");
    int i;
    int tmp;
    for(i=0; i<=su; i++){
        tmp = *(u+i) - *(pnu + i);
        if(p != 0){
            tmp = tmp % p;
        }
        *(u+i) = tmp;
    }
    show(u, su, 0);
    printf("\n");

}
// mnożenie wielomianow
void power_polymian(int *u,int *nu,int *result, int su, int snu, int srs , int p){
    int i;
    for(i=0; i<=(su); i++){
        int j;
        for(j=0; j<=(snu); j++){
            int current_s  = (su-i)+ (snu-j);
            int index = (srs - current_s);
            // printf("s-%d \n in-%d \n i-%d, j-%d\n", current_s, index, i, j);
            *(result+index) += *(u+i) * *(nu+j);

        }
    }
    if(p!=0){
        for(i = 0; i<=srs; i++){
            *(result+i) %= p;
        }
    }
}

int is_prime_number(int p){
    int i;
    if(p==2){
        return 1;
    }
    for(i=2; i<p/2; i++){
        if(p%i == 0){
            return 0;
        }
    }

    return 1;
}

void division_polymian(int* denominator,int *numerator,int *result, int current_index, int p, int* ob_number){

    int dv;
    if((*(denominator) % *(numerator))  == 0 || p==0){
        *(result+current_index) = *(denominator) / *(numerator);
        if(p != 0){
            *(result+current_index) = *(result+current_index) % p;
        }
    }else
    {
        int tmp = *(ob_number+ (*numerator)-1);
        *(result+current_index) = (*denominator * tmp) % p;
    }

    //*(result+current_index) = *(denominator) / *(numerator);

}



void main_division(int *pu, int mod, int p,int *su){
    int is_prime = is_prime_number(p);
    if(p == 0){
        is_prime = 1;
    }
    if(!is_prime){
        printf("p musi być liczbą pierwsza - towoje p %d\n", p);
    }
    else{
        int nsu, is_ok =0;
        while (!is_ok)
        {
            printf("podaj stopień dzielnika: ");
            scanf("%d", &nsu);
            if(nsu <= *su){
                break;
            }
            else{
                printf("stopien musi byc mnieszy badz rowny stoponiowi rejestru \n");
            }
        }
        int reip[p-1];
        if(p != 0){
            // stworzenie tablicy znakow przciwnych w danej podstawie
            int i;
            int tmp = 1;
            for(i=1; i<(p); i++){
                tmp = 1;

                while ((tmp*i)%p != 1 && tmp < p)
                {
                    tmp++;
                }
                // printf("%d-%d \n", tmp, i);

                if((tmp*i)%p == 1){
                    reip[i-1] = tmp;
                }
                else{
                    reip[i-1] = 0;
                }

            }
        }
        int* ponter_op_nb = reip;


        int numerator[nsu];
        int *pointer_numerator = numerator;
        new_polynomial(pointer_numerator, nsu);

        int s_result = *su-nsu;
        printf("%d", s_result);
        int result[s_result+1];
        int* pointer_result = result;
        int i;
        for(i=0; i<=s_result; i++){
            result[i] = 0;
        }

        show(pu, *su, 0);

        is_ok = 0;
        int current_index = 0;
        int new_u;
        while (current_index <= s_result)
        {
            int min;
            division_polymian(pu, pointer_numerator, pointer_result, current_index, p, ponter_op_nb);
            int i = 0;
            int tmp[*su + 1];
            for(i=0; i<=nsu; i++){
                tmp[i] = *(pointer_result+current_index) * *(pointer_numerator+i);
                if(p!=0){
                    tmp[i] = tmp[i] % p;
                }
            }
            for(i=(nsu+1); i<= *su; i++){
                tmp[i] = 0;
            }


            for(i=0; i<=*su; i++){
                tmp[i] = *(pu+i) - tmp[i];
                if(tmp[i] < 0){
                    tmp[i] = p + tmp[i];
                }
            }


            int new_s = -1;
            int tmp_index;
            for(i=0; i<=*su; i++){
                if(tmp[i] != 0){
                    new_s = *su - i;
                    tmp_index = i;
                    break;
                }
            }
            if(new_s >= nsu){
                free(pu);
                pu = malloc((new_s+1)* sizeof(*pu));
                for(i=0; i<=new_s; i++){
                    *(pu+i) = tmp[tmp_index];
                    tmp_index++;
                }
                *su = new_s;
            }
            else{
                if(mod == 0){
                    free(pu);
                    pu = malloc((s_result+1)*sizeof(*pu));
                    for(i=0; i<= s_result; i++){
                        *(pu+i) = (*(pointer_result+i));
                    }
                    *su = s_result;
                }
                else{
                    int res[*su+1];
                    for(i=0; i<=nsu;i++){
                        res[i] = *(pointer_result+current_index ) * pointer_numerator[i];
                    }
                    for(i=nsu+1; i<=*su; i++){
                        res[i] = 0;
                    }
                    for(i=0; i<=*su; i++){
                        res[i] = *(pu+i) - res[i];
                    }


                    int new_s = 0;
                    int tmp_index = -1;
                    for(i=0; i<=*su; i++){
                        if(tmp[i] != 0){
                            new_s = *su - i;
                            tmp_index = i;
                            break;
                        }
                    }
                    free(pu);
                    if(tmp_index == -1){
                        tmp_index = 0;
                    }
                    pu = malloc((new_s+1)* sizeof(*pu));
                    for(i=0; i<=new_s; i++){
                        *(pu+i) = tmp[tmp_index++];
                        if(p != 0){
                            *(pu+i) %= p;
                        }
                    }
                    *su = new_s;

                }
                break;
            }

            current_index++;

        }
        for(i=0; i<=*su; i++){
            *(pu+i) = *(pu+i)%p;
        }
        if(!mod)
            printf(" / ");
        else
            printf(" %% ");

        show(pointer_numerator, nsu, 0);
        printf(" = ");
        show(pu, *su, 0);
        printf("\n");
    }
}

void save(int *pu, int *ts, int su, int *st){

    int i;
    for(int i = 0; i<=su; i++){
        *(ts+i) = *(pu+i);
    }
    *st = su;

    printf("\nuadlo się zapisać \n");
}

void load(int* pu, int* tr, int* su, int ss){
    free(pu);
    pu = malloc((ss+1) * sizeof(*pu));
    *su = ss;
    int i;
    for(i=0; i<=ss; i++){
        *(pu+i) = *(tr+i);
    }
    printf("udalo sie wczytac \n");
}

int main(int argc, char const *argv[])
{
    int p, su, is_run, dec;
    is_run = 1;
    new(&p, &su);

    int* pu = malloc((su+1)*sizeof(*pu));
    int* tmp;
    int* a, *b, *c;
    int sa, sb, sc;
    sa =0;
    sb=0;
    sc=0;
    new_polynomial(pu, su);

    while (is_run != 0)
    {
        show(pu, su, 1);
        printf("0: zeruj rejestr\n");
        printf("1:dodaj do rejestru\n");
        printf("2: odejmij od rejestru\n");
        printf("3: pomnoz rejestr\n");
        printf("4: podziel rejesrt\n");
        printf("5: rzesta z dzielenia rejestru\n");
        printf("6: zapisz rejestr w pamieci a b lub c \n");
        printf("7: odtwórz wratość rejestru z pamięci wyżej\n");
        printf("8: wylacz program\n");
        scanf("%d", &dec);
        if(dec == 0){
            new(&p, &su);
            free(pu);
            pu = malloc((su+1)*sizeof(*pu));
            new_polynomial(pu, su);
        }
        else if(dec == 1){
            add(pu, p, su);
        }else if (dec == 2)
        {
            subtraction(pu, p, su);
        }else if(dec==3){
                int nsu;
                printf("podaj stopien wilomianu przez ktory bedziemy mnozyc: ");
                scanf("%d", &nsu);
                int nu[nsu];
                int* pointer_nu = nu;
                new_polynomial(pointer_nu, nsu);
                int final_su = nsu + su;
                int result[final_su+1];
                int* pointer_result = result;
                int i;
                for(i=0; i<=final_su; i++){
                    result[i] = 0;
                }
                power_polymian(pu, pointer_nu, pointer_result, su, nsu, final_su, p);

                show(pu, su, 0);
                printf(" * ");
                show(pointer_nu, nsu, 0);
                printf(" = ");
                show(pointer_result, final_su, 0);
                printf("\n");
                free(pu);
                pu = malloc((final_su+1) * sizeof(*pu));
                su = final_su;
                for(i=0; i<=final_su; i++){
                    *(pu+i) = result[i];
                }

        }else if(dec == 4 ){
            main_division(pu, 0, p, &su);
        }else if(dec == 5){
            main_division(pu, 1, p, &su);
        }else if(dec == 6){
            int choose;
            printf("zapisz do 1-a, 2-b, 3-c \n");
            scanf("%d", &choose);
            printf("%d", choose);
            if(choose == 1){
                if(sa != 0){
                    free(a);
                }
                a = malloc((su+1)*sizeof(*a));
                save(pu, a, su, &sa);

            }
            else if(choose == 2){
                if(sb != 0){
                    free(b);
                }
                b = malloc((su+1)*sizeof(*b));
                save(pu, b, su, &sb);
                int i;
                for (i=0; i<=su; i++){
                    printf("i-%d", *(b+i));
                }
            }
            else if(choose == 3){
                if(sc != 0){
                    free(c);
                }
                c = malloc((su+1)*sizeof(*c));
                save(pu, c, su, &sc);

            }
            else{
                printf("zly index \n");
            }
        }else if(dec == 7){
            int choose;
            printf("wczytaj z 1-a, 2-b, 3-c \n");
            scanf("%d", &choose);
            if(choose == 1 && sa != 0){
                load(pu, a, &su, sa);
            }
            else if(choose == 2 && sb != 0 ){
                load(pu, b, &su, sb);
            }
            else if(choose == 3 && sc != 0 ){
                load(pu, c, &su, sc);
            }
            else{
                printf("nie udalo sie wczytac \n");
            }
        }
        else if(dec == 8){
            is_run = 0;
        }
    }


    return 0;
}
