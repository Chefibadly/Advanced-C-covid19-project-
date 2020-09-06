#include <tchar.h>
#include <myconio.h>
#include <stdio.h>
#include <windows.h>

//comment added
typedef struct Date{
   int day;
   int month;
   int year;
}Date;


typedef struct Maladies
{
    char maladie[20];
    int year_nbr;
}Maladies;


typedef struct CelluleMaladie
{
    Maladies maladies;
    struct CelluleMaladie *suivant;
}CelluleMaladie;

typedef  CelluleMaladie *ListeMaladies ;

typedef struct PersonneInfecte
{
    char CIN[1100];
    char nom[10];
    char prenom[10];
    char numTel[11];
    char nationalite[20];
    int age;
    Date dateInfection;
    int decede;
}PersonneInfecte;


typedef struct Cellule
{
    PersonneInfecte cellule;
    ListeMaladies infected_with;
    struct Cellule *suivant;
}Cellule;

typedef struct Cellule *ListePersonnesInfectees;




ListePersonnesInfectees AjoutPatient(ListePersonnesInfectees tete, PersonneInfecte C)
{
   ListePersonnesInfectees Nouveau;
   ListePersonnesInfectees Courant=tete;
   if (tete==NULL)
    {
      tete=(ListePersonnesInfectees) malloc(sizeof(Cellule));
      tete->cellule = C ;
      tete->suivant = NULL;
    }

     else {
           while (Courant->suivant != NULL)
               Courant = Courant->suivant;

           Nouveau=(ListePersonnesInfectees) malloc(sizeof(Cellule));
           Nouveau->cellule = C ;

 		   Courant->suivant = Nouveau;
           Nouveau->suivant = NULL;
           }
 return tete;
}

ListeMaladies AjoutMaladies(ListeMaladies tete, Maladies M)
{
   ListeMaladies Nouveau;
   ListeMaladies Courant=tete;
   if(tete==NULL)
    {
      tete=(ListeMaladies) malloc(sizeof(CelluleMaladie));
      tete->maladies= M ;
      tete->suivant = NULL;
    }

     else {
           while (Courant->suivant != NULL)
               Courant = Courant->suivant;

           Nouveau=(ListeMaladies) malloc(sizeof(CelluleMaladie));
           Nouveau->maladies= M ;

 		   Courant->suivant = Nouveau;
           Nouveau->suivant = NULL;
           }
 return tete;
}

ListeMaladies addMaladie(char CIN[],char *nomFichierMaladies,ListeMaladies L)
{
    FILE *f;
    char rep='c';
    Maladies M;
    char CIN_t[11];
    f=fopen(nomFichierMaladies,"r");

    if(f==NULL)
        printf("immposible ouvrir");


    while(rep!=EOF)
    {

        if(strcmp(CIN,CIN_t)==0){
            L=AjoutMaladies(L,M);
        }
        rep=fscanf(f,"%s%s%d",CIN_t,M.maladie,&M.year_nbr);
    }

    fclose(f);
    return L;
}

ListePersonnesInfectees supprimer (ListePersonnesInfectees L, char *CIN)
{
    ListePersonnesInfectees courant=L;
    ListePersonnesInfectees precedent;
    ListeMaladies courantM=L->infected_with;
    ListeMaladies nextM;
    if(L==NULL)
    {
        printf("Liste est vide");
        return L;
    }
    while(courant->suivant!=NULL && strcmp(courant->cellule.CIN,CIN)!=0)
    {
        precedent=courant;
        courant=courant->suivant;
        courantM=courant->infected_with;
    }

    if(courant==NULL)
    {
        printf("il n existe pas");
    }else
    {
        if(strcmp(courant->cellule.CIN,CIN)==0)
        {
            if(courant!=L)
            {
                precedent->suivant=courant->suivant;
                free(courant);
            }else
            {
                L=courant->suivant;
                free(courant);
            }
            while(courantM!=NULL)
            {
                nextM=courantM->suivant;
                free(courantM);
                courantM=nextM;
            }

        }
    }

    return L;
}

