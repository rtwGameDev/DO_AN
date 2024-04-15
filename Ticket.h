#pragma once
#include <string>
#include "myLib.h"
using namespace std;
using namespace NS_myLib;
namespace NS_Ticket {
	void ParseDataTicket(string& SCMND, string& TICKET_CODE, string JSON) {
		SCMND = "";
		TICKET_CODE = "";
		int i = 0;
		for (; i <= ((int)JSON.length()) - 1; ++i) {
			if (JSON[i] != '#') {
				SCMND = SCMND + JSON[i];
			}
			else break;
		}
		++i;
		for (; i <= ((int)JSON.length()) - 1; ++i) {
			TICKET_CODE = TICKET_CODE + JSON[i];
		}
	}
	string StringtifyTicket(string SCMND, string TICKET_CODE) {
		return SCMND + '#' + TICKET_CODE;
	}

	struct ticket {
		string SCMND;
		string TICKET_CODE{};
		ticket() {}
		ticket(int SCMND, string TICKET_CODE) {
			this->SCMND = SCMND;
			this->TICKET_CODE = TICKET_CODE;
		}
	};
	string handleLineCode(int iDong, int numberOfCharDONG) {
		string line_code = Number_to_String(iDong);
		for (int i = 1; i <= numberOfCharDONG - line_code.length(); ++i) {
			line_code = "0" + line_code;
		}
		return line_code;
	}
	void handleRangeCode(int soDay, int soDong, ticket* listTicket) {
		int index = 1;
		int count = 1;
		int numberOfCharDAY = 0;
		float round = log((float)soDay) / log(26.0);
		float floor = (int)(log((float)soDay) / log(26.0));
		if (round - floor == 0) numberOfCharDAY = floor;
		else numberOfCharDAY = floor + 1;
		if (numberOfCharDAY == 0) numberOfCharDAY = 1;
		int numberOfCharDONG = (int)Number_to_String(soDong).length();

		// sinh cau hinh dau + cau hinh cuoi
		string start = "", end = "";
		for (int i = 1; i <= numberOfCharDAY; ++i) {
			start = "A" + start;
			end = "Z" + end;
		}
		string running = start;
		while (count <= soDay) {
			for (int i = 1; i <= soDong; ++i) {
				string codeTicket = "";
				codeTicket = running + handleLineCode(i, numberOfCharDONG);
				listTicket[index++].TICKET_CODE = codeTicket;
			}
			if (running == end) break;
			// chay xong vong for, ta da co dc day ma ve o day thu count = 1
			// count++ => tang len chuyen den day ve tiep theo
			// tang running them 1
			count++;
			// j la chi so nam cuoi config AAA
			int j = numberOfCharDAY - 1;
			bool ctn = true;
			while (ctn) { // ctn -> continue
				if (j < 0) ctn = false;
				else {
					if (running[j] < 'Z') {
						running[j] = (char)((int)running[j] + 1);
						ctn = false;
					}
					else {
						for (int k = j; k <= numberOfCharDAY - 1; ++k) {
							running[k] = 'A';
						}
						j--;
					}
				}
			}
			// ket thuc vong while => ta co dc cau hinh tiep theo va chac chan se ko bi day
		}
	}
	void GTicketNumber(int soDay, int soDong, ticket* listTicket) {
		// so luong phan tu cua LIST_TICKET = soDay * soDong + 1
		handleRangeCode(soDay, soDong, listTicket);
	}
}
