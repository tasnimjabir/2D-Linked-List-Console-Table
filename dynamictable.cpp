#include <iostream>
#include <conio.h>
#include<string>
using namespace std;

int colNum, rowNum;
string tableName;

struct columndata{
    string data;
    int maxSize;
    columndata* next;
    columndata(){
        data = "---------";
        maxSize = 8;
    }
};

columndata* columnRoot = NULL;

struct cell{
    string data, spaces;
    cell* prev;
    cell* next;
    cell(string str){
        data = str;
        spaces = "        ";
        prev = NULL;
        next = NULL;
    }
};

struct record{
    record* prev;
    record* next;
    cell* cellRoot;
    record(){
        prev = NULL;
        next = NULL;
        cellRoot = new cell("");
        cell* cellTemp = cellRoot;
        cell* cellTemp2 = cellRoot;
        for(int i = 0; i<colNum-1; i++){
            cellTemp->next = new cell("");
            cellTemp2 = cellTemp;
            cellTemp = cellTemp->next;
            cellTemp->prev = cellTemp2;
        }

    }
};

void printLine(){
    columndata* columnTemp = columnRoot;
    cout<<"\t+";
    while(columnTemp!=NULL){
        cout<<columnTemp->data<<"+";
        columnTemp = columnTemp->next;
    }
    cout<<endl;
}

void display(record* recordRoot){
    record* recordTemp = recordRoot;
    cout<<"  "<<tableName<<": "<<endl<<endl;
    printLine();
    while(recordTemp!=NULL){
        cell* cellTemp = recordTemp->cellRoot;
        cout<<"\t|";
        while(cellTemp!=NULL){
            cout<<" "<<cellTemp->data<<cellTemp->spaces<<"|";
            cellTemp = cellTemp->next;
        }
        recordTemp = recordTemp->next;
        cout<<endl;
        printLine();
    }
    cout<<endl;
}

record* tableMake(){
    cout<<"  Table Name: ";
    cin>>tableName;
    cout<<"  Column Number: ";
    cin>>colNum;
    cout<<"  Row Number: ";
    cin>>rowNum;
    record* recordRoot = new record();
    record* recordTemp = recordRoot;
    record* recordTemp2 = recordRoot;
    for(int i = 1; i<rowNum; i++){
        recordTemp->next = new record();
        recordTemp2 = recordTemp;
        recordTemp = recordTemp->next;
        recordTemp->prev = recordTemp2;
    }

    columnRoot = new columndata;
    columndata* columnTemp = columnRoot;
    for(int i = 1; i<colNum; i++){
        columnTemp->next = new columndata();
        columnTemp = columnTemp->next;
    }

    return recordRoot;
}



void title(){
    cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t2D Linkedlist Console Table"<<endl;
    cout<<"\tMade by: Tasnim Jabir"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
}

record* editText(record* recordRoot){
    record* recordTemp = recordRoot;
    cell* cellTemp = recordTemp->cellRoot;

    int x=0,y=0;
    bool printOn = true;
    while(printOn){
        system("cls");
        title();
        string cdata = cellTemp->data;


        display(recordRoot);
        cout<<"  (Press Enter to edit. Use Arrow keys to change cell. Press ESC for go back)"<<endl<<endl;
        cout<<"  Current cell"<<" ("<<-y+1<<", "<<x+1<<")"<<": "<<cdata<<endl;



        int key = _getch();

        if(key == 224){
            key = _getch();
            if(key == 75 && cellTemp->prev!=NULL){
                cellTemp = cellTemp->prev;
                cdata = cellTemp->data;
                x--;
            }
            else if(key == 77 && cellTemp->next!=NULL){
                cellTemp = cellTemp->next;
                cdata = cellTemp->data;
                x++;
            }
            else if(key == 72 && recordTemp->prev!=NULL){
                recordTemp = recordTemp->prev;
                cellTemp = recordTemp->cellRoot;
                for(int i = 0; i<x; i++)
                    cellTemp = cellTemp->next;
                cdata = cellTemp->data;
                y++;
            }
            else if(key == 80 && recordTemp->next!=NULL){
                recordTemp = recordTemp->next;
                cellTemp = recordTemp->cellRoot;
                for(int i = 0; i<x; i++)
                    cellTemp = cellTemp->next;
                cdata = cellTemp->data;
                y--;
            }
        } else if (key == 13) {
            cout<<"  Enter text: ";
            //cin.ignore();
            string data;
            getline(cin, data);
            cellTemp->data = data;
            int len = data.length();
            columndata* columnTemp = columnRoot;
            for(int i = 0; i<x && columnTemp->next!=NULL; i++)
                columnTemp = columnTemp->next;
            if(len>columnTemp->maxSize){
                columnTemp->maxSize = len + 1;
                    record* recordTemp2 = recordRoot;
                    while (recordTemp2 != nullptr) {
                        cell* cellTemp2 = recordTemp2->cellRoot;
                        for (int i = 0; i < x; i++) {
                            if (cellTemp2->next != nullptr) {
                                cellTemp2 = cellTemp2->next;
                            }
                        }
                        int len2 = (cellTemp2->data).length();
                        string sp;
                        string datasp;
                        for(int i = len2; i<columnTemp->maxSize; i++){
                            sp += " ";
                            datasp += "-";
                        }
                        columnTemp->data = datasp + "-";
                        cellTemp2->spaces = sp;

                        // Move to the next row
                        recordTemp2 = recordTemp2->next;
                    }

            }else{
                string sp;
                for(int i = len; i<columnTemp->maxSize; i++)
                    sp += " ";
                cellTemp->spaces = sp;
            }

        } else if (key == 27) {
            return recordRoot;
        }
    }

