#include <stdio.h>
#include <stdlib.h>

int insert(int **v1, int n1, int c1, int *v2, int n2, int pos) {
	if(n1 + n2 > c1 || pos > n1)
		return -1;
	
	int *v = (int *)malloc((n1 + n2) * sizeof(int));
	int *vp = *v1;
	
	for(int i = 0; i < pos; i++)
		v[i] = vp[i];
	for(int i = 0; i < n2; i++)
		v[i + pos] = v2[i];
	for(int i = pos; i < n1; i++)
		v[i + n2] = vp[i];
		
	free((*v1));
	*v1 = v;
		
	return 0;
}

int main()
{
	int c1, n1, *v1, n2, *v2, pos;
	
    printf("Dati capacitatea primului sir: ");
    scanf("%d", &c1);
    
    printf("Dati numarul de lemente din primului sir: ");
    scanf("%d", &n1);
		
	v1 = (int*)malloc(n1 * sizeof(int));
    
    printf("Dati primului sir: ");
    for(int i = 0; i < n1; i++)
		scanf("%d", (v1 + i));
		
	printf("Dati numarul de lemente din ad doilea sir: ");
		scanf("%d", &n2);
	
	v2 = (int*)malloc(n2 * sizeof(int));
	
	printf("Dati al doilea sir: ");
	for(int i = 0; i < n2; i++)
		scanf("%d", (v2 + i));
		
	printf("Dati pozitia pt inserare: ");
	scanf("%d", &pos);
	
	int result = insert(&v1, n1, c1, v2, n2, pos);
	
	if(result != 0)
		printf("Nu am reusit");
	else {
		for(int i = 0; i < n1 + n2; i++)
			printf("%d ", v1[i]);
	}
		
	free(v1);
	free(v2);
    
    return 0;
}