ListePersonnesInfectees charger_Personnes (char *nomFichierPersonnes, char* nomFichierMaladies)
{
    FILE *f1;
    char rep1='c';



    ListePersonnesInfectees Head=NULL;
    ListePersonnesInfectees courantH=Head;
    ListeMaladies HeadM=NULL;

    PersonneInfecte P;



    f1=fopen(nomFichierPersonnes,"r");


    if(f1==NULL)
        printf("imposible d ouvrir le ficher personnes");


    while (rep1 !=EOF)
    {

        rep1 = fscanf(f1,"%s%s%s%s%s%d%d%d%d%d",
                     P.CIN,
                     P.nom,
                     P.prenom,
                     P.numTel,
                     P.nationalite,
                     &P.age,
                     &P.dateInfection.day,
                     &P.dateInfection.month,
                     &P.dateInfection.year,
                     &P.decede);

        Head=AjoutPatient(Head,P);

        courantH=Head;

        while(courantH->suivant!=NULL)
            courantH=courantH->suivant;

        HeadM=addMaladie(P.CIN, nomFichierMaladies,HeadM);
        courantH->infected_with=HeadM;
        HeadM=NULL;

        }



    fclose(f1);

    return Head;

}
void enregistrement (char *nomFichierPersonnes, ListePersonnesInfectees L)
{
    FILE *f1;
    char rep1='c';
    char ok='c';
    PersonneInfecte P;
    ListePersonnesInfectees courant=L;


    while(courant->suivant!=NULL)
    {
        courant=courant->suivant;
    }
    ListeMaladies courantM=courant->infected_with;
    P=courant->cellule;

    f1=fopen(nomFichierPersonnes,"w");


    if(f1==NULL)
        printf("imposible d ouvrir le ficher personnes");
    while(rep1!=EOF)
        rep1=fscanf(f1,"%s",ok);
    if(rep1=EOF)
    {
        fprintf(f1,"%s %s %s %s %s %d %d %d %d %d ",
                     P.CIN,
                     P.nom,
                     P.prenom,
                     P.numTel,
                     P.nationalite,
                     P.age,
                     P.dateInfection.day,
                     P.dateInfection.month,
                     P.dateInfection.year,
                     P.decede);



    while(courantM->suivant!=NULL)
        courantM=courantM->suivant;

    fprintf(f1," %s %d",courantM->maladies.maladie,courantM->maladies.year_nbr);
    }
    fclose(f1);

}





void AfficherPersonnesInfectees(ListePersonnesInfectees L)
{
    ListePersonnesInfectees courantP=L;
    ListeMaladies courantM=NULL;

    while (courantP!= NULL)
    {
        printf("\n |%s |%s |%s |%s |%s |%d |%d |%d |%d |%d |",
           courantP->cellule.CIN,
           courantP->cellule.nom,
           courantP->cellule.prenom,
           courantP->cellule.numTel,
           courantP->cellule.nationalite,
           courantP->cellule.age,
           courantP->cellule.dateInfection.day,
           courantP->cellule.dateInfection.month,
           courantP->cellule.dateInfection.year,
           courantP->cellule.decede);

           printf("Maladies de :");
            courantM=courantP->infected_with;
               courantP= courantP->suivant;
           while (courantM!= NULL)
           {
               printf("%s | %d | ",courantM->maladies.maladie,courantM->maladies.year_nbr);
               courantM= courantM->suivant;
           }
    }

}

ListePersonnesInfectees Ajouter(ListePersonnesInfectees L)
{

    PersonneInfecte P;
    Maladies M;
    ListeMaladies LM=NULL;
    ListePersonnesInfectees courant;
    char rep[10];

    printf("Donner CIN:\n");
    scanf("%s",P.CIN);
    printf("Donner Nom:\n");
    scanf("%s",P.nom);
    printf("Donner Prenom:\n");
    scanf("%s",P.prenom);
    printf("Donner Numereaux de telephone:\n");
    scanf("%s",P.numTel);
    printf("Donner Nationalite:\n");
    scanf("%s",P.nationalite);
    do
    {
    printf("Donner l age:\n");
    scanf("%d",&P.age);
    }while(P.age<0);
    do
    {
    printf("Donner la date d infection sou forme dd/mm/yyyy:");
    scanf("%d/%d/%d",&P.dateInfection.day,&P.dateInfection.month,&P.dateInfection.year);
    }while(!valide(P.dateInfection));
    do
    {
        printf("Donne 1 si decedé 0 si nn\n");
        scanf("%d",&P.decede);

    }while(P.decede!=0 && P.decede!=1);



    printf("possede t il de maladie? \n");
    scanf("%s",rep);

    if(strcmp(rep,"oui")==0)
    {
        printf("%s",rep);
        do
        {
            printf("Donner maladie\n");
            scanf("%s",M.maladie);
            printf("Donner nombre d annees\n");
            scanf("%d",&M.year_nbr);

            LM=AjoutMaladies(LM,M);

            printf("possede t il d autre  maladie? \n");
            scanf("%s",rep);
            if(strcmp(rep,"non")==0)
                break;
        }while(strcmp(rep,"oui")==0);
    }
    else
    {
        if(strcmp(rep,"non")==0)
            L=AjoutPatient(L,P);

        return L;
    }


    L=AjoutPatient(L,P);
    courant=L;
    while(courant->suivant!=NULL)
        courant=courant->suivant;

    courant->infected_with=LM;

        return L;
}

