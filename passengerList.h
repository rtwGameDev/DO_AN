#pragma once
#include <iostream>
#include <string>
#include <fstream>
// male: nam
// female: nữ
enum Sex { male, female };

// Giải mã JSON
// lastName: Họ
// firstName: Tên
void parseJSONPassenger(std::string &idCard, std::string &lastName, std::string &firstName, Sex &sex, std::string JSON) {
	int length = (int) JSON.length();
	int i = 0;
	for (; i <= length - 1; i++) {
		if (JSON[i] != '#') {
			idCard = idCard + JSON[i];
		}
		else break;
	}
	i++;
	for (; i <= length - 1; i++) {
		if (JSON[i] != '#') {
			lastName = lastName + JSON[i];
		}
		else break;
	}
	i++;
	for (; i <= length - 1; i++) {
		if (JSON[i] != '#') {
			firstName = firstName + JSON[i];
		}
		else break;
	}
	i++;
	// '0' -> name
	// '1' -> nữ
	if (JSON[length - 1] == '0') sex = male;
	else sex = female;
}

// Mã hóa JSON
std::string stringtifyPassenger(std::string idCard, std::string lastName, std::string firstName, Sex sex) {
	std::string Sx = sex == male ? "0" : "1";
	return idCard + "#" + lastName + "#" + firstName + "#" + Sx;
}

// Xây kiểu dữ liệu hành khách
struct Passenger {
	std::string idCard;
	std::string lastName;
	std::string firstName;
	Sex sex;
	
	// Constructer
	Passenger() {};
	Passenger(std::string idCard, std::string lastName, std::string firstName, Sex sex) {
		this->idCard = idCard;
		this->lastName = lastName;
		this->firstName = firstName;
		this->sex = sex;
	}

	// In thông tin hành khách: Chỗ giới tính có thể in trong slint để có dấu
	void prInfo() {
		std::cout << " --- " << lastName << " " << firstName << " --- " << ((sex == male) ? "Nam" : "Nu") << "\n";
	}

	// destructor 
	~Passenger(){};
};

// Xây dựng Info 1 node cây AVL
struct nodeAVLPassenger {
	Passenger info;
	nodeAVLPassenger *left;
	nodeAVLPassenger *right;
	int height = 1;
	
	// Constructor
	nodeAVLPassenger() {
		this->left = nullptr;
		this->right = nullptr;
	};
	nodeAVLPassenger(Passenger Info) {
		this->info = info;
	}
	
	
	// Destructor
	~nodeAVLPassenger() {};
};

// Lớp Passenger_list
class Passenger_list {
	private:
		nodeAVLPassenger *root = nullptr;
		int numberOfPassenger = 0;

		int max(int a, int b) {
			return a > b ? a : b;
		}

		// Trả lại chiều cao của 1 node
		int heightNode(nodeAVLPassenger *head) {
			if (head != nullptr) return head->height;
			else return 0;
		}

		// Trả lại chỉ số cân bằng 
		int getBalance(nodeAVLPassenger *head) {
			return  heightNode(head->left) - heightNode(head->right);
		}

		// Xoay
		// Xoay trái khi cây bị lệch phải
		nodeAVLPassenger *rotateLeft(nodeAVLPassenger *root) {
			nodeAVLPassenger *newRoot = root->right;
			root->right = newRoot->left;
			newRoot->left = root;
			root->height = 1 + max(heightNode(root->left), heightNode(root->right));
			newRoot->height = 1 + max(heightNode(newRoot->left), heightNode(newRoot->right));
			return newRoot;
		}
		// xoay phải khi cây bị lệch trái
		nodeAVLPassenger *rotateRight(nodeAVLPassenger *root) {
			nodeAVLPassenger *newRoot = root->left;
			root->left = newRoot->right;
			newRoot->right = root;
			root->height = 1 + max(heightNode(root->left), heightNode(root->right));
			newRoot->height = 1 + max(heightNode(newRoot->left), heightNode(newRoot->right));
			return newRoot;
		}

		// Thêm hành khách.. nên sửa head -> this
		nodeAVLPassenger *insertPassenger(Passenger newInfo, nodeAVLPassenger *head) {
			
			// xử lý trường hợp rỗng
			if (head == nullptr) {
				numberOfPassenger++;
				return new nodeAVLPassenger(newInfo);
			}

			// insert node như cây nhị phân bình thường
			if (newInfo.idCard > head->info.idCard) head->right = insertPassenger(newInfo, head->right);
			else if (newInfo.idCard < head->info.idCard) head->left = insertPassenger(newInfo, head->left);
			else return head;

			// Tính lại chiều cao và lấy chỉ số cân bằng
			head->height = 1 + max(heightNode(head->left), heightNode(head->right));
			int balance = getBalance(head);

			// Lệch phải -> quay trái
			if (balance < -1 && newInfo.idCard > head->right->info.idCard) 
				return rotateLeft(head);

			// Lệch phải trái
			if (balance < -1 && newInfo.idCard < head->right->info.idCard) {
				// đưa đó về lệch phải 
				head->right = rotateRight(head->right);
				return rotateLeft(head);
			}

			// Lệch trái -> quay phải
			if (balance > 1 && newInfo.idCard < head->left->info.idCard)
				return rotateRight(head);

			// Lệch trái phải
			if (balance > 1 && newInfo.idCard > head->right->info.idCard) {
				// đưa đó về lệch phải 
				head->left = rotateLeft(head->left);
				return rotateRight(head);
			}

			// Nếu đã là cây cân bẳng
			return head;
		}

