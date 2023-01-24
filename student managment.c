#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef struct Node node;  // Create new name for struct Node---> node
struct Node
{
    char student_id[50];
    char name[100];
    char average[50];
    char national_code[50];
    char phone_number[50];
    node *next;

} std,*head=NULL;

void display_student(); //to show student's details
void add_new_student(); //To add student's info in list
void remove_student(); //to delete student's info in list
void modify_average(); //to change student's info in list
void search_student(); //to search student's info in list
void print_title();//to show title
void saved_data(); //to save data to linked list
FILE *file;

void saved_data()
{
    node *temp,*new_node;
    head=NULL;
    rewind(file);
    while((fread(&std,sizeof(std),1,file))==1)
    {
        temp=(node*)malloc(sizeof(node));
        strcpy(temp->student_id,std.student_id);
        strcpy(temp->name,std.name);
        strcpy(temp->average,std.average);
        strcpy(temp->national_code,std.national_code);
        strcpy(temp->phone_number,std.phone_number);
        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;
            new_node=temp;
        }
        else
        {
            new_node->next=temp;
            new_node=temp;
        }
    }
}
void print_title()
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t*-------------------------------------*\n");
    printf("\n\n");
}
void search_student()
{
    print_title();
    saved_data();

    char flag='y';
    do
    {
        node *c=head,*temp=NULL;
        char id[100];
        printf("\n\t\t\tEnter Student id:");
        scanf("%s",id);
        printf("\n");
        while(c!=NULL)
        {
            if(strcmp(c->student_id,id)==0)
            {
                temp=c;
                break;
            }
            c=c->next;
        }
        if(temp==NULL)
            printf("\t\tRecord Not found!!!\n\n");
        else
        {

            printf("\n\t\tStudent\tid: %s %s\n",temp->student_id,temp->student_id);
            printf("\n\t\tName %s\n",temp->name);
            printf("\n\t\tAverage\t %s\n",temp->average);
            printf("\n\t\tNational_code %s\n",temp->national_code);
            printf("\n\t\tPhone_Number: %s\n",temp->phone_number);


        }
        getchar(); //For clearing the input buffer
        printf("Do you want to search more (Y/N) :");
        scanf("%c",&flag);

    }
    while(flag=='y'||flag=='Y');

    printf("\n");
    system("pause"); //Make the screen wait for a key press.



}
void modify_average()
{
    print_title();
    int check=0;
    char id[100];
    printf("\n\t\tEnter studnet id to Modify:");
    scanf("%s",id);

    rewind(file); //move file position indicator to the beginning
    while((fread(&std,sizeof(std),1,file)==1))
    {
        if(strcmp(id,std.student_id)==0)
        {
            check=1;
            break;
        }
    }

    if(check==0)
        printf("\n\t\tRecord not found!!!\n\n");
    else
    {
        fseek(file,-sizeof(std),SEEK_CUR);// file position indicator to the current
        printf("\n\t\tEnter new average :\n\n");
        scanf("%s",std.average);
        getchar();
        fwrite(&std,sizeof(std),1,file);
    }
    if(check==1)
    {
        printf("\n\t\tRecord was changed successfully.\n");
    }
    printf("\n");
    system("pause"); //Make the screen wait for a key press.


}
void remove_student()
{
    print_title();
    char id[100];
    FILE *tmp;
    if((tmp=fopen("tmp.txt","wb+"))==NULL)
    {
        printf("\n\t\tcan not be opened");

    }
    printf("\n\t\tEnter Student id to delete:");
    scanf("%s",id);
    int check=0;
    rewind(file); //move file position indicator to the beginning

    while((fread(&std,sizeof(std),1,file))==1)
    {
        if(strcmp(std.student_id,id)==0)
        {
            check=1;
        }
        else
        {
            fwrite(&std,sizeof(std),1,tmp);
        }

    }
    fclose(file);
    fclose(tmp);
    remove("file.txt"); //the file to delete
    rename("tmp.txt","file.txt"); //rename the file
    if((file=fopen("file.txt","rb+"))==NULL)
    {
        printf("Can not be opened.");

    }
    if(check==1)
    {
        printf("\n\t\tThe record has been deleted successfully.\n");
    }
    if(check==0)
        printf("\n\t\t\tERROR!!Record Not Found..\n");

    printf("\n");
    system("pause"); //Make the screen wait for a key press.


}
void add_new_student()
{
    print_title();
    char check='y';
    int k=1;
    while(check=='y'||check=='Y')
    {
        printf("\t\tStudent %d:\n",k);

        printf("\t\t\t\tEnter student id:");
        scanf("%s",std.student_id);

        printf("\n\t\t\t\tEnter name:");
        scanf("%s",std.name);

        printf("\n\t\t\t\tEnter average:");
        scanf("%s",std.average);

        getchar();

        printf("\n\t\t\t\tEnter national_code:");
        gets(std.national_code);

        printf("\n\t\t\t\tEnter phone_number:");
        gets(std.phone_number);

        fwrite(&std,sizeof(std),1,file);
        printf("\n\t\t\t\tDo You Want to Add More Information (y/n)--> ");
        getchar();
        check=getchar();
        printf("\n");
        k++;
    }

}
void display_student()
{
    print_title();
    saved_data();
    node *c=head;
    if(head!=NULL)
    {
        printf("\t\t\t\t\tID|\tNAME|\taverage|\tnational code|\tphone_number|\n\n");

    }
    while(c!=NULL)
    {
        printf("\t\t\t\t\t%s\t%s\t%s\t%s\t%s\n",c->student_id,c->name,c->average, c->national_code, c->phone_number);
        c=c->next;
    }

    printf("\n");
    system("pause"); //Make the screen wait for a key press.

}
int main()
{
    if((file=fopen("file.txt","rb+"))==NULL)
    {
        if((file=fopen("file.txt","wb+"))==NULL)
        {
            printf("The file can not be opened\n");
        }
    }

    while(1)
    {
        printf("\n");
        print_title();
        printf("\t\t\t\t\t\t1. Add New Student\n\n");
        printf("\t\t\t\t\t\t2. Display All Students Records\n\n");
        printf("\t\t\t\t\t\t3. Delete Student\n\n");
        printf("\t\t\t\t\t\t4. Search Student\n\n");
        printf("\t\t\t\t\t\t5. Modify Average Of Studnet\n\n");
        printf("\t\t\t\t\t\t6. sorted by average\n\n");
        printf("\t\t\t\t\t\t7. Exit\n\n");
        int choice;
        printf("\n\t\t\t\t\t\tEnter Option:--> ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        {
            add_new_student();
        }
        break;
        case 2:
        {
            display_student();
        }
        break;
        case 3:
        {
            remove_student();
        }
        break;
        case 4:
        {
            search_student();
        }
        break;
        case 5:
        {
            modify_average();
        }
        break;
        case 6:
        {   
            //selection_sort();
        }
        case 7:
        {
            system("cls");
            exit(0);
        }
        
        break;
        default:
        {
            printf("Wrong Input.. END!!\n");    
        }
        }
    }

    return 0;

}
