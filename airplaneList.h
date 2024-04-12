#pragma once
#include "MyLib.h"
#include "DefineConst.h"

// Information of Plane
struct airplane {
    std::string idPlane; // key
    std::string typePlane;
    int colNumber; // Số dòng
    int rowNumber; // Số dãy

    // Constructor
    airplane(){};
    airplane(std::string idPlane, std::string typePlane, int rowNumber, int colNumber) {
        this->idPlane = idPlane;
        this->typePlane = typePlane;
        this->rowNumber = rowNumber;
        this->colNumber = colNumber;
    }

    // In thông tin máy bay
    void prInfo() {
        std::cout << idPlane << " - " << typePlane << " - " << rowNumber << " - " << colNumber;
    }

    // Check Seats
    ~airplane(){};
};

// Pointer Array -> plane_list (New thì mới làm việc được)
class airplaneList {
    private:
        int index = -1; 
        airplane *data[MAX_PLANE]; 
    public:
        // Constructor
        airplaneList (){};

        // Mảng trống
        bool isEmpty() {
            if (this->index == -1) return true;
            return false;
        }

        // Tìm máy bay 
        int findAirplane(std::string idPlane) {
            if (this->index != -1) {
                for (int i = 0; i <= this->index; i++) {
                    if (this->data[i]->idPlane == idPlane) return i;
                }
            }
            return -1;
        }

        // Đếm số máy bay và lấy số lượng phần tử
        int countIndexPlane () {
            return this->index + 1;
        }

        // In danh sách
        void show() {
            for (int i = 0; i <= this->index; i++) {
                this->data[i]->prInfo();
            }
        }

        // Thêm phần tử
        void addPlane(std::string idPlane, std::string typePlane, int rowNumber, int colNumber){
            if (this->index <= 299) {
                airplane* newairplane = new airplane(idPlane, typePlane, rowNumber, colNumber);
                data[++this->index] = newairplane;
            }
        }

        // Xóa 1 phần tử
        void deletePlane(std::string idPlane) {
            int index = this->findAirplane(idPlane);
            if (index != -1) {
                delete this->data[index];
                for (int i = index; i <= this->index - 1; i++) {
                    this->data[i] = this->data[i + 1];
                }
                --this->index;
            }
        }
        // Load data
        void LoadDataPlane() {
            std::string JSON;
            int index;
            std::string idPlane;
            std::string typePlane;
            int rowNumber;
            int colNumber;

            std::fstream out;
            out.open("airplaneList.txt");
            out >> index;
            out.ignore();
            for (int i = 0; i <= index; i++) {
                idPlane = "";
                typePlane ="";
                rowNumber = 0;
                colNumber = 0;
                std::getline(out, JSON);
                NS_myLib::parseJSON_Plane(idPlane, typePlane, rowNumber, colNumber, JSON);
                addPlane(idPlane, typePlane, rowNumber, colNumber);
            }
            out.close();
        }

        // Save Data
        void saveDataPlane() {
            std::fstream inp;
            inp.open("airPlaneList.txt", std::ios::out);
            int n = this->countIndexPlane();
            inp << n << "\n";
            for (int i = 0; i <= n - 1; i++) {
                std::string JSON = NS_myLib::stringtifyJSON_Plane(this->data[i]->idPlane, this->data[i]->typePlane, this->data[i]->rowNumber, this->data[i]->colNumber);
                inp << JSON << "\n";
            }
            inp.close();
        }

        // Xóa dữ liệu từng phần tử
        void deletePlaneList() {
	        for (int i = 0; i <= this->index; i++)
		    delete this->data[i];
        }

        // Destructor
        ~airplaneList(){};
};

