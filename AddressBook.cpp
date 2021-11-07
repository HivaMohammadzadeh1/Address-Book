// Lab 3 Mohammadzadeh,Hiva Thursday
// Address Book Unsorted linked List

#include<iostream>
#include<fstream>

using namespace std;

string upperCase(string input);

class Address{
    
private:
    string bnumber, stname, city, state, zipCode;
    
    
public:
    string getBNumber()const {
        return bnumber;
    }
    
    string getStName()const {
        return stname;
    }
    string getCity()const {
        return city;
    }
    string getState() const {
        return state;
    }
    string getZipCode() const {
        return zipCode;
    }
    
    void setAddress(string b, string c, string st, string s, string z){
        bnumber= b;
        city= c;
        stname = st;
        state= s;
        zipCode= z;
        
    }
    
    string toString(){
        string add;
        add = bnumber + " " + stname +" " + city + ", " + state + " " + zipCode + " ";
        return add;
    }
    
};

class Record{
    
private:
    string firstName, lastName, phoneNum;
    Address address;
    
public:
    string getFName() const{
        return firstName;
    }
    string getLName() const{
        return lastName;
    }
   string getPhoneNum()const {
        return phoneNum;
    }
    
    string fixedPhone()const{
    if(phoneNum.size() >= 7)
        return string ("(" + phoneNum.substr(0,3) + ")" + phoneNum.substr(3,3) + "-" + phoneNum.substr(6,4));
    else
        return phoneNum;
    }
    
    void printPerson(){
        cout << left << setw(10) << firstName << setw(12) << lastName << setw(2) << " " << setw(40)<< address.toString()  << setw(3)<< " " << setw(14) << fixedPhone() << endl;
        
       }
    
    void outfilePeople(ofstream &outFile){
        outFile<< left << setw(10) << firstName << setw(10) << lastName << setw(6) << " " << setw(35)<< address.toString()  << setw(3)<< " " << setw(14) << fixedPhone() << endl;
        
    }
    
   Record(const string& firstN= "", const string& lastN = "", const string& buildingN = "", const string& streetN = "", const string& c = "", const string & s = "", const string& zipC = "", const string& phoneN = "");
};

//CONSTRUCTOR
  Record::Record(const string& firstN, const string& lastN, const string& buildingN, const string& streetN, const string& c, const string& s, const string& zipC, const string& phoneN) {
      
      firstName = firstN;
      lastName = lastN;
      address. setAddress(buildingN, streetN, c, s, zipC);
      phoneNum = phoneN;
  }


class Node{
    
private:
    Node* next = nullptr;
    Record info;
    
public:
    Node();
    Node(Record i);
    Node* getNext();
    Record getInfo();
    void setNext(Node* n);
    void setInfo(Record i);
};

Node::Node(Record i) {
    info = i;
    next = nullptr;
}

Node* Node::getNext() {
    return next;
}

Record Node::getInfo() {
    return info;
}

void Node::setNext(Node* n) {
    next = n;
}

void Node::setInfo(Record i) {
    info = i;
}


class AddressBook{
    
private:
    Node *head = nullptr;
     
public:
    ~AddressBook();
    
    Node* getHead() {
           return head;
       }
    
    void setHead(Node* h) {
            head = h;
       }
    void loadData();
    void add();
    void search(string s);
    void display();
    void delet(string s);
    void OutData();
    void deleteNodes(Node *head);
        
};

void AddressBook:: deleteNodes(Node *head){
        Node* p;
        p = head;
        
        while(head != nullptr){
            head = head->getNext();
            delete p;
            p = head;
        }
        
}

AddressBook:: ~AddressBook(){
    deleteNodes(head);
    head = nullptr;
}

