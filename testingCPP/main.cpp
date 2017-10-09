//
//  main.cpp
//  testingCPP
//
//  Created by Mahmud Ahmad on 1/11/17.
//  Copyright © 2017 Mahmud Ahmad. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <fstream>


using namespace std;

string clearNEW_LINE(string str) {
    string toReturn;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != '\n') {
            toReturn += str[i];
        }
    }
    return toReturn;
}

string clearWHITE_SPACE(string str) {
    string returned;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != ' ') {
            returned += str[i];
        }
    }
    return returned;
}

string clearEXTRA_WHITE_SPACE(string str) {
    string returned;
    bool firstSpaceFound = false;
    for(int i = 0; i < str.length(); i++) {
        if((str[i] != ' ') && (firstSpaceFound == true)) {
            returned += str[i];
        } else if(firstSpaceFound == false) {
            returned += str[i];
        }
        if(str[i] == ' ') {
            firstSpaceFound = true;
        }
    }
    return returned;
}

void readFromFile(string fileName) {
    string str;
    ifstream file(fileName);
    if(file.is_open()) {
        while(getline(file, str)) {
            cout << str;
        }
        file.close();
    }
}

ofstream writeToFile(){
    ofstream file("/sample.txt");
    if(file.is_open()) {
        file << "add r1, r2, r3\n";
        file << "add r2, r2, r2\n";
        file << endl;
        file.close();
    }
    return file;
}


int main() {
    //writeToFile();
    readFromFile("smplz.txt");
    
    return 0;
}

//int main() {
//int i;
//    printf("Checking if processor is available...");
//
//    if(system(NULL)) {
//        puts ("Ok\n\n");
//    }
//    else {
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Executing command DIR...\n\n");
//    printf ("The value returned was: %d.\n\n",i);
//}
