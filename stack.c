#include<stdio.h>
#include<stdlib.>
int stack1[10], stack2[10];
int size, num, top, i;
void main()
{
    printf("ENTER THE SIZE OF STACK\n");
    scanf("%d",&size);
    void push();
    for(i=0;i<=top;i++)
    {
        stack1[i]=stack2[i];
    }
    void display();
}
void push()
{   for(i=0;i<=size;i++) 
    {
        printf("ENTER THE NUMBER TO BE PUSHED\n");
        scanf("%d",&num);
        top++;
        stack1[top]=num;
    }
}

void diplay()
{
    printf("ORIGINAL STACK 1 CONTENTS ARE:\n");
    for(i=top;i>=0;i--)
    {
        printf("%d\n",stack1[i])
    }
    printf("STACK 2 CONTENTS IN REVERSE ARE:\n");
    for(i=0;i<=top;i++)
    {
        printf("%d\n",stack2[i]);
    }
}