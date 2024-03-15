#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "file_pessoas"
#define BUFFER_SIZE 100

// TO DO

typedef struct person
{
    char name[200];
    int age;
}Person;

int add_person(char name, int age);

int list_persons(int N);

int update_age(char *name, int age);
