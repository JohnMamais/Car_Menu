//ΙΩΑΝΝΗΣ ΜΑΜΑΗΣ ΤΕΠ Α'2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//strlen(), strcpy()
#include <unistd.h>
#include <ctype.h> //isdigit(), isalpha() etc

#define BUFFER 256
#define YEAR 2023
#define MAX_CARS 100

struct Data{
	int empty;
	char plate[5];
	char colour[8];
	char manufacturer[16];
	char year[5];
};

int InputCheck(char string[BUFFER]) //returns -1 if input is alphabet, negative or not int
{
	//δηλωση μεταβλητων
	int flag, i, l, selection;
	int DecimalCheck;	//used as a secondary flag to check for more that one decimal points '.'
	float temp;
	
	//	!!ALL FLAGS MUST BE 0!!
	
	
	flag=0;
	DecimalCheck=0;
	l=strlen(string);
	
	//Checking has three "phases": for position 0, for positions 1-3, for fositions 4+
	
	//POS 0
	//check if string is negative or starts with alphabet
	if(!(string[0]=='+' || isdigit(string[0])!=0))
		flag=1;
	
	//POS 1-3
	i=1;
	if(l>1)
	{
		do
		{
			if(!(isdigit(string[i])!=0 || string[i]=='.' || string[i]=='\0'))
				flag=1;
			
			if(string[i]=='.' && DecimalCheck==1)
				flag=1;
			
			if(string[i]=='.')
				DecimalCheck=1;
			
			i++;
		}while(i<=3 && i<l);
	}
		
	//POS 4+
	if(l>4)
	{
		i=4; //positions 0-3 have already been checked
		
		while(i<l && flag==0)
		{
			//check if the rest is alphabet
			if(!(isdigit(string[i])!=0))
				flag=1;
			
			i++;
		}
	}
	
	sscanf(string,"%f", &temp);
	
	if(temp!=(int)temp)
		flag=1;
	else
		selection=(int)temp;
	
	if(flag==1)
		selection=-1; //default error value
		
	return selection;
}

void get_num_plate(char data[MAX_CARS][16], int entries, char numplate[5], char *sp)
{
	int flag1, flag2, temp_int, i;
	char compare[5];
	
	do//AΡΙΘΜΟΣ ΠΙΝΑΚΙΔΑΣ
	{
		flag1=0;
		printf("ΑΡΙΘΜΟΣ: (%s): ", numplate);
		scanf("%s",numplate);
		
		strcpy(compare, numplate);
		sscanf(numplate, "%d", &temp_int);//αποθηκευση του number plate ως integer
		
	//	printf("%s %s %d\n", numplate, )
		if(temp_int<1000 || temp_int>9999)//ελεγχος οτι ειναι τετραψηφιος
				flag1=1;
		
		//ελεγχος για διπλη εισαγωγη
		i=0;
		flag2=0;
		while(i<=entries && flag2==0)
		{
			if((strcmp(data[i], numplate)==0) && (strcmp(compare,numplate)!=0))
				flag2=1;
				
			i++;
		}
	}while(flag1==1 || flag2==1);//τελος ελεγχου

	strcpy(sp, numplate);
}

void get_colour(char colour[8], char *sp)
{
	int	i, flag, col_length;
	char search[8];
	
	FILE *fp;
	
	do//ΧΡΩΜΑ
	{			
		printf("ΧΡΩΜΑ: (%s): ", colour);
		scanf("%s", colour);
		fp = fopen("BasicColors.txt", "r");
		i=0;
		flag=0;
		col_length=strlen(colour);//αποθηκευση μηκους του string για πιο συγκεκριμενη συγκριση
		while(!feof(fp) && flag==0)//οσο "οχι end of file"
		{
			fgets(search,8,fp);//παιρνουμε την καθε γραμμη η οποια αντιστοιχει και σε ενα χρωμα και την βαζουμε στον πινακα search
			if(strncmp(search,colour, col_length)==0)//ελεγχος αν το χρωμα υπαρχει
			{
				flag=1;
			}
		i++;
		}
		fclose(fp);
	}while(flag==0);
	
	strcpy(sp, colour);
}

