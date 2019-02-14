#include "management.h"

int main()
{
    initscr();
  int exit=0;
  int login_flag=0;
  Create_Struct();
  while(!exit)
  {
      clear();
  	switch(Account_Manage())
  	{
  		case '1' :
            echo();
            clear();
		  login_flag=login();
		  if(login_flag==1)
		  {
		  	call_menu();
		  }
		  else
          {
              clear();
		    printw("Error : Your account information is wrong!!\n");
            getch();
          }
		    break;
  		case '2' :
          echo();
          clear();
		  New_Account();
		  break;
  		case '3' :
          echo();
          clear();
		  Delete_Account();
		  break;
  		case '4' :
          echo();
          clear();
		  Temp_Password();
		  break;
  		case '5' : 
		  exit=1;
		  break;
  		default : 
          clear();
		  printw("Error : It is wrong order!!\n");
          getch();
		  break;
	}
    clear();
  		
  	
  }
  endwin();
  Save_Data();
  system("clear");
  user_free();
  return 0;
}
void Save_Data()
{
  int i,j,k;
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  FILE* fpoint;
  fpoint=fopen("data.txt","w");
  fprintf(fpoint,"%d\n",TOP->Year_Size);

  for(i=0;i<TOP->Year_Size;i++)
  {
     	fprintf(fpoint,"%s\n",TOP->ST_YEAR[i].year);
  		fprintf(fpoint,"%d\n",TOP->ST_YEAR[i].Num_Size);
  		current_num=TOP->ST_YEAR[i].Num_Size;
  		
  		for(j=0;j<current_num;j++)
  		{
  			fprintf(fpoint,"%s%s %s\n",TOP->ST_YEAR[i].year,TOP->ST_YEAR[i].ST_NUM[j].number,TOP->ST_YEAR[i].ST_NUM[j].password);
  			fprintf(fpoint,"%d\n",TOP->ST_YEAR[i].ST_NUM[j].Assign_Size);
  			current_assign=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
  			
  			for(k=0;k<current_assign;k++)
  			{
  				fprintf(fpoint,"%s",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name);
  				fprintf(fpoint,"%s",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe);
  				fprintf(fpoint,"%s",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor);
  				fprintf(fpoint,"%d/%d\n",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0],TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1]);
			}
			
			fprintf(fpoint,"%d\n",TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size);
			current_cgpa=TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size;
			for(k=0;k<current_cgpa;k++)
			{
				fprintf(fpoint,"%f\n",TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].score);
			}
  			
		}  		
  }
  fclose(fpoint);
}

void Create_Struct()
{
  int i,j,k;
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  char* token;
  char temp[350];
  FILE* fpoint=fopen("data.txt","r");
  TOP=malloc(sizeof(TREE_HEAD));
  fscanf(fpoint,"%d\n",&TOP->Year_Size);
  current_year=TOP->Year_Size;
  TOP->ST_YEAR=malloc(sizeof(YEAR)*current_year);
  for(i=0;i<current_year;i++)
  {
      fscanf(fpoint,"%s\n",TOP->ST_YEAR[i].year);
  		fscanf(fpoint,"%d\n",&Student_Count);
  		TOP->ST_YEAR[i].Num_Size=Student_Count;
  		TOP->ST_YEAR[i].ST_NUM=malloc(sizeof(STUDENT)*Student_Count);
  		for(j=0;j<Student_Count;j++)
  		{
  			fscanf(fpoint,"%4s%4s %s\n",TOP->ST_YEAR[i].year,TOP->ST_YEAR[i].ST_NUM[j].number,TOP->ST_YEAR[i].ST_NUM[j].password);
  			fscanf(fpoint,"%d\n",&TOP->ST_YEAR[i].ST_NUM[j].Assign_Size);
        	Assign_Count=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
        	TOP->ST_YEAR[i].ST_NUM[j].Child_A=malloc(sizeof(ASSIGN)*Assign_Count);
        	for(k=0;k<Assign_Count;k++)
        	{
          		fgets(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name,100,fpoint);
          		fgets(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe,100,fpoint);
          		fgets(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor,100,fpoint);
          		fscanf(fpoint,"%d/%d\n",&TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0],&TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1]);
        	}

        	fscanf(fpoint,"%d\n",&TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size);
        	CGPA_Count=TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size;
        	TOP->ST_YEAR[i].ST_NUM[j].Child_C=malloc(sizeof(CGPA)*CGPA_Count);
        	for(k=0;k<CGPA_Count;k++)
        	{
          		TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].semester=k+1;
          		fscanf(fpoint,"%f\n",&TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].score);
        	}
	}  		
  }
  fclose(fpoint);
}