ListePersonnesInfectees AjouterMaladie (ListePersonnesInfectees L,char* CIN, char* maladie, int annees)
{
    ListePersonnesInfectees courant=L;
    ListeMaladies courantM=courant->infected_with;
    Maladies M;
    int check=1;


    while(courant->suivant!=NULL && strcmp(CIN,courant->cellule.CIN)!=0)
    {
        courant=courant->suivant;
        courantM=courant->infected_with;

    }

    if(strcmp(CIN,courant->cellule.CIN)==0)
    {
        while(courantM!=NULL)
        {
            if(strcmp(maladie,courantM->maladies.maladie)==0)
                check=0;
            courantM=courantM->suivant;
        }

        if(check==1)
        {
                strcpy(M.maladie,maladie);
                M.year_nbr=annees;
                courant->infected_with=AjoutMaladies(courant->infected_with,M);

        }else
        {
            printf("le maladie deja exist");
        }
    }else
    {
        printf("ce personne n existe pas");
    }

    return L;

}


ListePersonnesInfectees modifierDeces(ListePersonnesInfectees L, char* CIN)
{
    ListePersonnesInfectees courant=L;


    while(courant->suivant!=NULL && strcmp(CIN,courant->cellule.CIN)!=0)
        courant=courant->suivant;

    if(strcmp(CIN,courant->cellule.CIN)==0)
    {

        if(courant->cellule.decede==0)
            courant->cellule.decede=1;
        else
            printf("decede deja 1");

    }else
        printf("ce CIN n existe pas");


    return L;

}

void afficherParNationalite(ListePersonnesInfectees L, char*Nationalite)
{
    ListePersonnesInfectees courantP=L;
    ListeMaladies courantM=courantP->infected_with;

    while (courantP->suivant!= NULL )
    {
        if(strcmp(Nationalite,courantP->cellule.nationalite)==0)
        {
           printf("\n |%s |%s |%s |%s |%s |%d |%d |%d |%d |%d |",
           courantP->cellule.CIN,
           courantP->cellule.nom,
           courantP->cellule.prenom,
           courantP->cellule.numTel,
           courantP->cellule.nationalite,
           courantP->cellule.age,
           courantP->cellule.dateInfection.day,
           courantP->cellule.dateInfection.month,
           courantP->cellule.dateInfection.year,
           courantP->cellule.decede);

           printf("Maladies de :");
            courantM=courantP->infected_with;
           while (courantM!= NULL)
           {
               printf("%s | %d | ",courantM->maladies.maladie,courantM->maladies.year_nbr);
               courantM= courantM->suivant;
           }
        }
               courantP= courantP->suivant;

    }
}
int convertDays(Date DateEnCours)
{
    int days;
    days=((DateEnCours.year/4) * 366)+((DateEnCours.year - DateEnCours.year/4)*365)+(DateEnCours.month-2)*30 + (DateEnCours.month-5)*31 +DateEnCours.day;
    //printf("nombre de jour=%d\n",days);
    return days;
}