void AddressBook::loadData() {
    
    Node* p = head;
    
      ifstream inFile;
    
      inFile.open("/Users/hivamoh/Desktop/CS 136/Labs/CS 136 Lab 3 FINALL/136lab3file.txt");

        
    string firstName, lastName, buildingNumber, street, city, state, zipCode, phoneNumber;

        if (!inFile) {
           cout<<"error: unable to open input file";
           exit(1);
        }
    
        while (inFile>> firstName >> lastName >> buildingNumber >> street >> city >> state >> zipCode >> phoneNumber ) {

            firstName = upperCase(firstName);
            lastName = upperCase(lastName);
            street = upperCase(street);
            state = upperCase(state);
            city = upperCase(city);

            Record rec(firstName, lastName, buildingNumber, street, city, state, zipCode, phoneNumber);
           
            // use try catch to ensure it was allocated and if not dealicate the things that were previously and then make the new node
            try
            {
                if (head == nullptr){
                    head = new Node(rec);
                    
                }
                else{
                    Node* dummy = head;
                    p = new Node(rec);
                    
                    while (dummy->getNext() != nullptr){
                        
                        dummy= dummy->getNext();
                       
                    }
                    
                    dummy->setNext(p);
                
                }
            }
            catch (exception *e){
                cout<< "\nThere is not enough memory.\n"<< endl;
                delete head;
                throw;
            }
            
        }
    inFile.close();
}
       
    
void AddressBook::OutData(){
    
    ofstream outFile;
    outFile.open("/Users/hivamoh/Desktop/CS 136/Labs/CS 136 Lab 3 FINALL/updatedlab3file.txt");
    
    if(!outFile){
        cout<<"error: unable to open file to write data";
        return;
    }
    
    Node *p = head;
   
    
    while(p)

    {
        p->getInfo().outfilePeople(outFile);
        p=p->getNext();
    }
    

    
    outFile.close();
    cout<<"Data written into file successfully";
    
}
    
bool isEmpty(Node* head){
    
    if( head == nullptr){
            return true;
        }
    else{
            return false;
        }
    
}
    
void AddressBook::display(){
    Node *p = head;

        
    cout << "\nNAME"<<"\t\t\t\t\t" << "ADDRESS"
         << "\t\t\t\t\t\t\t\t\t\t" << "PHONE NUMBER\n" << endl;

    while(p != nullptr){
            
        p->getInfo().printPerson();
        p = p-> getNext();
    }
    cout << endl<< endl;
}
    
    
    
void AddressBook::search(string s){
    Node *p = head;
    
    while(p){
        
        if(p->getInfo().getLName()==s||p->getInfo().getPhoneNum()==s){
            
            cout << "\nNAME"<<"\t\t\t\t\t" << "ADDRESS"
                 << "\t\t\t\t\t\t\t\t\t\t" << "PHONE NUMBER\n" << endl;
            
            p->getInfo().printPerson();
            cout << endl;
            return;
        }
        
        p=p->getNext();
      
    }
    
    cout<<"\nNo matching record found\n"<< endl;
    
}

void AddressBook::add(){
    
    cout << "Enter the following information:\n"
         << "First Name: ";
    
    string fName;
    cin>> fName;
    fName= upperCase(fName);
    
    cout<<"Last Name: ";
    string lName;
    cin>> lName;
    lName= upperCase(lName);
    
    cout<<"Building Number: ";
    string bNumber;
    cin>>bNumber;
    
    cout<<"Street Name: ";
    string streetN;
    cin>>streetN;
    streetN = upperCase(streetN);
    
    cout<<"City: ";
    string City;
    cin>>City;
    City = upperCase(City);
    
    cout << "State: ";
    string State;
    cin >> State;
    State = upperCase(State);
    
    cout << "Zip Code: ";
    string ZipC;
    cin >> ZipC;
    
    cout<<"Phone Number: ";
    string phoneNum;
    cin>>phoneNum;
    
    Node *p = new Node(Record(fName, lName, bNumber, streetN, City, State, ZipC, phoneNum));
    
    p->setNext(head);
    head = p;
    

    cout<<"\nRecord was added successfully\n"<< endl;
}

   
void AddressBook::delet(string s){
    
    Node *p=nullptr;
    Node *c=head;

    while(c&&!(c->getInfo().getLName()==s||c->getInfo().getPhoneNum()==s)){

        p=c;
        c=c->getNext();
    }

    if(p==nullptr){

        head = c->getNext();
        delete c;
        cout<<"\nRecord deleted successfully\n"<< endl;
    }
    
    else if(p&&c){
        
        p->setNext(c->getNext());
        delete c;
        cout<<"\nRecord deleted successfully\n"<< endl;
    }

    else
        cout<<"\nNo matching record found. Deletion failed\n"<< endl;

}