    return recordRoot;
}

void columndataAdd(int position){
    if(position == 0){
        columndata* newcolumndata = new columndata();
        newcolumndata->next = columnRoot;
        columnRoot = newcolumndata;
        return;
    }
    columndata* columnTemp = columnRoot;
    columndata* columnTemp2 = columnRoot;
    columndata* newcolumndata = new columndata();

    if(columnRoot == NULL)
        columnRoot = newcolumndata;
    else{
        for(int i = 0; i<position&&columnTemp->next!=NULL; i++){
            columnTemp2 = columnTemp;
            columnTemp = columnTemp->next;
        }
        columnTemp2->next = newcolumndata;
        newcolumndata->next = columnTemp;

    }

};


void columndataDelete(int position){
    if(position == 0){
        columndata* temp = columnRoot;
        columnRoot = columnRoot->next;
        free(temp);
        temp = NULL;
    }else{
        columndata* temp = columnRoot, *temp1= temp;
        for(int i = 0; i<position&&temp->next!=NULL; i++){
            temp1 = temp;
            temp = temp->next;
        }
        temp1->next = temp->next;
        free(temp);
        temp=NULL;

    }

};

void replaceRowValues(record* recordRoot, int position) {
    if (position < 0 || position >= rowNum) {
        cout << "Invalid row position!" << endl;
        return;
    }
    record* recordTemp = recordRoot;
    for (int i = 0; i < position; i++) {
        recordTemp = recordTemp->next;
    }
    cell* cellTemp = recordTemp->cellRoot;
    columndata* columnTemp = columnRoot;
    while (cellTemp != nullptr) {
        string sp;
        for(int i = 0; i<columnTemp->maxSize; i++)
            sp += " ";
        cellTemp->spaces = sp;
        cellTemp = cellTemp->next;
        columnTemp = columnTemp->next;
    }
}

void addColumnAt(record* recordRoot, const string& defaultData, int columnIndex) {
    if (columnIndex < 0 || columnIndex > colNum) {
        cout << "Invalid column index!" << endl;
        getch();
        return;
    }

    record* recordTemp = recordRoot;

    while (recordTemp != nullptr) {
        cell* cellTemp = recordTemp->cellRoot;

        for (int i = 0; i < columnIndex; i++) {
            cellTemp = cellTemp->next;
        }

        cell* newCell = new cell(defaultData);

        if (cellTemp != nullptr) {
            newCell->prev = cellTemp->prev;
            newCell->next = cellTemp;
            if (cellTemp->prev != nullptr) {
                cellTemp->prev->next = newCell;
            } else {
                recordTemp->cellRoot = newCell;
            }
            cellTemp->prev = newCell;
        } else {
            cellTemp = recordTemp->cellRoot;
            while (cellTemp->next != nullptr) {
                cellTemp = cellTemp->next;
            }
            cellTemp->next = newCell;
            newCell->prev = cellTemp;
        }

        recordTemp = recordTemp->next;
    }

    colNum++;
}

