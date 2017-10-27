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

map<string, string> opDictionary() {
    map<string, string> opCodeDictionary;
    opCodeDictionary.insert(make_pair("j", "000010"));
    opCodeDictionary.insert(make_pair("jal", "000011"));
    opCodeDictionary.insert(make_pair("beqz", "000100"));
    opCodeDictionary.insert(make_pair("bnez", "000101"));
    opCodeDictionary.insert(make_pair("addi", "001000"));
    opCodeDictionary.insert(make_pair("addui", "001001"));
    opCodeDictionary.insert(make_pair("subi", "001010"));
    opCodeDictionary.insert(make_pair("subui", "001011"));
    opCodeDictionary.insert(make_pair("andi", "001100"));
    opCodeDictionary.insert(make_pair("ori", "001101"));
    opCodeDictionary.insert(make_pair("xori", "001110"));
    opCodeDictionary.insert(make_pair("lhi", "001111"));
    opCodeDictionary.insert(make_pair("jr", "010010"));
    opCodeDictionary.insert(make_pair("jalr", "010011"));
    opCodeDictionary.insert(make_pair("seqi", "011000"));
    opCodeDictionary.insert(make_pair("snei", "011001"));
    opCodeDictionary.insert(make_pair("slti", "011010"));
    opCodeDictionary.insert(make_pair("sgti", "011011"));
    opCodeDictionary.insert(make_pair("slei", "011100"));
    opCodeDictionary.insert(make_pair("sgei", "011101"));
    opCodeDictionary.insert(make_pair("lb", "100000"));
    opCodeDictionary.insert(make_pair("lh", "100001"));
    opCodeDictionary.insert(make_pair("lw", "100011"));
    opCodeDictionary.insert(make_pair("lbu", "100100"));
    opCodeDictionary.insert(make_pair("lhu", "100101"));
    opCodeDictionary.insert(make_pair("sb", "101000"));
    opCodeDictionary.insert(make_pair("sh", "101001"));
    opCodeDictionary.insert(make_pair("sw", "101011"));
    opCodeDictionary.insert(make_pair("sequi", "110000"));
    opCodeDictionary.insert(make_pair("sneui", "110001"));
    opCodeDictionary.insert(make_pair("sltui", "110010"));
    opCodeDictionary.insert(make_pair("sgtui", "110011"));
    opCodeDictionary.insert(make_pair("sleui", "110100"));
    opCodeDictionary.insert(make_pair("sgeui", "110101"));
    opCodeDictionary.insert(make_pair("slli", "110110"));
    opCodeDictionary.insert(make_pair("srli", "110111"));
    opCodeDictionary.insert(make_pair("srai", "111000"));
    opCodeDictionary.insert(make_pair("sll", "000000"));
    opCodeDictionary.insert(make_pair("srl", "000000"));
    opCodeDictionary.insert(make_pair("sra", "000000"));
    opCodeDictionary.insert(make_pair("sltu", "000000"));
    opCodeDictionary.insert(make_pair("sgtu", "000000"));
    opCodeDictionary.insert(make_pair("sleu", "000000"));
    opCodeDictionary.insert(make_pair("sgeu", "000000"));
    opCodeDictionary.insert(make_pair("add", "000000"));
    opCodeDictionary.insert(make_pair("addu", "000000"));
    opCodeDictionary.insert(make_pair("sub", "000000"));
    opCodeDictionary.insert(make_pair("subu", "000000"));
    opCodeDictionary.insert(make_pair("and", "000000"));
    opCodeDictionary.insert(make_pair("or", "000000"));
    opCodeDictionary.insert(make_pair("xor", "000000"));
    opCodeDictionary.insert(make_pair("seq", "000000"));
    opCodeDictionary.insert(make_pair("sne", "000000"));
    opCodeDictionary.insert(make_pair("slt", "000000"));
    opCodeDictionary.insert(make_pair("sgt", "000000"));
    opCodeDictionary.insert(make_pair("sle", "000000"));
    opCodeDictionary.insert(make_pair("sge", "000000"));
    
    return opCodeDictionary;
}