void get_man(char manufacturer[16], char *sp)
{
	int i, flag, temp_int;
	char search[20];
	
	FILE *fp;
	
	do//ΚΑΤΑΣΚΕΥΑΣΤΗΣ
	{
		printf("ΚΑΤΑΣΚΕΥΑΣΤΗΣ: (%s): ", manufacturer);
		scanf("%s", manufacturer);
		fp = fopen("Companies.txt", "r");
		i=0;
		flag=0;
		temp_int = strlen(manufacturer);//αποθηκευση μηκους του string για πιο συγκεκριμενη συγκριση
		
		while(!feof(fp) && flag==0)//οσο "οχι end of file"
		{
			fgets(search,20,fp);//παιρνουμε την καθε γραμμη η οποια αντιστοιχει και σε εναν κατασκευαστη και την βαζουμε στον πινακα search
			if(strncmp(search,manufacturer, temp_int)==0)//ελεγχος αν ο κατασκευαστης υπαρχει
				flag=1;
		i++;
		}
		fclose(fp);
		
	}while(flag==0);
	
	strcpy(sp, manufacturer);
}

void get_year(char year[5], char *sp)
{
	int i, flag, temp_int;
	char search[20];
	
	do//ΗΜΕΡΟΜΗΝΙΑ ΚΑΤΑΣΚΕΥΗΣ
	{
		printf("ΗΜΕΡΟΜΗΝΙΑ ΚΑΤΑΣΚΕΥΗΣ: (%s): ", year);
		scanf("%s", year);
		sscanf(year, "%d", &temp_int);//αποθηκευση του date ως integer
	}while(temp_int<1960 || temp_int>YEAR);
	
	strcpy(sp, year);
}

void num_sort(char data[MAX_CARS][16], int lines)//sort for numbers
{
	int i, j, tempx, tempy;
	char temp[5];
	
	for(i=0 ; i<lines-1 ; i++)
	{
		for(j=i+1 ; j<lines ; j++)
		{
			sscanf(data[i], "%d", &tempx);
			sscanf(data[j], "%d", &tempy);
			if(tempx>tempy)
			{
				//Αλλαγη
				strcpy(temp, data[j]);
				strcpy(data[j], data[i]);
				strcpy(data[i], temp);
			}
		}
	}
}

