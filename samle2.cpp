#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class movie {
    int movie_number;
    string movie_name;
    string movie_actor;
    int rating;
    int price;
    int seat_available;

public:
    void menu();
    void admin();
    void user();
    void insert_details();
    void delete_details();
    void edit_details();
    void display();
    void append_details();
    void movie_details();

    float calculate_price(int movie_number, int num_seats);
    void receipt(int movie_number, int num_seats, float total_price);
    void update_seat_availability(int movie_number, int booked_seats);


};

void movie::menu() {
    int choice, admin_user;
    string username, password;

    cout << "\n\n\t\t\t\t \tW E L C O M E  T O  M U L T I P L E X  T H E A T E R\n";
    cout << "\t\t\t\t ____________________________________________________________________";
    cout <<"\n\n\t\t\t\t1. Enter booking ";
    cout <<"\n\t\t\t\t2. Exit\n\n";
    cout <<"\t\t\t\tENTER YOUR CHOICE :";
    cin >> choice;

    if (choice == 1) {
        cout<<"\n\n\t\t\t\tIf you are admin please enter 1 otherwise enter 2\n";
        cout<<"\n\t\t\t\t1. Administration\n";
        cout <<"\t\t\t\t2. User\n";
        cout << "\t\t\t\tENTER YOUR CHOICE : ";
        cin >> admin_user;

        switch (admin_user) {
            case 1:
                cout << "\n\n\t\t\t\tPlease login your  credientials \n";
                cout << "\t\t\t\tEnter the username: ";
                cin >> username;
                cout << "\t\t\t\tEnter the password: ";
                cin >> password;

                if (username == "soundappan" && password == "123") {
                    cout<<"\n\n\t\t\t\t\t\tSuccessfully!!!!...... You have logged in as administration\n";
                    admin();
                } else {
                    cout << "\n\n\t\t\t\t\t\tInvalid login\n";
                }
                break;

            case 2:
                
                user();
                break;

            default:
                cout << "\t\t\t\tPlease select a correct option\n";
        }
    } else if(choice==2){
        cout << "Exit\n";
        exit(0);
    }else{
        cout << "\n\t\t\t\t\tenter vaild option";
    }
}
// ADMIN MENU BAR
void movie::admin() {
    int admin_option;
    string yes_or_no;

    do {
        cout << "\n\t\t\t\tMENU\n";
        cout << "\t\t\t\t-----\n";
        cout << "\t\t\t\t1) Input movies\n";
        cout << "\t\t\t\t2) Delete a movie\n";
        cout << "\t\t\t\t3) Append a movie\n";
        cout << "\t\t\t\t4) Edit a movie\n";
        cout << "\t\t\t\t5) Display all movies\n";
        cout << "\t\t\t\tDo you want to continue? (yes/no): ";
        cin >> yes_or_no;

        if (yes_or_no == "no") {
            cout << "\t\t\t\tExit\n";
            exit(0);
        } else if (yes_or_no == "yes") {
            cout << "\n\t\t\t\tENTER YOUR CHOICE: ";
            cin >> admin_option;

            switch (admin_option) {
                case 1:
                    insert_details();
                    break;
                case 2:
                    delete_details();
                    break;
                case 3:
                    append_details();
                    break;
                case 4:
                    edit_details();
                    break;
                case 5:
                    display();
                    break;
                default:
                    cout << "\n\t\t\t\tInvalid option. Please select a valid option.\n";
                    break;
            }
        } else {
            cout << "\t\t\t\tPlease enter a valid option.\n";
        }
    } while (yes_or_no == "yes" && (admin_option < 1 || admin_option > 5));
}


// USER
void movie::user() {
    string option;
    bool bookAnother = true;
    movie_details();
    do {
        
        cout << "\t\t\t\tAre you sure you want to proceed with booking a ticket? (yes or no): ";
        cin >> option;

        if (option == "yes") {
            int movie_choice, num_seats;
            cout << "\t\t\t\tEnter the movie number you want to book: ";
            cin >> movie_choice;

            ifstream file("database.txt");
            int c, r, s, p;
            string n, a;
            bool movie_found = false;

            while (file >> c >> n >> a >> r >> p >> s) {
                if (c == movie_choice) {
                    movie_found = true;
                    cout << "\t\t\t\tEnter the number of seats you want to book: ";
                    cin >> num_seats;

                    if (s >= num_seats) {
                        float total_price = calculate_price(movie_choice, num_seats);
                        cout << "\t\t\t\tTotal price for " << num_seats << " seat(s) is: $" << total_price << endl;
                        cout << "\t\t\t\tSelect payment mode (1 - Cash, 2 - Credit Card, 3 - Debit Card): ";
                        int payment_mode;
                        cin >> payment_mode;
                        receipt(movie_choice, num_seats, total_price);
                        cout << "\t\t\t\t\tBooking successful!!!........ Enjoy the movie!\n";
                        update_seat_availability(movie_choice, num_seats); // Update seat availability
                    } else {
                        cout << "\t\t\t\tSorry, only " << s << " seats are available for this movie.\n";
                    }
                    break;
                }
            }

            if (!movie_found) {
                cout << "\t\t\t\tMovie not found. Please enter a valid movie number.\n";
            }
        } else if (option == "no") {
            cout << "\t\t\t\tThanks for visiting the theater.\n";
            break; 
        } else {
            cout << "\t\t\t\tInvalid option. Please enter 'yes' or 'no'.\n";
        }

        string choice;
        cout << "\t\t\t\tDo you want to book another ticket? (yes or no): ";
        cin >> choice;
        if (choice == "no") {
            cout << "\t\t\t\tThanks for visiting the theater.\n";
            bookAnother = false;
        }

    } while (bookAnother);
}