char Account_Manage()
{
  printw("1. Login\n");
  printw("2. Create new Account\n");
  printw("3. Delete Account\n");
  printw("4. Get Temporary Password\n");
  printw("5. Exit\n");
  noecho();
  return wgetch(stdscr);
}
void call_menu()
{
	int logout_flag=0;

	while(!logout_flag)
	{
        clear();
	  switch(menu())
	  {
		case '1':
            clear();
			Search_Assign();
			break;
		case '2':
            clear();
			call_cgpa_menu();
			break;
		case'3':
            clear();
			Change_Password();
			break;
		case '4':
			logout_flag=1;
			break;
		default:
            clear();
			printw("Error : It is wrong order!!\n");
            getch();
			break;
	  }
      clear();
	}
			
}

char menu()
{
  printw("1. Assignment Management\n");
  printw("2. CGPA Management\n");
  printw("3. Change Password\n");
  printw("4. Logout\n");
  noecho();
  return wgetch(stdscr);
}
void Search_Assign()
{
  int Asize;
  char input;
  clear();
  printw("<Assignment Management for %s>\n",Curr_Num);
  Asize = TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Assign_Size;
  Sort_Assign();
  Print_Assign(Asize);
  printw("1. New Assignment\n2. Delete Assignment\n3. Return to main menu\n");
  noecho();
  input=wgetch(stdscr);
  echo();
  switch(input)
  {
      clear();
    case '1':
        clear();
        Add_Assign(); 
              break;
    case '2': clear();
              Delete_Assign(); 
              break;
    case '3': return;
              break;
    default : clear();
              printw("Error : Your command is wrong!!\n");
              getch();
              break;
  }
  clear();
}

void Print_Assign(int Asize)
{
  int k,D_day,thistime,thattime;
  time_t t;
  time_t c;
  struct tm *today;
  struct tm dueday;
  struct tm* due={0};
  int i;
  int j;
  i=Login_Year;
  j=Login_Num;
  t = time(NULL);
  today = localtime(&t);
  thistime = today->tm_yday;
  for(k=0;k<TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;k++)
  {
      dueday.tm_year=2017-1900;
      dueday.tm_mon=TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0]-1;
      dueday.tm_mday=TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1];
      dueday.tm_hour=0;
      dueday.tm_min=0;
      dueday.tm_sec=0;
      dueday.tm_isdst=0;
      c=mktime(&dueday);
      due=localtime(&c);
      thattime=due->tm_yday;
      printw("<%d> Name\t: %s",k+1,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name);
      printw("     Describe\t: %s",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe);
      printw("     Professor\t: %s",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor);
      printw("     Due\t: %d/%d\n",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0],TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1]);  
      if(thattime-thistime==0)
      {
          printw("     D-day\t: TODAY!\n\n");
          continue;
      }
      else if(thattime-thistime>0)
      {
          printw("     D-day\t: %d\n\n",thistime-thattime);
          continue;
      }
      else if(thattime-thistime<0)
      {
          printw("     D-day over!!\n\n");
          continue;
      }
  }

  
  
}

