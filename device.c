#include<stdio.h>
#include<stdlib.h>
#include"device.h"
#define DEVICE_DB "device.db"
#include<string.h>
//---------Scan the elements--------//

void scan_device(device_t *device)
{
	printf("Enter the details:\n");
	printf("Model:");
	scanf("%*c%[^\n]s",device->model);
	printf("Company:");
	scanf("%*c%[^\n]s",device->company);
	printf("Catefory(1-Mobile,2-TV,3-WashingMachine):");
	scanf("%d",(int *)&device->category);
	printf("Price:");
	scanf("%f",&device->price);
}

//---------Add the elements to the file------//
void add_device(device_t *device)
{

	FILE *fp;
	fp = fopen(DEVICE_DB,"ab");
	
	if(fp == NULL)
		printf("Error in opening file.");
	fwrite(device,sizeof(device_t),1,fp);
	
	fclose(fp);
}
char *tostring(type_t category)
{
	switch(category)
		{
			case MOBILE:
				return "MOBILE";
				break;
			case TV:
				return "TV";
				break;
			case WASHING_MACHINE:
				return "WashingMachine";
				break;
		}
	return NULL;
}

//------------print device

static void print_device(device_t device)
{	
	
	printf("%-15s %-20s %-25s %-4.2f\n",device.model,device.company,tostring(device.category),device.price);

}

//-------write to the file

void display_device(device_t *device)
{
  FILE *fp;
  fp = fopen(DEVICE_DB,"rb");
  
	if(fp == NULL)
		printf("Error in opening file.");
	
	/*if(fread(device,sizeof(device_t),1,fp) == 0)
	{
		printf("No elements to display.\n");
	}*/
		
		printf("%-15s %-20s %-25s %-4s\n","Model","Company","Category","Price");
		while(fread(device,sizeof(device_t),1,fp)!=0)
			print_device(*device);
		
	

	fclose(fp);
}

//-----delete device by Model----

void delete_device(char * model)
{
	printf("%s\n",model);
	int found = 0;
  FILE *fp,*tempfp;
  device_t d;
  fp = fopen(DEVICE_DB,"rb");

	if(fp == NULL)
		printf("Error in opening file.");

	tempfp = fopen("temp.db","wb");

	while(fread(&d,sizeof(device_t),1,fp)!=0)
		{
		
			if(strcmp(d.model,model))
			{
			 fwrite(&d,sizeof(device_t),1,tempfp);
			}
			else
				found = 1;
		}


	remove(DEVICE_DB);
	rename("temp.db",DEVICE_DB);

	if(found == 1)
		printf("\nSuccessfully deleted.\n");
	else
		printf("\nNot found\n");
	fclose(fp);
	fclose(tempfp);
}

//-----------search device by model------------------

void search_device(char *model)
{

  FILE *fp;
  device_t d;
  fp = fopen(DEVICE_DB,"rb");
  
	if(fp == NULL)
		printf("Error in opening file.");
	
	while(fread(&d,sizeof(device_t),1,fp)!=0)
		{
			if(!strcmp(d.model,model))
				print_device(d);
		}
	fclose(fp);
}

//-------------to get the total number of records----------------

static int count_device(device_t device)
{
	FILE *fp;

	int cnt = 0;
	fp = fopen(DEVICE_DB,"rb");

	if(fp == NULL)
		printf("Error in opening file.\n");

	while(fread(&device,sizeof(device_t),1,fp)!=0)
		cnt++;
	fclose(fp);
	return cnt;
}


int compare(const void *ptr1,const void *ptr2)
{
float p1 = ((device_t *)ptr1)->price;
float p2 = ((device_t *)ptr2)->price;
return p1 - p2;
}

//------------Sorting devices by price------------------

void sort_device()
{
	int i=0,cnt = 0;
	FILE *fp;
	device_t device;
	fp = fopen(DEVICE_DB,"rb");
	
	if(fp == NULL)
		printf("Error in opening file.\n");
	
	cnt = count_device(device);
	
	device_t *d = (device_t *)malloc(sizeof(device_t)*cnt);
	
	

	while(fread(&device,sizeof(device),1,fp)!=0)
		{
			d[i] = device;
			i++;
		}
		
	qsort(d,cnt,sizeof(device_t),compare);
		
	for(i=0;i<cnt;i++)
		print_device(d[i]);

	
	fclose(fp);	
	free(d);
	
}




