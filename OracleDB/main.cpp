#include "CODBC.h"
#include <conio.h>
using namespace std;

// 201663021 �̰��� 
// ����깰 �̷��� �����ͺ��̽� C++ ����

#define DNS_name L"trace_DB" // ODBC�� ������ �����ͺ��̽�
#define User_name L"lee" // �����ͺ��̽� ��Ʈ���� ����
#define Password L"1213" // �����ͺ��̽� ��Ʈ���� ���� ��й�ȣ

wstring GetPW()
{
    wstring PW;
    int index = 0;
    char chpw[256];
    while (true) // ���� ������ ���� �ݺ�
    {
        chpw[index] = _getch(); // �� ���ھ� ��й�ȣ �Է�
        if (chpw[index] != '\r') {
            if (chpw[index] == 8) {
                if (index > 0) {
                    cout << "\b \b";
                    index--;
                }
            }
            else {
                index++;
                cout << "*";
            }
        }
        else {
            chpw[index] = '\0';
            break;
        }
    }
    return PW;
}

int main()
{
    setlocale(LC_ALL, "");

    CODBC DB;
    DB.AllocateHandles();
    if (DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password) != SQL_SUCCESS) {
        return 1;
    }

    wstring Stance = L"Init";
    while (true) {
        system("cls");
        if (Stance == L"Init") {
            wcout << L"1. �α���\n2. ������\n3. ����\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Login";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Dev_Show";
            }
            else {
                Stance = L"Exit";
            }
        }

        // ������ ����
        else if (Stance == L"Dev_Show") {
            wcout << L"�Ⱦ���б� ��ǻ�Ͱ��а� 4�г� 201663021 �̰��� ����\n";
            wcout << L"����깰 �̷��� ������ ��� ����Ŭ �����ͺ��̽��� ODBC�� ���� C++�� �����߽��ϴ�.\n";
            wcout << L"�������̽��� �ܼ�â �������� �����˴ϴ�.\n";
            wcout << L"�����, ������, �Ǹ���, ������, �����ڿ� ���� �ٸ� ������ �־����ϴ�.\n";
            wcout << L"�α����� ���� �����ް� ���񽺸� �̿��ϼ���.";
            Sleep(5000);
            Stance = L"Init";
        }

        // �α��� ����
        else if (Stance == L"Login") {
            wstring ID_Input, PW_Input;
            wcout << L"ID: ";
            wcin >> ID_Input;
            wcout << L"PW: ";
            PW_Input = GetPW();

            // �ſ� ����
            wstring Authority;
        }

        // �� �޴�
        else if (Stance == L"Customer_Init") {
            wcout << L"������깰 �̷��� �ý����Դϴ�. ���Ͻô� ����� �������ּ���.\n";
            wcout << L"1. ��ǰ �̷���ȸ\n2. ��ǰ ���� �Ű�\n3. �α׾ƿ�\n�Է�: ";
            wstring Input;
            wcin >> Input;

            if (stoi(Input) == 1) {
                Stance = L"Customer_Trace";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Customer_Report";
            }
            if (stoi(Input) == 3) {
                Stance = L"Login";
            }
        }

        // �� �̷���ȸ
        else if (Stance == L"Customer_Trace") {
            wcout << L"Ȯ���Ϸ��� ��ǰ�� ��� ���ϳ���?\n";
            wcout << L"1. ��깰\n2. ��깰\n3. ���깰\n�Է�: ";
            wstring Input;
            wcin >> Input;
            int classify = stoi(Input);
            wcout << L"��ȸ�Ϸ��� ��ǰ�� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            bool Exist = false;
            if (classify == 1) {
                // sql�� ����
            }
            else if (classify == 2) {
                // sql�� ����
            }
            else if (classify == 3) {
                // sql�� ����
            }

            if (Exist) {
                Stance = L"Customer_Result";
            }
            else {
                wcout << L"��ȸ�Ϸ��� ��ǰ�� �����ϴ�.\n";
                Sleep(2000);
                Stance = L"Customer_Init";
            }
        }

        // �� ��ǰ �̷���ȸ ���
        else if (Stance == L"Customer_Result") {
            // ��ǰ ���� �ָ��� ���
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Customer_Init";
        }

        // �� ��ǰ �Ű�
        else if (Stance == L"Customer_Report") {
            wstring Input, P_ID;
            wcout << L"��ǰ�� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> P_ID;
            wcout << L"��ǰ�� � ���� �����ΰ���? ������ �ۼ����ּ���.\n�Է�: ";
            wcin >> Input;

            bool Exist = false;
            // ���� ���� sql ��

            if (!Exist) {
                wcout << L"��ȸ�Ϸ��� ��ǰ�� �����ϴ�.\n";
            }
            else {
                // ��ǰ ���� Insert sql��
                wcout << L"��ǰ�� ������ ���������� �����Ǿ����ϴ�!\n";
            }
            Sleep(2000);
            Stance = L"Customer_Init";
        }

        // �Ǹ��� �޴�
        else if (Stance == L"Seller_Init") {
            // �ڽ��� ���� ���
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. ������ڿ� �ŷ�\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Seller_Modify";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Seller_Receipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Seller_Trade";
            }
        }

        // �Ǹ��� ���� ����
        else if (Stance == L"Seller_Modify") {
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // �Ǹ��� �ŷ� ���� ��ȸ
        else if (Stance == L"Seller_Receipt") {
            // �ŷ� ���� ���̺� ��ȸ sql
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Seller_Init";
        }

        // �Ǹ��� ������ڿ� �ŷ�
        else if (Stance == L"Seller_Trade") {
            // ������ڵ� �����ִ� �� �ʿ�, ����, �������� ������ �ѱ�鼭 ������ �� �ְ� ����

            wcout << L"�ŷ� �� ������� ID�� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;
            
            wcout << L"�ŷ��� �۹� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            wcout << L"������ �ݾ��� �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            wcout << L"������ �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            wcout << L"Ư�̻����� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
        }

        // �Ǹ��ڰ� ������ ��ǰ �̷� ��ȸ, ������� �ŷ��������� �۹� ID �̰� �� ������ ���
        else if (Stance == L"Seller_Trace") {
            wcout << L"������� ID�� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;

            // ������ڰ� �ŷ��� �۹��� ���� ������ ������ �ѱ�鼭 ������ �� �ְ� ����
        }

        // ������ �޴�
        else if (Stance == L"Wholesaler_Init") {
            // �ڽ��� ���� ���
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. �����ڿ� �ŷ�\n4. ������깰 ��ȸ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Wholesaler_Modify";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Wholesaler_Receipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Wholesaler_Trade";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Wholesaler_Trace";
            }
        }

        else if (Stance == L"Wholesaler_Modify") {
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n4. �����ü� �ּ�\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            else if (stoi(Input) == 4) {
                wcout << L"�����Ͻ� �����ü��� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                // update sql ����
            }
            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Wholesaler_Init";
        }

        else if (Stance == L"Wholesaler_Receipt") {
            wcout << L"� �ŷ� ������ ��ȸ�Ͻǰǰ���?\n";
            wcout << L"1. �����ڿ��� �ŷ� ����\n2. �Ǹ��ڿ��� �ŷ� ����\n�Է�: ";

        }

        // ������ �޴�
        else if (Stance == L"Producer_Init") {

        }

        // ���� ����
        else {
            system("cls");
            break;
        }
    }

    DB.DisconnectDataSource();
    return 0;
}

/*
int main()
{
    setlocale(LC_ALL, "");
    
    CODBC DB;
    DB.AllocateHandles();
    DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password);
    DB.ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM plan_table;");
    DB.PrintTable(29);
    DB.ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM classes;");
    DB.PrintTable(3);
    DB.ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM emps;");
    DB.PrintTable(2);
    DB.ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM mydept;");
    DB.PrintTable(3);

    DB.DisconnectDataSource();
    return 0;
}
*/