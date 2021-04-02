#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <vector>
#define buildingNumber 30
using namespace std;

struct Building
{
	int x,y;
	char name[30];
};

Building building[buildingNumber];

int main()
{
	freopen("matrix.txt","r",stdin);
	freopen("generate_matrix.txt","w",stdout);
	int matrix[buildingNumber][buildingNumber]={-1};
	for(int i=1;i<buildingNumber;++i)
	{
		for(int j=1;j<buildingNumber;++j)
		{
			scanf("%d",&matrix[i][j]);
		}
	}
	for(int i=1;i<buildingNumber;++i)
	{
		for(int j=1;j<buildingNumber;++j)
		{
			if(matrix[j][i]!=-1) matrix[i][j]=matrix[j][i];
		}
	}
	
	for(int i=1;i<buildingNumber;++i)
	{
		for(int j=1;j<buildingNumber-1;++j)
		{
			printf("%d ",matrix[i][j]);
		}
		printf("%d\n",matrix[i][29]);
	}
} 
