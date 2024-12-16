#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<cctype>
#include<algorithm>

using namespace std;

fstream lib;
bool adminFlag= false, studentLogFlag = false, adminLogFlag= false;

int menu();
void AdminLogin();
bool VerifyPass();
void StudentLogin();
void Signup();
int checkIssue(string book);
void issueBook();
void issueAdd(string book, string genre);
void returnBook();
void returnAdd(string book, string genre);
void addbooks();
void DeleteBookReturn(string bookName);
void DeleteBook();
void availableBook_list();


int main(){
    menu();
    
}
int menu(){
    int counter=0;
    do{
    int option;

    cout<<".........Please Select An Option......... \n";
    cout<<"......... 1.Admin login.........\n";
    cout<<"......... 2.Student login.........\n";
    cout<<"......... 3.Student SignUp.........\n";
    cout<<"......... 4.Exit.........\n";
    
    cin>> option;

    switch(option){
        case 1: AdminLogin();
                return 0;
        case 2: StudentLogin();
                return 0;
        case 3: Signup();
                return 0;
        
        case 4: return 0;
        default:cout<<"User Input not recognized.\n";
                cout<<"Try again.\n";
                counter=1;
                break;


    }
    }while(counter==1);
}

void AdminLogin(){

    int option;
    adminFlag=true;
    if(adminLogFlag || VerifyPass()){
        cout<<".........Please Select An Option......... \n";
        cout<<"......... 1.Add Books.........\n";
        cout<<"......... 2.Delete Books.........\n";
        cout<<"......... 3.List of books.........\n";
        cout<<"......... 4.Main Menu.........\n";

        cin>> option;
        adminLogFlag=true;

        switch(option){
            case 1: addbooks();
                    return;
            case 2: DeleteBook();
                    return;
            case 3: availableBook_list();
                return;
            case 4: menu();
            default: { 
                cout<<"input not valid.\n";
                menu();
            }

    }
}

}

bool VerifyPass(){
    bool validUsername = false; 
    bool validPassword = false;
    int line=0, usernameLine, counter=3;
    string s1, username, password;
    do{
        if(adminFlag){
            username = "Admin";
            cout<<"Welcome Administrator. "<<endl;
        }
        else{
        cout<<"Please enter your username: ";
        cin>>username;
        }

        cout<<"Please enter your password: ";
        cin>>password;

        lib.open("pass.txt", ios::in);

        if(!lib.is_open()){
            cout<<"could not open file";
            
            int c;
            cout<<"Do you want to return to Main Menu \n?"<<endl;
            cout<<"Press 1 for Yes\n"<<endl;
            cout<<"Press 2 for No : ";
            cin>>c;

            if(c == 1){
                return menu();
            }
            return 0;
        }
        
        while(getline(lib, s1)){ //goes through file and stores in s1.
            
            if(s1.find(username)!=string::npos){//if username is found validated.
                validUsername = true;
                usernameLine = line;

            }
            if(validUsername && (s1.find(password)!=string::npos) && usernameLine== line-1){//if pass is found in line below username then validated.
                validPassword = true;
            }
            line++;
        }
        lib.close();
        adminFlag= false;

        if(validUsername && validPassword){
            return true;
        }
        else{
            counter--;
            cout<<"Username or password is incorrect."<<endl;
            cout<<"Program will terminate on third attempt."<<endl;
        }
    }while(counter!=0);
}

void Signup(){

    int n;

    do{
        
    ifstream file;
    string username, password, line;
    bool existsFlag=false;

    cout<<"Please Enter Your Username: ";
    cin.ignore();
    getline(cin, username);
    
    cout<<"Please Enter Your Password: ";
    getline(cin, password);

    file.open("pass.txt");

    while(getline(file, line)){
        if(line.find(username)!= string::npos){
            existsFlag = true;
        }
    }
    file.close();
    if(existsFlag){
        cout<<"username not available."<<endl;
        //hamza here.
    }
    else{
        lib.open("pass.txt", ios:: app);
        if(!lib.is_open()){
        cerr<<"error opening the file";
        }
        lib<<endl<<username;
        lib<<endl<<password;
        lib.close();
        
        cout<<"You've signed up succesfully Mr."<<username<<endl;

     cout<<"Press 1 to Return to main menu "<<endl;
    cout<<"Press 2 to Create another account : ";
    cin>>n;

    }
    
    }while(n==2);

     menu();
        
    }


void StudentLogin(){
    int option;
    if(studentLogFlag || VerifyPass()){
        cout<<"......... Please Select An Option......... \n";
        cout<<"......... 1.Issue a Book.........\n";
        cout<<"......... 2.Return a Book.........\n";
        cout<<"......... 3.Main Menu.........\n";

        cin>> option;
        studentLogFlag = true;

        switch(option){
            case 1: issueBook();
                    return;
            case 2: returnBook();
                    return;
            case 3: menu();
                    return;

        }

    }
}

