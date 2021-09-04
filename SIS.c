#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// strucs...
typedef struct lecture_submission{
	int sub_ID;
	int Std_No;
	char lecture_code[20];
	int status;
	char date[50]; // TARIH date; ??
}LECTURE_SUBMIT;

typedef struct prof_members{
	int prof_ID;
	char name[20];
	char surname[20];
	char member_title[10];
}PROF;
typedef struct students{
	int Std_No;
	char name[20];
	char surname[20];
	int lecture_sum;
	int credit_sum;
}STUDENT;
typedef struct lectures{
	char lecture_code[20];
	char name[40];
	int credit;
	int capacity;
	int prof_ID;
}LECTURE;




void add_prof(){
	setlocale(LC_ALL, "Turkish"); // karakterler türkçeye dönüþtürülemiyor, ing gir !???
	FILE *fp1;
	fp1 = fopen("prof_members.txt", "a+");
		if(fp1 == NULL){
			printf("dosya acilamadý...");
		}
		else {
				PROF *profp;
				profp = (PROF*)malloc(sizeof(PROF));
				printf("yeni öðretim üyesinin ID'sini' girininiz: \n "); scanf("%d", &profp->prof_ID);
				printf("yeni öðretim üyesinin adýný girininiz: \n "); scanf("%s", profp->name);
				printf("yeni öðretim üyesinin soyadýný girininiz: \n "); scanf("%s", profp->surname);
				printf("yeni öðretim üyesinin unvanýný girininiz: \n "); scanf("%s", profp->member_title);
				fprintf(fp1,"%d %s  %s %s\n", profp->prof_ID, profp->name, profp->surname, profp->member_title);
				free(profp);
				fclose(fp1);
			}
		
}
void registered_students( char lectureCode[] ){ // sýkýntýlý olabilir
	int strCpy;
	FILE *fp1 = fopen("student_lecture_record.txt", "r+");
	
	LECTURE_SUBMIT submit;
	
	submit.sub_ID = 5;
	printf("id = %d \n\n",submit.sub_ID );
	
	if(fp1 == NULL){
		printf("dosya acilamadi");
		
	}
	else {
		printf("\t %s KODLU DERSE KAYDOLAN OGRENCILER\n\n", lectureCode);
		while(!feof(fp1)){
			//printf(" while'a giris yapti\n");
			fscanf(fp1, "%d %d %s %d %s", &submit.sub_ID, &submit.Std_No, submit.lecture_code, &submit.status, submit.date);
			
			fprintf(fp1, "%d %d %s %d %s\n", submit.sub_ID, submit.Std_No, submit.lecture_code, submit.status, submit.date);
			
			printf("karsilastirilacak stringler: '%s' ve '%s' \n",lectureCode, submit.lecture_code );
			
			strCpy = strcmp(lectureCode,submit.lecture_code);
			
			printf("strcmp degeri = %d", strCpy);
			
			if( strcmp(lectureCode,submit.lecture_code) == 0){
				printf("submit bukundu\n");
				FILE *fp2;
				fp2 = fopen("students.txt", "r+");
				
				STUDENT student;
				
				if(fp2 == NULL){
					printf("2. dosya acilamadi");
				}
				else {
					printf("2. dosya acildi.\n");
					while(!feof(fp2)){
						fscanf(fp2, "%d %s %s %d %d", &student.Std_No, student.name, student.surname, &student.lecture_sum, &student.credit_sum);
						
						if(submit.Std_No == student.Std_No){
							printf("\t%d %s %s %d %d\n", student.Std_No, student.name, student.surname, student.lecture_sum, student.credit_sum);
						}
					}
				}
				fclose(fp2);
				//printf("while sonunu gördü.\nwhile sonunu gördü.\n");
			}
			else{
				printf("lecture kodu eþleþmedi\n\n");
			}
			
		}
	}
	fclose(fp1);
}
void add_new_lecture(){
	setlocale(LC_ALL, "Turkish"); // karakterler türkçeye dönüþtürülemiyor, ing gir !???
	FILE *fp1;
	fp1 = fopen("lectures.txt", "a+");
		if(fp1 == NULL){
			printf("dosya acilamadý...");
		}
		else {
				LECTURE *lecturep;
				lecturep = (LECTURE*)malloc(sizeof(LECTURE));
				printf("açýlacak dersin kodunu giriniz: \n"); scanf("%s", lecturep->lecture_code);
				printf("açýlacak dersin adýný giriniz: \n"); scanf("%s", lecturep->name);
				printf("açýlacak dersin kredisini giriniz: \n"); scanf("%d", &lecturep->credit);
				printf("açýlacak dersin kontenjanýný giriniz: \n"); scanf("%d", &lecturep->capacity);
				printf("açýlacak dersin prof_ID'sini giriniz: \n"); scanf("%d", &lecturep->prof_ID);
				
				fprintf(fp1, "%s %s %d %d %d\n",lecturep->lecture_code, lecturep->name, lecturep->credit, lecturep->capacity, lecturep->prof_ID );
				free(lecturep);
				fclose(fp1);
			}
	
}
void add_student(){
	setlocale(LC_ALL, "Turkish"); // karakterler türkçeye dönüþtürülemiyor, ing gir !???
	FILE *fp1;
	fp1 = fopen("students.txt", "a+");
		if(fp1 == NULL){
			printf("dosya acilamadý...");
		}
		else {
				STUDENT *studentp;
				studentp = (STUDENT*)malloc(sizeof(STUDENT));
				printf("eklenecek öðrencinin öðrenci numarasýný giriniz: \n"); scanf("%d", &studentp->Std_No);
				printf("eklenecek öðrencinin adýný giriniz: \n"); scanf("%s", studentp->name);
				printf("eklenecek öðrencinin soyadýný giriniz: \n"); scanf("%s", studentp->surname);
				printf("eklenecek öðrencinin kaydolduðu toplam ders sayýsýný giriniz: \n"); scanf("%d", &studentp->lecture_sum);
				printf("eklenecek öðrencinin kaydolduðu toplam kredisini giriniz: \n"); scanf("%d", &studentp->credit_sum);
			
				fprintf(fp1, "%d %s %s %d %d\n",studentp->Std_No, studentp->name, studentp->surname, studentp->lecture_sum, studentp->credit_sum);
				free(studentp);
				fclose(fp1);
			}
}
void student_lecture_record(int N){

	int status = 1;
	int id;
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	id = spot_lecture_lastID();
	FILE *fp1;
	fp1 = fopen("student_lecture_record.txt", "a+");
	if(fp1 == NULL){
			printf("dosya acilamadý...");
	}
	else {
		LECTURE_SUBMIT *recordp;
		recordp = (LECTURE_SUBMIT*)malloc(sizeof(LECTURE_SUBMIT));
		printf("Dersin kodu: \n "); scanf("%s", recordp->lecture_code);
		char time1[30];
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);

		sprintf(time1, "%d-%02d-%02d/%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		
		
		
		fprintf(fp1, "%d %d %s %d %s\n", id, N, recordp->lecture_code, status, time1);
		free(recordp);
		fclose(fp1);
		
	}
}
void delete_std(int delStd){ // sýkýntýlý olabilir...
	char a[20], s[20];	
	int n, d, k;
	int i= 0,j;
	FILE *fp1;
	fp1 = fopen("students.txt", "r+" );
	
	STUDENT *student;
	student = (STUDENT*)malloc(sizeof(STUDENT));
	
	if(fp1==NULL){
		printf("dosya acilamadi..\n");
	}
	else {
		while(!feof(fp1)){
			fscanf(fp1, "%d %[^,] %[^,] %d %d", &n, a, s, &d, &k );
			if(delStd == n){
				printf("%d nolu student siliniyor...", delStd );
			}
			else{
				
				student = (STUDENT*)realloc(student,(i+1)*sizeof(STUDENT));
				
				student[i].Std_No= n;
				strcpy(student[i].name, a); 
				strcpy(student[i].surname, s);
				student[i].lecture_sum = d;
				student[i].credit_sum = k;
				printf("son okunan ögrenci no= %d\n", student[i].Std_No);
				printf("sondan bir önceki ögrenci no= %d\n", student[i-1].Std_No);
				
				i++;
			}
			
		}
		printf("while'dan cikti\n");
	}
	
	fclose(fp1);
	printf("okuma bitti.\n");
	FILE *fp2;
	fp2 = fopen("students.txt", "w");
	if(fp2== NULL){
		printf("yeniden yazmak icin dosya acilamadi.. \n");
	}
	else {
		for(j=0; j<i-1; j++){
			fprintf(fp2, "%d %s %s %d %d\n", 
			student[j].Std_No, student[j].name, student[j].surname, student[j].lecture_sum, student[j].credit_sum);
		}
	}
	fclose(fp2);
	free(student);
	
}
int spot_lecture_lastID(){ 
		int c, counter =1;
		FILE *fp1;
		fp1 = fopen("student_lecture_record.txt", "r+");
	
		while( fp1!=NULL && !feof(fp1)){
			c = getc(fp1);
			if(c == '\n'){
				counter++;			
			}		
		}
		return counter;
}

