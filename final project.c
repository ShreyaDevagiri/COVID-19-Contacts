#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


typedef struct details
{
  char name[20];
  int uniqueid_no;
  char address[20];
  int phone_no;
}CITY;


typedef struct hospital
{
    char hospital_name[10];
    char location[20];
    char doctor_name[10];
}PLACE;

void BFS(int timesec[][10],int start,int n);

void write(FILE *,int,CITY *);

void read(FILE *,int,CITY *);

CITY info[100];

PLACE doctor[10];

 int infected[10] = {0}, possibility[10] = {0};

 int visited[10] = {0}; //initializing visited array

void write(FILE *fp,int n,CITY *a)
{
    int i;
    fp=fopen("citizen_details.txt","w");
    for(i=1;i<=n;i++)
    {
        printf("Enter the Name  Unique_ID  Address Phone_no\n");
        scanf("%s  %d  %s  %d",a[i].name,&a[i].uniqueid_no,a[i].address,&a[i].phone_no);
        fprintf(fp,"%s  %d  %s  %d\n",a[i].name,a[i].uniqueid_no,a[i].address,a[i].phone_no);

    }
    fclose(fp);
}

void write1(FILE *,PLACE *);

void write1(FILE *fp1,PLACE *f)
{
    int i;
    fp1=fopen("hospital_details.txt","w");
    for(i=1;i<=6;i++)
    {
        printf("Enter the hospital name,location, doctor name \n");
        scanf("%s %s %s",f[i].hospital_name,f[i].location,f[i].doctor_name);
        fprintf(fp1,"%s  %s  %s\n",f[i].hospital_name,f[i].location,f[i].doctor_name);

    }
    fclose(fp1);
}

void read(FILE *fp, int n, CITY *d)
{
    int i;
    fp=fopen("citizen_details.txt","r");
    if(fp==NULL)
    {
        printf("ERROR IN FILE READING.\n");
        exit(0);
    }
    else
    {
        printf("\nLIST OF CITIZENS:\n");
        i=1;
     while(fscanf(fp,"%s %d %s %d",d[i].name,&d[i].uniqueid_no,d[i].address,&d[i].phone_no)!=EOF)
        {
            printf("\n%s\t%d\t%s\t%d\n",d[i].name,d[i].uniqueid_no,d[i].address,d[i].phone_no);
            strcpy(info[i].name,d[i].name);
            info[i].uniqueid_no=d[i].uniqueid_no;
            strcpy(info[i].address,d[i].address);
            info[i].phone_no=d[i].phone_no;
            i++;
        }
    }
    fclose(fp);
   // printf("%d\n",i);
   /* for(i=1;i<=3;i++)
    printf("%s\n",info[i].name);*/
}

void read1(FILE *fp1,PLACE *f)
{
int i;
  fp1=fopen("hospital_details.txt","r");
   if(fp1==NULL)
    {
        printf("ERROR IN FILE READING.\n");
        exit(0);
    }
    else
    {
        printf("\nHOSPITAL LIST.\n");
        i=1;
    while(fscanf(fp1,"%s %s %s",f[i].hospital_name,f[i].location,f[i].doctor_name)!=EOF)
    {
      printf("\n%s %s %s\n",f[i].hospital_name,f[i].location,f[i].doctor_name);
      strcpy(doctor[i].hospital_name,f[i].hospital_name);
      strcpy(doctor[i].location,f[i].location);
      strcpy(doctor[i].doctor_name,f[i].doctor_name);
      i++;
    }
    }
    fclose(fp1);
    printf("\n");
}

//------Queue Start------

typedef struct queue
{
    int front;
    int rear;
    int q[100];
}que;

int empty(que *q)
{
    if (q->front>q->rear) {
        return 1;
    }
    else{
        return 0;
    }
}

void enqueue(que *q, int data)
{
    q->rear = q->rear + 1;
    q->q[q->rear] = data;
}

int dequeue(que *q)
{
    int data;
    data = q->q[q->front];
    q->front = q->front + 1;
    return data;
}
//------Queue End------

