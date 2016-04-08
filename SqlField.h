//
// Copyright (C) 2010 Piotr Zagawa
//
// Released under BSD License
//
// Updated by Frank Lin on 2016 - Added "const" to make it more compatitable with Google C++ Code Style.
//

#ifndef EASYSQLITE_SQL_FIELD_H_
#define EASYSQLITE_SQL_FIELD_H_

#include "SqlCommon.h"
#include "sql_macro.h"

NS_SQL_BEGIN

class Field {
public:
  friend class FieldSet;

  // Creation and lifetime --------------------------------------------------------
  
	Field(field_use use);
	Field(string name, field_type type, int flags = flag_none);
	Field(const Field& value);

public:
	
  // Getters --------------------------------------------------------

  int getIndex() const;
	string getName() const;
  string getTypeStr() const;
  field_type getType() const;
  
  // Utils --------------------------------------------------------
  
  bool isKeyIdField() const;
  bool isEndingField() const;
  bool isPrimaryKey() const;
  bool isNotNull() const;

  string getDefinition() const;
	static Field* createFromDefinition(string value);

private:
  string _name;
  field_use _use;
  field_type _type;
  int _index;
  int _flags;
};

NS_SQL_END

#endif /* EASYSQLITE_SQL_FIELD_H_ */
