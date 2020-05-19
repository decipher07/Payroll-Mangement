#include <iostream.h>

#include <fstream.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <ctype.h>

#include <conio.h>

#include <dos.h>

class MENU {
  public:
    void MAIN_MENU();

  void EDIT_MENU();
  void INTRODUCTION();
}
M;

class EMPLOYEE {
  public:
    void NEW_EMPLOYEE();
  void MODIFICATION();
  void DELETION();
  void DISPLAY();
  void LIST();
  void SALARY_SLIP();
  private:
    void ADD_RECORD(int, char[], char[], char[], int, int, int, char[], char, char, char, float, float);
  void MODIFY_RECORD(int, char[], char[], char[], char[], char, char,
    char, float, float);
  void DELETE_RECORD(int);
  int LASTCODE();
  int RECORDNO(int);
  int FOUND_CODE(int);
  void DISPLAY_RECORD(int);
  int VALID_DATE(int, int, int);
  int code, dd, mm, yy;
  char name[31], address[41], phone[10], desig[21];
  char grade, house, conveyence;
  float loan, basic;
}
E;
void MENU::INTRODUCTION() {

  cout << "\nWELCOME\n";
  cout << "\n*****************\n  ";
  cout << "  ";
  cout << "\nTHIS IS PAYROLL MANAGEMENT SYSTEM OF SAFAL INTERNATIONAL \n  ";
  cout << "  ";
  cout << "  ";
  cout << "  ";
  cout << "  ";

  cout << "\n PRESS ANY KEY TO CONTINUE....\n";
  getch();
  clrscr();
  gotoxy(8, 2);
  cout << "            ABOUT THE COMPANY   \n\n";
  cout << "    The Company SAFAL INTERNATIONAL was established.\n";
  cout << "    in the year 1997,the prime business of company \n";
  cout << "    is distribution of MEDICINES.\n";
  cout << "    The company has been a leading company in\n";
  cout << "    and is striving to continue the tradition";
  gotoxy(2, 25);
  cout << "PRESS ANY KEY TO CONTINUE ....";
  getch();
  clrscr();
}
void MENU::MAIN_MENU() {
  char ch;
  while (1) {
    clrscr();
    gotoxy(28, 8);
    cout << "SAFAL INTERNATIONAL\n ";
    gotoxy(20, 9);
    cout << "************************************";
    gotoxy(30, 11);
    cout << "1: NEW EMPLOYEE";
    gotoxy(30, 12);
    cout << "2: DISPLAY EMPLOYEE";
    gotoxy(30, 13);
    cout << "3: LIST OF EMPLOYEES";
    gotoxy(30, 14);
    cout << "4: SALARY SLIP";
    gotoxy(30, 15);
    cout << "5: EDIT";
    gotoxy(30, 16);
    cout << "0: QUIT";
    gotoxy(30, 18);
    cout << "ENTER YOUR CHOICE :";
    ch = getch();
    if (ch == 27 || ch == '0')
      break;
    else
    if (ch == '1')
      E.NEW_EMPLOYEE();
    else
    if (ch == '2')
      E.DISPLAY();
    else
    if (ch == '3')
      E.LIST();
    else
    if (ch == '4')
      E.SALARY_SLIP();

    else
    if (ch == '5')
      EDIT_MENU();
  }
}

