#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <iostream> 
#include <algorithm> 
#include <cstring> 
#include <string> 
#include <map> 
#include <queue> 
using namespace std; 
typedef long long ll; 
#define TRUE 1 
#define FALSE 0 
const int IFINITY = 20000000; 
const int buildingNumber = 29; 
typedef struct node { 
        char name[50]; 
        int x, y; 
        int xuhao; 
}building; 
 
building Building[30]; 
char lesson[10][10][20]; 
char timetable[10][10][20]; 
int start, destination; 
int P[30][30]; 
int final[30]; 
int D[30]; 
deque<int> path[30]; 
char direction,faceDirection;
 
void init();//��ȡ��ͼԭʼ��Ϣ 
void getLocation();//��ȡʼĩλ�� 
int askLocation();//ѯ������λ�� 
int getBuilding(char* s);//��ȡ����һ�������� 
void Dijstra(int v0);//�����㷨 
void OutputPath(int v); 
 
int main() { 
 
        init(); 
        //start = 21; 
        getLocation(); 
        Dijstra(start); 
        OutputPath(destination);
        return 0; 
} 
 
void init() { 
        FILE* fp1, * fp2, * fp3, * fp4; 
        fp1 = fopen("lesson.txt", "r"); 
        fp2 = fopen("timetable.txt", "r"); 
        fp3 = fopen("building.txt", "r"); 
        fp4 = fopen("matrix.txt", "r"); 
        for (int i = 1; i <= 8; i++) { 
                for (int j = 1; j <= 5; j++) { 
                        fscanf(fp1, "%s", lesson[i][j]); 
                        fscanf(fp2, "%s", timetable[i][j]); 
                } 
        } 
        for (int i = 1; i <= buildingNumber; i++) { 
                fscanf(fp3, "%s", Building[i].name); 
                fscanf(fp3, "%d,%d", &Building[i].x, &Building[i].y); 
        } 
        for (int i = 1; i <= buildingNumber; i++) { 
                for (int j = 1; j <= buildingNumber; j++) { 
                        fscanf(fp4, "%d", &P[i][j]); 
                        if (P[i][j] == -1) P[i][j] = IFINITY; 
                } 
        } 
        fclose(fp1); 
        fclose(fp2); 
        fclose(fp3); 
        fclose(fp4); 
        /*for (int i = 1; i <= buildingNumber; i++) { 
                for (int j = 1; j <= buildingNumber; j++) { 
                        printf("%d ", P[i][j]); 
                } 
                printf("\n"); 
        }*/ 
        return; 
} 
 
void getLocation() {//��ȡ��ʼλ�� 
        printf("��������ʼλ��:1Ϊ�߼�λ�ã�2Ϊ����λ��\n"); 
        start = askLocation(); 
        printf("��ʼλ����%s,����Ϊ��(%d,%d)\n", Building[start].name, Building[start].x, Building[start].y); 
        printf("������Ŀ��λ��:1Ϊ�߼�λ�ã�2Ϊ����λ��\n"); 
        destination = askLocation(); 
        printf("��ֹλ����%s,����Ϊ��(%d,%d)\n", Building[destination].name, Building[destination].x, Building[destination].y); 
        return; 
} 
 
int askLocation() { 
        int select; 
        char location[50]; 
        int num; 
        scanf("%d", &select); 
        if (select == 1) {   //ѡ���߼�λ�� 
                //��ӡ�γ̱� 
                int week, course; 
                printf("\t\t"); 
                for (int i = 1; i <= 5; i++) printf("����%-17d", i); 
                printf("\n"); 
                for (int i = 1; i <= 8; i++) { 
                        printf("��%d�ڿ� ", i); 
                        for (int j = 1; j <= 5; j++) { 
                                printf("%20s", lesson[i][j]); 
                        } 
                        printf("\n           "); 
                        for (int j = 1; j <= 5; j++) { 
                                printf("%20s", timetable[i][j]); 
                        } 
                        printf("\n\n"); 
                } 
                //ͨ���γ̱�������λ�� 
                printf("���������ڵ����ڣ�\n"); 
                scanf("%d", &week); 
                printf("������γ̽ڴΣ�\n"); 
                scanf("%d", &course); 
                strcpy(location, timetable[course][week]); 
                num = getBuilding(location); 
        } 
        else if (select == 2) { //ѡ������λ�� 
                printf("��ѡ�������ڵ�λ�ã�\n"); 
                for (int i = 1; i <= buildingNumber; i++) { 
                        printf("%d : %s\n", i, Building[i].name); 
                } 
                scanf("%d", &num); 
        } 
        return num; 
} 
 
