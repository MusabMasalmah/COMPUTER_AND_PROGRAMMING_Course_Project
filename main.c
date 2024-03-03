#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maximum 1000//تعريف ان الحد الاقصى هو 100 طالب
void tarteb(int [], char [][50], double [], int );
void IDSort(int [], char [][50], double [], int );
void nameSort(int [], char [][50], double [], int );
void SID(int [], char [][50], double [], int );
void scoreSort(int [], char [][50], double [], int );
void SN(int [], char [][50], double [], int );

const char* GetValues(int N,char *L)// A function to separate the information from the file according to the $
{
    const char* T;
    for(T=strtok(L, "$"); T&&*T; T = strtok(NULL, "$\n"))//فور لوب لتقطيع المعلومات حسب $
    {
        if(!--N)
            return T;
    }
    return NULL;
}
int main()
{
    int StuID[maximum],TheChoice,musab=0;double scores[maximum],type[5];char NamesOfStu[maximum][50],NamesOfFile[30],TheLines[1024],*flag;
    printf("Enter file name: ");
    scanf("%s", NamesOfFile);
    FILE *Fopen;
    Fopen = fopen(NamesOfFile, "r");
    while(fgets(TheLines, 1024, Fopen))//while statment to get values and put it in aray and separate it to int,double and char
    {
        flag=strdup(TheLines);
        StuID[musab]=atoi(GetValues(1,flag));//تخزين معلومات بصيجة انتجر في ال اي دي اراي
        flag=strdup(TheLines);
        strcpy(NamesOfStu[musab], GetValues(2,flag));
        for(int i = 0; i < 5; i++)
        {
            flag = strdup(TheLines);
            type[i] = atof(GetValues(i+3,flag));
        }
        scores[musab] = (0.15*type[0])+(0.15*type[1])+(0.25*type[2])+(0.10*type[3])+(0.35*type[4]);//حساب المعدل
        musab++;
    }
    fclose(Fopen);

    tarteb(StuID, NamesOfStu, scores, musab);
    printf("------------------------------------------------musab---------------------------------------------------- \n");
    printf("the menu:\n");
    printf("1. Sort data in ascending order according to students' IDs and then display it.\n");
    printf("2. Sort data in ascending order according to students' names and then display it.\n");
    printf("3. Sort data in descending order according to students' scores and then display it.\n");
    printf("4. Ask the user to enter a student ID and display his score.\n");
    printf("5. Ask the user to enter a student name and display his score.\n");
    printf("6. Exit the program.\n");
    printf("Enter your choic plese:");
    printf("\n------------------------------------------------musab-----------------------------------------------------\n");
    scanf("%d",&TheChoice);
    switch (TheChoice)//switch statement to get the choic
    {
    case 1:
        IDSort(StuID,NamesOfStu, scores, musab);
        break;
    case 2:
        nameSort(StuID,NamesOfStu, scores, musab);
        break;
    case 3:
        scoreSort(StuID,NamesOfStu, scores, musab);
        break;
    case 4:
        SID(StuID,NamesOfStu, scores, musab);
        break;
    case 5:
        SN(StuID,NamesOfStu, scores, musab);
        break;
    case 6:
        printf("Can you give me a score of 10 out of 10?\n");
        printf("\n------------------------------------------------musab-----------------------------------------------------\n");
        break;
    }
}
void tarteb(int StuID[], char NamesOfStu[][50], double scores[], int musab)//فنكشن لترتيب المعطيات واخراجها بشكل مناسب
{
    printf("ID");
    printf("              names");
    printf("                                    score\n");
    for(int i = 0; i < musab; i++)//فور لوب لطباعة المخرجات
    {
        printf("%-15d %-40s %-15.2lf\n", StuID[i], NamesOfStu[i], scores[i]);

    }
}
void IDSort(int StuID[], char NamesOfStu[][50], double scores[], int musab)//فنكشن للترتيب المعطبات تصاعديا حسب ال اي دي
{
    int MIN,TI,counter = 0;double T;char *TC = malloc(sizeof(char) * 50),want,nameoffile[15];
    while(counter<musab)
    {
        MIN = counter;
        for(int j = counter+1; j < musab; j++)//فور لوب لترتيب تصاعديا
        {
            if(StuID[j] < StuID[MIN])
                MIN = j;
        }
        TI = StuID[counter];//ترتب المعلومات
        StuID[counter] = StuID[MIN];
        StuID[MIN] = TI;
        strcpy(TC, NamesOfStu[counter]);
        strcpy(NamesOfStu[counter], NamesOfStu[MIN]);
        strcpy(NamesOfStu[MIN], TC);
        T = scores[counter];
        scores[counter] = scores[MIN];
        scores[MIN] = T;
        counter++;
    }
    tarteb(StuID, NamesOfStu, scores, musab);//استدعاء الفنكشن لطباعة المعلومات بعد ترتيبها تصاعديا حسب ال اي دي
    printf("if you want to save it click (y) ");//  من سطر 109 حتى سطر 125 هو لسؤال الاخ المستخدم اذا كان يريدحفظ المعلومات في ملف وحفظهم اذا اراد
    printf("\n------------------------------------------------musab-----------------------------------------------------\n");
    scanf(" %c", &want);
    if(want == 'y')
    {
        printf("Enter filename to save the result: ");
        scanf("%s", nameoffile);
        FILE *openit;
        openit = fopen(nameoffile, "w");
        fprintf(openit, "%s            %s              %s\n", "ID", "Name", "Score");
        for(int i = 0; i < musab; i++)
        {
            fprintf(openit, "%d      %s      %.2lf\n", StuID[i], NamesOfStu[i], scores[i]);
        }
        fclose(openit);
    }
    else
        printf("Can you give me a score of 10 out of 10?");
}
void nameSort(int StuID[], char NamesOfStu[][50], double scores[], int musab)// فنكشن لترتيب المعلوكات حسب الحروف الابجدية للاسماء
{
    int MIN,TI;double T;char *TC = malloc(sizeof(char) * 50),want,nameoffile[15];
    for(int i = 0; i < musab; i++)
    {
        MIN = i;
        for(int j = i+1; j < musab; j++)
        {
            if(strcmp(NamesOfStu[j], NamesOfStu[MIN]) < 0)
                MIN = j;
        }
        TI = StuID[i];// من سطر 138 حتى سطر 146 هو طريقة ترتيب المعلومات حسب الحروف الابجدية
        StuID[i] = StuID[MIN];
        StuID[MIN] = TI;
        strcpy(TC, NamesOfStu[i]);
        strcpy(NamesOfStu[i], NamesOfStu[MIN]);
        strcpy(NamesOfStu[MIN], TC);
        T = scores[i];
        scores[i] = scores[MIN];
        scores[MIN] = T;
    }
    tarteb(StuID, NamesOfStu, scores, musab);
     printf("if you want to save it click (y) ");
     printf("\n------------------------------------------------musab-----------------------------------------------------\n");
    scanf(" %c", &want);
    if(want == 'y')
    {
        printf("Enter filename to save the result: ");
        scanf("%s", nameoffile);

        FILE *openit;
        openit = fopen(nameoffile, "w");
        fprintf(openit, "%s            %s              %s\n", "ID", "Name", "Score");
        for(int i = 0; i < musab; i++)
        {
            fprintf(openit, "%d      %s      %.2lf\n", StuID[i], NamesOfStu[i], scores[i]);
        }
        fclose(openit);
    }
    else
        printf("Can you give me a score of 10 out of 10?");
    }