void prof_classes(int ID_){
	int Credit, Capacity, ProfID;
	char Code[20], Name[20];
	FILE *fp1;
	fp1 = fopen("lectures.txt", "r+");
	
	LECTURE *lecture;
	lecture = (LECTURE*)malloc(sizeof(LECTURE));
	
	if(fp1 == NULL){
		printf("dosya acilamadi");
	}
	else {
		printf("%d ID'li ogretim uyesinin verdiði lectures\n\n", ID_);
		while(!feof(fp1)){
				fscanf(fp1, "%[^,], %[^,], %d, %d, %d", Code, Name, &Credit, &Capacity, &ProfID);
				if(ProfID == ID_){
				printf("%s %s %d %d %d\n", Code, Name, Credit, Capacity, ProfID);
			}
		}
		
		
		
	
		
	}
	
	fclose(fp1);
	free(lecture);
	
}
void delete_prof(member_delete){ // sýkýntýlý olabilir...
	printf("fonksiyona girdi\n");
	int i= 0,j, id;
	char a[20], s[20], u[20];
	int index= 1, last =1;
	
	FILE *fp1;
	fp1 = fopen("prof_members.txt", "r+" );
	
	PROF *prof;
	prof = (PROF*)malloc(sizeof(PROF));
	
	if(fp1==NULL){
		printf("dosya acilamadi..\n");
	}
	else {
		
		
		while( !feof(fp1)){
			
			
			fscanf(fp1, "%d %[^,] %[^,] %[^,]", &id, a, s, u);
			
			prof[i].prof_ID = id;
			strcpy(prof[i].name, a);
			strcpy(prof[i].surname, s);
			strcpy(prof[i].member_title, u);
			printf(" %d ID'li %s %s kontrol ediliyor\n",prof[i].prof_ID , prof[i].name, prof[i].surname);
			if(member_delete == prof[i].prof_ID ){
				printf(" %d ID'li %s %s siliniyor\n", member_delete, prof[i].name, prof[i].surname);
			}
			else{
				
				i++;
				prof = (PROF*)realloc(prof,(i+1)*sizeof(PROF));
			}
		}	
	}
	fclose(fp1);
	
	
	
	FILE *fp2;
	fp2 = fopen("prof_members.txt", "w");
	if(fp2== NULL){
		printf("yeniden yazmak icin dosya acilamadi.. \n");
	}
	else{
		for(j= 0; j<i; j++){
			fprintf(fp2,"%d %s %s %s\n", prof->prof_ID, prof->name, prof->surname, prof->member_title);
		}
	}
	
	fclose(fp2);
	free(prof);
	
}






