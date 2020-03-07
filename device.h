#ifndef __DEVICE_H
#define __DEVICE_H
typedef enum type{
	MOBILE=1,TV,WASHING_MACHINE
}type_t;


typedef struct device
{	
	char model[20];
	char company[20];
	type_t category;
	float price;
}device_t;

void scan_device(device_t *device);
void add_device(device_t *device);
//void print_device(device_t *device);
void display_device(device_t *device);
void delete_device(char *);
void search_device(char *);
void sort_device();

#endif