void BFS(int G[][10], int start, int n)
{
    //initializing queue
    struct queue q;
    q.front = 0;
    q.rear = -1;

    struct queue inf;
    inf.front = 0;
    inf.rear = -1;

    struct queue pos;
    pos.front = 0;
    pos.rear = -1;

    int i, j;

    i = start; //You can consider infection source rather than start


    //printf("%d\t", i);
    enqueue(&q, i);
    enqueue(&inf, i);
    visited[i] = 1;

    while (!empty(&q))
     {
        i = dequeue(&q);
        for (j=0; j<=n; j++)
         {
            if (G[i][j]!=0 && visited[j]==0 && G[i][j]>10)
             {
                    infected[j] = j;
                    enqueue(&inf, j);
                    //printf("%d\t", j);
                    enqueue(&q, j);
                    visited[j] = 1;
            }
        }
    }
    while (!empty(&inf))
    {
        i = dequeue(&inf);
        for (j=0; j<=n; j++)
        {
            if (G[i][j]!=0 && visited[j]==0 && G[i][j]<=10 && G[i][j]>=5)
             {
                    possibility[j] = j;
                    enqueue(&pos, j);

                    //printf("%d\t", j);

                    enqueue(&inf, j);
                    visited[j] = 1;
            }
        }
    }
    printf("Infected id: %d\t", start);
    for (i=0; i<=n; i++)
     {
        if (infected[i]==0)
        {
            continue;
        }
        printf("%d ", infected[i]);
    }

    printf("\nPossibility of infection id: ");
    for (i=0; i<n; i++) {
        if (possibility[i]==0)
        {
            continue;
        }
        printf("%d ", possibility[i]);
    }

    printf("\nNot Infected id: ");
    for (i=1; i<=n; i++)
     {
        if (visited[i]==0)
        {
            printf("%d ", i);
        }
    }
    printf("\n\n");
}
int main()
{
    CITY d[10];
    int n,i,j;
    FILE *fp;
    FILE *fp1;
    PLACE f[10];

    //printf("enter number of citizen\n");

    //scanf("%d",&n);

    //write(fp,n,d);

   //write1(fp1,f);
   read(fp,10,d);
   read1(fp1,f);
   int G[10][10] =    {{0,0,0,0,0,0,0,0,0,0},
                        {0,0,16,0,0,0,0,0,0,6},
                        {0,16,0,2,0,0,0,8,0,0},
                        {0,0,2,0,0,6,0,0,0,0},
                        {0,0,0,0,0,0,1,0,0,0},
                        {0,0,0,6,0,0,7,0,0,0},
                        {0,0,0,0,1,7,0,13,0,0},
                        {0,0,8,0,0,0,13,0,11,0},
                        {0,0,0,0,0,0,0,11,0,3},
                        {0,6,0,0,0,0,0,0,3,0}};

    BFS(G, 7, 10); //7 is source, 10 is no of vertices/nodes

    printf("\n");
    printf("\n");
    printf("\n:POSSIBILITY OF INFECTED List:\n");

    for(i=1;i<=10;i++)
    {
        if(possibility[i]==info[i].uniqueid_no)
        {
            printf("NAME:%s\tUNIQUE NO:%d\tADDRESS:%s\tPHONE NO:%d\n",info[i].name,info[i].uniqueid_no,info[i].address,info[i].phone_no);
        }
    }
    printf("\n");
    printf("\n");
    printf("\n:INFECTED List:\n");
    for(i=1;i<=10;i++)
    {
        if(infected[i]==info[i].uniqueid_no)
        {

        printf("\nNAME:%s\tUNIQUE ID:%d\tADDRESS:%s\tPHONE NO:%d\n",info[i].name,info[i].uniqueid_no,info[i].address,info[i].phone_no);

        printf("\nSUGGESTION\n");

        for(j=1;j<=6;j++)
        {
            if(strcmp(info[i].address,doctor[j].location)==0)
            {
                printf("\nHOSPITAL NAME:%s\tLOCATION:%s\tDOCTOR NAME:%s\n",doctor[j].hospital_name,doctor[j].location,doctor[j].doctor_name);
                printf("\n");
            }
        }
        }
    }
    printf("\n\n");
    return 0;
}

