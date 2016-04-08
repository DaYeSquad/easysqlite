//
// Copyright (C) 2010 Piotr Zagawa
//
// Released under BSD License
//

#pragma once

#include <map>
#include <vector>
#include "SqlField.h"
#include "sql_macro.h"

NS_SQL_BEGIN

class FieldSet {
public:
  
  // Creation and lifetime --------------------------------------------------------
  
	FieldSet(Field* definition);
	FieldSet(const std::vector<Field>& definition);
	FieldSet(const FieldSet& source);

  // Utils --------------------------------------------------------
  
	string toString() const;
	int count() const;
	Field* getByIndex(int index);
	Field* getByName(string name);

public:
	string definitionHash();
	string getDefinition();
	static FieldSet* createFromDefinition(string value);
  
private:
  std::vector<Field> _vec;
  std::map<string, Field*> _map;
  
  void copy(const std::vector<Field>& definition);
  
  // Utils (sakura extension) --------------------------------------------------------
  
  // Returns field name by index, if index is not valid, returns empty string instead.
  string GetFieldNameByIndex(int index) const;
};

NS_SQL_END
