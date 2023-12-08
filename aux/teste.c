#include <stdio.h>


int main() {

    int v[] = {15, 20, 19, 5, 434,9,10,23};
    int size = sizeof(v) / sizeof(int);

    int aux;
    for(int ult = size - 1; ult > 0; ult--) {
        for (int i=0; i < ult; i++) {
            if (v[i] < v[i+1]) {
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d ", v[i]);
    }puts("");

    int i = 0;
    while (i < size - 1) {
        if (v[i] > 21) {
            int j = i;
            while (j < size - 1) {
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                j++;
            }
        } else {
            i++;
        }

        for (int i = 0; i < size; i++)
    {
        printf("%d ", v[i]);
    }puts("");
    }
    

    for (int i = 0; i < size; i++)
    {
        printf("%d ", v[i]);
    }puts("");
    

    return 0;
}