int checkIssue(string book){
    ifstream file;
    file.open("library.txt");
    if(!file.is_open()){
        cerr<<"could not open file";
        return 0; // need to see how to return error.

    }
    string line, chunk, check; // line will store each line from txt file as the while loop iterates through.
    cin.ignore(); //clearing buffer so that first character isnt overlooked.
    while(getline(file, line)){
        if(line.find(book)!= string::npos){//finds the position of the book in the txt file.
            stringstream stream(line); // stringstream object parses through line and divides based on whitespace.
            if(stream>>chunk>>check){ // since storage format is book bool, we use the second column to check.   
                
                if(check=="1"){
                    file.close();
                    return 1;
                }
                else if(check=="0"){
                    file.close();
                    return 0;
                }
                

            }
        }
    }
    file.close();
    cerr<<"could not find";
    return 2; // not using bool because we need three options.
    
}

void issueBook(){
    int option=2;
    string book, line, genre;
    do{ 
        cout<<"Which book would you like to issue?"<<endl;
        cin.ignore();
        getline(cin, book);
        cout<<"please specify the genre"<<endl;
        getline(cin, genre);

        lib.open("library.txt", ios::in);
        while(getline(lib, line)){
            int issued = 2;
            if(line.find(book) != string:: npos){        
                issued = checkIssue(book);
                if(issued==1){
                    lib.close();
                    cout<<"This book has already been issued."<<endl;
                    cout<<"Would you like to try another one?"<<endl;
                    cout<<"1.Try again"<<endl;
                    cout<<"2.Exit"<<endl;
                    cin>>option;  
                }
                else if(issued==0){
                    lib.close();
                    cout<<"This book has been issued to you"<<endl;
                    DeleteBookReturn(book);
                    issueAdd(book, genre);                     
                }
                else{
                    lib.close();
                    cout<<"Book does not exist in our directory. Please use - for empty space"<<endl;
                    cout<<"1.Try again"<<endl;
                    cout<<"2.Exit"<<endl;
                    cin>>option;
                }
            }
        }
            
    }
    while(option!=2);
    
}

void returnBook(){
    int c2;
    lib.open("library.txt", ios::in);
    string book,line, genre;
    bool flag=false;
    int option;
    cout<<"would you like to see the list of books?"<<endl;
    cout<<"1.Yes"<<endl;
    cout<<"2.No"<<endl;
    cin>>option;
    if(option==1){
        availableBook_list();
    }
    cout<<"Which book would you like to return?"<<endl;
    cin.ignore();
    getline(cin,book);
    cout<<"Please specify the genre as well."<<endl;
    
    getline(cin,genre);
    
    if(lib.is_open()){
        while(getline(lib,line)){
            if(line.find(book)!=string::npos){
                lib.close();
                DeleteBookReturn(book);
                returnAdd(book, genre);
                flag=true;
            }
        }
        if(!flag){
            lib.close();
            cout<<"book does not exist in our directory."<<endl;
        }
    }
    else{
        cerr<<"could not open file";
    }

    cout<<"Press 1 to return to Main Menu \n"<<endl;
    cout<<"Press 2 to return another book : ";
    cin>>c2;
    if(c2 == 2 ){
        returnBook();
    }
    else if(c2 == 1){
    menu();
    }
    return;
}

void addbooks(){
    ifstream file;
    string line, book,genre;
    bool flag= false;
    int c3;

    do{
   
    cout<<"Please enter the book you would like to add"<<endl;
    cin.ignore();
    getline(cin, book);
    cout<<"Please enter the genre of the book"<<endl;
    getline(cin, genre);

    book.erase(remove_if(book.begin(), book.end(), ::isspace), book.end());//only used algoritm header file to do remove if. this is done to remove whitespace.
    genre.erase(remove_if(genre.begin(), genre.end(), ::isspace), genre.end());
    
    file.open("library.txt");
    if(!file.is_open()){
        cerr<<"could not open file"<<endl;
    }
    else{
        
        while(getline(file, line)){
            if(line.find(book)!=string::npos){
                cout<<"book already exists."<< endl;
                flag=true;
            }
            
        }
        file.close();
        if(flag==false){
            lib.open("library.txt", ios::app);
                lib<<book<<" 0 "<<genre;
                lib.close();
        
            
        }
    }
    cout<<"Press 1 to Add another book  "<<endl;
    cout<<"Press 2 Return to Main Menu : ";
    cin>>c3;

    }while(c3 == 1);

    menu();

    return;
    
    
}
void returnAdd(string book, string genre){
    lib.open("library.txt", ios::app);
    lib<<book<<" 0 "<<genre;
    lib.close();
}