int main(){
	
	//Ελληνικοί Χαρακτηρες
	system("chcp 1253");
	system("cls");
	
	//Δηλωση μεταβλητών
	int selection, selection_search, flag, i, j, l, entries, temp_int, pos, tempx, tempy, table_pos[MAX_CARS];
	char buffer[BUFFER], search[20], data[MAX_CARS][16], compare, check;
	float temp;
	
	//μεταβλητες για "return" απο τα functions και αναζητηση
	char plate[5], colour[8], manufacturer[16], year[5];
	
	//Το total entries χρησιμοποιειται για  να υπολογισουμε το μεγεθος καποιων πινακων
	//flag is used to check if the menu loop should continue
	
	//Αρχικες τιμες μεταβλητων
	
	FILE *fp;
	struct Data car[MAX_CARS] = {0,0,0,0,0};
	
	
	//καταμετρηση γραμμών
	fp = fopen("Cars.txt", "r");
	entries=0;
	do
	{
		fgets(buffer,BUFFER,fp);//απλα για να τερματισει ο κερσορας
		if(!feof(fp))
			entries++;
	}while(!feof(fp));
	fclose(fp);

	//μεταφορα εισαγωγων απο το txt στο struct
	fp = fopen("Cars.txt", "r");
	for(i=0 ; i<entries ; i++)
	{
		//number plate pos
		pos=i*54;
		fseek(fp,pos,SEEK_SET);
		fgets(car[i].plate,5,fp);
		//colour
		pos=16+i*54;
		fseek(fp,pos,SEEK_SET);
		fgets(car[i].colour,8,fp);
		//manufacturer
		pos=32+i*54;
		fseek(fp,pos,SEEK_SET);
		fgets(car[i].manufacturer,16,fp);
		//year
		pos=48+i*54;
		fseek(fp,pos,SEEK_SET);
		fgets(car[i].year,5,fp);
		//make empty 1 to indicate "not empty"
		car[i].empty=1;
	}
	fclose(fp);
	
	
	do{//START OF MENU LOOP
		
		system("cls");
		
		//Εκτύπωση βασικού μενού, καταγραφή επιλογής
		printf("ΒΑΣΙΚΟ ΜΕΝΟΥ\n1. ΕΜΦΑΝΙΣΗ ΟΛΩΝ\n2. ΕΙΣΑΓΩΓΗ ΝΕΑΣ ΕΓΓΡΑΦΗΣ\n3. ΔΙΑΓΡΑΦΗ ΕΓΓΡΑΦΗΣ\n"
		"4. ΑΝΑΝΕΩΣΗ ΕΓΓΡΑΦΗΣ\n5. ΑΝΑΖΗΤΗΣΗ\n6. ΕΝΗΜΕΡΩΣΗ ΒΑΣΗΣ\n0. ΕΞΟΔΟΣ\n");
			
		printf("\nΕΠΙΛΟΓΗ: ");
		gets(buffer);
		selection=InputCheck(buffer);

		
		switch(selection){//SELECTION MENU
		case 1 :
		{//ΕΜΦΑΝΙΣΗ ΟΛΩΝ	FINISHED
			i=0;
			for(i=0;i<entries;i++)
				if(car[i].empty==1)
					printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n", car[i].plate, car[i].colour, car[i].manufacturer, car[i].year);
			
			printf("\n");
			system("PAUSE");
			
		break;
		}
		case 2 :
		{//ΝΕΑ ΚΑΤΑΧΩΡΙΣΗΣ	FINISHED
			
			system("cls");
			
			printf("----------\nΝΕΑ ΕΓΓΡΑΦΗ\n----------\n");
			
			//Ευρεση της πρωτης αδειας θεσης του struct
			flag=0;
			i=0;
			while(i<entries && flag==0)
			{
				if(car[i].empty==0)
				{
					pos=i;
					flag=1;
				}
				else
					pos=i;
				i++;
			}
			flag=0;
			do//AΡΙΘΜΟΣ ΠΙΝΑΚΙΔΑΣ
			{
				if(flag==1)
					printf("ΛΑΘΟΣ. ΔΟΚΙΜΑΣΤΕ ΞΑΝΑ.\n");
				
				flag=0;
				printf("ΑΡΙΘΜΟΣ: ");
				gets(buffer);
				
				temp_int=InputCheck(buffer);//αποθηκευση του number plate ως integer και ελεγχος για χαρακτηρες
				
				if(temp_int<1000 || temp_int>9999 || temp_int==-1)//ελεγχος οτι ειναι τετραψηφιος
					flag=1;
				
				strncpy(car[pos].plate, buffer, 5);
				
				//ελεγχος για διπλη εισαγωγη
				i=0;
				while(i<=entries && flag==0)
				{
					if((strcmp(car[i].plate, car[pos].plate)==0) && (i!=pos))
						flag=1;
					i++;
				}
				fclose(fp);
				
			}while(flag==1);//τελος ελεγχου
			flag=0;		
			do//ΧΡΩΜΑ
			{		
				if(flag==1)
					printf("ΛΑΘΟΣ. ΔΟΚΙΜΑΣΤΕ ΞΑΝΑ.\n");
						
				printf("ΧΡΩΜΑ: ");
				gets(buffer);
				
				strcpy(colour, buffer);

				
				fp = fopen("BasicColors.txt", "r");
				flag=1;
				while(!feof(fp) && flag==1)//οσο "οχι end of file"
				{
					fgets(search,8,fp);//παιρνουμε την καθε γραμμη η οποια αντιστοιχει και σε ενα χρωμα και την βαζουμε στον πινακα search
					temp_int=strlen(search)-1;
					if(strncmp(search,colour,temp_int)==0 && strncmp(search,colour,strlen(colour))==0)//ελεγχος αν το χρωμα υπαρχει στο txt με τα χρωματα
						flag=0;
				}
				fclose(fp);
				
				if(strlen(buffer)>8)
					flag=1;
								
				if(flag==0)
					strncpy(car[pos].colour,buffer,8);
					
			}while(flag==1);
			flag=0;
			do//ΚΑΤΑΣΚΕΥΑΣΤΗΣ
			{
				if(flag==1)
					printf("ΛΑΘΟΣ. ΔΟΚΙΜΑΣΤΕ ΞΑΝΑ.\n");
					
				printf("ΚΑΤΑΣΚΕΥΑΣΤΗΣ: ");
				gets(car[pos].manufacturer);
				fp = fopen("Companies.txt", "r");
				i=0;
				flag=1;
				temp_int=strlen(car[pos].manufacturer);//αποθηκευση μηκους του string για πιο συγκεκριμενη συγκριση
				while(!feof(fp) && flag==1)//οσο "οχι end of file"
				{
					fgets(search,20,fp);//παιρνουμε την καθε γραμμη η οποια αντιστοιχει και σε εναν κατασκευαστη και την βαζουμε στον πινακα search
					if(strncmp(search,car[pos].manufacturer, temp_int)==0)//ελεγχος αν ο κατασκευαστης υπαρχει
						flag=0;
				i++;
				}
				fclose(fp);
			}while(flag==1);
			flag=0;			
			do//ΗΜΕΡΟΜΗΝΙΑ ΚΑΤΑΣΚΕΥΗΣ
			{
				if(flag==1)
					printf("ΛΑΘΟΣ. ΔΟΚΙΜΑΣΤΕ ΞΑΝΑ.\n");
					
				flag=0;
				printf("ΗΜΕΡΟΜΗΝΙΑ ΚΑΤΑΣΚΕΥΗΣ: ");
				gets(buffer);
				
				temp_int=InputCheck(buffer);//αποθηκευση του number plate ως integer και ελεγχος για χαρακτηρες
				
				if(strlen(buffer)>4 || temp_int==-1)
					flag=1;
					
				if(temp_int<1960 || temp_int>YEAR)
					flag=1;
				
				strncpy(car[pos].year, buffer, 5);
				
			}while(flag==1);
			
			car[pos].empty=1;
			
			printf("ΕΠΙΤΥΧΗΣ ΕΓΓΡΑΦΗ.\n");
			
			//αυξηση αριθμου καταχωρησεων μονο αν η θεση ειναι ιση με το entries
			//ετσι το entries δειχνει το τελευταιο στοιχειο της δομης
			if(entries==pos)
				entries++;
			
			sleep(2);
			break;
		}
		case 3 :
		{//ΔΙΑΓΡΑΦΗ ΚΑΤΑΧΩΡΗΣΗΣ		FINISHED
			
			system("cls");
			
			printf("----------\nΔΙΑΓΡΑΦΗ ΕΓΓΡΑΦΗΣ\n----------\n");

			//εισαγωγη δεδομενων απο το struct σε πινακα για να γινει ταξινομηση
			j=0;
			for(i=0;i<entries;i++)
			{
				if(car[i].empty==1)
				{
					strcpy(data[j],car[i].plate);
					j++;
				}
			}
			
			num_sort(data, j);
						
			//ΕΜΦΑΝΙΣΗ ΠΙΝΑΚΙΔΩΝ ΜΕ ΑΥΞΟΥΣΑ ΣΕΙΡΑ
			
			for(i=0;i<j;i++)
			{
				if(i!=0 && i%5==0)
					printf("\n");
				printf("%s, ", data[i]);
			}
			printf("\n");
			
			//ΕΠΙΛΟΓΗ ΑΥΤΟΚΙΝΗΤΟΥ ΠΡΟΣ ΔΙΑΓΡΑΦΗ
			printf("\nΕΠΙΛΟΓΗ ΠΙΝΑΚΙΔΑΣ: ");
			scanf("%s", search);
			getchar();
			
			//ελεγχος εγγυροτητας, διαγραφη και εμφανιση αντιστοιχου μηνυματος
			flag=0;
			i=0;
			do
			{
				if(strcmp(car[i].plate, search)==0)
				{
					car[i].empty=0;
					printf("\nΕΠΙΤΥΧΗΣ ΔΙΑΓΡΑΦΗ ΚΑΤΑΧΩΡΗΣΗΣ.\n\n");
					flag=1;
				}
				
				i++;	
			}while(i<entries && flag==0);
			
			if(flag==0)
				printf("\nΗ ΕΠΙΛΟΓΗ ΔΕΝ ΒΡΕΘΗΚΕ.\n\n");
			
			sleep(2);
			break;
		}
		case 4 :
		{//ΑΝΑΝΕΩΣΗ ΕΓΓΡΑΦΗΣ	FINISHED
			
			system("cls");
			
			printf("----------\nΑΝΑΝΕΩΣΗ ΕΓΓΡΑΦΗΣ\n----------\n");
			
			//εισαγωγη δεδομενων απο το struct σε πινακα για να γινει ταξινομηση
			j=0;
			for(i=0;i<entries;i++)
			{
				if(car[i].empty==1)
				{
					strcpy(data[j],car[i].plate);
					j++;
				}
			}
			
			num_sort(data, j);
			
			//ΕΜΦΑΝΙΣΗ ΠΙΝΑΚΙΔΩΝ ΜΕ ΑΥΞΟΥΣΑ ΣΕΙΡΑ
			
			for(i=0;i<j;i++)
			{
				if(i!=0 && i%5==0)
					printf("\n");
				printf("%s, ", data[i]);
			}
			printf("\n");
			
			//ΕΠΙΛΟΓΗ ΕΓΓΡΑΦΗΣ ΠΡΟΣ ΕΝΗΜΕΡΩΣΗ
			
			do
			{//εισαγωγη πινακιδας απο τον χρηστη(με ελεγχο εγκυροτητας) και στην συνεχεια εισαγωγη νεων στοιχειων
				printf("\nΕΠΙΛΟΓΗ ΠΙΝΑΚΙΔΑΣ: ");
				scanf("%s", search);
				for(i=0;i<entries;i++)
				{
					if(strcmp(car[i].plate, search)==0)//σκαναρουμε για να βρουμε την θεση της συγκεκριμενης πινακιδας στον car.plate αν υπαρχει
					{
						pos=i;
						flag=1;
					}
				}	
				if(flag==0)
					printf("\nΗ ΕΠΙΛΟΓΗ ΔΕΝ ΒΡΕΘΗΚΕ.\n\n");
					
			}while(flag==0);
			
			//char data[MAX_CARS][16], int entries, char numplate[5], char *sp
			strcpy(plate,car[pos].plate);				//Θα χρησιμοποιησουμε το plate για τα παλια στοιχεια του αυτοκινητου
			get_num_plate(data, entries, plate, plate);	//δινουμε το data, το entries και το char array: plate το οποιο χρησιμοποιειται
			strcpy(car[pos].plate,plate);				//για την εγγραφη κατευθειαν στην θεση μηνμης μεσα απο το function get_num_plate
			
			strcpy(colour,car[pos].colour);
			get_colour(colour, colour);
			strcpy(car[pos].colour,colour);
			
			strcpy(manufacturer,car[pos].manufacturer);
			get_man(manufacturer, manufacturer);
			strcpy(car[pos].manufacturer,manufacturer);
			
			strcpy(year,car[pos].year);
			get_year(year, year);
			strcpy(car[pos].year,year);
			
			printf("\nΕΠΙΤΥΧΗΣ ΑΝΑΝΕΩΣΗ\n\n");
			
			sleep(2);
			getchar();
			break;
		}
		case 5 :
		{//ΑΝΑΖΗΤΗ		FINISHED
			
			do
			{
				system("cls");
				
				printf("----------\nΑΝΑΖΗΤΗΣΗ\n----------\n");
				
				//ΜΕΝΟΥ ΑΝΑΖΗΤΗΣΗΣ
				printf("ΜΕΝΟΥ ΑΝΑΖΗΤΗΣΗΣ\n1. ΜΕ ΒΑΣΗ ΤΟΝ ΑΡΙΘΜΟ\n2. ΜΕ ΒΑΣΗ ΤΟ ΧΡΩΜΑ\n3. ΜΕ ΒΑΣΗ ΤΟΝ ΚΑΤΑΣΚΕΥΑΣΤΗ\n"
				"4. ΜΕ ΒΑΣΗ ΤΗΝ ΗΜΕΡΟΜΗΝΙΑ ΚΑΤΑΣΚΕΥΗΣ\n0. ΕΠΙΣΤΡΟΦΗ ΣΤΟ ΒΑΣΙΚΟ ΜΕΝΟΥ\n");
				
				do
				{
					gets(buffer);
					selection_search=InputCheck(buffer);
			
				}while(selection==-1);
				
				switch(selection_search)
				{
				case 1 :
				{//Αναζητηση με βαση τον αριθμο
					
					system("cls");
					
					/*
					θα αρχικοποιησουμε εναν πινακα με τις θεσεις στοιχειων του car.plate ετσι ωστε να μπορουμε να αναφερθουμε
					στο car.plate και να το ταξινομησουμε χωρις να επεμβουμε στα πραγματικα στοιχεια του πινακα. Αυτο θα γινει
					με το να συγκρινουμε car[table_pos[i]].plate και car[table_pos[j]].plate και αναλογα ταξινομουμε τα στοιχεια του πινακα data
					δηλαδη τις θεσεις των στοιχειων του car.plate και επειτα στην εκτυπωση αναφερομαστε στον ταξινομημενο πινακα
					ως car[table_pos[i]].plate etc
					*/
					
					//Αρχικοποιηση ΘΕΣΗΣ δεδομενων
					for(i=0;i<entries;i++)
							table_pos[i]=i;
					
					//ταξινομιση πινακα
					for(i=0 ; i<entries-1 ; i++)
					{
						for(j=i+1 ; j<entries ; j++)
						{
							//αποθηκευση των δυο πινακιδων σε ακεραιο για συγκριση
							sscanf(car[table_pos[i]].plate, "%d", &tempx);
							sscanf(car[table_pos[j]].plate, "%d", &tempy);
							if(tempx>tempy)
							{
								//η ταξινομιση γινεται με σχετικη αναφορα στα στοιχεια του struct
								//δηλαδη ταξινομουμε την θεση του στοιχειου και οχι το ιδιο το στοιχειο
								temp_int=table_pos[i];
								table_pos[i]=table_pos[j];
								table_pos[j]=temp_int;
							}
						}
					}
					
					printf("--------------------\nΠΙΝΑΚΙΔΑ\n--------------------\n");
				
					do//κριτηρια αναζητησης με ελεγχο εισοδου
					{
						printf("ΚΡΙΤΗΡΙΑ ΑΝΑΖΗΤΗΣΗΣ  (</>ΧΧΧΧ): ");
						scanf("%c", &compare);
						scanf("%s", plate);
						
						sscanf(plate,"%d", &temp_int);
						
						flag=0;
						if(temp_int>9999 || temp_int<1000 || (compare!='<' && compare!='>'))
							flag=1;
						getchar();
						
					}while(flag==1);
					
					printf("\n--------------------\nΑΥΤΟΚΙΝΗΤΑ ΠΟΥ ΠΛΗΡΟΥΝ ΤΑ ΚΡΙΤΗΡΙΑ\n--------------------\n");
					
					if(compare=='<')
					{
						for(i=0;i<entries;i++)
						{
							temp_int=table_pos[i];
							strncpy(search,car[temp_int].plate,5);
							temp_int=strncmp(search,plate,5);
							
							if(temp_int<0 && car[table_pos[i]].empty==1)
								printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n", car[table_pos[i]].plate, car[table_pos[i]].colour, car[table_pos[i]].manufacturer, car[table_pos[i]].year);
								
						}
						
						printf("\n");
						system("pause");
					}
					else if(compare=='>')
					{
						for(i=0;i<entries;i++)
						{
							temp_int=table_pos[i];//θεση στοιχειου του struct member προς πιθανη εκτυπωση
							strncpy(search,car[temp_int].plate,5);	//αχρειαστη αντιγραφη του struct member προς πιθανη εκτυπωση σε μια προσωρινη μεταβλητη
																	//αληθεια αχρειαστο αλλα εχω καει και πλεον το παω βημα βημα... δεν χρειαζεται να το κανω unreadable
							temp_int=strncmp(search,plate,5);		//συγκρινουμε την πινακιδα που εβαλε με την πινακιδα που βρισκεται στην παραπανω θεση
																	//και αποθηκευουμε την τιμη που επιστρεφει η strcmp σε μια προσωρινη μεταβλητη και επειτα
																	//εκτυπωνουμε τα στοιχεια αν πληρουν τα κριτηρια αναζητησης
							
							if(temp_int>0 && car[table_pos[i]].empty==1)
								printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n"
								"", car[table_pos[i]].plate, car[table_pos[i]].colour, car[table_pos[i]].manufacturer, car[table_pos[i]].year);
								
								
						}
						
						printf("\n");
						system("pause");
					}
					break;
				}
				case 2 :
				{//Αναζητηση με βαση το χρωμα
					
					pos=1;//temp_int is used to indicate the total number of individual colours
					strncpy(data[0], car[0].colour,8);
					
					for(i=0;i<entries;i++)
					{
						flag=0;//this flag checks wether car[i].colour is already in the data array and it resets every i++
						j=0;
						
						do
						{
							if(strncmp(car[i].colour,data[j],8)==0)
								flag=1;
								
							j++;
						}while(j<pos && flag==0);
						
						if(flag==0)
							{
								strcpy(data[pos], car[i].colour);
								pos++;
							}
					}
					
					do
					{
						sleep(1);
						system("cls");
						
						printf("\n--------------------\nΔΙΑΘΕΣΗΜΑ ΧΡΩΜΑΤΑ\n--------------------\n");
							for(i=0;i<pos;i++)
								printf("- %s\n", data[i]);
					
						flag=1;	//αρχιζει με τιμη 1(δλδ λαθος) και αλλαζει εαν η εισοδος ειναι σωστη
						printf("\nΕΠΙΛΕΞΤΕ ΧΡΩΜΑ: ");
						gets(colour);
						temp_int=strlen(colour);
						for(i=0;i<pos;i++)
						{
							if(strncmp(data[i], colour,temp_int)==0)
								flag=0;
						}
						
						if(flag==1)
							printf("\nΔΕΝ ΒΡΕΘΗΚΕ ΑΥΤΟ ΤΟ ΧΡΩΜΑ.\n\n");
						
						
					}while(flag==1);
					
					
					printf("\n--------------------\nΑΥΤΟΚΙΝΗΤΑ ΠΟΥ ΠΛΗΡΟΥΝ ΤΑ ΚΡΙΤΗΡΙΑ\n--------------------\n");
					for(i=0;i<entries;i++)
					{
						if((strncmp(car[i].colour, colour, temp_int)==0) && car[i].empty==1)
							printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n", car[i].plate, car[i].colour, car[i].manufacturer, car[i].year);
					}
					
					printf("\n");
					system("pause");
					
					break;
				}
				case 3 :
				{//Αναζητηση με βαση τον κατασκευαστη
					
					pos=1;//temp_int is used to indicate the total number of individual manufacturers
					strncpy(data[0], car[0].manufacturer,16);
					
					for(i=0;i<entries;i++)
					{
						flag=0;//this flag checks wether car[i].manufacturer is already in the data array and it resets every i++
						j=0;
						
						do
						{
							if(strncmp(car[i].manufacturer,data[j],16)==0)
								flag=1;
								
							j++;
						}while(j<pos && flag==0);
						
						if(flag==0)
							{
								strcpy(data[pos], car[i].manufacturer);
								pos++;
							}
					}
										
					do
					{
						sleep(1);
						system("cls");
						
						printf("\n--------------------\nΔΙΑΘΕΣΗΜΟΙ ΚΑΤΑΣΚΕΥΑΣΤΕΣ\n--------------------\n");
							for(i=0;i<pos;i++)
								printf("- %s\n", data[i]);
						
						flag=1;	//αρχιζει με τιμη 1(δλδ λαθος) και αλλαζει εαν η εισοδος ειναι σωστη

						printf("\nΕΠΙΛΕΞΤΕ ΚΑΤΑΣΚΕΥΑΣΤΗ: ");
						gets(manufacturer);
						temp_int=strlen(manufacturer);
						
						for(i=0;i<pos;i++)
						{
							if(strncmp(data[i], manufacturer,temp_int)==0)
								flag=0;
						}
						
						if(flag==1)
							printf("\nΔΕΝ ΒΡΕΘΗΚΕ Ο ΚΑΤΑΣΚΕΥΑΣΤΗΣ.\n\n");
						
						
					}while(flag==1);
					
					
					printf("\n--------------------\nΑΥΤΟΚΙΝΗΤΑ ΠΟΥ ΠΛΗΡΟΥΝ ΤΑ ΚΡΙΤΗΡΙΑ\n--------------------\n");
					for(i=0;i<entries;i++)
					{
						if((strncmp(car[i].manufacturer, manufacturer, temp_int)==0) && car[i].empty==1)
							printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n", car[i].plate, car[i].colour, car[i].manufacturer, car[i].year);
					}
					
					printf("\n");
					system("pause");
					
					break;
				}
				case 4 :
				{//Αναζητηση με βαση την ημερομηνια
					
					system("cls");
					
					//Δουλευει παρομοια με το case 1 : Αναζητηση με βαση τον αριθμο
					
					//Αρχικοποιηση ΘΕΣΗΣ δεδομενων
					for(i=0;i<entries;i++)
							table_pos[i]=i;
					
					//ταξινομιση πινακα
					for(i=0 ; i<entries-1 ; i++)
					{
						for(j=i+1 ; j<entries ; j++)
						{
							sscanf(car[table_pos[i]].year, "%d", &tempx);
							sscanf(car[table_pos[j]].year, "%d", &tempy);
							if(tempx>tempy)
							{
								temp_int=table_pos[i];
								table_pos[i]=table_pos[j];
								table_pos[j]=temp_int;
							}
						}
					}
					
					printf("--------------------\nΗΜΕΡΟΜΗΝΙΑ ΚΑΤΑΣΚΕΥΗΣ\n--------------------\n");
					do
					{
						printf("ΚΡΙΤΗΡΙΑ ΑΝΑΖΗΤΗΣΗΣ  (</>ΧΧΧΧ): ");
						scanf("%c", &compare);
						scanf("%s", year);
						
						sscanf(year,"%d", &temp_int);
						
						flag=0;
						if(temp_int>9999 || temp_int<1000 || temp_int>YEAR || (compare!='<' && compare!='>'))
							flag=1;
						getchar();
						
					}while(flag==1);
					
					printf("\n--------------------\nΑΥΤΟΚΙΝΗΤΑ ΠΟΥ ΠΛΗΡΟΥΝ ΤΑ ΚΡΙΤΗΡΙΑ\n--------------------\n");
					if(compare == '>')
					{
						for(i=0;i<entries;i++)
						{
							temp_int=table_pos[i];
							strncpy(search,car[temp_int].year,5);
							temp_int=strncmp(search,year,5);
							
							if(temp_int>0 && car[table_pos[i]].empty==1)
								printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n", car[table_pos[i]].plate, car[table_pos[i]].colour, car[table_pos[i]].manufacturer, car[table_pos[i]].year);
								
						}
						
						printf("\n");
						system("pause");
					}
					else if(compare == '<')
					{
						for(i=0;i<entries;i++)
						{
							temp_int=table_pos[i];
							strncpy(search,car[temp_int].year,5);
							temp_int=strncmp(search,year,5);
							
							if(temp_int<0 && car[table_pos[i]].empty==1)
								printf("Number Plate: %-4s\tColour: %-8s\tManufacturer: %-15s\tYear: %-4s\n", car[table_pos[i]].plate, car[table_pos[i]].colour, car[table_pos[i]].manufacturer, car[table_pos[i]].year);
								
						}
						
						printf("\n");
						system("pause");
					}
					break;
				}
				case 0 :
				{
					printf("\nΕΞΟΔΟΣ ΑΠΟ ΜΕΝΟΥ ΑΝΑΖΗΤΗΣΗΣ\n");
					sleep(1);
					break;
				}
				default : 
				{
					printf("\nΛΑΘΟΣ ΕΠΙΛΟΓΗ!\n\a");
					sleep(1);
					system("cls");
				}
				}
				
			}while(selection_search!=0);
			
			sleep(2);
			break;
		}
		case 6 :
		{//ΕΝΗΜΕΡΩΣΗ ΒΑΣΗΣ	FINISHED
			//!TIP! %NUMs για στοιχιση, - για στοιχιση αριστερα
			
			system("cls");
			
			fp = fopen("Cars.txt", "w");
			j=1;
			printf("\n--------------------\nΑΠΟΘΗΚΕΥΣΗ\n--------------------\n\n");
			
			j=0;
			for(i=0 ; i<entries ; i++)
			{
				if(car[i].empty==1)
				{
					fprintf(fp, "%-15s\t%-15s\t%-15s\t%s\n", car[i].plate, car[i].colour, car[i].manufacturer, car[i].year);
					
					if(i<3)
					{
						printf(".");
						sleep(1);
					}
					
					j++;
				}
			}
			fclose(fp);
			printf("\n\n--------------------\nΕΠΙΤΥΧΗΣ ΕΝΗΜΕΡΩΣΗ.\n--------------------\n\n");
			system("pause");
			
			break;
		}
		case 0 : 
		{//ΕΞΟΔΟΣ			FINISHED
			printf("\nΤΕΡΜΑΤΙΣΜΟΣ ΠΡΟΓΡΑΜΜΑΤΟΣ...\n");
			sleep(1.5);
			break;		
		}
		default :
		{
			if(selection==-1)
			{
				printf("\nΛΑΘΟΣ ΕΠΙΛΟΓΗ!\n\a");
				sleep(1);
				system("cls");
			}
			
		}
	}//END OF MAIN MENU
	
	}while(selection!=0);//END OF MENU LOOP
	
	return 0;
}
