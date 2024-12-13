#include<iostream>
#include<fstream>
#include<string>

using namespace std;

fstream lib;
int menu();
void AdminLogin();
bool VerifyPass();
void StudentLogin();
void Signup();

int main(){
    menu();
    
}
int menu(){
    int option;

    cout<<".........Please Select An Option......... \n";
    cout<<"......... 1.Admin login.........\n";
    cout<<"......... 2.Student login.........\n";
    cout<<"......... 3.Student SignUp.........\n";
    cin>> option;

    switch(option){
        case 1: AdminLogin();
                return 0;
        // case 2: StudentLogin();
                return 0;
        case 3: Signup();
            return 0;
    }
    return 0;
}
void AdminLogin(){

    int option;
    if(VerifyPass()){
        cout<<".........Please Select An Option......... \n";
        cout<<"......... 1.Add Books.........\n";
        cout<<"......... 2.Delete Books.........\n";
        cout<<"......... 3.List of Issued books.........\n";
        cout<<"......... 4.Search Books.........\n";
        cin>> option;

        // switch(option){
        //     case 1: AdminLogin();
        //             return 0;
        //     case 2: StudentLogin();
        //             return 0;
        //     case 3: Signup();
        //         return 0;
    }

    }

bool VerifyPass(){
    bool validUsername = false; 
    bool validPassword = false ;
    int line=0, usernameLine;
    string s1, username, password;

    cout<<"Please enter your username: ";
    cin>>username;

    cout<<"Please enter your password: ";
    cin>>password;

    lib.open("library.txt", ios::in);

    if(!lib.is_open()){
        cout<<"could not open file";
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
    cout<<validUsername<<" "<<validPassword;
    if(validUsername && validPassword){
        return true;
    }
    else{
        return false;
    }
}

void Signup(){
    string username, password;
    lib.open("library.txt", ios:: app);

    if(!lib.is_open()){
        cout<<"error opening the file";
    }

    cout<<"Please Enter Your Username: ";
    cin.ignore();
    getline(cin, username);
    lib<<username<<endl;
    
    cout<<"Please Enter Your Password: ";
    getline(cin, password);
    lib<<password<<endl;
    

    lib.close();
    
    cout<<"You've signed up succesfully Mr."<<username;
    int menu();
    return;

}
void StudentLogin(){
    int option;
    if(VerifyPass){
        cout<<".........Please Select An Option......... \n";
        cout<<"......... 1.Admin login.........\n";
        cout<<"......... 2.Student login.........\n";
        cout<<"......... 3.Student SignUp.........\n";
        cin>> option;

        // switch(option){
        //     case 1: AdminLogin();
        //             return 0;
        //     case 2: StudentLogin();
        //             return 0;
        //     case 3: Signup();
        //         return 0;

    }
}
void AddBook() {
    string bookName;
    lib.open("books.txt", ios::app); // open in ammend mode

    if (!lib.is_open()) {
        cout << "Error opening the file" << endl;
        return;
    }

    cout << "Enter the name of the book to add: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, bookName);
    lib << bookName << " 0" << endl; // Store book with 0 copies initially

    lib.close();
    cout << "Book added successfully: " << bookName << endl;
}
void DeleteBook() {
    string bookName;
    fstream lib, tempFile;

    // enter book name to delete
    cout << "Enter the name of the book to delete: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, bookName);

    // Open the original file to read existing books
    lib.open("books.txt", ios::in);
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
    remove("books.txt"); // Delete the original file
    rename("temp.txt", "books.txt"); // Rename the temporary file

    if (found) {
        cout << "Book deleted successfully: " << bookName << endl;
    } else {
        cout << "Book not found: " << bookName << endl;
    }
}
