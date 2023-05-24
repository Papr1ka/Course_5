#include "TreeBase.h"

void test(TreeBase* obj)
{
	obj->insertNew();
}

TreeBase::TreeBase(TreeBase* p_head_object, string s_name, EMPTY_METHOD method)
{
	this->p_head_object = p_head_object;
	this->s_name = s_name;
	(this->*method) ();
}

void TreeBase::insertNew()
{
	if (p_head_object != nullptr)
	{
		p_head_object->p_sub_objects.push_back(this);
	}
}

void TreeBase::replaceByName()
{
	TreeBase* head = this->p_head_object;
	if (head == nullptr)
	{
		return;
	}
	auto end = head->p_sub_objects.cend();

	bool pasted = false;

	for (auto iter = head->p_sub_objects.cbegin(); iter != end; iter++)
	{
		if ((*iter)->s_name > this->s_name)
		{
			head->p_sub_objects.insert(iter, this);
			pasted = true;
			break;
		}
	}
	if (pasted)
	{
		head->p_sub_objects.erase(--head->p_sub_objects.cend());
	}
}

TreeBase* TreeBase::get_head()
{
	return this->p_head_object;
}

TreeBase::~TreeBase()
{
	int size = this->p_sub_objects.size();
	for (int i = 0; i < size; i++)
	{
		delete this->p_sub_objects[i];
	}
	this->deleteConnects();
}

TreeBase* TreeBase::get_sub_object(string s_name)
{
	int size = this->p_sub_objects.size();
	for (int i = 0; i < size; i++)
	{
		if (this->p_sub_objects[i]->get_name() == s_name)
		{
			return p_sub_objects[i];
		}
	}
	return nullptr;
}

string TreeBase::getAbsoluteCoordinate()
{
	string cord = "";
	TreeBase* obj = this;
	while (obj->get_head() != nullptr)
	{
		cord = "/" + obj->get_name() + cord;
		obj = obj->get_head();
	}
	if (cord.empty())
	{
		cord = "/";
	}
	return cord;
}

bool TreeBase::set_name(string s_new_name)
{
	if (p_head_object != nullptr && p_head_object->get_sub_object(s_new_name) == nullptr)
	{
		this->s_name = s_new_name;
		return true;
	}
	else if (p_head_object == nullptr)
	{
		this->s_name = s_new_name;
		return true;
	}
	return false;
}

void TreeBase::print_tree(string str)
{
	cout << endl << str << this->get_name();
	int size = this->p_sub_objects.size();
	for (int i = 0; i < size; i++)
	{
		this->p_sub_objects[i]->print_tree(str + "    ");
	}
}

void TreeBase::printTreeReady(string str)
{
	cout << endl << str << this->get_name() << " ";
	cout << (this->state != 0 ? "is ready" : "is not ready");
	int size = this->p_sub_objects.size();
	for (int i = 0; i < size; i++)
	{
		this->p_sub_objects[i]->printTreeReady(str + "    ");
	}
}

string TreeBase::get_name()
{
	return this->s_name;
}

TreeBase* TreeBase::searchSub(string name)
{
	TreeBase* base = nullptr;
	queue<TreeBase*> q;
	q.push(this);
	while (!q.empty())
	{
		TreeBase* current = q.front();
		q.pop();
		if (current->get_name() == name)
		{
			if (base != nullptr)
			{
				return nullptr;
			}
			else
			{
				base = current;
			}
		}
		int size = current->p_sub_objects.size();
		for (int i = 0; i < size; i++)
		{
			q.push(current->p_sub_objects[i]);
		}
	}
	return base;
}

TreeBase* TreeBase::searchRoot(string name)
{
	TreeBase* head = this;
	TreeBase* new_head;
	while (true)
	{
		new_head = head->get_head();
		if (new_head != nullptr)
		{
			head = new_head;
		}
		else
		{
			break;
		}
	}
	return head->searchSub(name);
}

void TreeBase::setState(int new_state)
{
	if (new_state != 0)
	{
		if (this->p_head_object != nullptr)
		{
			if (this->p_head_object->getState() != 0)
			{
				this->state = new_state;
			}
		}
		else
		{
			this->state = new_state;
		}
	}
	else
	{
		this->state = 0;
		int size = this->p_sub_objects.size();
		for (int i = 0; i < size; i++)
		{
			this->p_sub_objects[i]->setState(state);
		}
	}
}

int TreeBase::getState()
{
	return this->state;
}

bool TreeBase::deleteSub(string name)
{
	int size = this->p_sub_objects.size();
	for (int i = 0; i < size; i++)
	{
		if (this->p_sub_objects[i]->get_name() == name)
		{
			delete this->p_sub_objects[i];
			this->p_sub_objects.erase(this->p_sub_objects.begin() + i);
			return true;
		}
	}
	return false;
}