void call_cgpa_menu()
{
    int exit=0;
    while(!exit)
    {
        clear();
        switch(cgpa_menu())
        {
            case '1':
                clear();
                Add_GPA();
                break;
            case '2':
                clear();
                Print_CGPA();
                Print_CGPA_Graph();
                break;
            case '3':
                exit=1;
                clear();
                break;
            default :
                clear();
                printw("Error : Your command is wrong!!\n");
                getch();
                break;
        }
        clear();

    }
}

char cgpa_menu()
{
  printw("1. Add new GPA or Change existing GPA\n");
  printw("2. View all\n");
  printw("3. Exit\n");
  noecho();
  return wgetch(stdscr);
}
void Search_CGPA() 
{
  int exit;
  //Curr_year_index=Login_Year;
  //Curr_num_index=Login_Num;
  while(!exit)
  {
    clear();
    noecho();
    switch(cgpa_menu())
    {
      case CGPA_ADD: 
          clear();
          Add_GPA(); 
          break;
      case CGPA_VIEW: clear(); 
                      Print_CGPA(); break;
      case CGPA_QUIT: exit = 1; break;
	  default: break;
    }
  }
  exit = 0;
}
void Add_GPA()
{
  char semester;
  float gpa;
  int gpa_size;
  clear();
  echo();
  printw("Input the semester of GPA : ");
  scanw("%c", &semester);

  gpa_size = TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].CGPA_Size;  

  if(semester - '0' > (gpa_size + 1) || semester - '0' < 1) {
    printw("You entered wrong number!\n");
    getch();
    return ;
  } 
  printw("Input the GPA : ");
  scanw("%f", &gpa);

  if(gpa < 0 || gpa > 4.31) {
    printw("You entered wrong number!\n");
    getch();
    return ;
  }

  if(semester - '0' <= gpa_size) {
    Cor_GPA(semester, gpa);
    return ;
  }

  TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].CGPA_Size++;
  gpa_size++;

  TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C = (CGPA*)realloc(TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C,gpa_size * sizeof(CGPA));

  TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[gpa_size - 1].semester = semester - '0';
  TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[gpa_size - 1].score = gpa; 

  return ;

}
void Cor_GPA(char semester, float gpa) 
{
  int i;
  TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[semester - '0' - 1].score = gpa;
  printw("GPA is changed successfully!\n");
  getch();
  return ;

}
void Print_CGPA() //Additional
{
  int i;
  int tmpSemester;
  float tmpGPA;
  float sum = 0;
  clear();
  printw("<CGPA Management for %s>\n", Curr_Num);
  printw("------------------------------\n");
  printw("  Semester  |  GPA  |  CGPA  |  \n");
  for(i = 0 ; i < TOP -> ST_YEAR[Login_Year].ST_NUM[Login_Num].CGPA_Size ; i++) 
  {
      tmpSemester=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[i].semester;
      tmpGPA=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[i].score;
      sum=sum+TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[i].score;

    printw("------------------------------\n");
    printw("     %d      |  %.2f |  %.2f  |\n", tmpSemester, tmpGPA, sum/(i + 1));
  }
  printw("------------------------------\n\n");
  printw("<CGPA Management by Graph for %s>\n", Curr_Num);
  printw("(x-axis : semester,  y-axis : score)\n");
  Print_CGPA_Graph();
  getch();
}
void Print_CGPA_Graph() 
{
 	/*
		To do...(Additional)
	*/
}
void Sort_Assign()
{
    int i,j;
    int x,y;
    ASSIGN temp;
    i=Login_Year;
    j=Login_Num;
    for(x=1;x<TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;x++)
    {
        temp=TOP->ST_YEAR[i].ST_NUM[j].Child_A[x];
        for(y=x;y>0;y--)
        {
            if(TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1].date[0]>temp.date[0])
            {
                TOP->ST_YEAR[i].ST_NUM[j].Child_A[y]=TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1];
                if(y==1)
                {
                    TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1]=temp;
                    break;
                }
            }
            else if(TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1].date[0]==temp.date[0])
            {
                if(TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1].date[1]>temp.date[1])
                {
                    TOP->ST_YEAR[i].ST_NUM[j].Child_A[y]=TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1];
                    if(y==1)
                    {
                        TOP->ST_YEAR[i].ST_NUM[j].Child_A[y-1]=temp;
                        break;
                    }
                }
                else
                {
                    TOP->ST_YEAR[i].ST_NUM[j].Child_A[y]=temp;
                    break;
                }
            }
            else
            {
                TOP->ST_YEAR[i].ST_NUM[j].Child_A[y]=temp;
                break;
            }

        }

    
    }

}
void Add_Assign()
{
    int i,j,k;
    i=Login_Year;
    j=Login_Num;
    k=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
    TOP->ST_YEAR[i].ST_NUM[j].Child_A=realloc(TOP->ST_YEAR[i].ST_NUM[j].Child_A,sizeof(ASSIGN)*(TOP->ST_YEAR[i].ST_NUM[j].Assign_Size+1));
    TOP->ST_YEAR[i].ST_NUM[j].Assign_Size++;
    printw("Enter the name of new assignment : ");
    getstr(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name);
    strcat(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name,"\n");
    printw("Enter the description of new account : ");
    getstr(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe);
    strcat(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe,"\n");

    printw("Enter the professor of new assignment : ");
    getstr(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor);
    strcat(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor,"\n");

    printw("Enter the due month of new assignment : ");
    scanw("%d",&TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0]);
    printw("Enter the due day of new assignment : ");
    scanw("%d",&TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1]);
    printw("New assignment is successfully added!!\n");

    
}
void Delete_Assign()
{
    char temp[100];
    int i,j,k,m;
    int check;
    int flag=0;
    i=Login_Year;
    j=Login_Num;
    check=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
    printw("Enter the name of assignment to delete : ");
    getstr(temp);
    strcat(temp,"\n");
    for(k=0;k<check;k++)
    {
        if(strcmp(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name,temp)==0)
        {
            TOP->ST_YEAR[i].ST_NUM[j].Assign_Size--;
            for(m=k;m<TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;m++)
            {
                TOP->ST_YEAR[i].ST_NUM[j].Child_A[m]=TOP->ST_YEAR[i].ST_NUM[j].Child_A[m+1];
            }
            TOP->ST_YEAR[i].ST_NUM[j].Child_A=realloc(TOP->ST_YEAR[i].ST_NUM[j].Child_A,sizeof(ASSIGN)*(check-1));
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printw("Error : Your assignment name does not exist!!\n");
        getch();
    }

}
/*void Add_CGPA()
{
    int i;
    TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].CGPA_Size++;
    i=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].CGPA_Size-1;
    TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C=realloc(sizeof(CGPA)*(i+1));


  
}*/
void New_Account()
{
	int i,j;
    int x=-1;
    int y;
	int check=0;
	char temp[16];
	printw("Enter Your Student ID : ");
	scanw("%s",New_Num);
	for(i=0;i<TOP->Year_Size;i++)
	{
		if(strncmp(TOP->ST_YEAR[i].year,New_Num,4)==0)
		{
            x=i;
			for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
			{
				if(strncmp(TOP->ST_YEAR[i].ST_NUM[j].number,New_Num+4,4)==0) 
				{
					check=1;
					break;
				}
			}
		}
	}
	if(check==1) 
	{
		printw("Error : Your ID is already exist!!\n");
        getch();
		return;
	}
	else
	{
		printw("Enter Your Password : ");
		get_password(New_Pass);
		printw("Confirm Your Password : ");
		get_password(temp);
		if(strcmp(New_Pass,temp)!=0)
		{
			printw("Error : Your confirm password should be new password!!\n");
            getch();
			return;
		}
		else
		{
            if(x>=0)
            {
			    TOP->ST_YEAR[x].Num_Size++;
			    TOP->ST_YEAR[x].ST_NUM=realloc(TOP->ST_YEAR[x].ST_NUM,sizeof(STUDENT)*(TOP->ST_YEAR[x].Num_Size));
			    TOP->ST_YEAR[x].ST_NUM[j].Assign_Size=0;
			    TOP->ST_YEAR[x].ST_NUM[j].CGPA_Size=0;
			    strcpy(TOP->ST_YEAR[x].ST_NUM[j].number,New_Num+4);
			    strcpy(TOP->ST_YEAR[x].ST_NUM[j].password,New_Pass);	
			    printw("New account is successfully added!!\n");
			    return;
            }
            else 
            {
                TOP->Year_Size++;
                x=TOP->Year_Size-1;
                TOP->ST_YEAR=realloc(TOP->ST_YEAR,sizeof(YEAR)*(TOP->Year_Size));
                strncpy(TOP->ST_YEAR[x].year,New_Num,4);
                TOP->ST_YEAR[x].Num_Size=1;
                TOP->ST_YEAR[x].ST_NUM=malloc(sizeof(STUDENT));
                strcpy(TOP->ST_YEAR[x].ST_NUM[0].number,New_Num+4);
                strcpy(TOP->ST_YEAR[x].ST_NUM[0].password,New_Pass);
                TOP->ST_YEAR[x].ST_NUM[0].Assign_Size=0;
                TOP->ST_YEAR[x].ST_NUM[0].CGPA_Size=0;
                printw("New account is successfully added!!\n");
                return;
            }
		}
	}
	
	
}
void Delete_Account()
{
    int i,j;
    int x=-1;
    int y=-1;
    printw("Enter the student number to delete : ");
    scanw("%s",Curr_Num);

    for(i=0;i<TOP->Year_Size;i++)
    {
        if(strncmp(TOP->ST_YEAR[i].year,Curr_Num,4)==0)
        {
            x=i;
            for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
            {
                if(strncmp(TOP->ST_YEAR[i].ST_NUM[j].number,Curr_Num+4,4)==0)
                {
                    y=j;
                    break;
                }
            }
        }
    }
    if(x<0 || y<0)
    {
        printw("Error : Your id does not exist!!\n");
        getch();
        return;
    }
    else
    {
        printw("Enter the password : ");
        get_password(Curr_Pass);
        if(strcmp(TOP->ST_YEAR[x].ST_NUM[y].password,Curr_Pass)==0)
        {
            if(TOP->ST_YEAR[x].Num_Size==1)
            {
                TOP->Year_Size--;
                for(i=x;i<TOP->Year_Size;i++)
                {
                    TOP->ST_YEAR[x]=TOP->ST_YEAR[x+1];
                }
                TOP->ST_YEAR=realloc(TOP->ST_YEAR,sizeof(YEAR)*(TOP->Year_Size));

            }
            else
            {
                TOP->ST_YEAR[x].Num_Size--;
                for(i=y;i<TOP->ST_YEAR[x].Num_Size;i++)
                {
                    TOP->ST_YEAR[x].ST_NUM[y]=TOP->ST_YEAR[x].ST_NUM[y+1];
                }
                TOP->ST_YEAR[x].ST_NUM=realloc(TOP->ST_YEAR[x].ST_NUM,sizeof(STUDENT)*(TOP->ST_YEAR[x].Num_Size));
            }

        }
        else
        {
            printw("Error : Your password is wrong!!\n");
            getch();
            return;
        }

    }

}
void Change_Password()
{
	char temp[16];
	printw("Enter new password : ");
	get_password(New_Num);
	printw("Confirm new password : ");
	get_password(temp);
	if(strcmp(New_Num,temp)==0)
	{
		printw("Password of Account <%s%s> is successfully changed.\n",TOP->ST_YEAR[Login_Year].year,TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].number);
		strcpy(TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].password,New_Num);
	}
	else
	{
		printw("Error : Your confirm password should be New password!!\n");
        getch();
	}

}

