//
//  main.cpp
//  PROJECT_1_MAHMUD_AHMAD
//
//  Created by Mahmud Ahmad on 10/7/17.
//  Copyright © 2017 Mahmud Ahmad. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <unistd.h>
#include <sstream>

using namespace std;

/*
 for the jumping instructions
 I have to count the number of
 lines in the file. And then,
 get the line number of the
 labels. When calling a jump
 instruction, I find the
 difference between currentLineNum
 and jumpLineNum
 (so jumpLineNum - currentLineNum)
 and multiply it by 4 to get the
 location. I have to convert to hex.
 */


void insertM(map<string, string> a, string b, string c) {
    a.insert(make_pair(b, c));
}

map<string, string> opDictionary() {
    map<string, string> opCodeDictionary;
    insertM(opCodeDictionary, "j", "000010");
    insertM(opCodeDictionary, "jal", "000011");
    insertM(opCodeDictionary, "beqz", "000100");
    insertM(opCodeDictionary, "bnez", "000101");
    insertM(opCodeDictionary, "addi", "001000");
    insertM(opCodeDictionary, "addui", "001001");
    insertM(opCodeDictionary, "subi", "001010");
    insertM(opCodeDictionary, "subui", "001011");
    insertM(opCodeDictionary, "andi", "001100");
    insertM(opCodeDictionary, "ori", "001101");
    insertM(opCodeDictionary, "xori", "001110");
    insertM(opCodeDictionary, "lhi", "001111");
    insertM(opCodeDictionary, "jr", "010010");
    insertM(opCodeDictionary, "jalr", "010011");
    insertM(opCodeDictionary, "seqi", "011000");
    insertM(opCodeDictionary, "snei", "011001");
    insertM(opCodeDictionary, "slti", "011010");
    insertM(opCodeDictionary, "sgti", "011011");
    insertM(opCodeDictionary, "slei", "011100");
    insertM(opCodeDictionary, "sgei", "011101");
    insertM(opCodeDictionary, "lb", "100000");
    insertM(opCodeDictionary, "lh", "100001");
    insertM(opCodeDictionary, "lw", "100011");
    insertM(opCodeDictionary, "lbu", "100100");
    insertM(opCodeDictionary, "lhu", "100101");
    insertM(opCodeDictionary, "sb", "101000");
    insertM(opCodeDictionary, "sh", "101001");
    insertM(opCodeDictionary, "sw", "101011");
    insertM(opCodeDictionary, "sequi", "110000");
    insertM(opCodeDictionary, "sneui", "110001");
    insertM(opCodeDictionary, "sltui", "110010");
    insertM(opCodeDictionary, "sgtui", "110011");
    insertM(opCodeDictionary, "sleui", "110100");
    insertM(opCodeDictionary, "sgeui", "110101");
    insertM(opCodeDictionary, "slli", "110110");
    insertM(opCodeDictionary, "srli", "110111");
    insertM(opCodeDictionary, "srai", "111000");
    
    return opCodeDictionary;
}

map<string, string> functionDictionary() {
    map<string, string> functionDictionary;
    insertM(functionDictionary, "sll", "00000000100");
    insertM(functionDictionary, "srl", "00000000110");
    insertM(functionDictionary, "sra", "00000000111");
    insertM(functionDictionary, "sltu", "00000010010");
    insertM(functionDictionary, "sgtu", "00000010011");
    insertM(functionDictionary, "sleu", "00000010100");
    insertM(functionDictionary, "sgeu", "00000010101");
    insertM(functionDictionary, "add", "00000100000");
    insertM(functionDictionary, "addu", "00000100001");
    insertM(functionDictionary, "sub", "00000100010");
    insertM(functionDictionary, "subu", "00000100011");
    insertM(functionDictionary, "and", "00000100100");
    insertM(functionDictionary, "or", "00000100101");
    insertM(functionDictionary, "xor", "00000100110");
    insertM(functionDictionary, "seq", "00000101000");
    insertM(functionDictionary, "sne", "00000101001");
    insertM(functionDictionary, "slt", "00000101010");
    insertM(functionDictionary, "sgt", "00000101011");
    insertM(functionDictionary, "sle", "00000101100");
    insertM(functionDictionary, "sge", "00000101101");
    return functionDictionary;
}

string getCodeFromDictionary(map<string, string> fromMap, string codeToGet) {
    if(fromMap.find(codeToGet) != fromMap.end()) {
        return fromMap.find(codeToGet)->second;
    } else {
        return "0";
    }
}

