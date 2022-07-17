#include <iostream>
#include <fstream>
#include "StudentsGroup.pb.h"
#include <sstream>


using namespace std;

//========================================================================================================================================
//Task 2. Protobuf classes
//========================================================================================================================================
/*
С помощью компилятора protobuf в отдельном пространстве имен сгенерировать классы :
a.FullName с полями имя, фамилия, отчество(отчество опционально).
b.Student с полями полное имя, массив оценок, средний балл.
c.StudentsGroup с полем массив студентов.
*/

//========================================================================================================================================
//Task 3. Interface classes
//========================================================================================================================================
/*
Создать класс StudentsGroup, который реализует интерфейсы:
*/

class IRepository
{
	virtual void Open() = 0; // бинарная десериализация в файл
	virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods
{
	virtual double GetAverageScore(const Students::FullName& name) = 0;
	virtual string GetAllInfo(const Students::FullName& name) = 0;
	virtual string GetAllInfo() = 0;
};

bool operator==(const Students::FullName& name1, const Students::FullName& name2)
{
	if ((name1.name() == name2.name()) && (name1.surname() == name2.surname()))
	{
		if ((name1.has_middle_name() == true) && (name2.has_middle_name() == true))
			if (name1.middle_name() == name2.middle_name())
				return true;
			else
				return false;
		else
			return false;
	}
	else
		return false;
}

namespace NoProtoBuf
{
	class StudentsGroup : public IRepository, public IMethods
	{
	private:
		Students::StudentsGroup m_group;
		string m_save_path;
	public:
		StudentsGroup(Students::StudentsGroup& _group) : m_group(_group) {}
		StudentsGroup(Students::StudentsGroup& _group, string _path) : m_group(_group), m_save_path(_path) {}
		StudentsGroup() {} //for cases when we read StudentsGroup from file only
		~StudentsGroup() {};

		void SetSavePath(string _path)
		{
			m_save_path.clear();
			m_save_path = _path;
		}

		void Save() override
		{
			ofstream out(m_save_path, ios_base::binary);
			if (out.is_open())
			{
				m_group.SerializeToOstream(&out);
				out.close();
				return;
			}
			else
			{
				cout << "Не удалось открыть файл для записи!";
				return;
			}
		}

		void Open() override
		{
			ifstream in(m_save_path, ios_base::binary);
			if (in.is_open())
			{
				m_group.ParseFromIstream(&in);
				in.close();
				return;
			}
			else
			{
				cout << "Не удалось открыть файл для чтения!";
				return;
			}
		}

		double GetAverageScore(const Students::FullName& name) override
		{
			if (m_group.student_group_size() == 0)
			{
				cout << "Не найдены записях о студентах!";
				return 0.0;
			}

			int index{ -1 };
			for (size_t i = 0; i < m_group.student_group_size(); i++)
			{
				if (m_group.student_group(i).name() == name)
					index = i;
			}

			if (index == -1)
			{
				cout << "Студент с таким именем не найден!";
				return 0.0;
			}

			return m_group.student_group(index).average_mark();
		}

		string GetAllInfo(const Students::FullName& name) override
		{
			if (m_group.student_group_size() == 0)
			{
				return "Не найдены записях о студентах!";
			}

			int index{ -1 };
			for (size_t i = 0; i < m_group.student_group_size(); i++)
			{
				if (m_group.student_group(i).name() == name)
					index = i;
			}

			if (index == -1)
			{
				return "Студент с таким именем не найден!";
			}

			stringstream return_string;
			return_string << "Студент " << m_group.student_group(index).name().surname() << " " << m_group.student_group(index).name().name() << " " << ((m_group.student_group(index).name().has_middle_name()) ? (m_group.student_group(index).name().middle_name()) : ("")) << " имеет следующие оценки: ";
			for (size_t i = 0; i < m_group.student_group(index).marks_size(); i++)
			{
				return_string << " " << m_group.student_group(index).marks(i);
				if (i + 1 == m_group.student_group(index).marks_size())
					return_string << ". ";
				else
					return_string << ",";
			}
			return_string << "Средний балл равен: " << m_group.student_group(index).average_mark() << "\n";
			return return_string.str();
		}