void issueAdd(string book, string genre){
    lib.open("library.txt", ios::app);
    if(lib.is_open()){
    lib<<book<<" 1 "<<genre<<endl;
    }
    else{
        cerr<<"could not open file"<<endl;
    }
    lib.close();
    return;
            
}
void DeleteBook() {
    string bookName;
    ofstream tempFile;
    int c4;

    do{

    // enter book name to delete
    cout << "Enter the name of the book to delete: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, bookName);

    // Open the original file to read existing books
    lib.open("library.txt", ios::in);
    if (!lib.is_open()) {
        cout << "Error opening the file" << endl;
        return;
    }

    // make a temp file to write remaining books
    tempFile.open("temp.txt");
    if (!tempFile.is_open()) {
        cout << "Error creating temporary file" << endl;
        lib.close();
        return;
    }

    string line;
    bool found = false;

    //each line is read and writeen to the temp. file if it doesnt match the book we want to delte 
    while (getline(lib, line)) {
        if (line.find(bookName) == string::npos) {
            tempFile << line << endl; // Write back the book if it doesn't match
        } else {
            found = true; // Book found for deletion
        }
    }

    lib.close();
    tempFile.close();

    // Replace the original file with the temporary file
    remove("library.txt"); // Delete the original file
    rename("temp.txt", "library.txt"); // Rename the temporary file

    if (found) {
        cout << "Book deleted successfully: " << bookName << endl;
    } else {
        cout << "Book not found: " << bookName << endl;
    }

     cout<<"Press 1 to Delete Another Book "<<endl;
    cout<<"Press 2 to Return to Main Menu : ";
    cin>>c4;

    }while(c4 == 1);

    menu();

    return;
}
void DeleteBookReturn(string bookName) {
    fstream tempFile;

    // Open the original file to read existing books
    lib.open("library.txt", ios::in);
    if (!lib.is_open()) {
        cout << "Error opening the file" << endl;
        return;
    }

    // make a temp file to write remaining books
    tempFile.open("temp.txt", ios::out);
    if (!tempFile.is_open()) {
        cout << "Error creating temporary file" << endl;
        lib.close();
        return;
    }

    string line;

    //each line is read and writeen to the temp. file if it doesnt match the book we want to delte 
    while (getline(lib, line)) {
        if (line.find(bookName) == string::npos) {
            tempFile << line << endl; // Write back the book if it doesn't match
        }
    }

    lib.close();
    tempFile.close();

    // Replace the original file with the temporary file
    remove("library.txt"); // Delete the original file
    rename("temp.txt", "library.txt"); // Rename the temporary file

   return;
}

void availableBook_list(){
    ifstream file;
    //open file in read mode 
    file.open("library.txt", ios::in);

    //check if file exists
    if (!file.is_open()) {

        cout << "could not open file." << endl;

    }
    int option;
    string genre;
    cout<<"Would you like to see:"<<endl;
    cout<<"1.All Books"<<endl;
    cout<<"2.Issued Books"<<endl;
    cout<<"3.Available Books"<<endl;
    cout<<"4.By genre"<<endl;
    cin>>option;
    if(option==0 || option>4){
        cout<<"invalid input";
        return;
    }
    else if(option==4){
        cout<<"please specify the genre for search: ";
        cin>>genre;
    }



    //Header of book list
    cout << "<<--- Books List --->>"<<endl;
    cout << "Title  " << endl;
    cout<<endl;
    
    string line;
    int c2;
    while(getline(file, line)){

        //string stream "info" that stores data of variable "line"
        stringstream info(line);
        string disp, issuetag, Genre;
        //variable "info" stores inside "disp" and prints contents of the books seprately 
        if (info>>disp>>issuetag>>Genre) {
            switch (option){
            case 1: cout<<disp<<"\t"<<Genre<<endl;
            break;
            case 2: if(issuetag== "1"){
                    cout << disp <<"\t"<<Genre<<endl;
            }
            break;
            case 3: if(issuetag=="0"){
                cout << disp <<"\t"<<Genre<<endl;
            }
            break;
            case 4: if(Genre==genre){
                cout<<disp<<"\t"<<Genre<<endl;
            }
            break;
            
            }
        }
    }
    //close file after reading 
    file.close();

     cout<<endl;
                cout<<"Do you want to return to Main Menu ?"<<endl;
                cout<<"Press 1 for Main Menu "<<endl;
                cout<<"Press 2 to go Back :";
                cout<<"Press 3 to Exit :";
                cin>>c2;

                if(c2 == 3){
                    return;
                }
                else if(c2 == 2){
                    AdminLogin();
                }
    
                 menu();    

}