void afficherPersonnesEnQuarantaine (ListePersonnesInfectees L, Date DateEnCours)
{
    ListePersonnesInfectees courantP=L;
    ListeMaladies courantM=courantP->infected_with;
    int diff_days;
    while (courantP->suivant!= NULL )
    {
        diff_days=convertDays(DateEnCours) - convertDays(courantP->cellule.dateInfection);
        //printf("diff days=%d",diff_days);
        if(diff_days<14)
        {
           printf("\n |%s |%s |%s |%s |%s |%d |%d |%d |%d |%d |",
           courantP->cellule.CIN,
           courantP->cellule.nom,
           courantP->cellule.prenom,
           courantP->cellule.numTel,
           courantP->cellule.nationalite,
           courantP->cellule.age,
           courantP->cellule.dateInfection.day,
           courantP->cellule.dateInfection.month,
           courantP->cellule.dateInfection.year,
           courantP->cellule.decede);

           printf("Maladies de :");
            courantM=courantP->infected_with;
           while (courantM!= NULL)
           {
               printf("%s | %d | ",courantM->maladies.maladie,courantM->maladies.year_nbr);
               courantM= courantM->suivant;
           }
        }
               courantP= courantP->suivant;

    }
}

void afficherPersonnesDecedes (ListePersonnesInfectees L)
{
    ListePersonnesInfectees courantP=L;
    ListeMaladies courantM=courantP->infected_with;
    int nb_per=0,nb_per_dec=0;
    printf("les personne decedee:\n");

    while (courantP->suivant!= NULL )
    {
        nb_per=nb_per+1;

        if(courantP->cellule.decede==1)
        {
           nb_per_dec=nb_per_dec+1;

           printf("\n |%s |%s |%s |%s |%s |%d |%d |%d |%d |%d |",
           courantP->cellule.CIN,
           courantP->cellule.nom,
           courantP->cellule.prenom,
           courantP->cellule.numTel,
           courantP->cellule.nationalite,
           courantP->cellule.age,
           courantP->cellule.dateInfection.day,
           courantP->cellule.dateInfection.month,
           courantP->cellule.dateInfection.year,
           courantP->cellule.decede);

           printf("Maladies de :");
            courantM=courantP->infected_with;
           while (courantM!= NULL)
           {
               printf("%s | %d | ",courantM->maladies.maladie,courantM->maladies.year_nbr);
               courantM= courantM->suivant;
           }
        }
               courantP= courantP->suivant;

    }

    printf("\n pourcentage de deces = %f\n",nb_per_dec/(float)nb_per);
}
int valide(Date d)
{
    int jmax;
    switch (d.month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: jmax=31; break;
        case 4:
        case 6:
        case 9:
        case 11: jmax=30; break;
        case 2: if (d.year%4==0&&d.year%100||d.year%400==0)
                    jmax=29;
                else jmax=28;
    }
    return d.day>0&&d.day<=jmax&&d.month>0&&d.month<=12&&d.year>=1900;
}

ListePersonnesInfectees supp_dec(ListePersonnesInfectees L)
{
    ListePersonnesInfectees courant=L;
    ListePersonnesInfectees precedent;
    ListeMaladies courantM=L->infected_with;
    ListeMaladies nextM;
    if(L==NULL)
    {
        printf("Liste est vide");
        return L;
    }
    while(courant->suivant!=NULL)
    {
        if(courant->cellule.decede == 1)
        {
            if(courant!=L)
            {
                precedent->suivant=courant->suivant;
                free(courant);
            }else
            {
                L=courant->suivant;
                free(courant);
            }
            while(courantM!=NULL)
            {
                nextM=courantM->suivant;
                free(courantM);
                courantM=nextM;
            }

        }
        precedent=courant;
        courant=courant->suivant;
        courantM=courant->infected_with;
    }



    return L;
}
float pourcentageRisque(ListePersonnesInfectees L)
{
    ListeMaladies courantM=L->infected_with;
    float percentR=(float)0;
    if(L->cellule.age>70)
    {
        if(percentR==0.0)
            percentR=(float)20;
        else
            percentR=percentR+(percentR*20)/(float)100;
    }

    if(L->cellule.age<70 && L->cellule.age>=50)
    {
        if(percentR==0.0)
            percentR=(float)10;
        else
            percentR=percentR+(percentR*10)/(float)100;
    }

    while(courantM!=NULL)
    {
        if(strcmp(courantM->maladies.maladie,"DIABETE")==0)
        {
            if(percentR==0.0)
                percentR=(float)15;
            else
                percentR=percentR+(percentR*15)/(float)100;
        }

        if(strcmp(courantM->maladies.maladie,"HYPERTENSION")==0)
        {
            if(percentR==0.0)
                percentR=(float)20;
            else
                percentR=percentR+(percentR*20)/(float)100;
        }

        if(strcmp(courantM->maladies.maladie,"ASTHME")==0)
        {
            if(percentR==0.0)
                percentR=(float)20;
            else
                percentR=percentR+(percentR*20)/(float)100;
        }

        courantM=courantM->suivant;
    }


    return percentR;
}