void TreeBase::deleteConnects()
{
	TreeBase* rootObject = this;
	while (rootObject->get_head() != nullptr) {
		rootObject = rootObject->get_head();
	}

	queue<TreeBase*> queue;
	queue.push(rootObject);
	while (!queue.empty())
	{
		TreeBase* obj = queue.front();
		queue.pop();

		int size = obj->connects.size();
		for (int i = 0; i < size; i++)
		{
		
			if (obj->connects[i]->p_object == this)
			{
				delete obj->connects[i];
				obj->connects.erase(obj->connects.begin() + i);
				i--;
				size--;
			}
		}
		size = obj->p_sub_objects.size();
		for (int i = 0; i < size; i++)
		{
			queue.push(obj->p_sub_objects[i]);
		}
	}
}

bool TreeBase::reOrder(TreeBase* new_head)
{
	if (new_head->p_head_object == nullptr || new_head == nullptr || new_head->get_sub_object(this->s_name) != nullptr)
	{
		return false;
	}

	TreeBase* obj = new_head;

	while (obj != nullptr)
	{
		if (obj == this)
		{
			return false;
		}
		obj = obj->get_head();
	}
	obj = this->p_head_object;
	int size = obj->p_sub_objects.size();
	for (int i = 0; i < size; i++)
	{
		if (obj->p_sub_objects[i]->get_name() == this->s_name)
		{
			obj->p_sub_objects.erase(obj->p_sub_objects.begin() + i);
			break;
		}
	}

	this->p_head_object = new_head;
	new_head->p_sub_objects.push_back(this);
	return true;
}

TreeBase* TreeBase::getByPath(string name)
{
	TreeBase* obj = this;
	if (name.empty())
	{
		return nullptr;
	}
	if (name[0] == '/' && name.size() == 1)
	{
		//вернуть корневой объект
		while (obj->get_head() != nullptr)
		{
			obj = obj->get_head();
		}
		return obj;
	}
	else if (name[0] == '.' && name.size() == 1)
	{
		return this;
	}
	else if (name[0] == '.')
	{
		//остальное равно имени поиск объект от текущего
		name = name.substr(1, name.size());
		return this->searchSub(name);
	}
	else if (name.size() > 1 && name[0] == '/' && name[1] == '/')
	{
		//остальное равно имени, поиск от корневого
		name = name.substr(2, name.size());
		return this->searchRoot(name);
	}
	else if (name[0] == '/')
	{
		//Найти по абсолютной координате, значит от корневого
		while (obj->get_head() != nullptr)
		{
			obj = obj->get_head();
		}
	}

	while (!name.empty())
	{
		int left = 0;
		if (name[left] == '/')
		{
			left++;
		}
		int right = left + 1;
		while (name[right] != '/' && right < name.size())
		{
			right++;
		}
		obj = obj->get_sub_object(name.substr(left, right - left));
		if (obj == nullptr)
		{
			return nullptr;
		}
		name = name.substr(right, name.size());
	}
	return obj;
}

void TreeBase::set_connect(TYPE_SIGNAL p_signal, TreeBase* p_object, TYPE_HANDLER p_object_handler)
{
	Conn* p_value;
	for (size_t i = 0; i < connects.size(); i++)
	{
		if (this->connects[i]->p_signal == p_signal && this->connects[i]->p_object == p_object && this->connects[i]->p_handler == p_object_handler)
		{
			return;
		}
	}

	p_value = new Conn();
	p_value->p_signal = p_signal;
	p_value->p_object = p_object;
	p_value->p_handler = p_object_handler;

	this->connects.push_back(p_value);
}

void TreeBase::emit_signal(TYPE_SIGNAL p_signal, string& s_command, TreeBase* handlerObject)
{
	string response;
	if (this->state == 0)
	{
		return;
	}
	TYPE_HANDLER p_handler;
	TreeBase* p_object;
	(this->*p_signal) (s_command);

	for (size_t i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal && connects[i]->p_object->getState() != 0 && (connects[i]->p_object == handlerObject || handlerObject == nullptr))
		{
			p_handler = connects[i]->p_handler;
			p_object = connects[i]->p_object;

			(p_object->*p_handler) (s_command);
		}
	}
}

void TreeBase::delete_connect(TYPE_SIGNAL p_signal, TreeBase* p_object, TYPE_HANDLER p_object_handler)
{
	for (size_t i = 0; i < connects.size(); i++)
	{
		if (this->connects[i]->p_signal == p_signal && this->connects[i]->p_object == p_object && this->connects[i]->p_handler == p_object_handler)
		{
			delete this->connects[i];
			this->connects.erase(this->connects.begin() + i);
		}
	}
}

void TreeBase::setSubTreeReady()
{
	queue<TreeBase*> q;
	q.push(this);
	while (!q.empty())
	{
		TreeBase* current = q.front();
		q.pop();
		current->state = 1;
		int size = current->p_sub_objects.size();
		for (int i = 0; i < size; i++)
		{
			q.push(current->p_sub_objects[i]);
		}
	}
}