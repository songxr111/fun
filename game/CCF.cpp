#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <random>
#include <stdexcept>

using namespace std;

// 比赛类型枚举
enum class CompetitionType {
	CSP,
	NOIP,
	GESP,
	APIO,
	NOI,
	WC
};

// 资助申请结构体
struct GrantApplication {
	int amount;
	int year;
	string status;
};

class Competition {
public:
	string name;
	int registrationFee;
	int participants;
	string status;
	
	Competition(string name, int fee, int participants) 
	: name(name), registrationFee(fee), participants(participants), status("未开始") {}
	
	void start() {
		status = "进行中";
	}
	
	void end(bool success) {
		status = success ? "成功举办" : "举办失败";
	}
};

class CCFPresident {
private:
	int calculateBaseCost(const Competition& comp) const {
		return static_cast<int>(comp.participants * comp.registrationFee * 0.3);
	}
	
public:
	string name;
	int supportRate;
	long budget;
	int currentYear;
	map<CompetitionType, Competition> competitions;
	vector<GrantApplication> grants;
	
	CCFPresident(string name) : name(name), supportRate(50), budget(1000000) {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		currentYear = 1900 + ltm->tm_year;
		
		competitions.emplace(CompetitionType::CSP, Competition("CSP认证", 300, 50000));
		competitions.emplace(CompetitionType::NOIP, Competition("NOIP", 500, 100000));
		competitions.emplace(CompetitionType::GESP, Competition("GESP认证", 200, 30000));
		competitions.emplace(CompetitionType::APIO, Competition("APIO", 800, 2000));
		competitions.emplace(CompetitionType::NOI, Competition("NOI竞赛", 0, 500));
		competitions.emplace(CompetitionType::WC, Competition("冬令营", 1500, 300));
	}
	
	bool organizeCompetition(CompetitionType type) {
		auto it = competitions.find(type);
		if (it == competitions.end()) {
			throw invalid_argument("无效的比赛类型");
		}
		
		Competition& comp = it->second;
		int cost = calculateBaseCost(comp);
		
		if (budget < cost) return false;
		
		comp.start();
		int income = comp.participants * comp.registrationFee;
		budget += (income - cost);
		return true;
	}
	
	void applyGrant(int amount) {
		grants.push_back({amount, currentYear, "待审核"});
	}
	
	void processGrants() {
		static mt19937 rng(random_device{}());
		uniform_real_distribution<double> dist(0.0, 1.0);
		
		for (auto& grant : grants) {
			if (grant.status == "待审核") {
				if (dist(rng) < 0.7) {
					grant.status = "通过";
					budget += grant.amount;
				} else {
					grant.status = "拒绝";
				}
			}
		}
	}
};

class CommentSystem {
public:
	static vector<string> generateComments(const CCFPresident& president) {
		vector<string> comments;
		
		for (const auto& pair : president.competitions) {
			const Competition& comp = pair.second;
			if (comp.status == "成功举办") {
				comments.push_back(comp.name + "顺利举办，" + president.name + "主席功不可没！");
			} else if (comp.status == "举办失败") {
				comments.push_back("强烈谴责" + comp.name + "的组织混乱！");
			}
		}
		
		if (president.budget > 5000000) {
			comments.push_back("CCF资金去向应该更透明！");
		} else if (president.budget < 500000) {
			comments.push_back("财政吃紧还能坚持办赛，不容易啊");
		}
		
		if (president.supportRate > 70) {
			comments.push_back(president.name + "是我们信任的好主席！");
		} else if (president.supportRate < 30) {
			comments.push_back("现任领导层应该集体辞职！");
		}
		
		return comments;
	}
};

class GameSystem {
private:
	vector<CCFPresident> presidents;
	size_t currentPresidentIndex;
	
	void showMainMenu() {
		cout << "\n操作列表:\n";
		cout << "1. 组织竞赛\n2. 申请资助\n3. 更换主席\n4. 查看评论\n5. 新年推进\n0. 退出\n";
	}
	
	void handleGrantApplication(CCFPresident& president) {
		cout << "请输入申请金额: ";
		int amount;
		cin >> amount;
		if (amount <= 0) {
			cout << "无效的金额！\n";
			return;
		}
		president.applyGrant(amount);
		cout << "已提交" << amount << "元的资助申请\n";
	}
	
public:
	GameSystem() : currentPresidentIndex(0) {
		presidents.emplace_back("杜子德");
		presidents.emplace_back("王选");
		presidents.emplace_back("新任领导");
	}
	
	void run() {
		while (true) {
			CCFPresident& current = presidents[currentPresidentIndex];
			
			cout << "\n当前主席: " << current.name << endl;
			cout << "支持率: " << current.supportRate << "%" << endl;
			cout << "可用资金: " << current.budget << "元" << endl;
			cout << "当前年份: " << current.currentYear << endl;
			showMainMenu();
			
			int choice;
			cin >> choice;
			
			if (choice == 0) break;
			
			switch (choice) {
				case 1: organizeCompetition(current); break;
				case 2: handleGrantApplication(current); break;
				case 3: changePresident(); break;
				case 4: showComments(current); break;
				case 5: advanceYear(current); break;
				default: cout << "无效的选项！\n";
			}
		}
	}
	
private:
	void organizeCompetition(CCFPresident& president) {
		cout << "选择竞赛类型:\n";
		cout << "1.CSP 2.NOIP 3.GESP 4.APIO 5.NOI 6.WC\n";
		
		int type;
		cin >> type;
		
		if (type < 1 || type > 6) {
			cout << "无效的选择！\n";
			return;
		}
		
		try {
			bool success = president.organizeCompetition(
				static_cast<CompetitionType>(type-1));
			
			if (success) {
				president.supportRate += 5;
				cout << "比赛成功启动!\n";
			} else {
				president.supportRate -= 3;
				cout << "资金不足无法举办!\n";
			}
		} catch (const exception& e) {
			cerr << "错误: " << e.what() << endl;
		}
	}
	
	void advanceYear(CCFPresident& president) {
		president.currentYear++;
		president.processGrants();
		president.supportRate += (president.budget > 1000000) ? 2 : -5;
		cout << "进入新年：" << president.currentYear << endl;
	}
	
	void showComments(const CCFPresident& president) {
		auto comments = CommentSystem::generateComments(president);
		cout << "\n=== 社会舆论 ===" << endl;
		for (const auto& comment : comments) {
			cout << "> " << comment << endl;
		}
	}
	
	void changePresident() {
		cout << "选择新任主席:\n";
		for (size_t i = 0; i < presidents.size(); ++i) {
			cout << i+1 << "." << presidents[i].name << endl;
		}
		
		size_t choice;
		cin >> choice;
		if (choice < 1 || choice > presidents.size()) {
			cout << "无效的选择！\n";
			return;
		}
		currentPresidentIndex = choice-1;
		cout << "已更换为" << presidents[currentPresidentIndex].name << "主席\n";
	}
};

int main() {
	GameSystem game;
	game.run();
	cout << "感谢使用CCF模拟器！\n";
	return 0;
}