void get_password(char pass[16])
{
	int i=0;
    char temp;
  while(1)
  {
      noecho();
    temp=getch();
    if(temp=='\n')
    {
      pass[i]='\0';
      break;
    }
    else if(temp==127)
    {
      if(i<1)
        i=-1;
      else
        i=i-2;
    }
    else
    {
      pass[i]=temp;
    }
    i++; 
  }
  printw("\n");
}

int login()
{
  int i,j;
  int year_flag=0;
  int num_flag=0;
  int pass_flag=0;
  char year[5]={};
  char num[5]={};
  char temp;

  printw("Student Number : ");
  scanw("%s",Curr_Num);
  printw("Password : ");
  get_password(Curr_Pass);

  for(i=0;i<4;i++)
    year[i]=Curr_Num[i];
  for(i=4;i<8;i++)
    num[i-4]=Curr_Num[i];
  for(i=0;i<TOP->Year_Size;i++)
  {
    if(!strcmp(TOP->ST_YEAR[i].year,year))
    {
      year_flag=1;
      break;
    }
  }
  if(year_flag==1)
  {
    for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
    {
      if(!strcmp(TOP->ST_YEAR[i].ST_NUM[j].number,num))
      {
        num_flag=1;
        break;
      }
    }
  }
  if(num_flag==1)
  {
    if(!strcmp(TOP->ST_YEAR[i].ST_NUM[j].password,Curr_Pass))
    {
      pass_flag=1;
      Login_Year=i;//stores logged in user's year
      Login_Num=j;//stores logged in user's number
    }
  }
  if(pass_flag==1)
    return 1;
  return 0;
}