map<string, string> functionDictionary() {
    map<string, string> functionDictionary;
    functionDictionary.insert(make_pair("sll", "00000000100"));
    functionDictionary.insert(make_pair("srl", "00000000110"));
    functionDictionary.insert(make_pair("sra", "00000000111"));
    functionDictionary.insert(make_pair("sltu", "00000010010"));
    functionDictionary.insert(make_pair("sgtu", "00000010011"));
    functionDictionary.insert(make_pair("sleu", "00000010100"));
    functionDictionary.insert(make_pair("sgeu", "00000010101"));
    functionDictionary.insert(make_pair("add", "00000100000"));
    functionDictionary.insert(make_pair("addu", "00000100001"));
    functionDictionary.insert(make_pair("sub", "00000100010"));
    functionDictionary.insert(make_pair("subu", "00000100011"));
    functionDictionary.insert(make_pair("and", "00000100100"));
    functionDictionary.insert(make_pair("or", "00000100101"));
    functionDictionary.insert(make_pair("xor", "00000100110"));
    functionDictionary.insert(make_pair("seq", "00000101000"));
    functionDictionary.insert(make_pair("sne", "00000101001"));
    functionDictionary.insert(make_pair("slt", "00000101010"));
    functionDictionary.insert(make_pair("sgt", "00000101011"));
    functionDictionary.insert(make_pair("sle", "00000101100"));
    functionDictionary.insert(make_pair("sge", "00000101101"));
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
ofstream writeToFile(string fileName, string lineToWrite, bool closeFile){
    ofstream file;
    file.open(fileName, ios::out | ios::app);
    if(file.is_open()) {
        file << lineToWrite + "\n";
    } 
    if(closeFile == true) {
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

int *parseIntFromAlphaNumeric(string str) {
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

int getLineNumber(string filename, string line) {
    string str;
    ifstream file(filename);
    map<string, int> labelLineNumber;
    int lineNumber = 0;
    if(file.is_open()) {
        while(getline(file, str)) {
            labelLineNumber.insert(make_pair(stringToLower(str), lineNumber));
            lineNumber++;
        }
        file.close();
    } else {
        return -1;
    }
    return labelLineNumber[line];
}

string reverseString(string toReverse) {
    string reversed = "";
    for(int i = 0; i < toReverse.length(); i++) {
        char x = toReverse[toReverse.length() - (i+1)];
        //cout << x << "\n";
        reversed += x;
    }
    return reversed;
}

string intToBinary(int _int, int length) {
    string binaryString = "";
    while(_int >= 1) {
        binaryString += to_string(_int % 2);
        _int = _int - (_int % 2);
        _int = _int / 2;
    }
    binaryString = reverseString(binaryString);
    if(binaryString.length() < length) {
        for(int i = 0; i < binaryString.length() - length; i++) {
            binaryString.insert(0, "0");
        }
    }
    return binaryString;
}

string returnBinFromAlphaNumeric(string reg, int length) {
    string numberFromReg = "";
    stringstream hexOfReg;
    string _hex = "";

    int regNumber = 0;
    for(int i = 0; i < reg.length(); i++) {
        if(isInt(reg[i]) == 0) {
            numberFromReg += reg[i];
        }
    }
    for(int i = 0; i < numberFromReg.length(); i++) {
        regNumber += pow(10, numberFromReg.length() - (i + 1)) * (numberFromReg[i] - 48);
    }

    return intToBinary(regNumber, length);
}

void readFromFile(string fileName) {
    string str;
    ifstream file(fileName);
    int lineNumber = 0;
    if(file.is_open()) {
        while(getline(file, str)) {
            cout << str << "\n";
            //buildInstruction(0, 0, "", str, lineNumber);
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

bool checkIfContainsR(string str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == 'r') {
            return true;
        }
    }
    return false;
}

void buildInstruction2(string _asm, string fileName) {
    int currentLineNumber = getLineNumber(fileName, _asm);
    _asm = clearEXTRA_WHITE_SPACE(_asm);
    _asm = stringToLower(_asm);
    bool isLabel = false;
    string portion = "";
    string finalInstruction = "";
    int part = 0;
    map<string, string> portionsOf_asm;
    for(int i = 0; i < _asm.length(); i++) {
        if(_asm[i] == ' ' || _asm[i] == ',') {
            portionsOf_asm.insert(make_pair("Part " + to_string(part), portion));
            portion = "";
            part++;
        } else if(_asm[i + 1] == '\0') {
            portion += _asm[i];
            portionsOf_asm.insert(make_pair("Part " + to_string(part), portion));
            portion = "";
            part = 0;
        } else {
            portion += _asm[i];
        }
    }
    for(int i = 0; i < _asm.length(); i++) {
        if(_asm[i] == ':') {
            isLabel = true;
            break;
        }
    }
    for(map<string, string>::iterator it = portionsOf_asm.begin(); it != portionsOf_asm.end(); ++it) {
        cout << "Key: " << it->first << ", Value: " << it->second << "\n";
    }

    map<string, string> instruction;
    if(isLabel == true) {
        instruction.insert(make_pair("Part 0", intToBinary(getLineNumber(fileName, _asm) * 4, 32)));
    } else {
        instruction.insert(make_pair("Part 0", getCodeFromDictionary(opDictionary(), portionsOf_asm["Part 0"])));
    }
    cout << instruction["Part 0"] << "\n";
    if(isLabel == true) {
        
    } else if(instruction["Part 0"] == "000000") {
        instruction.insert(make_pair("Part 1", returnBinFromAlphaNumeric(portionsOf_asm["Part 2"], 5)));
        instruction.insert(make_pair("Part 2", returnBinFromAlphaNumeric(portionsOf_asm["Part 3"], 5)));
        instruction.insert(make_pair("Part 3", returnBinFromAlphaNumeric(portionsOf_asm["Part 1"], 5)));
        instruction.insert(make_pair("Part 4", getCodeFromDictionary(functionDictionary(), returnOPCODE(_asm))));
    } else {
        if(_asm[0] == 'b') {
            instruction.insert(make_pair("Part 1", returnBinFromAlphaNumeric(portionsOf_asm["Part 1"], 5)));
            instruction.insert(make_pair("Part 2", "00000"));
            int dLineNumber = 4 * (getLineNumber(fileName, portionsOf_asm["Part 2"] + ":") - currentLineNumber);
            instruction.insert(make_pair("Part 3", intToBinary(dLineNumber, 16)));
        } else if(_asm[0] == 'j') {
            if(checkIfContainsR(_asm) == true) {
                string registerBin = returnBinFromAlphaNumeric(portionsOf_asm["Part 1"], 26);
                instruction.insert(make_pair("Part 1", registerBin));
            } else {
                instruction.insert(make_pair("Part 1", intToBinary(getLineNumber(fileName, portionsOf_asm["Part 1"] + ":"), 26)));
            }
        } else if(_asm[0] + _asm[1] == 's' + 'h' || _asm[0] + _asm[1] == 's' + 'b' || _asm[0] + _asm[1] == 's' + 'w') {


            int *registerImmediate = parseIntFromAlphaNumeric(portionsOf_asm["Part 1"]);
            int immediate = *(registerImmediate);
            int _register = *(registerImmediate + 1);
            instruction.insert(make_pair("Part 1", intToBinary(_register, 5)));
            instruction.insert(make_pair("Part 2", returnBinFromAlphaNumeric(portionsOf_asm["Part 2"], 5)));
            instruction.insert(make_pair("Part 3", intToBinary(immediate, 16)));

        } else {
            instruction.insert(make_pair("Part 1", returnBinFromAlphaNumeric(portionsOf_asm["Part 1"], 5)));
            int *part2 = parseIntFromAlphaNumeric(portionsOf_asm["Part 2"]);
            int length = 1;
            int i = 0;
            while(*(part2 + i) != -1) {
                i++;
                length++;
            }
            if(length == 3) {
                int immediate = *(part2);
                int _register = *(part2 + 1);
                instruction.insert(make_pair("Part 2", intToBinary(_register, 5)));
                instruction.insert(make_pair("Part 3", intToBinary(immediate, 16)));
            } else {
                instruction.insert(make_pair("Part 1", returnBinFromAlphaNumeric(portionsOf_asm["Part 1"], 5)));
                instruction.insert(make_pair("Part 2", returnBinFromAlphaNumeric(portionsOf_asm["Part 2"], 5)));
                int *immediate = parseIntFromAlphaNumeric(portionsOf_asm["Part 3"]);
                instruction.insert(make_pair("Part 3", intToBinary(*immediate, 16)));
            }


        }
    }

    for(map<string, string>::iterator it = instruction.begin(); it != instruction.end(); ++it) {
            cout << "Key: " << it->first << ", Value: " << it->second << "\n";
        finalInstruction += it->second;
    }
    cout << finalInstruction << "\n";
    writeToFile("bin.txt", finalInstruction, false);
    cout << finalInstruction.length() << "\n";
    cout << returnHexFromBin(finalInstruction) << "\n";
    finalInstruction = returnHexFromBin(finalInstruction);
    writeToFile("hex.txt", finalInstruction, false);
}


int main(int argc, char * argv[]) {
    ofstream binFile("bin.txt");
    ofstream hexFile("hex.txt");
    string inputFileName;
    if(*argv == nullptr) {
        cout << "What is the name of your input file?" << "\n";
        cin >> inputFileName;
    } else {
        inputFileName = *argv;
        cout << inputFileName << "\n";
    }
    string readLine = "";
    ifstream inputFile(inputFileName);
    if(inputFile.is_open()) {
        while(getline(inputFile, readLine)) {
            buildInstruction2(readLine, inputFileName);
        }
        inputFile.close();
    } else {
        cout << "No file with that name" << "\n";
    }

    writeToFile("bin.txt", "\0", true);
    writeToFile("hex.txt", "\0", true);


    
    return 0;
}