		// Max node
		nodeAVLPassenger *maxNode(nodeAVLPassenger *head) {
			nodeAVLPassenger *temp = head;
			while (temp->right != nullptr) temp = temp->right;
			return temp;
		}
		
		// Xóa node hành khách
		nodeAVLPassenger *deletePassenger(std::string idCard, nodeAVLPassenger *head) {

			// Xử lý trường hợp rỗng
			if (head == nullptr) return head;

			// Chảy phải chạy trái ??
			if (head->info.idCard < idCard) head->right = deletePassenger(idCard ,head->right);
			else if (head->info.idCard > idCard) head->left = deletePassenger(idCard, head->left);

			// Tìm được node bằng
			else {
				if ((head->left == nullptr) || (head->right == nullptr)) {
					
					// kiểm tra có con mấy con hoặc không có con
					nodeAVLPassenger *temp = head->left;
					if (head->right != nullptr) temp = head->right;

					// No child case
					if (temp == nullptr) {
						temp = head;
						head = nullptr;
						delete temp; // Giải phóng bộ nhớ
					}

					// One child case
					else {
						*head = *temp;
						delete temp; // giải phóng bộ nhớ
					}
				}

				// Two child case
				else {
					nodeAVLPassenger *maxLeftPassenger = maxNode(head->left);
					head->info = maxLeftPassenger->info;
					head->left = deletePassenger(head->info.idCard, head->left);
				}
			}

			// Không còn j trả về luôn
			if (head == nullptr) return head;

			// Tính lại chiều cao và lấy chỉ số cân bằng
			head->height = 1 + max(heightNode(head->left), heightNode(head->right));
			int balance = getBalance(head);

			// Cân bằng cây
			if (balance < -1 && getBalance(head->right) <= 0)
				return rotateLeft(head);
			if (balance < -1 && getBalance(head->right) > 0) {
				head->right = rotateRight(head->right);
				return rotateLeft(head);
			}
			if (balance > 1 && getBalance(head->left) >= 0)
				return rotateRight(head);
			if (balance > 1 && getBalance(head->left) < 0) {
				head->left = rotateLeft(head->left);
				return rotateRight(head);
			}

			// cây cân bằng sẵn
			return head;
		}

		// có tồn tại or ko 
		void exist(std::string idCard, nodeAVLPassenger *head, nodeAVLPassenger *&temp) {
			if (head == nullptr) return;
			if (head->info.idCard == idCard) temp = head;
			if (head->info.idCard < idCard) exist (idCard, head->right, temp);
			else exist(idCard, head->left, temp);
		}

		// Show....
		
	public:
		int getNumberOfPassenger() {
			return this->numberOfPassenger;
		}
		bool isEmpty() {
			if (this->root == nullptr) return true;
			return false;
		}
		bool search(std::string idCard) {
			nodeAVLPassenger *temp = nullptr;
			exist(idCard, this->root, temp);
			if (temp == nullptr) return false;
			return true;
		}
		// get this-> luôn
		Passenger getInfoPassenger(std::string idCard, std::string lastName, std::string firstName, Sex sex) {
			Passenger newPassenger(idCard, lastName, firstName, sex);
			return newPassenger;
		}
		void insertNode(Passenger newPassenger) {
			this->root = insertPassenger(newPassenger, this->root);
		}
		void deleteNode(std::string idCard) {
			if (search(idCard)) {
				this->numberOfPassenger--;
				this->root = deletePassenger(idCard, this->root);
			}
		}
		// show...
		// Load dữ liệu hành khách
		void loadDataPassenger() {
			std::string idCard = "";
			std::string lastName = "";
			std::string firstName = "";
			Sex sex;
			int numberOfPassenger = 0;
			std::string JSON = "";
			std::fstream data;
			data.open("passengerList.txt", std::ios::in);
			data >> numberOfPassenger;
			data.ignore();
			for (int i = 1; i <= numberOfPassenger; i++) {
				idCard = ""; 
				lastName = "";
				firstName = "";
				std::getline(data, JSON);
				parseJSONPassenger(idCard, lastName, firstName, sex, JSON);
				Passenger newPassenger(idCard, lastName, firstName, sex);
				insertNode(newPassenger);
			}
		}
		
		// Delete
		void deleteAll(nodeAVLPassenger *&root) {
			if (root != nullptr) {
				deleteAll(root->left);
				deleteAll(root->right);
			}
		}
};