/*

void kaydolduguDersler(Num){
	
	int dersiSilmisMi(int ){
		
	}
	
	FILE *fp1 = fopen ("student_lecture_record.txt", "r+");
	LECTURE_SUBMIT submit;
	if(!fp1){
		printf("dosya acilmadi");
	}
	else {
		while(!feof(fp1)){
			fscanf(fp1, "%d %d %s %d %s", &submit.sub_ID, &submit.Std_No, submit.lecture_code, &submit.status, submit.date);
			if(Num == submit.Std_No && submit.status){
				if( ){  // dersi sonradan silmiþ olabilir mi
					dersiSilmisMi(Num, submit.lecture_code);
				}
			}
		}
	}
}
*/
int main (){
	setlocale(LC_ALL, "Turkish");
	int number, i, exe=1,zt=0;	
	int *sub_ID;	
	int credit_limit=25, lecture_limit=6, d, e, x_ID;
	char lecturecode[20];	
	sub_ID = (int *)malloc(sizeof(int)); 
	*sub_ID = 1;				 // 1'den baþlayýp oto artan öðrenci ders kayýt ID'si 
	int studentNo, n; 
	int del_std, del_member;
	printf("\n\n\n\t\t\tHOS GELDINIZ\n\n Otomatik Maksimum ders sayýsý 6, ve maksimum kredi sayýsý 25 atanmýþtýr\n Deðiþtirmek için 1 devam etmek için 0 giriniz.\n\n  ");
	scanf("%d", &zt);
	
	if(zt==1){
	printf("Ders sayisi limiti nedir? :  ");
	scanf("%d", &lecture_limit);	
	printf("Ogrenci icin kredi limiti nedir? :  "); 
	scanf("%d", &credit_limit);
	zt=0;
	}
	
	else if (zt!=1 && zt!=0){
		printf(" farklý bir rakam girdiniz Hata! lütfen 0 veya 1 girin:\n\n ");

	}

	printf(" ----ANA MENU----");
	
	   

	
	while (exe = 1 && zt==0){	// ana menü switch
		printf("\n\n\n"
		   " 1- Islem Menusu-->Ogrenci\n\n"
		   " 2- Islem Menusu-->Dersler\n\n"
		   " 3- Islem Menusu-->Ogretim Uyesi\n\n"
		   " 4- Islem Menusu-->Ders Ekle/Sil \n\n"
		   " 5- Islem Menusu-->Raporlar&Listelemeler\n\n"
		   " 6- Cýkýs\n\n"
		);
		printf(" Menu Numarasý: ");
		scanf("%d", &d);
		switch(d){
			case 1: // öðrenci iþlemleri
				printf("\t-OGRENCÝ DÜZENLEME MENUSU-\n\n\n"
					"\t 1- Öðrenci --> ekle\n\n" 
					"\t 2- Öðrenci  --> sil\n\n"
					"\t 3- Öðrenci  --> güncelle\n\n"
					"\t 4- <--- Geri Dön\n\n Seçim: "
				);
				scanf("%d", &e);
			
				switch(e){ // öðrenci iþlem menüsü
					case 1:  //öðrenci ekle
						printf("Eklenecek Ögrenci Sayýsý: \n ");
						scanf("%d", &number);
						for(i=0; i<number; i++)
							add_student();
						
						break;
					case 2: // öðrenci sil
						printf("Ögrenci Numarasý: \n ");
						scanf("%d", &del_std);
						delete_std(del_std);
						break;
					case 3: // öðrenci güncelle 
						
						break;
					case 4:  // ana menüye dön
					
						break;	
					default: 
						printf("hatalý tercih yaptýnýz. \n\n");	
				}
				break; 
			case 2:  // ders iþlemleri
				printf("\t-DERS DÜZENLEME MENUSU-\n\n\n"
					"\t 1- Ders --> Yeni Ekle\n\n" 
					"\t 2- Ders --> Sil\n\n"
					"\t 3- Ders -->  Güncelle\n\n"
					"\t 4- <--- Geri Dön\n\n"
				);
				scanf("%d", &e);
				switch(e){ // ders iþlem menüsü
					case 1:  	//yeni ders aç
						printf("Açýlacak Yeni Ders Sayýsý: \n ");
						scanf("%d", &number);
						for(i=0; i<number; i++)
							add_new_lecture();	
						
						
						break;
					case 2:		 //dersi sil
						
						break;
					case 3:		//dersi güncelle
					
						break;
					case 4:		// ana menüye dön
					
						break;
					default: 
						printf("hatalý tercih yaptýnýz!\n\n");	
				}
				break;
			case 3:  // öðretim üyesi iþlemleri
				printf("\t-ÖÐRETÝM ÜYESÝ DÜZENLEME MENUSU-\n\n\n"
				"\t 1- Öðretim üyesi -->  Yeni Ekle\n\n" 
				"\t 2- Öðretim üyesi -->  Sil\n\n"
				"\t 3- Öðretim Üyesi  --> Güncelle\n\n"
				"\t 4-  <--- Geri Dön\n\n"
				);
				scanf("%d", &e);
				switch(e){ // üye menü
					case 1:		//üye ekle
						printf("Eklenecek Ogretim Uyesi Sayisi: \n ");
						scanf("%d", &number);
						for(i=0; i<number; i++)
							add_prof();	
						
						break;
					case 2:		//üye sil
						printf("Silinecek Ögretim Uyesinine Ait ID:\n ");
						scanf("%d", &del_member);
						delete_prof(del_member);
						break;
					case 3:		//üye güncelle
					
						break;
					case 4:		// ana menüye dön
					
						break;
					default: 
						printf("hatalý tercih yaptýnýz!\n\n");	
				}
				break;
			case 4:  // öðrenci ders kayýt iþlemleri
				printf("\t-ÖÐRENCÝ DERS KAYIT MENUSU-\n\n\n"
					"\t 1- Ders --> Kayýt Ol\n\n" 
					"\t 2- Ders -->  Kaydý Sil\n\n"
					"\t 3- <--- Geri Dön\n\n"
				);
				scanf("%d", &e);
				switch(e){ 		//öðrenci ders kayýt menüsü
					case 1: 	// derse kayýt ol
						printf("öðrenci Numaranýz: \n "); scanf("%d", &studentNo);
						printf("Kayýt Olunacak Ders Sayýsý: \n "); scanf("%d", &n);
						for(i=0; i<n; i++)
							student_lecture_record(studentNo);
						
						break;
					case 2:		//derse kaydý sil
						break;
					case 3:		//ana menüye dön
						break;
					default :
						printf("hatalý bir seçim yaptýnýz!\n\n");	
				}
				break;
			case 5:	 // listeleme vb iþlemler 
				
				printf("\t-ARÞÝV GÖRÜNTÜLEME MENÜSÜ -\n\n\n"
					"\t 1- Ogretim Üyelerinin Verdiði Dersler\n\n" 
					"\t 2- Derse Kayýtlý Öðrenciler\n\n"
					"\t 3- Öðrencinin Kaydolduðu Dersler \n\n"
					"\t 4- Öðretim Üyesine ait ID ile verilen derslerden seçerek \n\n"
					"\t  Sýnýf listesi çýkartýp DERSKODU_SINIFLÝSTESÝ.txt dosyasýna yazmak.\n\n"
				);
				
						
				scanf("%d", &e);
				switch(e){ // listeleme menü
					case 1: // prof_ID ile verdiði dersleri listeleme
						printf("Öðretim üyesinine ait ID: \n ");
						scanf("%d", &x_ID);
						prof_classes(x_ID);
						break;
					case 2:	//	dersin kodu ile kendisine kayýtlý öðrenci listeleme
						printf("Dersin kodu: \n ");
						scanf("%s", lecturecode);
						registered_students(lecturecode);
						break;
					case 3:	//	numarasý ile kaydolduðu dersleri listeleme
						printf("Öðrenciye ait Numara: \n ");
						// scanf("%d", &num);
						// kaydolduguDersler(num);
						break;
					case 4:	//	prof_ID'den ders koduna, ordan da o dersi alan öðrencilere eriþip hepsini dosyaya yazdýrma
						break;
					default :
						printf("hatalý bir seçim yaptýnýz!\n\n");
				}
				break;	
			case 6:	 // çýkýþ
				return 0;
				break;
			default : // buraya dikkat
				printf("lütfen yeniden seçim yapýnýz \n\n");
				
	} // büyük switch bitiþ
	} // while biti
	
	return 0;
}