void MENU::EDIT_MENU() {
  char ch;
  while (1) {
    clrscr();
    gotoxy(31, 9);
    cout << "E D I T  M E N U";
    gotoxy(30, 13);
    cout << "1: DELETE RECORD";
    gotoxy(30, 14);
    cout << "2: MODIFY RECORD";
    gotoxy(30, 15);
    cout << "0: EXIT";
    gotoxy(30, 17);
    cout << "ENTER YOUR CHOICE :";
    ch = getch();
    if (ch == 27 || ch == '0')
      break;
    else
    if (ch == '1')
      E.DELETION();
    else
    if (ch == '2')
      E.MODIFICATION();
  }
}
void EMPLOYEE::ADD_RECORD(int ecode, char ename[31], char eaddress[41],
  char ephone[10], int d, int m, int y, char edesig[21], char egrade, char ehouse, char econv, float eloan, float ebasic) {
  fstream file;
  file.open("EMPLOYEE.dat", ios::app);
  code = ecode;
  strcpy(name, ename);
  strcpy(address, eaddress);
  strcpy(phone, ephone);
  dd = d;
  mm = m;
  yy = y;
  strcpy(desig, edesig);
  grade = egrade;
  house = ehouse;
  conveyence = econv;
  loan = eloan;
  basic = ebasic;
  file.write((char * ) this, sizeof(EMPLOYEE));
  file.close();
}
void EMPLOYEE::MODIFY_RECORD(int ecode, char ename[31],

  char eaddress[41],
  char ephone[10], char edesig[21], char egrade, char ehouse, char econv,
  float eloan, float ebasic) {
  int recno;
  recno = RECORDNO(ecode);
  fstream file;
  file.open("EMPLOYEE.DAT", ios::out | ios::ate);
  strcpy(name, ename);
  strcpy(address, eaddress);
  strcpy(phone, ephone);
  strcpy(desig, edesig);
  grade = egrade;
  house = ehouse;
  conveyence = econv;
  loan = eloan;
  basic = ebasic;
  int location;
  location = (recno - 1) * sizeof(EMPLOYEE);
  file.seekp(location);
  file.write((char * ) this, sizeof(EMPLOYEE));
  file.close();
}
void EMPLOYEE::DELETE_RECORD(int ecode) {
  fstream file;
  file.open("EMPLOYEE.DAT", ios:: in );
  fstream temp;
  temp.open("temp.dat", ios::out);
  file.seekg(0, ios::beg);

  while (!file.eof()) {
    file.read((char * ) this, sizeof(EMPLOYEE));
    if (file.eof())
      break;
    if (code != ecode)
      temp.write((char * ) this, sizeof(EMPLOYEE));
  }
  file.close();
  temp.close();
  file.open("EMPLOYEE.dat", ios::out);
  temp.open("temp.dat", ios:: in );
  temp.seekg(0, ios::beg);
  while (!temp.eof()) {
    temp.read((char * ) this, sizeof(EMPLOYEE));
    if (temp.eof())
      break;
    file.write((char * ) this, sizeof(EMPLOYEE));
  }
  file.close();
  temp.close();
}
int EMPLOYEE::LASTCODE() {
  fstream file;
  file.open("EMPLOYEE.dat", ios:: in );
  file.seekg(0, ios::beg);
  int count = 0;
  while (file.read((char * ) this, sizeof(EMPLOYEE)))
    count = code;
  file.close();
  return count;
}

