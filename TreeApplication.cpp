#include "TreeApplication.h"

TreeApplication::TreeApplication(TreeBase* p_head_object) : TreeBase(p_head_object) {}

int TreeApplication::build_tree_objects()
{
	string s_sub_name, s_head_name;
	int number;
	TreeBase* p_head_object = this;
	TreeBase* buffer = nullptr;
	cin >> s_head_name;
	set_name(s_head_name);
	while (true)
	{
		cin >> s_head_name;
		if (s_head_name == "endtree")
		{
			break;
		}
		p_head_object = this->getByPath(s_head_name);
		cin >> s_sub_name;
		cin >> number;
		if (p_head_object == nullptr)
		{
			cout << "Object tree";
			this->print_tree();
			cout << endl << "The head object " << s_head_name << " is not found" << endl;
			return 1;
		}
		if (p_head_object->get_sub_object(s_sub_name) == nullptr)
		{
			switch (number)
			{
			case 2:
				new Class_2(p_head_object, s_sub_name);
				break;
			case 3:
				new Class_3(p_head_object, s_sub_name);
				break;
			case 4:
				new Class_4(p_head_object, s_sub_name);
				break;
			case 5:
				new Class_5(p_head_object, s_sub_name);
				break;
			case 6:
				new Class_6(p_head_object, s_sub_name);
				break;
			}
		}
		else
		{
			cout << s_head_name << "    Dubbing the names of subordinate objects" << endl;
		}
	}
	return 0;
}

int TreeApplication::exec_app()
{
	this->setSubTreeReady();
	cout << "Object tree";
	this->print_tree();
	TreeBase* p_head_object = this;
	TreeBase* buffer;
	TreeBase* buffer2;
	string s_head_name;
	string s_sub_name;
	string param;
	string str;
	while (true)
	{
		getline(cin, str);

		if (str.empty())
		{
			continue;
		}

		s_head_name = str.substr(0, str.find(' '));
		str = str.substr(str.find(' ') + 1, str.size() - str.find(' '));

		if (s_head_name == "END")
		{
			break;
		}

		s_sub_name = str.substr(0, str.find(' '));
		str = str.substr(str.find(' ') + 1, str.size() - str.find(' '));

		if (s_head_name == "SET")
		{
			buffer = p_head_object->getByPath(s_sub_name);
			if (buffer != nullptr)
			{
				p_head_object = buffer;
				cout << "Object is set: " << p_head_object->get_name() << endl;;
			}
			else
			{
				cout << "The object was not found at the specified coordinate: " << s_sub_name << endl;
			}
		}
		else if (s_head_name == "FIND")
		{
			buffer = p_head_object->getByPath(s_sub_name);
			if (buffer != nullptr)
			{
				cout << s_sub_name << "     Object name: " << buffer->get_name() << endl;
			}
			else
			{
				cout << s_sub_name << "     Object is not found" << endl;
			}
		}
		else if (s_head_name == "MOVE")
		{
			buffer = p_head_object->getByPath(s_sub_name);
			if (buffer == nullptr)
			{
				cout << s_sub_name << "    Head object is not found" << endl;
			}
			else
			{
				bool flag = p_head_object->reOrder(buffer);
				if (flag)
				{
					cout << "New head object: " << buffer->get_name() << endl;
				}
				else
				{
					if (buffer->get_sub_object(p_head_object->get_name()) != nullptr)
					{
						cout << s_sub_name << "     Dubbing the names of subordinate objects" << endl;
					}
					else if (p_head_object->get_head() == nullptr)
					{
						cout << s_sub_name << "      Redefining the head object failed" << endl;
					}
					else
					{
						cout << s_sub_name << "     Redefining the head object failed" << endl;
					}
				}
			}
		}
		else if (s_head_name == "DELETE")
		{
			buffer = p_head_object->get_sub_object(s_sub_name);
			if (buffer == nullptr)
			{
				continue;
			}
			string coord = buffer->getAbsoluteCoordinate();
			bool result = p_head_object->deleteSub(s_sub_name);
			if (result == true)
			{
				cout << "The object " << coord << " has been deleted" << endl;
			}
		}
		else if (s_head_name == "EMIT")
		{
			param = str;
			buffer = p_head_object->getByPath(s_sub_name);
			buffer->emit_signal(buffer->getSignal(), param);
		}
		else if (s_head_name == "SET_CONNECT")
		{
			param = str;
			buffer = p_head_object->getByPath(s_sub_name);
			buffer2 = p_head_object->getByPath(param);
			buffer->set_connect(buffer->getSignal(), buffer2, buffer2->getHandler());
		}
		else if (s_head_name == "DELETE_CONNECT")
		{
			param = str;
			buffer = p_head_object->getByPath(s_sub_name);
			buffer2 = p_head_object->getByPath(param);
			buffer->delete_connect(buffer->getSignal(), buffer2, buffer2->getHandler());
		}
		else if (s_head_name == "SET_CONDITION")
		{
			param = str;
			buffer = p_head_object->getByPath(s_sub_name);
			buffer->setState(stoi(param));
		}
	}
	return 0;
}

void TreeApplication::connect_tree_objects()
{
	string cord1, cord2;
	TreeBase* object1;
	TreeBase* object2;
	while (true)
	{
		cin >> cord1;
		if (cord1 == "end_of_connections")
		{
			break;
		}
		cin >> cord2;
		object1 = this->getByPath(cord1);
		object2 = this->getByPath(cord2);
		object1->set_connect(object1->getSignal(), object2, object2->getHandler());
	}
}

void TreeApplication::signal(string& param)
{
	cout << endl << "Signal from " << this->getAbsoluteCoordinate();
	param += " (class: 1)";
}
void TreeApplication::handler(string param)
{
	cout << endl << "Signal to " << this->getAbsoluteCoordinate() << " Text:  " << param;
}

TreeBase::TYPE_SIGNAL TreeApplication::getSignal()
{
	return (TYPE_SIGNAL)SIGNAL_D(TreeApplication::signal);
}

TreeBase::TYPE_HANDLER TreeApplication::getHandler()
{
	return (TYPE_HANDLER)HANDLER_D(TreeApplication::handler);
}
