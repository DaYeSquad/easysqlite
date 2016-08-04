#include "SqlFieldSet.h"

NS_SQL_BEGIN

////////////////////////////////////////////////////////////////////////////////
// FieldSet, public:

// Creation and lifetime --------------------------------------------------------

FieldSet::FieldSet(Field* definition)
{
	//make fields map from array
	if (definition)
	{
		int index = 0;
		while (true)
		{
			Field& field = definition[index];

			if (field.isEndingField())
				break;

			field._index = index;

			_vec.push_back(field);			
			_map[field.getName()] = &field;

			index++;
		}
	}
}

FieldSet::FieldSet(const std::vector<Field>& definition)
{
	copy(definition);
}

FieldSet::FieldSet(const FieldSet& source)
{
	copy(source._vec);
}

// Utils --------------------------------------------------------

int FieldSet::count() const {
	return (int)_vec.size();
}

Field* FieldSet::getByIndex(int index)
{
	if ((index >= 0) && (index < count()))
		return &_vec[index];

	return NULL;
}

Field* FieldSet::getByName(string name)
{
	return _map[name];
}

string FieldSet::getDefinition()
{
	string s;

	for (int index = 0; index < count(); index++)
	{
		if (Field* f = getByIndex(index))
		{
			s += f->getDefinition();
			if (index < (count() - 1))
				s += ", ";
		}
	}

	return s;
}

string FieldSet::definitionHash()
{
	return generateSHA(getDefinition());
}

string FieldSet::toString() const {
	string s;

	for (int index = 0; index < count(); index++)
	{
    // use const method instead (Frank Lin)
    /*
		if (Field* f = getByIndex(index))
		{
			s += f->getName();
			if (index < (count() - 1))
				s += ", ";
		}
     */
    
    string field_name = GetFieldNameByIndex(index);
    if (!field_name.empty()) {
      s += field_name;
      if (index < (count() - 1))
        s += ", ";
    }
	}

	return s;
}

FieldSet* FieldSet::createFromDefinition(string value)
{
	std::vector<string> vec;
	listToVector(value, vec, ",");

	std::vector<Field> fields;

	for (int index = 0; index < (int)vec.size(); index++)
	{
		std::string definition = vec[index];

		if (Field* field = Field::createFromDefinition(definition))
		{
			Field f(*field);
			fields.push_back(f);
			delete field;
		} else {
			return NULL;
		}
	}

	return new FieldSet(fields);
}

////////////////////////////////////////////////////////////////////////////////
// FieldSet, private:

void FieldSet::copy(const std::vector<Field>& definition)
{
  _vec = definition;
  
  //make fields map from vector
  for (int index = 0; index < (int)_vec.size(); index++)
  {
    Field& field = _vec[index];
    _map[field.getName()] = &field;
  }
}

// Utils (sakura extension) --------------------------------------------------------

string FieldSet::GetFieldNameByIndex(int index) const {
  if ((index >= 0) && (index < count()))
    return _vec[index].getName();
  
  return "";
}

NS_SQL_END
