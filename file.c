#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    
    //opening file in write mode
    FILE *fptr = fopen("contacts.csv","w");
    if(fptr == NULL)
    {
        printf("❌ Opening of file is failed\n");
        return;
    }
    //write the contact count
    fprintf(fptr,"%d\n",addressBook->contactCount);
    //loop through contacts and save
    for(int i=0;i < addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("✅ Contacts saved successfully!\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {

    //opening file in read mode
    FILE *fptr = fopen("contacts.csv","r");
    if(fptr == NULL)
    {
        printf("❌ Opening of file is failed\n");
        return;
    }
    int num;
    //read contact count
    fscanf(fptr,"%d\n",&num);
    addressBook->contactCount = num;
    //read contacts
    for(int i=0;i < num;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("✅ Contacts loaded successfully!\n");
}