void addRowAt(record* &recordRoot, const string& defaultData, int rowIndex) {
    if (rowIndex < 0 || rowIndex > rowNum) {
        cout << "Invalid row index!" << endl;
        getch();
        return;
    }

    record* newRecord = new record();

    cell* cellTemp = newRecord->cellRoot;
    for (int i = 0; i < colNum - 1; i++) {
        cell* newCell = new cell(defaultData);
        cellTemp->next = newCell;
        newCell->prev = cellTemp;
        cellTemp = newCell;
    }

    record* recordTemp = recordRoot;
    for (int i = 0; i < rowIndex; i++) {
        recordTemp = recordTemp->next;
    }

    newRecord->prev = recordTemp->prev;
    newRecord->next = recordTemp;

    if (recordTemp->prev != nullptr) {
        recordTemp->prev->next = newRecord;
    } else {
        recordRoot = newRecord;
    }
    recordTemp->prev = newRecord;

    rowNum++;
}

void deleteColumnAt(record* recordRoot, int columnIndex) {
    if (columnIndex < 0 || columnIndex >= colNum) {
        cout << "Invalid column index!" << endl;
        getch();
        return;
    }

    record* recordTemp = recordRoot;

    while (recordTemp != nullptr) {
        cell* cellTemp = recordTemp->cellRoot;

        for (int i = 0; i < columnIndex; i++) {
            cellTemp = cellTemp->next;
        }

        if (cellTemp->prev != nullptr) {
            cellTemp->prev->next = cellTemp->next;
        } else {
            recordTemp->cellRoot = cellTemp->next;
        }

        if (cellTemp->next != nullptr) {
            cellTemp->next->prev = cellTemp->prev;
        }

        delete cellTemp;

        recordTemp = recordTemp->next;
    }

    colNum--;
}

// Function to delete a row at any position
void deleteRowAt(record* &recordRoot, int rowIndex) {
    if (rowIndex < 0 || rowIndex >= rowNum) {
        cout << "Invalid row index!" << endl;
        getch();
        return;
    }

    record* recordTemp = recordRoot;

    for (int i = 0; i < rowIndex; i++) {
        recordTemp = recordTemp->next;
    }

    if (recordTemp->prev != nullptr) {
        recordTemp->prev->next = recordTemp->next;
    } else {
        recordRoot = recordTemp->next;
    }

    if (recordTemp->next != nullptr) {
        recordTemp->next->prev = recordTemp->prev;
    }

    delete recordTemp;

    rowNum--;
}


int main(){
    title();
    record* recordRoot = tableMake();

    bool printOn = true;
    string menu[3] = {"Edit Text","Edit Column","Edit Rows"};
    int selected = 0;

    while (printOn) {
        system("cls");
        title();
        display(recordRoot);

        for(int i = 0; i<3; i++){
            if(selected == i)
                cout<<" -->";
            cout<<"\t"<<menu[i]<<endl;
        }

        cout<<endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            if (key == 72) {
                if(selected!=0)
                    selected--;
            }
            else if (key == 80) {
                if(selected!=2)
                    selected++;
            }
        } else if (key == 13 && selected == 0) {
            editText(recordRoot);
        } else if (key == 13 && selected == 1) {
            cout<<"  1. Add"<<endl;
            cout<<"  2. Delete"<<endl;
            int choise;
            cout<<"  Enter your choies: ";
            cin>>choise;
            if(choise == 1){
                cout<<"  Add new column at: ";
                int position;
                cin>>position;
                columndataAdd(position);
                addColumnAt(recordRoot, "", position);
            }else if(choise == 2){
                cout<<"  Delete column at: ";
                int position;
                cin>>position;
                deleteColumnAt(recordRoot,position-1);
                columndataDelete(position-1);
                if(columnRoot == NULL){
                    cout<<"  Table is fully deleted!";
                    getch();
                    return 0;
                }
            }else{
                cout<<"  Invalid Input!";
                getch();
            }
            } else if (key == 13 && selected == 2) {
            cout<<"  1. Add"<<endl;
            cout<<"  2. Delete"<<endl;
            int choise;
            cout<<"  Enter your choies: ";
            cin>>choise;
            if(choise == 1){
                cout<<"  Add new row at: ";
                int position;
                cin>>position;
                addRowAt(recordRoot, "", position);
                replaceRowValues(recordRoot, position);
            }else if(choise == 2){
                cout<<"  Delete row at: ";
                int position;
                cin>>position;
                deleteRowAt(recordRoot,position-1);
                if(columnRoot == NULL){
                    cout<<"  Table is fully deleted!";
                    getch();
                    return 0;
                }
            }else{
                cout<<"  Invalid Input!";
                getch();
            }
        }
    }
}