int EMPLOYEE::FOUND_CODE(int ecode) {
  fstream file;
  file.open("EMPLOYEE.dat", ios:: in );
  file.seekg(0, ios::beg);
  int found = 0;
  while (file.read((char * ) this, sizeof(EMPLOYEE))) {
    if (code == ecode) {
      found = 1;
      break;
    }
  }
  file.close();
  return found;
}
int EMPLOYEE::RECORDNO(int ecode) {
  fstream file;
  file.open("EMPLOYEE.dat", ios:: in );
  file.seekg(0, ios::beg);
  int recno = 0;
  while (file.read((char * ) this, sizeof(EMPLOYEE))) {
    recno++;
    if (code == ecode)
      break;
  }
  file.close();
  return recno;
}
void EMPLOYEE::LIST() {
  clrscr();
  int row = 6, found = 0, flag = 0;
  char ch;
  gotoxy(31, 2);
  cout << "LIST OF EMPLOYEES";
  gotoxy(30, 3);
  cout << "~~~~~~~~~~~~~~~~~~~";
  gotoxy(1, 4);
  cout << "CODE NAME                     PHONE      DOJ      DESIGNATION   GRADE   SALARY";
  gotoxy(1, 5);
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  fstream file;
  file.open("EMPLOYEE.dat", ios:: in );
  file.seekg(0, ios::beg);
  while (file.read((char * ) this, sizeof(EMPLOYEE))) {
    flag = 0;
    found = 1;
    gotoxy(2, row);
    cout << code;
    gotoxy(6, row);
    cout << name;
    gotoxy(31, row);
    cout << phone;
    gotoxy(40, row);
    cout << dd << "/" << mm << "/" << yy;
    gotoxy(52, row);
    cout << desig;
    gotoxy(69, row);
    cout << grade;
    if (grade != 'E') {
      gotoxy(74, row);
      cout << basic;
    } else {
      gotoxy(76, row);
      cout << "-";
    }
    if (row == 23) {
      flag = 1;
      row = 6;
      gotoxy(1, 25);
      cout << "Press any key to continue or Press<ESC> to exit";
      ch = getch();
      if (ch == 27)
        break;
      clrscr();
    } else
      row++;
  }
  if (!found) {
    gotoxy(5, 10);
    cout << "\7Records not found";
  }
  if (!flag) {
    gotoxy(1, 25);
    cout << "Press any key to continue...";
    getch();
  }
  file.close();
}
void EMPLOYEE::DISPLAY_RECORD(int ecode) {
  fstream file;
  file.open("EMPLOYEE.dat", ios:: in );
  file.seekg(0, ios::beg);
  while (file.read((char * ) this, sizeof(EMPLOYEE))) {
    if (code == ecode) {
      gotoxy(5, 5);
      cout << "Employee Code # " << code;
      gotoxy(5, 6);
      cout << "~~~~~~~~~~~~~";
      gotoxy(5, 7);
      cout << "Name         : " << name;
      gotoxy(5, 8);
      cout << "Address      : " << address;
      gotoxy(5, 9);
      cout << "Phone no.    : " << phone;
      gotoxy(5, 11);
      cout << "JOINING DATE";
      gotoxy(5, 12);
      cout << "~~~~~~~~~~~~";
      gotoxy(5, 13);
      cout << "Day   : " << dd;
      gotoxy(5, 14);
      cout << "Month : " << mm;
      gotoxy(5, 15);
      cout << "Year  : " << yy;
      gotoxy(5, 17);
      cout << "Designation :" << desig;
      gotoxy(5, 18);
      cout << "Grade       :" << grade;
      if (grade != 'E') {
        gotoxy(5, 19);
        cout << "House (y/n)    : " << house;
        gotoxy(5, 20);
        cout << "Conveyence (y/n) : " << conveyence;
        gotoxy(5, 22);
        cout << "Basic Salary   : " << basic;
      }
      gotoxy(5, 21);
      cout << "Loan           : " << loan;
    }
  }
  file.close();
}

