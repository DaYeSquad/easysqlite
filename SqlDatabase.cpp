#include "options.h"
#include "SqlDatabase.h"
#include "SqlRecordSet.h"
#include <time.h>
#include <unistd.h>

#ifdef WIN32
// Fix Chinese chars issues on Windows platform
std::string StringToUTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
#endif

namespace sql
{

Database::Database(void)
{
	_db = NULL;
	_result_open = SQLITE_ERROR;

	close();

#ifdef WIN32
  _tzset();
#else
    tzset();
#endif
}

Database::~Database(void)
{
	close();
}

sqlite3* Database::getHandle()
{
	return _db;
}

string Database::errMsg()
{
	return _err_msg;
}

void Database::close()
{
	if (_db)
	{
		sqlite3_close(_db);
		_db = NULL;
		_err_msg.clear();
		_result_open = SQLITE_ERROR;
	}
}

bool Database::isOpen()
{
	return (_result_open == SQLITE_OK);
}

bool Database::open(string filename)
{
	close();

#ifdef WIN32
	_result_open = sqlite3_open(StringToUTF8(filename).c_str(), &_db);
#else
  _result_open = sqlite3_open(filename.c_str(), &_db);
#endif

	if (isOpen())
	{
		sqlite3_busy_handler(_db, Database::busy_callback, (void*)_db);
		return true;
	} else {
		_err_msg = sqlite3_errmsg(_db);
	}

	THROW_EXCEPTION("Database::open: " + errMsg())

	return false;
}

bool Database::transactionBegin()
{
	RecordSet rs(_db);

	if (rs.query("BEGIN TRANSACTION"))
		return true;

	return false;
}

bool Database::transactionCommit()
{
	RecordSet rs(_db);

	if (rs.query("COMMIT TRANSACTION"))
		return true;

	return false;
}

bool Database::transactionRollback()
{
	RecordSet rs(_db);

	if (rs.query("ROLLBACK TRANSACTION"))
		return true;

	return false;
}

	int Database::busy_callback(void *, int count) {
		usleep(50000); //wait 50ms
		if (count < 20) {
			return 1;
		} else {
			return 0;
		}
	}

//sql eof
};
