#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Noi day chua cac ham doc lap voi cac thu vien
namespace NS_MyLib {
    string Number_to_String(int number) {
        if (number == 0) return "0";
        string result = "";
        int n;
        while (number != 0) {
            n = number % 10;
            result = ((char)(n + 48)) + result;
            number = (number - n) / 10;
        }
        return result;
    }
    int String_to_Number(string str) {
        int result = 0; int index = 1;
        for (int i = ((int)str.length()) - 1; i >= 0; --i) {
            if (str[i] < '0' || str[i] > '9') {
                return -1;
            }
            result += ((int)str[i] - 48) * index;
            index = index * 10;
        }
        return result;
    }

    // xoa 1 ki tu, bat dau tu start, do dai la length
    string eraseString(string str, int start, int length) {
        if (start < 0 || length < 0) return "ERROR";
        string result = "";
        if (start + length > ((int)str.length())) return "ERROR";
        else {
            for (int i = 0; i <= start - 1; ++i) {
                result = result + str[i];
            }
            for (int i = start + length; i <= ((int)str.length()) - 1; ++i) {
                result = result + str[i];
            }
        }
        return result;
    }

    // bo khoang trang o day string
    string TrimFirst(string str) {
        while (str.length() > 0 && str[0] == ' ') {
            str = eraseString(str, 0, 1);
        }
        return str;
    }

    // bo khoang trang o cuoi chuoi
    string TrimLast(string str) {
        while (((int)str.length()) > 0 && str[((int)str.length() - 1)] == ' ') {
            str = eraseString(str, ((int)str.length()) - 1, 1);
        }
        return str;
    }

    // xoa 2 khoang trang lien tiep ben trong chuoi
    string delSpace(string str) {
        string result = "";
        str = str + "r";
        for (int i = 0; i <= ((int)str.length()) - 2; ++i) {
            if (str[i] == ' ' && str[i + 1] == ' ') {
                continue;
            }
            else {
                result = result + str[i];
            }
        }
        return result;
    }

    // Kiem tra xem, 1 ki tu co la 1 chu cai, hay 1 so hay khong
    bool checkChar(char a) {
        if (
            ((a <= '9') && (a >= '0')) ||
            ((a <= 'z') && (a >= 'a')) ||
            ((a <= 'Z') && (a >= 'A')) ||
            (a == ' ')
            ) {
            return true;
        }
        return false;
        string str;
    }
    void toUppercase(char& c) {
        if (c <= 'z' && c >= 'a') c = ((int)c) - 32;
    }
    void toLowerCase(char& c) {
        if (c <= 'Z' && c >= 'A') c = ((int)c) + 32;
    }


    // Phân giải 1 chuỗi thành dữ liệu
    void parseJSON_Plane(std::string& idPlane, std::string& typePlane, int& rowNumber, int& colNumber, std::string JSON) {
        std::string strRowNumber = "";
        std::string strColNumber = "";
        //int length = ((int)JSON.length());
        int length = JSON.length();
        int i = 0;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                idPlane = idPlane + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                typePlane = typePlane + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                strRowNumber = strRowNumber + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                strColNumber = strColNumber + JSON[i];
            }
            else break;
        }
        rowNumber = library::String_to_Number(strRowNumber);
        colNumber = library::String_to_Number(strColNumber);
    }
    
    std::string stringtifyJSON_Plane(std::string idPlane, std::string typePlane, int rowNumber, int colNumber) {
        std::string strRowNumber = library::Number_to_String(rowNumber);
        std::string strColNumber = library::Number_to_String(colNumber);
        return idPlane + "#" + typePlane + "#" + strRowNumber + "#" + strColNumber;
    }
}