void EMPLOYEE::NEW_EMPLOYEE() {
  clrscr();
  char ch, egrade, ehouse = 'N', econv = 'N';
  char ename[31], eaddress[41], ephone[10], edesig[21], t1[10];
  float t2 = 0.0, eloan = 0.0, ebasic = 0.0;
  int d, m, y, ecode, valid;
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(28, 3);
  cout << "ADDITION OF NEW EMPLOYEE";
  gotoxy(5, 5);
  cout << "Employee Code #  ";
  gotoxy(5, 6);
  cout << "~~~~~~~~~~~~~";
  gotoxy(5, 7);
  cout << "Name        :";
  gotoxy(5, 8);
  cout << "Address     :";
  gotoxy(5, 9);
  cout << "Phone no.   :";
  gotoxy(5, 11);
  cout << "JOINING DATE";
  gotoxy(5, 12);
  cout << "~~~~~~~~~~~~";
  gotoxy(5, 13);
  cout << "Day   :";
  gotoxy(5, 14);
  cout << "Month :";
  gotoxy(5, 15);
  cout << "Year  :";
  gotoxy(5, 17);
  cout << "Designation:";
  gotoxy(5, 18);
  cout << "Grade      :";
  gotoxy(5, 21);
  cout << "Loan       :";
  ecode = LASTCODE() + 1;
  gotoxy(21, 5);
  cout << ecode;
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter the name of the Employee";
    gotoxy(20, 7);
    clreol();
    gets(ename);
    strupr(ename);
    if (ename[0] == '0')
      return;
    if (strlen(ename) < 1 || strlen(ename) > 30) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly (Range: 1..30)";
      getch();
    }
  } while (!valid);
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter Address of the Employee";
    gotoxy(20, 8);
    clreol();
    gets(eaddress);
    strupr(eaddress);
    if (eaddress[0] == '0')
      return;
    if (strlen(eaddress) < 1 || strlen(eaddress) > 40) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly (Range: 1..40)";
      getch();
    }
  } while (!valid);
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter Phone no. of the Employee or Press <ENTER> for none";
    gotoxy(20, 9);
    clreol();
    gets(ephone);
    if (ephone[0] == '0')
      return;
    if ((strlen(ephone) < 7 && strlen(ephone) > 0) || (strlen(ephone) > 10)) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly";
      getch();
    }
  } while (!valid);
  if (strlen(ephone) == 0)
    strcpy(ephone, "-");
  char tday[3], tmonth[3], tyear[5];
  int td;
  do {
    valid = 1;
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ENTER DAY OF JOINING";
      gotoxy(13, 13);
      clreol();
      gets(tday);
      td = atoi(tday);
      d = td;
      if (tday[0] == '0')
        return;
    } while (d == 0);
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ENTER MONTH OF JOINING";
      gotoxy(13, 14);
      clreol();
      gets(tmonth);
      td = atoi(tmonth);
      m = td;
      if (tmonth[0] == '0')
        return;
    } while (m == 0);
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ENTER YEAR OF JOINING";
      gotoxy(13, 15);
      clreol();
      gets(tyear);
      td = atoi(tyear);
      y = td;
      if (tyear[0] == '0')
        return;
    } while (y == 0);
    if (d > 31 || d < 1)
      valid = 0;
    else
    if (((y % 4) != 0 && m == 2 && d > 28) || ((y % 4) == 0 && m == 2 && d > 29))
      valid = 0;
    else
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
      valid = 0;
    else
    if (y < 1990 || y > 2020)
      valid = 0;
    if (!valid) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly";
      getch();
      gotoxy(13, 14);
      clreol();
      gotoxy(13, 15);
      clreol();
    }
  } while (!valid);
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter Designation of the Employee";
    gotoxy(20, 17);
    clreol();
    gets(edesig);
    strupr(edesig);
    if (edesig[0] == '0')
      return;
    if (strlen(edesig) < 1 || strlen(edesig) > 20) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly (Range: 1..20)";
      getch();
    }
  } while (!valid);
  do {
    gotoxy(5, 25);
    clreol();
    cout << "Enter Grade of the Employee (A,B,C,D,E){in capitals}";
    gotoxy(20, 18);
    clreol();
    egrade = getch();
    if (egrade == '0')
      return;
  } while (egrade < 'A' || egrade > 'E');
  if (egrade != 'E') {
    gotoxy(5, 19);
    cout << "House (y/n)    : ";
    gotoxy(5, 20);
    cout << "Conveyence(y/n): ";
    gotoxy(5, 22);
    cout << "Basic Salary   : ";
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ENTER IF HOUSE ALLOWANCE IS ALLOTED TO EMPLOYEE OR NOT";
      gotoxy(22, 19);
      clreol();
      ehouse = getche();
      ehouse = toupper(ehouse);
      if (ehouse == '0')
        return;
    } while (ehouse != 'Y' && ehouse != 'N');
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ENTER IF CONVEYENCE ALLOWANCE IS ALLOTED TO EMPLOYEE OR NOT";
      gotoxy(22, 20);
      clreol();
      econv = getche();
      econv = toupper(econv);
      if (econv == '0')
        return;
    } while (econv != 'Y' && econv != 'N');
  }
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "ENTER LOAN AMOUNT IF ISSUED";
    gotoxy(22, 21);
    clreol();
    gets(t1);
    t2 = atof(t1);
    eloan = t2;
    if (eloan > 50000) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7SHOULD NOT GREATER THAN 50000";
      getch();
    }
  } while (!valid);
  if (egrade != 'E') {
    do {
      valid = 1;
      gotoxy(5, 25);
      clreol();
      cout << "ENTER BASIC SALARY OF THE EMPLOYEE";
      gotoxy(22, 22);
      clreol();
      gets(t1);
      t2 = atof(t1);
      ebasic = t2;
      if (t1[0] == '0')
        return;
      if (ebasic > 50000) {
        valid = 0;
        gotoxy(5, 25);
        clreol();
        cout << "\7SHOULD NOT GREATER THAN 50000";
        getch();
      }
    } while (!valid);
  }
  gotoxy(5, 25);
  clreol();
  do {
    gotoxy(5, 24);
    clreol();
    cout << "Do you want to save (y/n) ";
    ch = getche();
    ch = toupper(ch);
    if (ch == '0')
      return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N')
    return;
  ADD_RECORD(ecode, ename, eaddress, ephone, d, m, y, edesig, egrade, ehouse, econv, eloan, ebasic);
}

