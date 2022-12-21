#include <iostream>
#include <conio.h>
using namespace std;

struct PhoneBook
{
    string name, number, email;
    PhoneBook *next;
    PhoneBook *prev;
};

bool prec(PhoneBook *a, PhoneBook *b)
{
    // here temp1 we want to insert
    string tmp1, tmp2;
    bool flag = false;
    tmp1 = a->name;
    tmp2 = b->name;
    int x = (tmp1.size() < tmp2.size()) ? tmp1.size() : tmp2.size();

    // we are checkign aac name
    for (int i = 0; i < x; i++)
    {
        if (tmp1[i] > tmp2[i])
        {
            flag = true;
            break;
        }
        else if (tmp1[i] < tmp2[i])
        {
            flag = false;
            break;
        }
    }

    // we are checking acc number
    if (flag == false && tmp1 == tmp2)
    {
        tmp1 = a->number;
        tmp2 = b->number;
        x = (tmp1.size() < tmp2.size()) ? tmp1.size() : tmp2.size();
        for (int i = 0; i < x; i++)
        {
            if (tmp1[i] > tmp2[i])
            {
                flag = true;
                break;
            }
            else if (tmp1[i] < tmp2[i])
            {
                flag = false;
                break;
            }
        }
    }

    return flag;
}

PhoneBook *insert(PhoneBook *head)
{
    PhoneBook *ptr = new PhoneBook;
    PhoneBook *q;
    q = head;
    cout << "\nEnter Name: ";
    cin >> ptr->name;
    cout << "Enter Number: ";
    cin >> ptr->number;
    cout << "Enter Email: ";
    cin >> ptr->email;

    // When the linked list is empty
    if (head == NULL)
    {
        ptr->next = NULL;
        ptr->prev = NULL;
        head = ptr;
    }

    // we are sorting the linked list
    // with temp variable we are checking that is it going to be first or not
    bool flag, temp = true;
    while (q != NULL)
    {
        flag = prec(ptr, q);
        if (flag == true)
        {
            q = q->next;
        }
        else
        {
            if (temp == false)
                q->prev->next = ptr;
            ptr->prev = q->prev;
            q->prev = ptr;
            ptr->next = q;
            if (temp == true)
                head = ptr;
            break;
        }
        temp = false;
    }

    if (flag == true)
    {
        // this condition means we are adding at the end
        q = head;
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = ptr;
        ptr->prev = q;
        ptr->next = NULL;
    }

    return head;
}

void print(PhoneBook *head)
{
    PhoneBook *ptr;
    ptr = head;
    if (ptr == NULL)
        return;
    while (ptr != NULL)
    {
        cout << "\nName:-" << ptr->name << "\t"
             << "Number:-" << ptr->number << "\t"
             << "Email:-" << ptr->email << endl;
        ptr = ptr->next;
    }
}

int Questions()
{
    char c;
    int val;
    cout << "\nDo You Want To Continue Operations????????? ";
    cin >> c;
    if (c != 'y' && c != 'Y')
        return -1;
    cout << "\n1.Display Your PhoneBook" << endl;
    cout << "2.Insert New Contact" << endl;
    cout << "3.Update Details On Existing Contact" << endl;
    cout << "4.Delete Contact" << endl;
    cout << "5.Delete Same Name In PhoneBook" << endl;
    cout << "6.Search" << endl;
    cin >> val;
    return val;
}

void Update(PhoneBook *head)
{
    string name;
    char c;
    int val;
    cout << "\nEnter The Name Of Person That Details You Want To Update : ";
    cin >> name;

    PhoneBook *ptr;
    ptr = head;

    while (ptr != NULL && ptr->name != name)
        ptr = ptr->next;

    if (ptr == NULL)
    {
        cout << "\nUser does not exist!\n";
        return;
    }

    cout << "What Do You Want To Update" << endl;
    cout << "1.Name\n2.Number\n3.Email\n";
    cin >> val;
    switch (val)
    {
    case 1:
        cout << "\nEnter New Name: ";
        cin >> ptr->name;
        break;
    case 2:
        cout << "\nEnter New Number: ";
        cin >> ptr->number;
        break;
    case 3:
        cout << "\nEnter New Email: ";
        cin >> ptr->email;
        break;
    }

    cout << "\nDo You Want To Continue Updating????????? ";
    cin >> c;
    if (c == 'y' || c == 'Y')
        Update(head);
    else
        return;
}