		string GetAllInfo() override
		{
			if (m_group.student_group_size() == 0)
			{
				return "Не найдены записях о студентах!";
			}

			stringstream return_string;

			for (size_t index = 0; index < m_group.student_group_size(); index++)
			{
				return_string << "Студент " << m_group.student_group(index).name().surname() << " " << m_group.student_group(index).name().name() << " " << ((m_group.student_group(index).name().has_middle_name()) ? (m_group.student_group(index).name().middle_name()) : ("")) << " имеет следующие оценки: ";
				for (size_t i = 0; i < m_group.student_group(index).marks_size(); i++)
				{
					return_string << " " << m_group.student_group(index).marks(i);
					if (i + 1 == m_group.student_group(index).marks_size())
						return_string << ". ";
					else
						return_string << ",";
				}
				return_string  << "Средний балл равен: " << m_group.student_group(index).average_mark() << "\n";
			}

			return return_string.str();
		}
	};
}


int main()
{
	system("chcp 1251");
	//========================================================================================================================================
	//Task 2. Protobuf classes
	//========================================================================================================================================
	
	{
		//test of protobuf classes
		Students::StudentsGroup TestGroup;
		TestGroup.add_student_group();
		TestGroup.add_student_group();

		TestGroup.mutable_student_group(0)->mutable_name()->set_name("Tim");
		TestGroup.mutable_student_group(0)->mutable_name()->set_surname("Kor");
		TestGroup.mutable_student_group(0)->mutable_name()->set_middle_name("Vad");
		TestGroup.mutable_student_group(1)->mutable_name()->set_name("Ann");
		TestGroup.mutable_student_group(1)->mutable_name()->set_surname("Cor");
		TestGroup.mutable_student_group(1)->mutable_name()->set_middle_name("Vas");
		TestGroup.mutable_student_group(0)->add_marks(0);
		TestGroup.mutable_student_group(0)->add_marks(0);
		TestGroup.mutable_student_group(0)->add_marks(0);
		TestGroup.mutable_student_group(0)->set_marks(0, 5);
		TestGroup.mutable_student_group(0)->set_marks(1, 4);
		TestGroup.mutable_student_group(0)->set_marks(2, 5);
		TestGroup.mutable_student_group(1)->add_marks(0);
		TestGroup.mutable_student_group(1)->add_marks(0);
		TestGroup.mutable_student_group(1)->add_marks(0);
		TestGroup.mutable_student_group(1)->set_marks(0, 5);
		TestGroup.mutable_student_group(1)->set_marks(1, 5);
		TestGroup.mutable_student_group(1)->set_marks(2, 3);

		TestGroup.mutable_student_group(0)->set_average_mark(static_cast<double>((TestGroup.mutable_student_group(0)->marks(0) + TestGroup.mutable_student_group(0)->marks(1) + TestGroup.mutable_student_group(0)->marks(2))) / 3);
		TestGroup.mutable_student_group(1)->set_average_mark(static_cast<double>((TestGroup.mutable_student_group(1)->marks(0) + TestGroup.mutable_student_group(1)->marks(1) + TestGroup.mutable_student_group(1)->marks(2))) / 3);
		
		//checking if TestGroup was written correctly
		{
		cout << "Имя студента: " << TestGroup.student_group(0).name().name() << " " << TestGroup.student_group(0).name().surname() << " " << ((TestGroup.student_group(0).name().has_middle_name()) ? (TestGroup.student_group(0).name().middle_name()) : ("")) << endl;
		cout << "Оценки студента: " << TestGroup.mutable_student_group(0)->marks(0) << " " << TestGroup.mutable_student_group(0)->marks(1) << " " << TestGroup.mutable_student_group(0)->marks(2) << endl;
		cout << "Средняя оценка: " << TestGroup.student_group(0).average_mark() << endl;
		}

		ofstream out("test.bin", ios_base::binary);
		TestGroup.SerializeToOstream(&out);
		out.close(); //will not read file properly without it!!

		ifstream in("test.bin", ios_base::binary);
		Students::StudentsGroup TestGroup2;
		bool check = TestGroup2.ParsePartialFromIstream(&in);
		cout << boolalpha << check << endl;
		cout << "Средняя оценка: " << TestGroup2.student_group(0).average_mark() << endl;
		in.close();

		google::protobuf::ShutdownProtobufLibrary();  // Optional:  Delete all global objects allocated by libprotobuf.
	}


	//========================================================================================================================================
	//Task 3. Interface classes
	//========================================================================================================================================

	{
		NoProtoBuf::StudentsGroup Group1;
		Group1.SetSavePath("test.bin");
		Group1.Open();
		Students::FullName name1;
		name1.set_name("Tim");
		name1.set_surname("Kor");
		name1.set_middle_name("Vad");
		cout << Group1.GetAllInfo(name1);
		cout << Group1.GetAverageScore(name1) << endl;
		cout << Group1.GetAllInfo();
	}
	return 0;
}
