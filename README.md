# EasySqlite

## [Usage](https://code.google.com/archive/p/easysqlite/)

## More useful SQL extension:

```Cpp
class Table {
  ... Remainder ommited ...

public:
  bool addRecordIfNotExists(Record* record, string key, string value);
  bool updateRecord(Record* record, string where_condition);
  bool addOrReplaceRecord(Record *record);
  bool createIndex(const std::string& index_name, const std::string& column_name);
}
```

## License: New BSD License