PhoneBook *Delete(PhoneBook *head)
{
    string name;
    char c;
    int val;
    cout << "Enter The Name Of Person That Contact You Want To Delete: ";
    cin >> name;

    PhoneBook *ptr, *q;
    ptr = head;

    // when we want to delete first node
    if (ptr != NULL && ptr->name == name)
    {
        head = ptr->next;
        delete ptr;
        cout << "Your Contact Is Successfully Deleted" << endl;
        return head;
    }

    while (ptr != NULL && ptr->name != name)
    {
        q = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL)
    {
        cout << "\nUser does not exist!\n";
        return head;
    }
    q->next = ptr->next;
    delete ptr;
    cout << "Your Contact Is Successfully Deleted" << endl;
    return head;
}

void Delete_Same_Name(PhoneBook *head)
{
    PhoneBook *q, *r;
    q = head;
    r = head->next;
    while (q->next != NULL && r != NULL)
    {
        if (q->name == r->name)
        {
            if (r->next == NULL)
            {
                q->next = NULL;
                delete r;
            }
            else
            {
                q->next = r->next;
                r->next->prev = q;
                delete r;
                r = q->next;
            }
        }
        else
        {
            q = q->next;
            r = r->next;
        }
    }
    print(head);
}

void Search(PhoneBook *head)
{
    PhoneBook *ptr;
    int flag = true;
    ptr = head;
    if (ptr == NULL)
        return;

    int val;
    string search_val;
    char c;
    cout << "\n1.Search By Name\n2.Search By Number\n3.Search By Email\n";
    cin >> val;
    switch (val)
    {
    case 1:
        cout << "\nEnter The Name To Be Searched: ";
        cin >> search_val;
        while (ptr != NULL && ptr->name != search_val)
            ptr = ptr->next;
        if (ptr == NULL)
        {
            cout << "\nName Not Found" << endl;
            flag = false;
            break;
        }
        cout << "\nName Found Conact Details Are Bellow:" << endl;
        break;
    case 2:
        cout << "Enter The Number To Be Searched: ";
        cin >> search_val;
        while (ptr != NULL && ptr->number != search_val)
            ptr = ptr->next;
        if (ptr == NULL)
        {
            cout << "\nNumber Not Found" << endl;
            flag = false;
            break;
        }
        cout << "\nNumber Found Conact Details Are Bellow:" << endl;
        break;
    case 3:
        cout << "\nEnter The Email To Be Searched: ";
        cin >> search_val;
        while (ptr != NULL && ptr->email != search_val)
            ptr = ptr->next;
        if (ptr == NULL)
        {
            cout << "\nEmail Not Found" << endl;
            flag = false;
            break;
        }
        cout << "\nEmail Found Contact Details Are Bellow:" << endl;
        break;
    }

    if (flag)
        cout << "\nName:-" << ptr->name << "\t"
             << "Number:-" << ptr->number << "\t"
             << "Email:-" << ptr->email << endl;

    cout << "\nDo You Want To Continue Searching: ";
    cin >> c;
    if (c == 'y' || c == 'Y')
        Search(head);
    else
        return;
}

char what_to_do()
{
    char c;
    cout << "\nDo You Want To Continue Inserting????????? ";
    cin >> c;
    return c;
}

void Start()
{
    PhoneBook *head = NULL;
    char c = 'y';
    while (c == 'y' || c == 'Y')
    {
        head = insert(head);
        c = what_to_do();
    }
    while (1)
    {
        int val;
        val = Questions();
        switch (val)
        {
        case 1:
            print(head);
            break;
        case 2:
            head = insert(head);
            c = what_to_do();
            while (c == 'y' || c == 'Y')
            {
                head = insert(head);
                c = what_to_do();
            }
            break;
        case 3:
            Update(head);
            break;
        case 4:
            head = Delete(head);
            break;
        case 5:
            Delete_Same_Name(head);
            break;
        case 6:
            Search(head);
            break;
        }

        if (val == (-1))
        {
            break;
        }
    }
}

int main()
{
    cout << "\n\n***********************************PHONE BOOK***********************************";
    string user;
    cout << "\n\nWhat Is Your Name?: ";
    getline(cin, user);
    cout << "\n\n!!!!!!!!!!!!!!!!!!!! Welcome " << user << " !!!!!!!!!!!!!!!!!!!!\n\n";
    cout << "Let's Create Your PhoneBook " << user << endl;
    Start();
    cout << "\nThanks For Using PHONE BOOK, Have A Nice Day!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    getch();
    return 0;
}