// displaying movie details for user
void movie::movie_details() {
    ifstream f("database.txt");
    int c, r, s, p;
    string n, a;

    if (!f.is_open()) {
        cout << "File not found or unable to open\n";
    } else {
        cout << "\n\n\t\t\t\t================================ Movie Records ==============================\n";
        cout<<"\n";
         cout << "\t\t\t\tmovie number " << " movie name " << "  movie actor " << "rating " <<"  price   "<<"seat available " <<"\n";
         cout << "\t\t\t\t------------  ----------  -----------  ------   -------  --------------\n";
        while (f >> c >> n >> a >> r >> p >> s) {
           
            cout <<"\t\t\t\t"<< c<<"\t\t" << n <<"\t\t"<< a <<"\t"<< r <<"\t"<< p <<" "<<"   \t"<< s <<"\n";
           
        }
        cout << "\t\t\t\t==============================================================================\n";
        cout<<"\n";
        f.close();
    }
    
    
}
// Price calculation based on the selected movie and number of seats
float movie::calculate_price(int movie_number, int num_seats) {
    ifstream file("database.txt");
    int c, r, s, p;
    string n, a;
    float price = 0.0;

    while (file >> c >> n >> a >> r >> p >> s) {
        if (c == movie_number) {
            price = p * num_seats; 
            break;
        }
    }

    file.close();
    return price;
}
// displaying receipt once user booked ticket
void movie::receipt(int movie_number, int num_seats, float total_price) {
    ofstream receipt("receipt.txt", ios::app);
    ifstream file("database.txt");
    int c, r, s, p;
    string n, a;

    receipt << "================== Movie Ticket Receipt ==================\n";
    receipt << "Movie Details:\n";
    while (file >> c >> n >> a >> r >> p >> s) {
        if (c == movie_number) {
            receipt << "Movie Number    : " << c << "\n";
            receipt << "Movie Name      : " << n << "\n";
            receipt << "Movie Actor     : " << a << "\n";
            receipt << "Number of Seats : " << num_seats << "\n";
            receipt << "Total Price     : $" << total_price << "\n";
            break;
        }
    }
    receipt << "=========================================================\n\n";

    file.close();
    receipt.close();
}

void movie::update_seat_availability(int movie_number, int booked_seats) {
    ifstream file("database.txt");
    int c, r, s, p;
    string n, a;
    ofstream temp("temp.txt");

    while (file >> c >> n >> a >> r >> p >> s) {
        if (c == movie_number) {
            s =s - booked_seats; // Updating available seats after booking
        }
        temp << c << " " << n << " " << a << " " << r << " " << p << " " << s << "\n";
    }

    file.close();
    temp.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

}

