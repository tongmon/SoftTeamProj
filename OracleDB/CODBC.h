#include <windows.h>
#include <iostream>
#include <sqlext.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct DB_Table {
    vector<wstring> Attribute; // �Ӽ�
    vector<vector<wstring>> tuples; // ���ڵ�
};

class CODBC {

    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN retcode;

    // Ư�� ���� ó��
    SQLSMALLINT length;
    SQLINTEGER rec = 0, native;
    SQLWCHAR state[7], message[256];

    // ���� ũ��
    SQLLEN mMaxBufferSize;

    // 

public:
    CODBC();
    ~CODBC();
    void AllocateHandles(); // �ڵ� ���� �ʱ�ȭ
    int ConnectDataSource(SQLWCHAR* DSN_name, SQLWCHAR* User_name, SQLWCHAR* Passwd); // ������ DBMS�� ����
    int ExecuteStatementDirect(SQLWCHAR* sql); // ������ �ٷ� ����
    int PrepareStatement(SQLWCHAR* sql); // ������ �غ�
    int ExecuteStatement(); // �غ�� ������ ����
    void DisconnectDataSource(); // �ڵ� ��� ����
    int PrintTable(int Degree, wstring title = L"Table Data Below"); // �Ӽ� ���� �־��ָ� ���̺� ��ȯ
    int GetTableData(int Degree, vector<vector<wstring>>& tableData);
};