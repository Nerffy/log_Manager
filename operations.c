#include "operations.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wait_for_enter() // işlemler sonrası devam etmek için kullanılan enter
{
    char tmp[10];
    fgets(tmp, sizeof(tmp), stdin);
}
void user_add()
{
    User user1, temp; // user1 yeni bakılan temp is dosyada var olanalra baktığımız kullanıcı
    FILE *fp;

    char id[10];
    int exist;

    while (1)
    {
        exist = 0;
        printf("Write the user ID: ");
        fgets(user1.id, sizeof(user1.id), stdin);
        user1.id[strcspn(user1.id, "\n")] = 0;

        // VAR MI KONTROL (temp ile!)
        fp = fopen("users.dat", "rb");
        if (fp)
        {
            while (fread(&temp, sizeof(User), 1, fp) == 1)
            {
                if (strcmp(temp.id, user1.id) == 0)
                {
                    printf("ID already exists!\n");
                    logMesaage(LOG_WARN, "Trying to log in with an existing ID");
                    exist = 1;
                    break; // iç while dan çıktı
                }
            }
            fclose(fp);
        }
        if (exist) // id var başa dön
        {
            continue;
        }
        break; // ID temiz çık
    }
    printf("Write an username: ");
    fgets(user1.name, sizeof(user1.name), stdin);
    user1.name[strcspn(user1.name, "\n")] = 0;

    while (1)
    {
        printf("\nChoose a role (1 for admin, 2 for user, 3 for guest ): ");
        int r;
        scanf("%d", &r);

        switch (r)
        {
        case ADMIN:
            user1.role = ADMIN;
            break;
        case USER:
            user1.role = USER;
            break;
        case GUEST:
            user1.role = GUEST;
            break;
        default:
            printf("Invalid number! Try Again.");
            logMesaage(LOG_WARN, "Access denied.");
            continue;
        }
        break; // Doğru seçimden sonra while'dan çık
    }
    fp = fopen("users.dat", "ab");
    if (!fp)
    {
        printf("File could not be opened for writing.\n");
        logMesaage(LOG_ERROR, "users.dat file could not be opened");
        return;
    }

    fwrite(&user1, sizeof(User), 1, fp);

    char log_buffer[128];
    snprintf(log_buffer, sizeof(log_buffer), "User Added ID : %s", user1.id);
    logMesaage(LOG_INFO, log_buffer);

    fclose(fp);
    wait_for_enter();
}
void user_list()
{
    FILE *fp = fopen("users.dat", "rb");

    const char *role_to_string[] = {
        // enum int verir bununla int değerlerin string karşılıklarını okuruz
        "",      // index 0 boş (kullanılmıyor)
        "admin", // 1
        "user",  // 2
        "guest"  // 3
    };

    User user;

    if (!fp)
    {
        printf("File could not be opened.\n");
        return;
    }
    while (fread(&user, sizeof(User), 1, fp) == 1)
    {
        if (user.role >= ADMIN && user.role <= GUEST)
            printf("Name: %s\nID: %s\nRole: %s\n", user.name, user.id, role_to_string[user.role]);

        else
        {
            printf("Role: unknown\n");
            continue;
        }
    }
    fclose(fp);
}
void user_update()
{
    FILE *fp = fopen("users.dat", "rb+");
    if (!fp)
    {
        printf("File could not be opened.\n");
        return;
    }
    User user;
    int found = 0;
    char target_id[10];

    printf("Enter the user ID to update: ");
    fgets(target_id, sizeof(target_id), stdin);
    target_id[strcspn(target_id, "\n")] = 0;

    while (fread(&user, sizeof(User), 1, fp) == 1)
    {
        if (strcmp(user.id, target_id) == 0)
        {
            printf("Update the username: ");
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = 0;

            fseek(fp, -(long)sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, fp);
            fflush(fp); // program da ki güncel adı direkt görebilmek için (fclose zaten flush yapar)

            found = 1;
            printf("User updated successfully.\n");
            char log_buffer[128];
            snprintf(log_buffer, sizeof(log_buffer), "User %s Updated ID : %s",user.name ,user.id);
            logMesaage(LOG_INFO, log_buffer);
            return;
        }
    }

    if (!found)
    {
        printf("User not found!\n");
    }

    fclose(fp);
    wait_for_enter();
}
void user_delete()
{
    FILE *fEx = fopen("users.dat", "rb");
    FILE *fNext = fopen("newUsers.dat", "wb");
    if (!fEx || !fNext)
    {
        printf("File could not be opened.\n");
        return;
    }
    User user;
    printf("\nEnter the ID to be delete: ");
    char target_id[10];
    //   scanf("%9s", target_id);
    fgets(target_id, sizeof(target_id), stdin); // fgets enter basıldığında \n karakterini de input olarak alır yani fgets ile id = 123\n şeklinde alınıyor aıl id için \n temizlenmeli
    target_id[strcspn(target_id, "\n")] = '\0'; // kullanıcı id si girdikten sonra enter yapılınca dosya bunu id+\n alıyor bundan dolayı bu satır \n temizler

    int found = 0;
    while (fread(&user, sizeof(User), 1, fEx) == 1)
    {
        if (strcmp(user.id, target_id) != 0) //\n temizlenmeseydi 123\n ile 123 compare i yapardı ve şifre silinemezdi
        {
            fwrite(&user, sizeof(User), 1, fNext);
        }
        else
        {
            found = 1;
        }
    }
    if (found)
    {
        printf("User deleted.\n");
        char log_buffer[128];
        snprintf(log_buffer, sizeof(log_buffer), "User %s deleted : ID %s", user.name, user.id);
        logMesaage(LOG_INFO, log_buffer);
    }
    else
    {
        printf("User not found.\n");
    }
    fclose(fEx);
    fclose(fNext);

    remove("users.dat");
    rename("newUsers.dat", "users.dat");

    wait_for_enter();
}

void operations()
{
    while (1)
    {
        char selection[10];

        printf(
            "\n1-) Add a new user\n"
            "2-) Show the users list\n"
            "3-) Update the user information\n"
            "4-) Delete the user\n"
            "(Press ENTER to exit)\n");

        fgets(selection, sizeof(selection), stdin);

        // ENTER = çıkış
        if (selection[0] == '\n')
        {
            printf("Program has ended...\n");
            break;
        }

        switch (selection[0])
        {
        case '1':
            user_add();
            continue;

        case '2':
            user_list();
            continue;

        case '3':
            user_update();
            continue;

        case '4':
            user_delete();
            continue;

        default:
            printf("Invalid choise! Try Again.");
            continue;
        }
        break;
    }
}
