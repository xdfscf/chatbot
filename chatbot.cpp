#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<string.h>
#include<ctype.h> 
#include <conio.h>
#define PI 3.141592
char *WFQ[20];

typedef struct dic
{
	int pos[6];//0 for n, 1 for v,2 for adj,3 for adv,4 for conj,5 for num,6 for prep.
	int like;
	int end;
	dic *letters[26];
}Node;

Node *buildtree()
{
	Node *head=(Node *)malloc(sizeof(Node));
	Node *current;
	int i;
	int n=0;
	int npos;
	char c;
    FILE *fp;
    
	for(i=0;i<26;i++)
    head->letters[i]=NULL;
    for(i=0;i<6;i++)
    head->pos[i]=0;
    head->end=0;
    head->like=0;
    
    fp=fopen("dic.txt", "rb");
    while(1)
    {
    	current=head;
    	//printf("%p",current);
            while((c=fgetc(fp)) !=' ')
        	{
        	if(c==EOF)
			break;
			
        	
        	if(islower(c))
			{
        	npos = c - 'a';
            if(current->letters[npos]==NULL)
            {
            //printf("%c",c);
            Node *node=(Node *)malloc(sizeof(Node));
            for(i=0;i<26;i++)
            node->letters[i]=NULL;
            for(i=0;i<6;i++)
            node->pos[i]=0;
            node->end=0;
            node->like=0;
            current->letters[npos]=node;
            current=node;
            }
            else
            current=current->letters[npos];
            }
            
        	}
        	//printf("%p",current);
        	//printf("\n");
        	current->end=1;
        	
        	while(c!='\n')
			{
				if(c==EOF)
				break;
			    
			    c=fgetc(fp);
				    if(islower(c))
				    {
			        	if(c=='n')
						{ 
							if(fgetc(fp)=='.')
							{
							current->like=(2*sin(n*PI/6)+0.5);
			        	    current->pos[0]=1;
			        	    }
			        	    else
			        	    current->pos[4]=1;
		        	    }
		        	    else if(c=='v')
		        	    {
		        	    current->pos[1]=1;
		        	    current->like=(2*sin(n*PI/6)+0.5);
		        	    }
		        	    else if(c=='a')
		        	    {
			        	    fgetc(fp);
							if(fgetc(fp)=='j')
							current->pos[2]=1;
							else
							current->pos[3]=1;
						}
						else if(c=='p')
						{
						for(i=0;i<3;i++)
						fgetc(fp);
						current->pos[5]=1;
					    }
				    }
			}
			n++;
			if(c==EOF)
			break;
			
    }
     
    fclose(fp);
    return head;
}

char *uncap(char *sentence)
{
	int i=0,m=0,n=0;
	char c;
	char *a=(char *)malloc(50*sizeof(char));
	while((c=*(sentence+n++)) !='\0')
	{
		while(isalpha(c)||c=='\'')
		{
		if(c>'A'&&c<'Z') 
		c=c+32;
		
		*(a+i++)=c;
		if(c=='\'')
		{
			c=*(sentence+n++);
			if(c=='s')
			{
			*(a+i-1)=' ';
			*(a+i)='i';
			*(a+i+1)='s';
			i+=2;
		    }
		    else
			{
			*(a+i)=c;
			i+=1;
			}
		}
		c=*(sentence+n++);
		m=1;
	    }
	    
	    if(m==1)
	    {
	     m=0;
		 *(a+i++)=' ';
		}
    
    }
    *(a+i-1)='\0';
    printf("%s",a);
    return a;
}

int compare(char *sentence)
{
	FILE *fp=fopen("train.txt", "rb");
	char c,p=' ';
	char *a,*b=(char *)malloc(50*sizeof(char));
	int m=0,i=0;
	
	/*while((c=*(sentence+(m++))) !='\0')
	{
	if(islower(c))
	*(a+(i++))=c;
    }
    *(a+i)='\0';
    
	i=0;*/
    while(p!=EOF)
    {
    		
    	while((p=fgetc(fp)) !='\\')
    	{
    	 if(p==EOF)
		 break;
	    	if(islower(p)||p==' ')
	    	{
		    	//printf("%c",p);
		    	if(*(sentence+i++)==p)
		    	{
				m=1;
				//if(*(sentence+i)=='\0')
				//break;
				//continue;
			    }
		    	else
		    	{
		    	i=0;
		    	m=0;	
		    	break;
		    	}
	        }
        }
        
        if(m==1)
        {
        i=0;
        while(p=fgetc(fp))
        {
        	if(isalpha(p))
        	{
        	*(b+i++)=p;
        	while((*(b+i++)=fgetc(fp))!='/')
        	m=0;
            }
            if(m==0)
            break;
		}
        *(b+i-1)='\0';
		printf("\n%s\n",b);	
		break;
		}
		
		while((p=fgetc(fp))!='/')
		{
		 if(p==EOF)
		 break;
        }
	}
	return 1;
} 

int order(Node *head,char *sentence)
{
	int n=0,i=0,a=0,b=0,m=0,d=0;
	char c=' ';
	char buf[20];
	
	while(c !='\0')
	{
		Node *current=head;
	    c=*(sentence+n++);
		FILE *fp=fopen("special.txt", "r+");
		char word[20]={0};
		while(isalpha(c))
		{
			word[i++]=c;
			c=*(sentence+n++);
			d=1;
		}
		
	if(d==1)
	{
    word[i]='\n';
	i=0;
	while (fgets(buf, sizeof(buf), fp) != NULL) 
	{
		if(*(buf+1)=='.')
		{
        a=*buf-48;
        //printf("%i",a);
        }
		if(!strcmp(buf,word))
		{
		b+=a*pow(10,m);
		m+=1;
	    }
	    d=0;
    }
	
	for(a=0;word[a]!='\n';a++) 
	current=current->letters[word[a]-'a'];
	
	if(current->pos[0]==1)
	{
	b+=4*pow(10,m);
	m+=1;
	}

    fclose(fp);
    }
    }
printf("%i",b);
	return 1;
}

int train()
{
	char senten[50];
	char answer[50];
	char p;
	FILE *fp=fopen("train.txt", "r+");
	while((p=fgetc(fp))!=EOF)
	{}
	printf("please enter the question\n");
	gets(senten);
	fprintf(fp,"%s\\",senten);
	printf("please enter the answer\n");
	gets(answer);
	fprintf(fp,"%s/",answer);
	
	return 0;
}
   

int main()
{
	Node *head=buildtree();
	int a;
	char *sentence;
	char senten[50];
	//a=order(head,sentence);
    while(1)
	{
	gets(senten);
	if((senten[0])=='$')
	break;
       
	//printf("1");
	sentence=(char *)malloc(50*sizeof(char));
	sentence=uncap(senten);
	
	
	//printf("1");
	if(compare(sentence));
	{
	a=order(head,sentence);
	
	}
	free(sentence);
	//train();
	
	//int a=head->letters[25]->letters[14]->letters[14]->pos[0];
	//head=head->letters[2];
	//printf("%i",a);
    }
	return 0;
}
