#include "person.h"
#include <stdio.h>


int add_person(char name, int age)
{
    int fd = open(FILENAME, O_WRONLY | O_CREAT, 0600);
    if (fd == -1)
    {
        perror("erro ao abrir ficheiro");
        return -1;
    }
    Person p;
    p.age = age;
    strcpy(p.name, name);
    ssize_t bytes_escritos = write(fd, &p, sizeof(Person));
    if (bytes_escritos < 0)
    {
        perror("erro ao escrever");
        return -1;
    }

    printf("Person added: %s, %d\n", name, age);

    close(fd);
    return 0;
}

int list_persons(int N)
{   
    Person p;

    char buffer[BUFFER_SIZE];
    ssize_t bytesLidos, bytesEscritos;

    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1)
    {
        perror("erro ao abrir ficheiro");
        return -1;
    }

    char buffer[200];
    int size = sprintf(buffer, "li uma pessoa %s com a idade %d", p.name, p.age);
    write(1, &p, size);

    close(fd);

    return 0;
}

int update_age(char name, int age)
{
    // TO DO
    return 0;
}