int getBuilding(char* s) { 
        int i, j, len; 
        for (i = 1; i <= buildingNumber; i++) { 
                len = strlen(Building[i].name); 
                for (j = 0; j < len; j++) { 
                        if (s[j] != Building[i].name[j]) break; 
                } 
                if (j == len) break; 
        } 
        return i; 
} 
 
void Dijstra(int v0) {//�����㷨 
        int v, w; 
        for (v = 1; v <= buildingNumber; ++v) { 
                final[v] = FALSE; 
                D[v] = P[v0][v]; 
                if (P[v0][v] && v != v0) path[v].push_back(v0); 
        } 
        D[v0] = 0; final[v0] = TRUE; 
        //Ŀǰ���Ҵ�v0��v�����·�� 
        for (int i = 1; i < buildingNumber; i++) { 
                int min = IFINITY; 
                for (w = 1; w <= buildingNumber; w++) { 
                        if (!final[w]) { 
                                if (D[w] < min) { v = w; min = D[w]; } 
                        } 
                } 
                //printf("%d is %d\n", v,D[v]); 
 
                final[v] = TRUE; 
                for (w = 1; w <= buildingNumber; w++) { 
                        if (!final[w] && min + P[v][w] < D[w]) { 
                                D[w] = min + P[v][w]; 
                                //path[w].push_back(v); 
 
                                while (!path[w].empty())  path[w].pop_back();//��ն��� 
                                for (deque<int>::iterator it = path[v].begin(); it != path[v].end(); ++it) 
                                { 
                                        path[w].push_back(*it); 
                                } 
                                path[w].push_back(v); 
                        } 
                } 
 
        } 
 
 
} 


void getDirection(int u,int p)
{
	if(Building[u].x==Building[p].x)
	{
		if(Building[p].y>Building[u].y) direction='��';
		else direction='��'; 
	}
	else
	{
		if(Building[p].x>Building[u].x) direction='��';
		else direction='��'; 
	}
}

char tellDirection(char faceDirection,char direction)
{
	if(faceDirection=='��')
	{
		if (direction=='��') return '��';
		else return '��'; 
	}
	if(faceDirection=='��')
	{
		if (direction=='��') return '��';
		else return '��'; 
	}
	if(faceDirection=='��')
	{
		if (direction=='��') return '��';
		else return '��'; 
	}
	if(faceDirection=='��')
	{
		if (direction=='��') return '��';
		else return '��'; 
	}
}
void OutputPath(int v) 
{ 
	int u=path[v].front();
	path[v].pop_front();
	int p=path[v].front();
	getDirection(u,p);
	faceDirection=direction;
	printf("��%s��%c����%dm����%s,",Building[u].name,direction,abs(Building[p].x+Building[p].y-Building[u].x-Building[u].y),Building[p].name);
	while (!path[v].empty()) 
	{ 
			u=p;
            path[v].pop_front(); 
            if(path[v].empty()) break;
            p=path[v].front();
            getDirection(u,p);
            if(faceDirection==direction) 
            {
            	printf("������ǰ����%dm����%s,",abs(Building[p].x+Building[p].y-Building[u].x-Building[u].y),Building[p].name);
			}
			else
			{
				printf("%cת����ǰ����%dm����%s��",tellDirection(faceDirection,direction),abs(Building[p].x+Building[p].y-Building[u].x-Building[u].y),Building[p].name);
				faceDirection=direction; 
			}
    }
    getDirection(u,v);
    if(faceDirection==direction) 
    {
        printf("������ǰ����%dm����%s,",abs(Building[v].x+Building[v].y-Building[u].x-Building[u].y),Building[v].name);
	}
	else
	{
		printf("%cת����ǰ����%d����%s��",tellDirection(faceDirection,direction),abs(Building[v].x+Building[v].y-Building[u].x-Building[u].y),Building[v].name);
		faceDirection=direction; 
	}
}