int main(){
    
    
    AddressBook ab;
    ab.loadData();
    string s;
    int choice=0;
    
    
    while (choice != 5)
    {
        
        cout<< "------------MENU----------\n\n"
            << "1. Display the list\n"
            << "2. Search for a person by last name or phone number\n"
            << "3. Add a new entry\n"
            << "4. Delete an entry based on phone number or lastname\n"
            << "5. Exit and make the new file" << endl;
        
        cin >> choice;
        
        switch (choice) {
        case 1:
            ab.display();
            break;
                
        case 2:
            cout<<"Enter last name or phone number: ";
            cin>>s;
            s = upperCase(s);
            ab.search(s);
            break;
                
        case 3:
                ab.add();
                break;
                
        case 4:
            cout<<"Enter last name or phone number: ";
            cin>>s;
            s = upperCase(s);
            ab.delet(s);
            break;
                
        case 5:
            break;
                
        default:
            cout << "\nInvalid input. Please enter a proper value, from 1 to 5.\n" << endl;
            cin.clear();
            cin.ignore(255, '\n');
            
        }
    }
   
    ab.OutData();
    ab.~AddressBook();
    cout<<"\nBye!!";
    return 0;

}

string upperCase(string input) {
    string temp = "";
    for (size_t i = 0; i < input.length(); i++) {
        temp += toupper(input[i]);
    }
    return temp;
}

/*
 FILE INPUT:
 John doe 6202 WinneTka Canoga ca 91336    9193457896
 Emma jones 4891 pacific Perry ca 90875    2324247894
 Ethan Williams 20455 whiteoak enCiNo CA 90565    7672726797
 Justin martin    64433 reseda tarzaNa cA 90323    8605001863
 John Adams 20355 sherman Winnetka ca 91306 2324590872
 Hasti Moh 30456 Winnetka resedA cA 90344 9893457687
 */
