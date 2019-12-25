#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
const char* test = "test.txt";
//                 ﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌Student类﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
class student {
public:
	string ID;                                           //学号
	int chinese=0, math=0, english=0, computer=0;                //四门课程成绩
	string x;                                            //班级
	string date;                                        //学期
	string  name;                                        //姓名
	int sum=0;                                             //总分
	double ave=0;
	void getGrade() {
		cout << "\t\t请输入学生的姓名：";  cin >> name;
		cout << "\t\t请输入学生的学号：";  cin >> ID;
		cout << "\t\t请输入学生的班级：";  cin >> x;
		cout << "\t\t请输入学期：";        cin >> date;
		cout << "\t\t请输入语文的成绩：";  cin >> chinese;
		cout << "\t\t请输入数学的成绩：";  cin >> math;
		cout << "\t\t请输入英语的成绩：";  cin >> english;
		cout << "\t\t请输入计算机的成绩：";  cin >>computer;
	}
	void putGrade() {
		sum = chinese + math + english + computer;
		ave = sum / 4;
		cout << "姓名:" << name << ' ' << "学号:" << ID << ' ' << "班级" << x << ' ' << "学期：" << date << endl << "语文:" << chinese << ' '
			<< "数学:" << math << ' ' << "英语：" << english << ' ' << "计算机:" << computer << endl << "总成绩:" << sum << "  " << "平均成绩：" << ave
			<< endl << endl << endl;
	}
	void ReadFile(istream& in)
	{
		in >> name >> ID >> x >> date >> chinese >> math >> english >> computer >> sum >> ave;
	}
	void Writefile(ostream& out) {
		sum = chinese + math + english + computer;
		ave = sum / 4;
		out << name << ' ' << ID << ' ' << x << ' ' << date << ' ' << chinese << "   " << math << "   " << english << "     " << computer << "    " << sum << "     "  << ave << endl;
	}
};

//             ﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌message类﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
class message{
public:
	void put();
	void add();
	void modify();
	void search();
	void menu();
	void MWriteFile(vector<student>);
	bool search_in(const char* test, string num);                //查找学号是否重复；
private:
	ofstream fout;
	ifstream fin;
	student stu, stui;
	vector<student> stuVec;                             //声明vector容器，里边存的是student类，成员名为stuvec
};
void message::MWriteFile(vector<student> wrtVec) {
	fout.open("test.txt");
	for (auto& stuwrite : wrtVec)                         //遍历容器wrtVec，无需给出开头和结束，auto&可以修改其中的元素，stuwrite为其中成员；
		stuwrite.Writefile(fout);
	fout.close();
}
//                     ~~~~~~~~~~添加成绩~~~~~~~~~~~~~~~~
void message::add() {
	string nID;
	string str= "n";                                                      //确保循环进行
	cout << "请先输入学号检查是否已存在：(若想退出添加功能，请在此输入n)" << endl;
	cin >> nID;
	while (nID != str) {
		if (search_in(test, nID))
			cout << "此学号已经存在重新输入！\n";
		else {
			stu.getGrade();
			fout.open("test.txt", ios::app);                             //append方式打开，可以往后再添加string；
			stu.Writefile(fout);
			cout << "添加成功！" << endl;
			fout.close();
		}
		cout << "请继续输入学生学号，学号为n表示结束输入：";
		cin >> nID;

	}
	fout.close();
}

//                 ~~~~~~~~~~~~~~~~~输出成绩~~~~~~~~~~~~~~~
void message::put() {             
	string nclass;
	string line_2;
	cout << "请输入要查找的班级：";
	cin >> nclass;
	fin.open("test.txt", ios::app);
	while (getline(fin, line_2) ){
		istringstream record(line_2);                                   
		stu.ReadFile(record);
		if (stu.x == nclass ) {
			ofstream fout("class test.txt",ios::app);                           //append方式打开，可以往后再添加string；
			stu.Writefile(fout);
			stuVec.push_back(stu);                                             //将Student数组添加到vector中
			cout << "数据已存入该文件夹下的clss test文本中。";
		}
		else
			stuVec.push_back(stu);
	}
	fin.close();
}
//               ~~~~~~~~~~~~~~~~~~~~~~~~~~~修改~~~~~~~~~~~~~~~~~~~
void message::modify() {
	int caseJudge;
	string modifyCondition;
	string line;
	cout << "1.按姓名修改！" << endl
		<< "2.按学号修改！" << endl;
	fin.open("test.txt");
	cin >> caseJudge;
	switch (caseJudge)
	{
	case 1:
		cout << "请输入要修改的学生姓名：";
		cin >> modifyCondition;
		while (getline(fin, line)) {                                        //getline使读入的行内容换到line中
			istringstream record(line);                                     //写入record中
			stu.ReadFile(record);
			if (stu.name == modifyCondition) {
				stu.putGrade();
				cout << "确认修改？Y/N" << endl;
				char judgeC;
				cin >> judgeC;
				switch (judgeC)
				{
				case 'Y':
					stu.getGrade();
					stuVec.push_back(stu);                                 
					cout << "修改成功！" << endl;
					break;
				default:
					break;
				}
			}
			else
				stuVec.push_back(stu);
		}
		break;
	case 2:
		cout << "请输入要修改的学生学号：";
		cin >> modifyCondition;
		while (getline(fin, line)) {
			istringstream record(line);
			stu.ReadFile(record);
			if (stu.ID == modifyCondition) {
				stu.putGrade();
				cout << "确认修改？Y/N" << endl;
				char judgeC;
				cin >> judgeC;
				switch (judgeC)
				{
				case 'Y':
					stu.getGrade();
					stuVec.push_back(stu);
					cout << "修改成功！" << endl;
					break;
				default:
					break;
				}
			}
			else
				stuVec.push_back(stu);
		}
		break;
	default:
		break;
	}
	fin.close();
	MWriteFile(stuVec);
}