// admin create a movie are available in theater
void movie::insert_details() {
    fstream f;
    int c, r, s, p;
    string n, a;
    cout << "\t\t\t\t\tC R E A T E   T H E   M O  V I E   D E T A I L S \n";
    cout << "\t\t\t\t---------------------------------------------------------\n\n";
    for (int i = 0; i < 1; ++i) {
    int token = 0;
    
    cout << "\n\t\t\t\tEnter the movie number        : ";
    cin >> movie_number;
    cout << "\t\t\t\tEnter movie name              : ";
    cin >> movie_name;
    cout << "\t\t\t\tEnter actor name              : ";
    cin >> movie_actor;
    cout << "\t\t\t\tEnter rating (on 10)          : ";
    cin >> rating;
    cout << "\t\t\t\tEnter price                   : ";
    cin >> price;
    cout << "\t\t\t\tEnter no. of seats available  : ";
    cin >> seat_available;

    f.open("database.txt", ios::in);
    if (!f) {
        f.open("database.txt", ios::app | ios::out);
        f<<"movie_id"<<" "<<"movie_name"<<" "<<"movie actor"<<" "<<"rating"<<" "<<"price"<<" "<<"seat"<<" "<<"\n";
        f  << movie_number  << movie_name  << movie_actor  << rating  << price  << seat_available << "\n";
        f.close();
        cout << "\n\t\t\tSuccessfully recorded inserted\n";
    } else {
        while (f >> c >> n >> a >> r >> p >> s) {
            if (c == movie_number) {
                token = 1;
                break;
            }
        }
        f.close();

        if (token == 1) {
            cout << "\t\t\t\tMovie with the same number already exists\n";
        } else {
            f.open("database.txt", ios::app | ios::out);
            
            f  << movie_number <<" " << movie_name  << " " << movie_actor <<" " << rating  <<" "<< price <<" " << seat_available << "\n";
            f.close();
            cout << "\n\t\t\t\t\tSuccessfully recorded inserted\n";
        }
    }
}
admin();
}
// upadating movie details 
void movie::edit_details() {
    fstream f;
    int c, r, s, p;
    string n, a;
    int found = 0;
    cout << "\t\t\t\t\tE D I T   T H E   M O  V I E   D E T A I L S \n";
    cout << "\t\t\t\t---------------------------------------------------------\n\n";
    cout << "\n\t\t\t\tEnter the movie number to edit: ";
    cin >> movie_number;

    f.open("database.txt", ios::in | ios::out);
    if (!f) {
        cout << "File not found!\n";
    } else {
        while (f >> c >> n >> a >> r >> p >> s) {
            if (c == movie_number) {
                found = 1;
                cout << "\n\t\t\t\tEnter the movie number      : ";
                cin >> movie_number;
                cout << "\t\t\t\tEnter movie name              : ";
                cin >> movie_name;
                cout << "\t\t\t\tEnter actor name              : ";
                cin >> movie_actor;
                cout << "\t\t\t\tEnter rating (on 10)          : ";
                cin >> rating;
                cout << "\t\t\t\tEnter price                   : ";
                cin >> price;
                cout << "\t\t\t\tEnter no. of seats available  : ";
                cin >> seat_available;

                f.seekp(f.tellg()); // Move the pointer to the current position for writing
                f << movie_number <<" " << movie_name <<" "<< movie_actor <<" " << rating <<" " << price <<" " << seat_available << "\n";
                cout << "\n\t\t\t\tDetails updated successfully\n";
                break;
            }
        }
        f.close();

        if (found == 0) {
            cout << "Movie not found\n";
        }
    }
    
    admin();
}

void movie::delete_details() {
    fstream f;
    int c, r, s, p;
    string n, a;
    int found = 0;
    int delete_id;

    cout << "\n\n\t\t\t\tEnter the movie number to delete: ";
    cin >> delete_id;

    f.open("database.txt", ios::in | ios::out);
    if (!f) {
        cout << "File not found!\n";
    } else {
        fstream temp;
        temp.open("temp.txt", ios::out);

        while (f >> c >> n >> a >> r >> p >> s) {
            if (c == delete_id) {
                found = 1;
                cout << "\t\t\t\tRecord deleted successfully\n";
            } else {
                temp <<  c <<" " << n  <<" "<< a  <<" "<< r  <<" "<< p  <<" "<< s << "\n";
            }
        }
        f.close();
        temp.close();

        remove("database.txt");
        rename("temp.txt", "database.txt");

        if (found == 0) {
            cout << "Movie not found\n";
        }
    }
    admin();
}

// appending the movie details in end 
void movie::append_details() {
    ofstream f;
    f.open("database.txt", ios::app);
    
    if (!f.is_open()) {
        cout << "Error opening file!\n";
    } else {
        cout << "\t\t\t\t\tU P D A T E   T H E   M O  V I E   D E T A I L S \n";
        cout << "\t\t\t\t---------------------------------------------------------\n\n";
        cout << "\n\t\t\t\tEnter the movie number      : ";
        cin >> movie_number;
        cout << "\t\t\t\tEnter movie name              : ";
        cin >> movie_name;
        cout << "\t\t\t\tEnter actor name              : ";
        cin >> movie_actor;
        cout << "\t\t\t\tEnter rating (on 10)          : ";
        cin >> rating;
        cout << "\t\t\t\tEnter price                   : ";
        cin >> price;
        cout << "\t\t\t\tEnter no. of seats available  : ";
        cin >> seat_available;

        f << movie_number<<" " << movie_name <<" "<< movie_actor <<" " << rating <<" " << price <<" " << seat_available << "\n";
        cout << "\n\t\t\t\t\t\tRecord added successfully!\n";
        f.close();
    }
    admin();
}
// display details 
void movie::display() {
    ifstream f("database.txt");
    int c, r, s, p;
    string n, a;

    if (!f.is_open()) {
        cout << "File not found or unable to open\n";
    } else {
        cout << "\n\n\t\t\t\t================================ Movie Records ==============================\n";
        cout<<"\n";
         cout << "\t\t\t\tmovie number " << " movie name " << "  movie actor " << "rating " <<"  price   "<<"seat available " <<"\n";
         cout << "\t\t\t\t------------  ----------  -----------  ------   -------  --------------\n";
        while (f >> c >> n >> a >> r >> p >> s) {
           
            cout <<"\t\t\t\t"<< c<<"\t\t" << n <<"\t\t"<< a <<"\t"<< r <<"\t"<< p <<" "<<"   \t"<< s <<"\n";
           
        }
        cout << "\t\t\t\t==============================================================================\n";
        cout<<"\n";
        f.close();
    }
    admin();
    
}

int main() {
    movie m;
    m.menu();
    return 0;
}
