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
    int i = 0;
    while (chpw[i] != '\0') {
        PW += (wchar_t)chpw[i++];
    }
    return PW;
}

int main()
{
    setlocale(LC_ALL, "");

    CODBC DB;
    DB.AllocateHandles();
    // DB ���� �ȵǸ� ���α׷� ����
    if (DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password) != SQL_SUCCESS) {
        return 1;
    }

    DB_Table tableData;
    wstring Stance = L"Init", ID_Input, PW_Input, sql;
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
            wcout << L"ID: ";
            wcin >> ID_Input;
            wcout << L"PW: ";
            PW_Input = GetPW();

            sql = L"select acc_pw from accout where acc_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            if (tableData.Tuples.empty() || tableData.Tuples[0][0] != PW_Input) {
                wcout << L"\n�� �� ���� ID �Ǵ� ��й�ȣ�Դϴ�.\n�ٽ� �Է��� �ּ���.";
                Sleep(1500);
                continue;
            }

            if (ID_Input[0] == L'P') {
                Stance = L"Producer_Init";
            }
            else if (ID_Input[0] == L'W') {
                Stance = L"Wholesaler_Init";
            }
            else if (ID_Input[0] == L'R') {
                Stance = L"Seller_Init";
            }
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
            sql = L"select * from retailer where ret_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"���̵�", L"��ü �̸�", L"�ּ�", L"��ȭ��ȣ" };
            tableData.PrintRecord(title, 0);

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
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. �����ڿ� �ŷ�\n�Է�: ";
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
        }

        // ������ ����
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
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Wholesaler_Receipt_Producer";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Wholesaler_Receipt_Seller";
            }
        }

        // �����ڿ��� �ŷ� ����
        else if (Stance == L"Wholesaler_Receipt_Producer") {
            // �ŷ� ���� ���̺� ��ȸ sql
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Wholesaler_Init";
        }

        // �Ǹ��ڿ��� �ŷ� ����
        else if (Stance == L"Wholesaler_Receipt_Producer") {
            // �ŷ� ���� ���̺� ��ȸ sql
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Wholesaler_Init";
        }

        else if (Stance == L"Wholesaler_Trade") {
            // ������ ��� ������
            wcout << L"�ŷ��� �������� ID�� �����ּ���\n�Է�: ";
            wstring Input;
            wcin >> Input;

            // �ش� �����ڰ� �Ĵ� �۹� ������
            wcout << L"�ŷ��� ������깰�� ID�� �����ּ���.\n�Է�: ";
            wcin >> Input;

            wcout << L"������ �ݾ��� �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            wcout << L"������ �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            wcout << L"Ư�̻����� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
        }

        // ������ �޴�
        else if (Stance == L"Producer_Init") {
            // �ڽ��� ���� ���
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. ������깰 ���\n4. ������깰 ����\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Producer_Modify";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Producer_Receipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Producer_Prod_Register";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Producer_Prod_Modify";
            }
        }

        else if (Stance == L"Producer_Modify") {
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
            Stance = L"Producer_Init";
        }

        else if (Stance == L"Producer_Receipt") {
            // �ŷ� ���� ���̺� ��ȸ sql
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Producer_Init";
        }

        // ������깰 ���
        else if (Stance == L"Producer_Prod_Register") {
            // ������깰 ���̺� ������
            wcout << L"����� ������깰 ID�� �����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;

            if (1) // ���̵� �� �տ� ���� �ٸ���
            {

            }
        }

        // ������깰 ����
        else if (Stance == L"Producer_Prod_Modify") {
            // �����ڰ� ��ǰ�� ��깰, ���깰, ��깰 ���̺� ������
            wcout << L"������ ������깰 ID�� �����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;

            // ������ ���� �� ����
        }

        else if (Stance == L"Admin_Init") {
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. �ο� ��ȸ\n2. �ŷ� ��ȸ\n3. ������깰 ��ȸ\n4. �̿��� ��ȸ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Admin_Report";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Admin_Recipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Admin_Product";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Admin_User";
            }
        }

        // �ο� ��ȸ
        else if (Stance == L"Admin_Report") {
            // �Ű� ���̺� ��ȸ
        }

        // �ŷ� ��ȸ
        else if (Stance == L"Admin_Recipt") {
            // �Ű� ���̺� ��ȸ
        }

        // ������깰 ��ȸ
        else if (Stance == L"Admin_Product") {

        }

        // �̿��� ��ȸ
        else if (Stance == L"Admin_User") {

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
    DB_Table TestTable;
    DB.AllocateHandles();
    DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password);
    DB.ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM accout;");
    DB.GetTableData(TestTable);
    DB.ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM producer;");
    DB.GetTableData(TestTable);

    DB.DisconnectDataSource();
    return 0;
}
*/