void EMPLOYEE::DISPLAY() {
  clrscr();
  char t1[10];
  int t2, ecode;
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(5, 5);
  cout << "Enter code of the Employee  ";
  gets(t1);
  t2 = atoi(t1);
  ecode = t2;
  if (ecode == 0)
    return;
  clrscr();
  if (!FOUND_CODE(ecode)) {
    gotoxy(5, 5);
    cout << "\7Record not found";
    getch();
    return;
  }
  DISPLAY_RECORD(ecode);
  gotoxy(5, 25);
  cout << "Press any key to continue...";
  getch();
}
void EMPLOYEE::MODIFICATION() {
  clrscr();
  char ch, egrade, ehouse = 'N', econv = 'N';
  char ename[31], eaddress[41], ephone[10], edesig[21], t1[10];
  float t2 = 0.0, eloan = 0.0, ebasic = 0.0;
  int ecode, valid;
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(5, 5);
  cout << "Enter code of the Employee  ";
  gets(t1);
  t2 = atoi(t1);
  ecode = t2;
  if (ecode == 0)
    return;
  clrscr();
  if (!FOUND_CODE(ecode)) {
    gotoxy(5, 5);
    cout << "\7Record not found";
    getch();
    return;
  }
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(22, 3);
  cout << "MODIFICATION OF THE EMPLOYEE RECORD";
  DISPLAY_RECORD(ecode);
  do {
    gotoxy(5, 24);
    clreol();
    cout << "Do you want to modify this record (y/n) ";
    ch = getche();
    ch = toupper(ch);
    if (ch == '0')
      return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N')
    return;
  clrscr();
  fstream file;
  file.open("EMPLOYEE.DAT", ios:: in );
  file.seekg(0, ios::beg);
  while (file.read((char * ) this, sizeof(EMPLOYEE))) {
    if (code == ecode)
      break;
  }
  file.close();
  gotoxy(5, 5);
  cout << "Employee Code # " << ecode;
  gotoxy(5, 6);
  cout << "~~~~~~~~~~~~~";
  gotoxy(40, 5);
  cout << "JOINING DATE : ";
  gotoxy(40, 6);
  cout << "~~~~~~~~~~~~~~";
  gotoxy(55, 5);
  cout << dd << "/" << mm << "/" << yy;
  gotoxy(5, 7);
  cout << "Name           : ";
  gotoxy(5, 8);
  cout << "Address        : ";
  gotoxy(5, 9);
  cout << "Phone no.      : ";
  gotoxy(5, 10);
  cout << "Designation    : ";
  gotoxy(5, 11);
  cout << "Grade          : ";
  gotoxy(5, 14);
  cout << "Loan           : ";
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter the name of the Employee or <ENTER> FOR NO CHANGE";
    gotoxy(20, 7);
    clreol();
    gets(ename);
    strupr(ename);
    if (ename[0] == '0')
      return;
    if (strlen(ename) > 25) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly (Range: 1..30)";
      getch();
    }
  } while (!valid);
  if (strlen(ename) == 0) {
    strcpy(ename, name);
    gotoxy(20, 7);
    cout << ename;
  }
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter Address of the Employee or <ENTER> FOR NO CHANGE";
    gotoxy(20, 8);
    clreol();
    gets(eaddress);
    strupr(eaddress);
    if (eaddress[0] == '0')
      return;
    if (strlen(eaddress) > 30) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly (Range: 1..40)";
      getch();
    }
  } while (!valid);
  if (strlen(eaddress) == 0) {
    strcpy(eaddress, address);
    gotoxy(20, 8);
    cout << eaddress;
  }
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter Phone no. of the Employee or or <ENTER> FOR NO CHANGE";
    gotoxy(20, 9);
    clreol();
    gets(ephone);
    if (ephone[0] == '0')
      return;
    if ((strlen(ephone) < 7 && strlen(ephone) > 0) || (strlen(ephone) > 9)) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly";
      getch();
    }
  } while (!valid);
  if (strlen(ephone) == 0) {
    strcpy(ephone, phone);
    gotoxy(20, 9);
    cout << ephone;
  }
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "Enter Designation of the Employee or <ENTER> FOR NO CHANGE";
    gotoxy(20, 10);
    clreol();
    gets(edesig);
    strupr(edesig);
    if (edesig[0] == '0')
      return;
    if (strlen(edesig) > 15) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7Enter correctly (Range: 1..15)";
      getch();
    }
  } while (!valid);
  if (strlen(edesig) == 0) {
    strcpy(edesig, desig);
    gotoxy(20, 10);
    cout << edesig;
  }
  do {
    gotoxy(5, 25);
    clreol();
    cout << "Enter Grade of the Employee (A,B,C,D,E) or <ENTER> FOR NO CHANGE";
    gotoxy(20, 11);
    clreol();
    egrade = getche();
    egrade = toupper(egrade);
    if (egrade == '0')
      return;
    if (egrade == 13) {
      egrade = grade;
      gotoxy(20, 11);
      cout << grade;
    }
  } while (egrade < 'A' || egrade > 'E');
  if (egrade != 'E') {
    gotoxy(5, 12);
    cout << "House (y/n)    : ";
    gotoxy(5, 13);
    cout << "Conveyence (y/n) : ";
    gotoxy(5, 15);
    cout << "Basic Salary   : ";
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ALLOTED HOUSE ALLOWANCE ? or <ENTER> FOR NO CHANGE";
      gotoxy(22, 12);
      clreol();
      ehouse = getche();
      ehouse = toupper(ehouse);
      if (ehouse == '0')
        return;
      if (ehouse == 13) {
        ehouse = house;
        gotoxy(22, 12);
        cout << ehouse;
      }
    } while (ehouse != 'Y' && ehouse != 'N');
    do {
      gotoxy(5, 25);
      clreol();
      cout << "ALLOTED CONVEYENCE ALLOWANCE or <ENTER> FOR NO CHANGE";
      gotoxy(22, 13);
      clreol();
      econv = getche();
      econv = toupper(econv);
      if (econv == '0')
        return;
      if (econv == 13) {
        econv = conveyence;
        gotoxy(22, 13);
        cout << econv;
      }
    } while (econv != 'Y' && econv != 'N');
  }
  do {
    valid = 1;
    gotoxy(5, 25);
    clreol();
    cout << "ENTER LOAN AMOUNT or <ENTER> FOR NO CHANGE";
    gotoxy(22, 14);
    clreol();
    gets(t1);
    t2 = atof(t1);
    eloan = t2;
    if (eloan > 50000) {
      valid = 0;
      gotoxy(5, 25);
      clreol();
      cout << "\7SHOULD NOT GREATER THAN 50000";
      getch();
    }
  } while (!valid);
  if (strlen(t1) == 0) {
    eloan = loan;
    gotoxy(22, 14);
    cout << eloan;
  }
  if (egrade != 'E') {
    do {
      valid = 1;
      gotoxy(5, 25);
      clreol();
      cout << "ENTER BASIC SALARY or <ENTER> FOR NO CHANGE";
      gotoxy(22, 15);
      clreol();
      gets(t1);
      t2 = atof(t1);
      ebasic = t2;
      if (t1[0] == '0')
        return;
      if (ebasic > 50000) {
        valid = 0;
        gotoxy(5, 25);
        clreol();
        cout << "\7SHOULD NOT GREATER THAN 50000";
        getch();
      }
    } while (!valid);
    if (strlen(t1) == 0) {
      ebasic = basic;
      gotoxy(22, 15);
      cout << ebasic;
    }
  }
  gotoxy(5, 25);
  clreol();
  do {
    gotoxy(5, 18);
    clreol();
    cout << "Do you want to save (y/n) ";
    ch = getche();
    ch = toupper(ch);
    if (ch == '0')
      return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N')
    return;
  MODIFY_RECORD(ecode, ename, eaddress, ephone, edesig, egrade, ehouse, econv, eloan, ebasic);
  gotoxy(5, 23);
  cout << "\7Record Modified";
  gotoxy(5, 25);
  cout << "Press any key to continue...";
  getch();
}
void EMPLOYEE::DELETION() {
  clrscr();
  char t1[10], ch;
  int t2, ecode;
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(5, 5);
  cout << "Enter code of the Employee  ";
  gets(t1);
  t2 = atoi(t1);
  ecode = t2;
  if (ecode == 0)
    return;
  clrscr();
  if (!FOUND_CODE(ecode)) {
    gotoxy(5, 5);
    cout << "\7Record not found";
    getch();
    return;
  }
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(24, 3);
  cout << "DELETION OF THE EMPLOYEE RECORD";
  DISPLAY_RECORD(ecode);
  do {
    gotoxy(5, 24);
    clreol();
    cout << "Do you want to delete this record (y/n) ";
    ch = getche();
    ch = toupper(ch);
    if (ch == '0')
      return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N')
    return;
  DELETE_RECORD(ecode);
  gotoxy(5, 23);
  cout << "\7Record Deleted";
  gotoxy(5, 25);
  cout << "Press any key to continue...";
  getch();
}
int EMPLOYEE::VALID_DATE(int d1, int m1, int y1) {
  int valid = 1;
  if (d1 > 31 || d1 < 1)
    valid = 0;
  else
  if (((y1 % 4) != 0 && m1 == 2 && d1 > 28) || ((y1 % 4) == 0 && m1 == 2 && d1 > 29))
    valid = 0;
  else
  if ((m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11) && d1 > 30)
    valid = 0;
  return valid;
}
void EMPLOYEE::SALARY_SLIP() {
  clrscr();
  char t1[10];
  int t2, ecode, valid, d1, m1, y1;
  gotoxy(72, 2);
  cout << "<0>=EXIT";
  gotoxy(5, 5);
  cout << "Enter code of the Employee  ";
  gets(t1);
  t2 = atoi(t1);
  ecode = t2;
  if (ecode == 0)
    return;
  clrscr();
  if (!FOUND_CODE(ecode)) {
    gotoxy(5, 5);
    cout << "\7Record not found";
    getch();
    return;
  }
  fstream file;
  file.open("EMPLOYEE.dat", ios:: in );
  file.seekg(0, ios::beg);
  while (file.read((char * ) this, sizeof(EMPLOYEE))) {
    if (code == ecode)
      break;
  }
  file.close();
  char * mon[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "November",
    "December"
  };
  gotoxy(31, 2);
  cout << "COSMOS INTERNATIONAL";
  gotoxy(34, 4);
  cout << "SALARY SLIP";
  gotoxy(6, 7);
  cout << "Employee Name : " << name;
  gotoxy(6, 8);
  cout << "Designation   : " << desig;
  gotoxy(67, 8);
  cout << "Grade : " << grade;
  int days, hours;
  if (grade == 'E') {
    do {

      valid = 1;
      gotoxy(10, 21);
      cout << "ENTER NO. OF DAYS WORKED IN THE MONTH ";
      gotoxy(10, 11);
      cout << "No. of Days   : ";
      gets(t1);
      t2 = atof(t1);
      days = t2;
      if (!VALID_DATE(days, m1, y1)) {
        valid = 0;
        gotoxy(10, 21);
        cout << "\7ENTER CORRECTLY            ";
        getch();
        gotoxy(10, 11);
        cout << "                    ";
      }
    } while (!valid);
    do {
      valid = 1;
      gotoxy(10, 21);
      cout << "ENTER NO. OF HOURS WORKED OVER TIME";
      gotoxy(10, 13);
      cout << "No. of hours  : ";
      gets(t1);
      t2 = atof(t1);
      hours = t2;
      if (hours > 8 || hours < 0) {
        valid = 0;
        gotoxy(10, 21);
        cout << "\7ENTER CORRECTLY          ";
        getch();
        gotoxy(10, 13);
        cout << "                    ";
      }
    } while (!valid);
    gotoxy(10, 21);
    cout << "                                     ";

    gotoxy(10, 11);
    cout << "                          ";
    gotoxy(10, 13);
    cout << "                          ";
  }
  gotoxy(10, 10);
  cout << "Basic Salary         : Rs.";
  gotoxy(10, 12);
  cout << "ALLOWANCE";
  if (grade != 'E') {
    gotoxy(12, 13);
    cout << "HRA  : Rs.";
    gotoxy(12, 14);
    cout << "CA   : Rs.";
    gotoxy(12, 15);
    cout << "DA   : Rs.";
  } else {
    gotoxy(12, 13);
    cout << "OT   : Rs.";
  }
  gotoxy(10, 17);
  cout << "DEDUCTIONS";
  gotoxy(12, 18);
  cout << "LD   : Rs.";
  if (grade != 'E') {
    gotoxy(12, 19);
    cout << "PF   : Rs.";
  }
  gotoxy(10, 21);
  cout << "NET SALARY         Rs.";
  gotoxy(6, 24);
  cout << "CASHIER";
  gotoxy(68, 24);
  cout << "EMPLOYEE";
  float HRA = 0.0, CA = 0.0, DA = 0.0, PF = 0.0, LD = 0.0, OT = 0.0, allowance, deduction, netsalary;
  if (grade != 'E') {
    if (house == 'Y')
      HRA = (15 * basic) / 100;
    if (conveyence == 'Y')
      CA = (2 * basic) / 100;
    DA = (15 * basic) / 100;
    PF = (5 * basic) / 100;
    LD = (5 * loan) / 100;
    allowance = HRA + CA + DA;
    deduction = PF + LD;
  } else {
    basic = days * 120;
    LD = (15 * loan) / 100;
    OT = hours * 150;
    allowance = OT;
    deduction = LD;
  }
  netsalary = (basic + allowance) - deduction;
  gotoxy(36, 10);
  cout << basic;
  if (grade != 'E') {
    gotoxy(22, 13);
    cout << HRA;
    gotoxy(22, 14);
    cout << CA;
    gotoxy(22, 15);
    cout << DA;
    gotoxy(22, 19);
    cout << PF;
  } else {
    gotoxy(22, 13);
    cout << OT;
  }
  gotoxy(22, 18);
  cout << LD;
  gotoxy(33, 15);
  cout << "Rs." << allowance;
  gotoxy(33, 19);
  cout << "Rs." << deduction;
  gotoxy(36, 21);
  cout << netsalary;
  gotoxy(2, 1);
  getch();
}
void main() {
  textcolor(0);
  textbackground(WHITE);
  clrscr();
  MENU m;
  m.INTRODUCTION();
  m.MAIN_MENU();
}
