#include <windows.h>
#include <iostream>
#include <sqlext.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <atlconv.h>

using namespace std;

struct DB_Table {
    int index = 0;
    vector<wstring> Attribute; // �Ӽ�
    vector<vector<wstring>> Tuples; // ���ڵ�

    void PrintTable(vector<wstring> &ptitle) {
        for (int i = 0; i < 5 && index + i < Tuples.size(); i++) {
            PrintRecord(ptitle, index + i);
            wcout << L"\n";
        }
    }

    void NextPage() {
        if (Tuples.size() <= 5)
            return;
        index = min(index + 5, Tuples.size() - 5);
    }

    void PrevPage() {
        index = max(0, index - 5);
    }

    void PrintRecord(vector<wstring>& ptitle, int n) {
        for (int i = 0; i < ptitle.size(); i++) {
            wcout << ptitle[i] << L": " << Tuples[n][i] << L"\n";
        }
    }
};

static wstring wstrconv(const string& src)
{
    USES_CONVERSION;
    return wstring(A2W(src.c_str()));
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
    // int GetTableData(int Degree, vector<vector<wstring>>& tableData);
    int GetTableData(DB_Table& tableData);
};