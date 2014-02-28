/* 
 * Author: Mufaddal Makati
   Official Post: http://www.rawbytes.com
 Copyright [2010] [Author: Mufaddal Makati]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 *
 * Created on September, 2010.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CONN 10
#define MAX_NODES 50
#define INFINITE 9999
/*
 *
 */
void view(); /* just prints out the graph*/
void djkstra(); /*runs at the begining and when file is rescaned*/
void min_route();
void scanfile(); /*it does not check for wrong format of the file.it is up to the user to verify it.*/
struct node /*data structure to store information of each node*/
{
    int id; 
    struct node *l[MAX_CONN+1]; /*array that points to all other nodes connected with this node*/
    int cost[MAX_CONN+1];  /*array that stores cost of all connections with this node*/
    struct node **next; /*address of the pointer of the next node to traverse, for the ith destination node in the array of records datastructure*/
    int *mincost;/*minimum cost to traverse the ith destination node in the array of records datastructure*/
};
typedef struct node nodes; 
struct record /* data structure to map node id and corresponding address of nodes structure.*/
{
    int nid;
    struct node *add;
};
typedef struct record records;
records nlist[MAX_NODES+1]={{0,0}}; /*create array of records and mark the end of the array with zero.*/
int count; /*stores number of nodes*/

int main()
{
    int c;
    nlist[MAX_NODES+1].nid=0;
    system("clear");

    scanfile();
    printf("\nSucessfully Scanned the graph.\n");
    djkstra();

    for(;;)
    {
        view();

        printf("\n1.Rescan file.");
        printf("\n2.View minimum route between nodes.");
        printf("\n3.Exit.");
        printf("\nEnter:");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
            {
                scanfile();
                djkstra();
                system("clear");
                break;
            }
            case 2:
            {
                min_route();
                system("clear");
                break;
            }
            case 3:
            {
                exit(0);
            }
            default:
            {
                printf("\nEnter proper choice.\n");
                break;
            }
        }        
    }
    return (EXIT_SUCCESS);
}

void scanfile()
{
    FILE *f;
    int d;
    int i=0,j=0,n_id,n_cost;
    nodes *temp=0,*temp1=0;

    if((f=fopen("graph.ospf","r"))== NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    memset(nlist, 0, sizeof(struct record) * MAX_NODES);
    count=0;
    do /*first get the id and address of all nodes*/
    {
        fscanf(f,"%d",&n_id);
        for(i=0;nlist[i].nid!=0;i++)
        {
            if(n_id==nlist[i].nid)
            {
                printf("Id already exists.");
                return;
            }
        }
        temp=malloc(sizeof(nodes));
        if (temp == 0)
        {
           printf("ERROR: Out of memory\n");
           return;
        }
        memset(temp, 0, sizeof(struct node));
        temp->id=n_id;
        temp->l[MAX_CONN+1]=0;
        temp->cost[MAX_CONN+1]=0;
        for(i=0;nlist[i].nid!=0;i++)
        {}
        nlist[i].nid=n_id;
        nlist[i].add=temp;
        count++;
        while((d=fgetc(f)!=';'))
        {}
    }while((d=fgetc(f))!=EOF);

    rewind(f);

    for(i=0;i<count;i++) /*now get the information of all nodes connections.*/
    {
        fscanf(f,"%*d");
        temp=nlist[i].add;
        while((d=fgetc(f)!=';'))
        {
            fscanf(f,"%d-%d",&n_id,&n_cost);
            for(j=0;nlist[j].nid!=0;j++)
            {
                if(nlist[j].nid==n_id)
                {
                    temp1=nlist[j].add;
                    break;
                }
            }
            for(j=0;temp->cost[j]!=0;j++)
            {}
            temp->cost[j]=n_cost;
            temp->l[j]=temp1;
        }
    }
    fclose(f);
}

void view()
{
    int i,j;
    nodes *temp=0,*temp1=0;

    printf("\nID\tConnceted to- ID:cost");
    for(i=0;nlist[i].nid!=0;i++)
    {
        printf("\n%d",nlist[i].nid);
        temp=nlist[i].add;
        for(j=0;temp->l[j]!=0;j++)
        {
            temp1=temp->l[j];
            printf("\t%d:%d",temp1->id,temp->cost[j]);
        }
    }
    printf("\n \n \n");
}

void djkstra()
{
    int i,j,k,num,num1=0,min=INFINITE;
    int *tcost=0,*done=0;
    nodes *temp=0,*temp1=0,**tent=0;

    tcost=calloc(count, sizeof(int));
    if (tcost == 0)
    {
	printf("ERROR: Out of memory\n");
	return;
    }
    done=calloc(count, sizeof(int));
    if (done == 0)
    {
	printf("ERROR: Out of memory\n");
	return;
    }
    tent=calloc(count, sizeof(nodes));
    if (tent == 0)
    {
	printf("ERROR: Out of memory\n");
	return;
    }

    for(i=0;nlist[i].nid!=0;i++)
    {
         for(j=0;j<count;j++)
         {
            tcost[j]=INFINITE;
            done[j]=0;
         }
        temp=nlist[i].add;
        temp->next=calloc(count, sizeof(nodes));
        temp->mincost=calloc(count, sizeof(int));
        tcost[i]=0;
        done[i]=1;
        temp->mincost[i]=0;
        temp1=temp;
        for(;;)
        {
            for(num1=0;nlist[num1].nid!=0;num1++)
            {
                if(nlist[num1].add==temp1)
                    break;
            }
            for(k=0;temp1->l[k]!=0;k++)
            {
                for(num=0;nlist[num].nid!=0;num++)
                {
                    if(nlist[num].add==temp1->l[k])
                        break;
                }

                if(tcost[num] > (tcost[num1]+temp1->cost[k]))
                {
                    tcost[num]= tcost[num1] + temp1->cost[k];
                    if(temp1==temp)
                        tent[num]=temp1->l[k];
                    else
                        tent[num]=tent[num1];
                }
            }
            min=INFINITE;num1=0;
            for(j=0;j<count;j++)
            {
                if(tcost[j]<min && done[j]!=1 && tcost[j]!=0)
                {
                    min=tcost[j];
                    num1=j;
                }
            }
            if(min==INFINITE)
                break;

            temp1=nlist[num1].add;
            temp->mincost[num1]=tcost[num1];
            temp->next[num1]=tent[num1];
            done[num1]=1;
        }
    }
}

void min_route()
{
    int i,sid,did,num,chk=0;
    nodes *temp=0,*temp1=0;

        printf("\nEnter source node ID:");
        scanf("%d",&sid);
        printf("\nEnter destination node ID:");
        scanf("%d",&did);

        for(i=0;nlist[i].nid!=0;i++)
        {
            temp=nlist[i].add;
            if(temp->id==sid)
            {
                chk=1;
                break;
            }
        }
        if(chk==0)
        {
            printf("\nSource Id not found.\n");
            return;
        }
        chk=0;
        for(num=0;nlist[num].nid!=0;num++)
        {
            temp1=nlist[num].add;
            if(temp1->id==did)
            {
                chk=1;
                break;
            }
        }
        if(chk==0)
        {
            printf("\nDestination Id not found.\n");
            return;
        }
        printf("%d-",temp->id);
        temp1=temp;
        for(;;)
        {
            if(temp1->id==did)
                break;
            if(temp1->next[num]!=0)
            {
                temp1=temp1->next[num];
                printf("-%d-",temp1->id);
            }
            else
            {
                printf("No Route");
                break;
            }
        }
        printf("\nTotal cost:%d",temp->mincost[num]);
}


