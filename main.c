
               /*-------------------------Electronics Shopping Application------------------------*/

#include<stdio.h>
#include"device.h"
#include<stdlib.h>
#define DEVICE_DB "device.db"
typedef enum menu{
	EXIT,ADD,DELETE,DISPLAY,SEARCH,SORT
}menu_t;

menu_t menu()
{
	menu_t ch;
	printf("\n0.Exit\n");
	printf("1.Add\n");
	printf("2.Delete\n");
	printf("3.Display\n");
	printf("4.Search\n");
	printf("5.Sort\n");
	printf("\nEnter your choice:");
	scanf("%d",(int *)&ch);
	return ch;
}

int main(void)
{
	printf("\n\t\t******....................Welcome to P1C1 Electronics Shop............................*******\n\n");
	menu_t ch;
	device_t *device = NULL;
	char model[20];

	//allocating memory dynamically
	device = (device_t *)malloc(sizeof(device_t)*10);

	if(device == NULL)
		{
			printf("Malloc failed\n");
			exit(1);
		}
	//--------displaying all the elements initially-------------
		
		display_device(device);	
	while((ch = menu())!=EXIT)
		{
			switch(ch)
				{
					case EXIT:
						break;

					case ADD:
							scan_device(device);
							add_device(device);
						break;

					case DELETE:
						 printf("Enter the model to be deleted:");
						scanf("%*c%[^\n]s",model);
				
						 delete_device(model);
						break;

					case DISPLAY:
							display_device(device);
						break;

					case SEARCH:
						printf("Enter the Model:");
						scanf("%*c%[^\n]s",model);
						search_device(model);
						break;

					case SORT:
						sort_device();
						break;

					default:
						printf("Invalid choice\n");
				}
		}
	free(device);
		
	return 0;
}





