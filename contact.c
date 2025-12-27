#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int indexarr[50];
int matchedcount = 0;
int found = 0;

//checking valid name
int isValidName(const char *name)
{
    for(int i=0;name[i] != '\0';i++)
    {
        if(name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || name[i] == ' ')
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

////checking valid ph-nor
int isValidPhone(AddressBook *ab,const char *phone)
{
    int len = strlen(phone);
    if(len != 10)
    {
        printf("❌ Invalid phone! Use exactly 10 digits.\n");
        return 1;
    }
    for(int i=0;i < len;i++)
    {
        if(isdigit(phone[i]))
        {

            continue;
        }
        else
        {
            printf("❌ Invalid phone! Use exactly 10 digits.\n");
            return 1;
        }
    }
    for(int i=0; i < ab->contactCount;i++)
    {
        if(strcmp(ab->contacts[i].phone,phone) == 0)
        {
            printf("❌ Error: Phone number already exists!\n");
            return 1;
        }
    }
    return 0;
}

//checking valid email-id
int isValidEmail(AddressBook *ab,const char *email)
{
    int len = strlen(email);

    //must have @ & must end with ".com"
    char *at = strchr(email,'@');
    if(at == NULL || len < 5 || strcmp(email + len - 4,".com") != 0)
    {
        printf("❌ Invalid Email id! Use only letters/numbers before @ & end with .com\n");
        return 1;
    }

    //index of '@' and index of '.'
    int atIndex = at - email;
    int dotIndex = len - 4;

    //must have atlest one character blw '@' & '.'
    if(atIndex < 1 || dotIndex - atIndex < 2)
    {
        printf("❌ Invalid Email id! Use only letters/numbers before @ & end with .com\n");
        return 1;
    }

    //No space allowed
    for(int i=0;i < len;i++)
    {
        if(email[i] == ' ')
        {
            printf("❌ Invalid Email id! Use only letters/numbers before @ & end with .com\n");
            return 1;
        }
    }

    //check character before '@' are only letters/digits
    for(int i=0;i < atIndex;i++)
    {
        if(!(isalpha((unsigned char)email[i]) || isdigit((unsigned char)email[i])))
        {
            printf("❌ Invalid Email id! Use only letters/numbers before @ & end with .com\n");
            return 1;
        }
    }

    for(int i=0; i < ab->contactCount;i++)
    {
        if(strcmp(ab->contacts[i].email,email) == 0)
        {
            printf("❌ Error: Email-Id already exists!\n");
            return 1;
        }
    }

    return 0; //valid email
}

void listContacts(AddressBook *addressBook) 
{
    //List of contacts
    printf("%40s","LIST OF CONTACTS\n");
    if(addressBook->contactCount == 0)
    {
        printf("❌ No Contacts Found.\n");
        return;
    }

    //printing in correct order
    printf("\n-----------------------------------------------------------------\n");
    printf("%-5s %10s %15s %15s\n","SL.NO","NAME","PHONE-NOR","EMAIL-ID");
    printf("-----------------------------------------------------------------\n");

    for(int i=0;i < addressBook->contactCount;i++)
    {
        printf("%-11d %-10s %-16s %-15s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is full! Cannot add more contacts.\n");
        return;
    }

    //Check valid name
    Contact *newContact = &addressBook->contacts[addressBook->contactCount];
    do
    {
        printf("Enter the Name: ");
        scanf(" %[^\n]",newContact->name);
        if(isValidName(newContact->name) == 1)
        {
            printf("❌ Invalid name! Use alphabets only.\n");
        }
    }while(isValidName(newContact->name));

    //Check valid phone number
    do
    {
        printf("Enter the Phone number: ");
        scanf(" %[^\n]",newContact->phone);
    }while(isValidPhone(addressBook, newContact->phone));

    //Check valid email-id
    do
    {
        printf("Enter the Email Id: ");
        scanf(" %[^\n]",newContact->email);
    }while(isValidEmail(addressBook,newContact->email));

    addressBook->contactCount++;

    printf("✅ Contact Added Successfully\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int option;
    char search[50];

    printf("----Search Contact----\n");
    printf("1. Search by Name\n");
    printf("2. Search by Ph-nor\n");
    printf("3. Search by Email-id\n");
    
    printf("Enter your option: ");
    scanf(" %d",&option);

    switch(option)
    {
        case 1:
        {
            printf("Enter name to search: ");
            scanf("%s",search);
            for(int i=0;i < addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].name,search) == 0)
                {
                    if(!found)
                    {
                        printf("Contact Found!\n");
                    }
                    printf("SL.NO %d. Name: %s | Ph-nor: %s | Email-id: %s\n",matchedcount + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    indexarr[matchedcount++] = i; //store in temp array
                    found = 1;
                }
            }
            if(!found)
            {
                printf("❌ Contact Not Found!\n");
            }
            break;
        }

        case 2:
        {
            printf("Enter ph-nor to search\n");
            scanf("%s",search);
            for(int i=0;i < addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].phone,search) == 0)
                {
                    if(!found)
                    {
                        printf("Contact Found!\n");
                    }
                    printf("SL.NO %d. Name: %s | Ph-nor: %s | Email-id: %s\n",matchedcount + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);                
                    indexarr[matchedcount++] = i; //store in temp array
                    found = 1;
                }
            }
            if(!found)
            {
                printf("❌ Contact Not Found!\n");
            }
            break;
        }

        case 3:
        {
            printf("Enter Email-id to search\n");
            scanf("%s",search);
            for(int i=0;i < addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].email,search) == 0)
                {
                    if(!found)
                    {
                        printf("Contact Found!\n");
                    }
                    printf("SL.NO %d. Name: %s | Ph-nor: %s | Email-id: %s\n",matchedcount + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    indexarr[matchedcount++] = i; //store in temp array
                    found = 1;
                }
            }
            if(!found)
            {
                printf("❌ Contact Not Found!\n");
            }
            break;
        }
        default:
        {
            printf("❌ Invalid option!\n");
        }
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int option;
    char re_edit[50];
    int choice;

    searchContact(addressBook);
    if(found == 1)
    {
        printf("----Edit Contact----\n");
        printf("1. Edit Name\n");
        printf("2. Edit Ph-nor\n");
        printf("3. Edit Email\n");

        printf("Enter the option: ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
            {
                printf("Enter name to edit contact: ");
                scanf("%s",re_edit);

                //check valid name
                if(isValidName(re_edit) == 1)
                {
                    printf("❌ Invalid name! Use alphabets only.\n");
                    return;
                }

                //checking this condition weather contact is found or not
                if(matchedcount == 0)
                {
                    return;
                }
                if(matchedcount > 1)
                {
                    printf("Enter SL.NO of contact to edit name: ");
                    scanf("%d",&choice);

                    if(choice < 1 || choice > matchedcount)
                    {
                        printf("❌ Invalid SL.NO!\n");
                        return;
                    }

                    strcpy(addressBook->contacts[indexarr[choice - 1]].name,re_edit);
                }
                else
                {
                    strcpy(addressBook->contacts[indexarr[0]].name,re_edit);
                }
                printf("✅ Contact Edited Successfully!\n");
                matchedcount = 0;
                break;

            }
            case 2:
            {
                printf("Enter ph-no to edit contact: ");
                scanf("%s",re_edit);

                //check valid ph-nor 
                if(isValidPhone(addressBook, re_edit) == 1 || matchedcount == 0)
                {
                    return;
                }

                if(matchedcount > 1)
                {
                    printf("Enter SL.NO of contact to edit ph-no: ");
                    scanf("%d",&choice);

                    if(choice < 1 || choice > matchedcount)
                    {
                        printf("❌ Invalid SL.NO!\n");
                        return;
                    }

                    strcpy(addressBook->contacts[indexarr[choice - 1]].phone,re_edit);
                }
                else
                {
                    strcpy(addressBook->contacts[indexarr[0]].phone,re_edit);
                }
                printf("✅ Contact Edited Successfully!\n");
                matchedcount = 0;
                break;
            }
            case 3:
            {
                printf("Enter email-id to edit contact: ");
                scanf("%s",re_edit);

                //check valid email
                if(isValidEmail(addressBook,re_edit) == 1 || matchedcount == 0)
                {
                    return;
                }
                if(matchedcount > 1)
                {
                    printf("Enter SL.NO of contact to edit email-id: ");
                    scanf("%d",&choice);

                    if(choice < 1 || choice > matchedcount)
                    {
                        printf("❌ Invalid SL.NO!\n");
                        return;
                    }

                    strcpy(addressBook->contacts[indexarr[choice - 1]].email,re_edit);
                }
                else
                {
                    strcpy(addressBook->contacts[indexarr[0]].email,re_edit);
                }
                printf("✅ Contact Edited Successfully!\n");
                matchedcount = 0;
                break;   
            }
            default:
            {
                printf("❌ Invalid option!\n");
            }

        }
    }
    else
    {
        return;
    }    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    if(addressBook->contactCount == 0)
    {
        printf("❌ No contact available to delete!\n");
        return;
    }

    searchContact(addressBook);

    //checking contact is found or not
    if(matchedcount == 0)
    {
        return;
    }

    int choice;
    if(matchedcount > 1)
    {
        printf("Enter SL.NO of contact to delete: ");
        scanf("%d",&choice);
        if(choice < 1 || choice > matchedcount)
        {
            printf("❌ Invalid SL.NO!\n");
            return;
        }
    }
    else
    {
        choice = 1;
    }

    int Index = indexarr[choice - 1];

    for(int i = Index;i < addressBook->contactCount - 1;i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("✅ Contact deleted successfully!\n");
   
}