void AfficherPersonnesARisque(ListePersonnesInfectees L)
{
    ListePersonnesInfectees courant=L;
    float percentR;


    while (courant->suivant!= NULL)
    {
        printf("\n |%s |%s |",courant->cellule.nom,courant->cellule.prenom);

           percentR=pourcentageRisque(courant);
            printf("%f\n",percentR);
           courant=courant->suivant;
    }
}



/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void addmenus(HWND);
void CreateBtt(HWND hwnd) ;

HWND hname ,hage,hout,hogo,Add,Finnish;
 HDC hdc;
HMENU hmenu ;

HBITMAP hlogoImage , hgenerateImage;
int intro=1 ;
char ch[30] ;
long p ;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("my project");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+7;


    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Covid-19 Project C"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1920,                 /* The programs width */
           1080,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{static HBITMAP  hBmp;
    ListePersonnesInfectees L=NULL;
   /* if(intro)
    {
        system("start test.exe") ;
        intro=0;
    }*/

    switch (message)                  /* handle the messages */
    {

        case WM_COMMAND:
        switch(wParam)
        {

        case 1:
                system("color F2");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                printf("/*-*/*-*/*-*/*-*/ Charger donnee /*-*/*-*/*-*/*-*/ \n");
                L=charger_Personnes("Infected.txt","Maladies.txt");
                if(L!=NULL)
                {
                    printf("/*-*/*-*/*-*/*-*/ Donnee Chargee  /*-*/*-*/*-*/*-*/ \n");
                    AfficherPersonnesInfectees(L);
                }
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 3:
                system("color F2");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf("    /*-*/*-*/*-*/*-*/ Supprimer decede /*-*/*-*/*-*/*-*/  \n");
                L=supp_dec(L);
                AfficherPersonnesInfectees(L);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 2:
                system("color F2");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                printf("/*-*/*-*/*-*/*-*/ Afficher liste infectee /*-*/*-*/*-*/*-*/ \n");
                L=charger_Personnes("Infected.txt","Maladies.txt");
                if(L!=NULL)
                {
                    AfficherPersonnesInfectees(L);
                }
                //AfficherPersonnesInfectees(L);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;


        case 4:
                system("color F2");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf("    /*-*/*-*/*-*/*-*/ Ajouter un personne infectee /*-*/*-*/*-*/*-*/  \n");
                L=Ajouter(L);


                    AfficherPersonnesInfectees(L);

                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 5:
                system("color F2");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf("    /*-*/*-*/*-*/*-*/ Ajouter des Maladies /*-*/*-*/*-*/*-*/  \n");
                char CIN[11];
                char Maladie[20];
                int nbann;
                printf("pour ajout maladie \ndonner le CIN: \n");
                scanf("%s",CIN);
                printf("donner Maladie:\n");
                scanf("%s",Maladie);
                printf("dooner nombre d annee:\n");
                scanf("%d",&nbann);
                L=AjouterMaladie(L,CIN,Maladie,nbann);
                if(L!=NULL)
                {
                    AfficherPersonnesInfectees(L);
                }
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 6:
                system("color F2");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf("    /*-*/*-*/*-*/*-*/ modifier etat deces /*-*/*-*/*-*/*-*/   \n");
                printf("donner CIN  pour modifier etat deces \n");

                scanf("%s",CIN);
                modifierDeces(L,CIN);
                if(L!=NULL)
                {
                    AfficherPersonnesInfectees(L);
                }
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;


        case 7:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf("    /*-*/*-*/*-*/*-*/ Supprimer personne /*-*/*-*/*-*/*-*/   \n");
                printf("donner le CIN de personne qu'on va supprimer:\n");
                scanf("%s",CIN);
                L=supprimer(L,CIN);
                if(L!=NULL)
                {
                    AfficherPersonnesInfectees(L);
                }
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 8:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf("    /*-*/*-*/*-*/*-*/ Affichage par Nationalite /*-*/*-*/*-*/*-*/   \n");
                printf("entrer nationalite \n");
                char Nat[20];
                scanf("%s",Nat);
                afficherParNationalite(L,Nat);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 9:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf(" /*-*/*-*/*-*/*-*/  Afficher Personnes En Quarantine  /*-*/*-*/*-*/*-*/ \n");
                Date DateAujourdhuit;
                printf("entrer date d ahjourdhuit sous forme dd/mm/yyyy:\n");
                scanf("%d/%d/%d",&DateAujourdhuit.day,&DateAujourdhuit.month,&DateAujourdhuit.year);
                afficherPersonnesEnQuarantaine(L,DateAujourdhuit);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 10:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf(" /*-*/*-*/*-*/*-*/  Les Decedees  /*-*/*-*/*-*/*-*/ \n");
                afficherPersonnesDecedes(L);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 11:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                L=charger_Personnes("Infected.txt","Maladies.txt");
                printf(" /*-*/*-*/*-*/*-*/  Les Personne A Risques  /*-*/*-*/*-*/*-*/ \n");
                AfficherPersonnesARisque(L);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 12:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                ShellExecute(NULL,"open","Infected.txt",NULL,NULL,SW_SHOWNORMAL);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 13:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                ShellExecute(NULL,"open","Maladies.txt",NULL,NULL,SW_SHOWNORMAL);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;

        case 14:
                system("color F3");
                ShowWindow(hwnd,SW_HIDE);
                gotoxy(25,10);
                ShellExecute(NULL,"open","projet C avancé 2020.pdf",NULL,NULL,SW_SHOWNORMAL);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;


        case 15:
                if (MessageBox(hwnd," Vous voulez quitter ?", "QUITTER", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {

                    DestroyWindow(hwnd);
                    system("cls");


        }
        }

    case WM_CREATE :
        addmenus(hwnd);
//        CreateBtt(hwnd) ;
            /*****************ajouter fond ********************/
           hBmp=LoadImage(NULL,"med chedly et mahdi.bmp",IMAGE_BITMAP,1540,790,LR_LOADFROMFILE);

            break;

        case WM_PAINT :
            {



         PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);



            DrawState(hdc,NULL,NULL,(long)hBmp,0,0,0,0,0,DST_BITMAP);

            EndPaint(hwnd, &ps);}
        break;
        case WM_DESTROY:
            PostQuitMessage (0);        /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void addmenus(HWND hwnd)
{
    hmenu=CreateMenu();
    HMENU htp=CreateMenu();
    HMENU htp1=CreateMenu();
    //HMENU htp2=CreateMenu();
    HMENU htp3=CreateMenu();
    HMENU htp4=CreateMenu();
    HMENU htp5=CreateMenu();





    //AppendMenu(hmenu,MF_STRING,0,"création du repertoire");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp,"Lire/Ecrire fichier");

    AppendMenu(htp,MF_STRING,1,"Charger liste des personnes ");
    AppendMenu(htp,MF_STRING,2,"Afficher liste des personage ");
    AppendMenu(htp,MF_STRING,3,"Supprimer decede");




    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp1,"Suppression et Modification");


      AppendMenu(htp1,MF_STRING,4,"Ajout personne infectee");
      AppendMenu(htp1,MF_STRING,5,"Ajouter des maladie");
      AppendMenu(htp1,MF_STRING,6,"Modifier Deces");
      AppendMenu(htp1,MF_STRING,7,"Supprimer personne infectee");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp3,"Recherche et d affichage");

      AppendMenu(htp3,MF_STRING,8,"Affichage Par Nationalite");
      AppendMenu(htp3,MF_STRING,9,"Afficher Personnes En Quarantaine");
      AppendMenu(htp3,MF_STRING,10,"Afficher Personnes Decedes");
      AppendMenu(htp3,MF_STRING,11,"Afficher Personnes A Risque");




      AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp4,"Contenue des Fichiers");
           AppendMenu(htp4,MF_STRING,12,"Fichier infected");
           AppendMenu(htp4,MF_STRING,13,"Fichier maladie");

      AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp5,"PDF");
           AppendMenu(htp5,MF_STRING,14,"Projet C Avance Enoncee");


      AppendMenu(hmenu,MF_STRING,15,"Quitter");
          SetMenu(hwnd,hmenu);
}