/*
 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 dagsdhja

 Invalid input. Please enter a proper value, from 1 to 5.

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 8

 Invalid input. Please enter a proper value, from 1 to 5.

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 1

 NAME                    ADDRESS                                        PHONE NUMBER

 JOHN      DOE           6202 CANOGA WINNETKA, CA 91336             (919)345-7896
 EMMA      JONES         4891 PERRY PACIFIC, CA 90875               (232)424-7894
 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797
 JUSTIN    MARTIN        64433 TARZANA RESEDA, CA 90323             (860)500-1863
 JOHN      ADAMS         20355 WINNETKA SHERMAN, CA 91306           (232)459-0872
 HASTI     MOH           30456 RESEDA WINNETKA, CA 90344            (989)345-7687


 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 2
 Enter last name or phone number: doE

 NAME                    ADDRESS                                        PHONE NUMBER

 JOHN      DOE           6202 CANOGA WINNETKA, CA 91336             (919)345-7896

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 2
 Enter last name or phone number: dssd

 No matching record found

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 2
 Enter last name or phone number: 7672726797

 NAME                    ADDRESS                                        PHONE NUMBER

 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 2
 Enter last name or phone number: WilLIAMS

 NAME                    ADDRESS                                        PHONE NUMBER

 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 2
 Enter last name or phone number: MOh

 NAME                    ADDRESS                                        PHONE NUMBER

 HASTI     MOH           30456 RESEDA WINNETKA, CA 90344            (989)345-7687

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 4
 Enter last name or phone number: doe

 Record deleted successfully

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 1

 NAME                    ADDRESS                                        PHONE NUMBER

 EMMA      JONES         4891 PERRY PACIFIC, CA 90875               (232)424-7894
 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797
 JUSTIN    MARTIN        64433 TARZANA RESEDA, CA 90323             (860)500-1863
 JOHN      ADAMS         20355 WINNETKA SHERMAN, CA 91306           (232)459-0872
 HASTI     MOH           30456 RESEDA WINNETKA, CA 90344            (989)345-7687


 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 4
 Enter last name or phone number: 9893457687

 Record deleted successfully

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 1

 NAME                    ADDRESS                                        PHONE NUMBER

 EMMA      JONES         4891 PERRY PACIFIC, CA 90875               (232)424-7894
 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797
 JUSTIN    MARTIN        64433 TARZANA RESEDA, CA 90323             (860)500-1863
 JOHN      ADAMS         20355 WINNETKA SHERMAN, CA 91306           (232)459-0872


 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 3
 Enter the following information:
 First Name: hiva
 Last Name: misagh
 Building Number: 20344
 Street Name: wilshire
 City: losangeles
 State: AZ
 Zip Code: 90233
 Phone Number: 9894342312

 Record was added successfully

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 1

 NAME                    ADDRESS                                        PHONE NUMBER

 HIVA      MISAGH        20344 LOSANGELES WILSHIRE, AZ 90233        (989)434-2312
 EMMA      JONES         4891 PERRY PACIFIC, CA 90875               (232)424-7894
 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797
 JUSTIN    MARTIN        64433 TARZANA RESEDA, CA 90323             (860)500-1863
 JOHN      ADAMS         20355 WINNETKA SHERMAN, CA 91306           (232)459-0872


 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 3
 Enter the following information:
 First Name: adas
 Last Name: karimi
 Building Number: 435
 Street Name: california
 City: florida
 State: Fl
 Zip Code: 89877
 Phone Number: 4745632328

 Record was added successfully

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 1

 NAME                    ADDRESS                                        PHONE NUMBER

 ADAS      KARIMI        435 FLORIDA CALIFORNIA, FL 89877           (474)563-2328
 HIVA      MISAGH        20344 LOSANGELES WILSHIRE, AZ 90233        (989)434-2312
 EMMA      JONES         4891 PERRY PACIFIC, CA 90875               (232)424-7894
 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797
 JUSTIN    MARTIN        64433 TARZANA RESEDA, CA 90323             (860)500-1863
 JOHN      ADAMS         20355 WINNETKA SHERMAN, CA 91306           (232)459-0872


 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 4
 Enter last name or phone number: marTIN

 Record deleted successfully

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 1

 NAME                    ADDRESS                                        PHONE NUMBER

 ADAS      KARIMI        435 FLORIDA CALIFORNIA, FL 89877           (474)563-2328
 HIVA      MISAGH        20344 LOSANGELES WILSHIRE, AZ 90233        (989)434-2312
 EMMA      JONES         4891 PERRY PACIFIC, CA 90875               (232)424-7894
 ETHAN     WILLIAMS      20455 ENCINO WHITEOAK, CA 90565            (767)272-6797
 JOHN      ADAMS         20355 WINNETKA SHERMAN, CA 91306           (232)459-0872


 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 4
 Enter last name or phone number: adajks

 No matching record found. Deletion failed

 ------------MENU----------

 1. Display the list
 2. Search for a person by last name or phone number
 3. Add a new entry
 4. Delete an entry based on phone number or lastname
 5. Exit and make the new file
 5
 Data written into file successfully
 Bye!!Program ended with exit code: 0
 */
/*
 OUTPUT FILE AFTER ENDING PROGRAM:
 ADAS      KARIMI          435 FLORIDA CALIFORNIA, FL 89877      (474)563-2328
 HIVA      MISAGH          20344 LOSANGELES WILSHIRE, AZ 90233    (989)434-2312
 EMMA      JONES           4891 PERRY PACIFIC, CA 90875          (232)424-7894
 ETHAN     WILLIAMS        20455 ENCINO WHITEOAK, CA 90565       (767)272-6797
 JOHN      ADAMS           20355 WINNETKA SHERMAN, CA 91306      (232)459-0872

 */
