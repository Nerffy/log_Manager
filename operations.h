#ifndef OPERATIONS_H
#define OPERATIONS_H

void user_add();
void user_list();
void user_update();
void user_delete();
void operations();

typedef enum{
    ADMIN = 1,
    USER,
    GUEST
}Role;

typedef struct
{
    char id[10];
    char name[32];
    Role role;
}User;


#endif