void Temp_Password()
{
  int flag1=0;
  int i, j, k;
  int x,y;
  char num[5]={};
  char temppassword[9];
  float temp;
  clear();
  echo();
  srand(time(NULL));
  printw("Student Number:");
  scanw("%s",Curr_Num);
  
  for(i=0;i<TOP->Year_Size;i++)
  {
  	if(strncmp(TOP->ST_YEAR[i].year,Curr_Num,4)==0)
  	{
  		for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
  		{
  			if(strncmp(TOP->ST_YEAR[i].ST_NUM[j].number,Curr_Num+4,4)==0)
  			{
                x=i;
                y=j;
  				flag1=1;
  				break;
  			} 			
		}  		
	}
  }
  if(flag1!=1) 
  {
      printw("Error : Your Id does not exist!!\n");
      getch();
      return;
  }
  else
  {
  	printw("Input latest semester's GPA : ");
  	scanw("%f",&temp);
  	k=TOP->ST_YEAR[x].ST_NUM[y].CGPA_Size;
  	if(temp==TOP->ST_YEAR[x].ST_NUM[y].Child_C[k-1].score)
  	{
	   	for(k=0;k<8;k++)
  		{
  			TOP->ST_YEAR[x].ST_NUM[y].password[k]=rand()%94+33;
		}
		strcat(TOP->ST_YEAR[x].ST_NUM[y].password,"\0");
		printw("Temporary Password is <%s>",TOP->ST_YEAR[x].ST_NUM[y].password);
	}
	else
	{
		printw("Error : Your last semester's GPA is worng!!\n");
        getch();
	}
  } 
}

void user_free()
{
    int i,j;
    for(i=0;i<TOP->Year_Size;i++)
    {
        for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
        {
            if(TOP->ST_YEAR[i].ST_NUM[j].Assign_Size!=0)
                free(TOP->ST_YEAR[i].ST_NUM[j].Child_A);
            if(TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size!=0)
                free(TOP->ST_YEAR[i].ST_NUM[j].Child_C);
        }
        free(TOP->ST_YEAR[i].ST_NUM);
    }
    free(TOP->ST_YEAR);
    free(TOP);
}
