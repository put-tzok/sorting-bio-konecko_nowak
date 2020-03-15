#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


unsigned int ns[] = {10, 100, 150, 500, 1000, 1500, 5000, 10000, 15000, 25000,   };

void fill_increasing(int *t, unsigned int n) {
    for(int i = 0; i < n; i++)
    t[i] = i;
}

void fill_decreasing(int *t, unsigned int n) {
    for(int i = 0; i < n; i++)
    t[i] = -i;
}

void fill_vshape(int *t, unsigned int n) {
    int a = 0;
    int b = n-1;
    for(int i = n; i > 0; i--)
    {
      if(i % 2 == 0)
      {
        t[a] = i;
      a++;
      }
      else
      {
        t[b] = i;
        b--;
      }
    }
}


void swap(int *t, int x, int y)
    {
    int wartosc = t[x];
    t[x] = t[y];
    t[y] = wartosc;
    }


void selection_sort(int *t, unsigned int n)
{
      int i;
      int j;
      int minimal;

    for (i = 0; i < n-1; i++)
    {
        minimal = i;
        for (j = i+1; j < n; j++)
          if (t[j] < t[minimal])
            minimal= j;
        swap(t, minimal, i);
    }
}

void insertion_sort(int *t, unsigned int n)
{
int wsk;
int i;
int j;
    for( i = 1; i <= n-1; i++)
        {
        wsk = t[i];
        j = i - 1;
        while(j >= 0 && t[j]>wsk)
            {
            t[j+1] = t[j];
            j = j - 1;
            }
        t[j+1] = wsk;
}
}


int partition(int *t,int l,int k)
{
    int z = t[k];
    int i = (l - 1);
    for(int j=l; j<k; j++)
        {
            if(t[j] <= z)
            {
                i++;
                swap(t, i, j);
            }
        }
    i = i+1;
    swap(t, i, k);
    return i;
}

int random(int max, int min)
{
    int tmp;
    if (max>=min)
        max-= min;
    else
    {
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return max ?(rand() % max + min) : min;
}

int random_partition(int *t, int l, int k)
{
     int z=random(l,k);
     swap(t, z , k);
     return partition(t, l, k);
}

void quick_sort_(int *t, int p, int r)
{
  if (p < r)
  {
    int q = partition(t, p, r);
    quick_sort_(t, p, q - 1);
    quick_sort_(t, q + 1, r);
  }
}
void quick_sort(int *t, unsigned int n)
{
     quick_sort_(t, 0, n-1);
}
void kopiec(int *t, int n, int i)
{
    int naj = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && t[l] > t[naj])
        naj = l;

    if (r < n && t[r] > t[naj])
        naj = r;

    if (naj != i)
    {
        swap(t, i , naj);
        kopiec(t, n, naj);
    }
}

void heap_sort(int *t, unsigned int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        kopiec(t, n, i);
    for (int i=n-1; i>=0; i--)
    {
        swap(t, 0 , i);
        kopiec(t, i, 0);
    }
}




void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i-1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    printf("end");
    return 0;
}