void scoreSort(int StuID[], char NamesOfStu[][50], double scores[], int musab)//فنكشن لترتيب المعلومات تنازليا حسب المعدل
{
    int MAX,TI;double TD;char *TC = malloc(sizeof(char) * 50),want,nameoffile[15];


    for(int i = 0; i < musab; i++)//فور لوب لترتيب المعلومات حسب المعدل
    {
        MAX = i;
        for(int j = i+1; j < musab; j++)
        {
            if(scores[j] > scores[MAX])
            MAX = j;
        }
        TI = StuID[i];//ترتيب معلومات
        StuID[i] = StuID[MAX];
        StuID[MAX] = TI;
        strcpy(TC, NamesOfStu[i]);
        strcpy(NamesOfStu[i], NamesOfStu[MAX]);
        strcpy(NamesOfStu[MAX], TC);
        TD = scores[i];
        scores[i] = scores[MAX];
        scores[MAX] = TD;
    }
    tarteb(StuID, NamesOfStu, scores, musab);
     printf("if you want to save it click (y) ");
     printf("\n------------------------------------------------musab-----------------------------------------------------\n");
    scanf(" %c", &want);
    if(want == 'y')
    {
        printf("Enter filename to save the result: ");
        scanf("%s", nameoffile);
        FILE *openit;
        openit = fopen(nameoffile, "w");
        fprintf(openit, "%s            %s              %s\n", "ID", "Name", "Score");
        for(int i = 0; i < musab; i++)
        {
            fprintf(openit, "%d      %s      %.2lf\n", StuID[i], NamesOfStu[i], scores[i]);
        }
        fclose(openit);
    }
    else
        printf("Can you give me a score of 10 out of 10?");
    }
void SID(int StuID[], char NamesOfStu[][50], double scores[], int musab)//فنكشن للبحث عن معدل الطالب حسب ال اي دي تبعه
{
    int ID, i;
    printf("Enter ID of student: ");
    scanf("%d", &ID);
    for(i = 0; i < musab; i++)// البحث عن معدل الطالب المطلوب حسب ال اي دي تبعه
    {
        if(StuID[i] == ID)
            break;
    }
    if(i != musab)
    {
        printf("The score is %.2lf\n", scores[i]);//طباعة المعدل الخاص بالطالب
        printf("Can you give me a score of 10 out of 10?");
        printf("\n------------------------------------------------musab-----------------------------------------------------\n");
    }
}
void SN(int StuID[], char NameOfStu[][50], double scores[], int musab)//فنكشن للبحث عن معدل الطالب حسب اسمه
{
    char TheName[30];int coun;
    printf("Insert student name: ");//musab
    scanf(" %[^\n]%*c", TheName);
    for(coun = 0; coun < musab; coun++)// البحث عن اسم الطالب لمعرفة معدله
    {
        int x=strcmp(TheName, NameOfStu[coun]);
        if(x == 0)
            break;
    }
    if(coun != musab)
    {
        printf("The score is %.2lf\n", scores[coun]);//طباعة معدل الطالب حسب اسمه
        printf("Can you give me a score of 10 out of 10?");
        printf("\n------------------------------------------------musab-----------------------------------------------------\n");
    }
}