int isInt(char chr) {
    if(chr >= '0' && chr <= '9') {
        return 0;
    } else {
        return 1;
    }
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

//this is a prototype, the official one will take a string parameter
//and write that as a new line to a text file
ofstream writeToFile(){
    ofstream file("sample.txt");
    if(file.is_open()) {
        file << "add r1, r2, r3\n";
        file << "add r2, r2, r2\n";
        file << endl;
        file.close();
    }
    return file;
}

string returnOPCODE(string asmInstruction) {
    string instruction;
    for(int i = 0; i < asmInstruction.length(); i++) {
        if(asmInstruction[i] == ' ') {
            break;
        } else {
            instruction += asmInstruction[i];
        }
    }
    return instruction;
}

map<string, int> getLabelLineNumber(string filename) {
    string str;
    ifstream file(filename);
    map<string, int> labelLineNumber;
    int lineNumber = 0;
    if(file.is_open()) {
        while(getline(file, str)) {
            for(int i = 0; i < str.length(); i++) {
                if(str[i] == ':') {
                    str[i] = '\0';
                    labelLineNumber.insert(make_pair(str, lineNumber));
                }
            }
            lineNumber++;
        }
        file.close();
    } else {
        return {{"null", 0}};
    }
    return labelLineNumber;
}

int *parseOutRegNumber(string str) {
    int count = 0;
    str = str + ' ';
    for(int i = 0; i < str.length(); i++) {
        if((str[i] >= '0') && (str[i] <= '9')) {
            //count++;
        } else {
            str[i] = ' ';
        }
    }
    
    int i = 0;
    while(str[i] != '\0') {
        if(isInt(str[i]) == 0) {
            count++;
            for(int j = i; j < str.length(); j++) {
                if(isInt(str[j]) == 1) {
                    i = j - 1;
                    break;
                }
            }
        }
        i++;
    }
    
    
    static int *numbers;
    numbers = new int [count + 1];
    int nextAvailablePosition = 0;
    i = 0;
    numbers[nextAvailablePosition] = 0;
    string intermediate;
    while(str[i] != '\0') {
        if(isInt(str[i]) == 0) {
            for(int j = i; j < str.length(); j++) {
                if(isInt(str[j]) == 1) {
                    for(int k = i; k < j; k++) {
                        intermediate += str[k];
                    }
                    for(int k = 0; k < intermediate.length(); k++) {
                        //int l = intermediate.length();
                        //int blah = pow(10, intermediate.length() - (k + 1)) * (intermediate[k] - 48);
                        numbers[nextAvailablePosition] += pow(10, intermediate.length() - (k + 1)) * (intermediate[k] - 48);
                    }
                    nextAvailablePosition++;
                    numbers[nextAvailablePosition] = 0;
                    i = j - 1;
                    intermediate.clear();
                    break;
                }
            }
        }
        i++;
    }
    numbers[count] = -1;
    
    int *arrayPointer = numbers;
    
    return arrayPointer;
}

string stringToLower(string str) {
    string lowerSTR = "";
    for(int i = 0; i < str.length(); i++) {
        if(str[i] >= 0x41 && str[i] <= 0x5a) {
            lowerSTR += str[i] + 0x20;
        } else {
            lowerSTR += str[i];
        }
    }
    return lowerSTR;
}

void buildInstruction(int portionNumber, int startIndex, string instruction, string _asm, int lineNumber) {
    _asm = clearEXTRA_WHITE_SPACE(_asm);
    _asm = stringToLower(_asm);
    string portion;
    for(int i = 0; i < _asm.length(); i++) {
        //this part is done
        if(startIndex == 0) {
            //Just the opcode... same for all instructions, start
            //index is 0, no need to increment i by start index.
            if(_asm[i] == ' ') {
                startIndex = i + 1;
                break;
            } else {
                portion += _asm[i];
            }
            portion = getCodeFromDictionary(opDictionary(), portion);
            instruction += portion;
            portionNumber++;
    
        } else if(instruction.compare("000000") == 0) {
            //R-Type Instructions, have to add more logic for third register
            if(_asm[startIndex + i] == ',') {
                startIndex = startIndex + i + 1;
                break;
            } else {
                portion += _asm[startIndex + i];
            }
            
        } else {
            
            //I-Type Instructions
            if(_asm[0] == 'b') {
                if(portionNumber == 1) {
                    //parse out the register number
                    portionNumber++;
                } else {
                    //label
                    portionNumber++;
                }
                
                
            } else if((_asm[0] + _asm[1] == 's' + 'h') || (_asm[0] + _asm[1] == 's' + 'b') || (_asm[0] + _asm[1] == 's' + 'w')) {
                //this is my store instructions, only ones where RS1 doesnt flip with RS2 (Easier encoding)
                if(portionNumber == 1 || portionNumber == 2) {
                    //parse out the register number,
                    //in the case of load/store, add a white space
                    if(_asm[startIndex + i] == ',') {
                        startIndex = startIndex + i + 1;
                        break;
                    } else {
                        portion += _asm[startIndex + i];
                    }
                    
                } else {
                    //were either at the end of line, or
                    //were a math instruction, in this case we get the immediate
                    
                }
                portionNumber++;
                
            } else {
                
                if(portionNumber == 1 || portionNumber == 2) {
                    //parse out the register number,
                    //in the case of load/store, add a white space
                    if(_asm[startIndex + i] == ',') {
                        startIndex = startIndex + i + 1;
                        break;
                    } else {
                        portion += _asm[startIndex + i];
                    }
                    
                } else {
                    //were either at the end of line, or
                    //were a math instruction, in this case we get the immediate
                }
                portionNumber++;
            }
        }
    }
    if(_asm[startIndex] == '\0') {
        writeToFile();
    } else {
        buildInstruction(portionNumber, startIndex, instruction, _asm, lineNumber);
    }
}

void buildInstruction2(string _asm) {
    _asm = clearEXTRA_WHITE_SPACE(_asm);
    _asm = stringToLower(_asm);
    map<string, string> portionsOf_asm;
    for(int i = 0; i < _asm.length(); i++) {
        if(_asm[i] == ' ' || _asm[i] == ',') {
            break;
        } else {
            
        }
    }

    map<string, string> instruction;
    insertM(instruction, "opCode", getCodeFromDictionary(opDictionary(), returnOPCODE()));
    if(instruction.find("opCode")->second == "000000") {
        //do R Typed
    } else {
        if(_asm[0] == 'b') {

        }
    }
    insertM(instruction, "RS1", /*getRS1*/);
    insertM(instruction, "RS2", /*getRS2*/);
    insertM(instruction, "IMM", /*getIMM*/);
}

void readFromFile(string fileName) {
    string str;
    ifstream file(fileName);
    int lineNumber = 0;
    if(file.is_open()) {
        while(getline(file, str)) {
            cout << str << "\n";
            buildInstruction(0, 0, "", str, lineNumber);
            lineNumber++;
        }
        file.close();
    }
}

string makeLengthMOD40(string str) {
    int numToAppend = 4 - str.length()%4;
    for(int i = 0; i < numToAppend; i++) {
        str.insert(0, "0");
    }
    return str;
}

string returnHexFromBin(string binString) {
    string hexString;
    if(binString.length()%4 != 0) {
        binString = makeLengthMOD40(binString);
    }
    for(int i = 0; i < (binString.length()/4); i++) {
        int startIndex = i*4;
        int sum = 0;
        for(int j = 0; j < 4; j++) {
            sum += (binString[startIndex + j] - '0') * (pow(2, 3 - j));
        }
        if(sum >= 10) {
            hexString += (sum + 55);
        } else {
            hexString += to_string(sum);
        }
    }
    return hexString;
}


int main() {
    
    //    //iterate through map
    //    map<string, int> test = getLabelLineNumber("sample.txt");
    //    for(map<string, int>::iterator it = test.begin(); it != test.end(); ++it) {
    //        cout << "Key: " << it->first << ", Value: " << it->second << "\n";
    //    }
    //
    //    //check if map contains value
    //    map<string, string> a = functionDictionary();
    //    if(a.find("plasdf") != a.end()) {
    //        cout << "found";
    //    } else {
    //        cout << "not found";
    //    }
    //
    //    //checking IO of CHARS
    //    char x = 0x30;
    //    //does my algorithm work?
    //    cout << parseOutRegNumber("4(r31)") << "\n";
    //    cout << x << "\n";
    //    //yes it does, now checking it for larger inputs. it works.
    //    int i = 0;
    //    int *array = parseOutRegNumber("93, 6, 77, 104, 99");
    //    string x;
    //    while(*(array + i) != -1) {
    //        cout << hex << *(array + i) << '\n';
    //        i++;
    //    }
        
    //    cout << stringToLower("This IS A String with 1234## and Letters") << "\n";
    
    return 0;
}