//                                ~~~~~~~~~~~~~~~~~~~寻找~~~~~~~~~~~~~~~~~~
void message::search() {                      
	  cout << "1.按姓名查找：" << endl
		<< "2.按学号查找：" << endl
		<< "请输入数字开始查找！"
	<< "（若未收到回应则没有该学生，请重新输入）" << endl;
	int judge;
	fin.open("test.txt");
	cin >> judge;
	string searchCondition;
	string nline;
	switch (judge)
	{
	case 1:
     	cout << "请输入学生姓名：";
		cin >> searchCondition;
		while (getline(fin, nline)) {
			istringstream record(nline);
			stu.ReadFile(record);
			if (stu.name == searchCondition) {
				stu.putGrade();
				if (stu.computer < 60 || stu.math < 60 || stu.chinese < 60 || stu.english < 60)
					cout << "不及格科目有：";
				if (stu.chinese < 60)
					cout << "语文";
				if (stu.english < 60)
					cout << "英语";
				if (stu.math < 60)
					cout << "数学";
				if (stu.computer < 60)
					cout << "计算机";
				if (stu.computer >= 60 && stu.math >= 60 && stu.chinese >= 60 && stu.english >= 60)
					cout << "没有不及格科目" << endl;
				stuVec.push_back(stu);
				break;
			}
			else {
				stuVec.push_back(stu);
			}
		}
		break;
	case 2:
		cout << "请输入学生学号：";
		cin >> searchCondition;
		while (getline(fin, nline)) {
			istringstream record(nline);
			stu.ReadFile(record);
			if (stu.ID == searchCondition) {
				stu.putGrade();
				if (stu.computer < 60 || stu.math < 60 || stu.chinese < 60 || stu.english < 60)
					cout << "不及格科目有：";
				if (stu.chinese < 60)
					cout << "语文";
				if (stu.english < 60)
					cout << "英语";
				if (stu.math < 60)
					cout << "数学";
				if (stu.computer < 60)
					cout << "计算机";
				if (stu.computer >= 60 && stu.math >= 60 && stu.chinese >= 60 && stu.english >= 60)
					cout << "没有不及格科目";
				stuVec.push_back(stu);
				break;
			}
			else {
				stuVec.push_back(stu);
			}
		}
		break;
	default:
		cout << "指令错误，请重新输入！" << endl;
		break;
	}
	fin.close();
}

//                         ~~~~~~~~~~~~~菜单~~~~~~~~~~~~~~
void message::menu() {
	cout << "★★★★★★★★★★★★★★★1.查看学生成绩信息★★★★★★★★★★★★★★★" << endl        //按照班级输出
		<< "★★★★★★★★★★★★★★★2.添加学生成绩信息★★★★★★★★★★★★★★★" << endl        //按照学期和班级输入
		<< "★★★★★★★★★★★★★★★3.查找学生成绩信息★★★★★★★★★★★★★★★" << endl       //学生成绩，不及格科目及学生名单
		<< "★★★★★★★★★★★★★★★4.修改学生成绩信息★★★★★★★★★★★★★★★" << endl
		<< "★★★★★★★★★★★★★★★0.从本系统退出    ★★★★★★★★★★★★★★★" << endl;
}
//                       ~~~~~~~~~~~~~~~~查重学号~~~~~~~~~~~~~~~~
bool message::search_in(const char* test, string num) {
	string line3;
	ifstream fin(test, ios_base::in | ios_base::binary);                      //base::in，防止删除现有内容，base::binary二进制打开防止换行符\n\r数据错误
	if (!fin.is_open()) 
		cout << "文件未打开";
	else
	{
		student stu;
		while (getline(fin, line3)) {
			istringstream record(line3);
			stu.ReadFile(record);
			if (stu.ID == num) 
			{ fin.close(); 
			return true; }
		}
	}

	fin.close();
	return false;

}

int main() {
	int x, y = 1;
	char judge;
	bool quit = false;
	while (y!=0) {
		message stum;
		stum.menu();
		cout << "请选择要进行的操作：";
		cin >> x;
		while (!quit) {
			switch (x)
			{
			case 0: quit = true;  break;
			case 1:stum.put();
				cout << "\n是否继续操作？Y/N？";
				cin >> judge;
				if (judge == 'Y')
					break;
				else {  quit = true; break; }
			case 2:stum.add();
				cout << "\n是否继续操作？Y/N？";
				cin >> judge;
				if (judge == 'Y') break;
				else { quit = true; break; }
			case 3:stum.search();
				cout << "\n是否继续操作？Y/N？";
				cin >> judge;
				if (judge == 'Y') break;
				else { quit = true; break; }
			case 4:stum.modify();
				cout << "\n是否继续操作？Y/N？";
				cin >> judge;
				if (judge == 'Y') break;
				else { quit = true; break; }
			default:
				break;
			}
		}
		if(x==0)
			y = 0;
		if (x != 0)
			quit = false;
	}
	return 0;
}
