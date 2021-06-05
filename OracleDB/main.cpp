#include "CODBC.h"
#include <conio.h>
#include <ctime>
using namespace std;

#pragma warning( disable : 4996 )

// 201663021 �̰��� 
// ����깰 �̷��� �����ͺ��̽� C++ ����

#define DNS_name L"trace_DB" // ODBC�� ������ �����ͺ��̽�
#define User_name L"lee" // �����ͺ��̽� ��Ʈ���� ����
#define Password L"1213" // �����ͺ��̽� ��Ʈ���� ���� ��й�ȣ

wstring GetCurTime()
{
    wstring result;
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    result += to_wstring(t->tm_year + 1900); result += L"-";
    result += to_wstring(t->tm_mon + 1); result += L"-";
    result += to_wstring(t->tm_mday); result += L" ";
    result += to_wstring(t->tm_hour); result += L":";
    result += to_wstring(t->tm_min); result += L":";
    result += to_wstring(t->tm_sec);
    return result;
}

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
            wcout << L"\n";

            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. ������ڿ� �ŷ�\n4. ����ǰ ��ȸ\n�Է�: ";
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
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n4. ��й�ȣ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update retailer set ret_phone = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update retailer set ret_address = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                // update sql ����
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update retailer set ret_name = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                // update sql ����
            }
            else if (stoi(Input) == 4) {
                wcout << L"�����Ͻ� ��й�ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                // update sql ����
            }
            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // �Ǹ��� �ŷ� ���� ��ȸ
        else if (Stance == L"Seller_Receipt") {
            // �ŷ� ���� ���̺� ��ȸ sql
            sql = L"select * from wr_recipt where wr_rid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Wname, ProdName;

            // ������� �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select whole_name from wholesaler where whole_id = '" + tableData.Tuples[i][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Wname.push_back(tableBuffer.Tuples[0][0]);
            }

            // ����ǰ �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wstring pid = tableData.Tuples[i][2];
                if (pid[0] == 'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";                    
                }
                else if (pid[0] == 'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[0] == 'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                ProdName.push_back(tableBuffer.Tuples[0][0]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"�������: " << Wname[i] << L"\n";
                wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Seller_Init";
        }

        // �Ǹ��� ������ڿ� �ŷ�
        else if (Stance == L"Seller_Trade") {
            
            // ������ڵ� �����ֱ�
            sql = L"select * from wholesaler;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"������� ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"������� �̸�: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"������� �ּ�: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"������� ��ȭ��ȣ: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"���� �ü�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            vector<wstring> rec_Inputs;

            wcout << L"�ŷ� �� ������� ID�� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;
            rec_Inputs.push_back(Input);
            rec_Inputs.push_back(ID_Input);

            system("cls");

            sql = L"select wr_prodid, wr_cost, wr_remark from wr_recipt where wr_wid = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> ProdName, Unit;
            for (int i = 0; i < tableData.Tuples.size(); i++)
            {
                wstring pid = tableData.Tuples[i][0];
                if (pid[0] == 'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                }
                else if (pid[0] == 'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[0] == 'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);
                
                sql = L"select product_item, product_retail_unit from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);
                ProdName.push_back(tableBuffer.Tuples[0][0]);
                Unit.push_back(tableBuffer.Tuples[0][1]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"����ǰ ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"����ǰ �̸�: " << ProdName[i] << L"\n";
                wcout << L"�����ڿ� �ŷ��� ����: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"�ŷ� ����: " << Unit[i] << L"\n";
                wcout << L"�����ڿ� �ŷ��� Ư�̻���: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ŷ��� ���깰 ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� �ð� �Է�
            rec_Inputs.push_back(GetCurTime());

            wcout << L"�ŷ��Ͻ� ������ �ݾ�(����: ��)�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� ������
            sql = L"select product_retail_unit from product where product_id = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            rec_Inputs.push_back(tableData.Tuples[0][0]);

            wcout << L"������ �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            wcout << L"Ư�̻����� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            sql = L"insert into wr_recipt values('" + rec_Inputs[0] + L"', '"
                + rec_Inputs[1] + L"', '" + rec_Inputs[2] + L"', '" + rec_Inputs[3] + L"', "
                + rec_Inputs[4] + L", '" + rec_Inputs[5] + L"', " + rec_Inputs[6] + L", '"
                + rec_Inputs[7] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �ŷ��Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // �Ǹ��ڰ� ������ ��ǰ �̷� ��ȸ, ������� �ŷ��������� �۹� ID �̰� �� ������ ���
        else if (Stance == L"Seller_Trace") {
            wcout << L"������� �̸��� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;

            sql = L"select * from wholesaler where whole_name = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"������� ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"������� �̸�: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"������� �ּ�: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"������� ��ȭ��ȣ: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"���� �ü�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"������� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            // ������ ȹ��
            sql = L"select whole_facility from wholesaler where whole_id = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wstring fac_loc = tableData.Tuples[0][0];

            wcout << L"�˻��ϰ��� �ϴ� ���깰 ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;

            DB_Table prodTable;
            if (Input[0] == 'A') {
                sql = L"select * from agriculture where ag_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);               

                wcout << L"������ ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"������: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"���: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"GAP ���� ����: " << tableData.Tuples[0][8] << L"\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[0][9] << L"\n";
            }
            else if (Input[0] == 'S') {
                sql = L"select * from seafood where sea_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);

                wcout << L"������ ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"���: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[0][8] << L"\n";
            }
            else if (Input[0] == 'L') {
                sql = L"select * from livestock where live_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);

                wcout << L"������ ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"���: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[0][8] << L"\n";
            }

            wcout << L"�̵����\n" << tableData.Tuples[0][3] << L"|\n|\n|\nV\n" << fac_loc << L"\n";
        }

        // ������ �޴�
        else if (Stance == L"Wholesaler_Init") {
            // �ڽ��� ���� ���
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. �����ڿ� �ŷ�\n4. ����ǰ ��ȸ\n5. �α׾ƿ�\n�Է�: ";
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
            else if (stoi(Input) == 3) {
                Stance = L"Wholesaler_Trace";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Init";
            }
        }

        // ������ ����
        else if (Stance == L"Wholesaler_Modify") {
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n4. �����ü� �ּ�\n5. ��й�ȣ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_phone = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

                // update sql ����
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_address = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                // update sql ����
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_name = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                // update sql ����
            }
            else if (stoi(Input) == 4) {
                wcout << L"�����Ͻ� �����ü��� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_facility = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                // update sql ����
            }
            else if (stoi(Input) == 5) {
                wcout << L"�����Ͻ� ��й�ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
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

        // �Ǹ��ڿ��� �ŷ� ����
        else if (Stance == L"Wholesaler_Receipt_Seller") {
            // �ŷ� ���� ���̺� ��ȸ sql
            sql = L"select * from wr_recipt where wr_wid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Rname, ProdName;

            // �Ǹ��� �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select ret_name from retailer where ret_id = '" + tableData.Tuples[i][1] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Rname.push_back(tableBuffer.Tuples[0][0]);
            }

            // ����ǰ �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wstring pid = tableData.Tuples[i][2];
                if (pid[0] == 'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                }
                else if (pid[0] == 'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[0] == 'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                ProdName.push_back(tableBuffer.Tuples[0][0]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"�Ǹ���: " << Rname[i] << L"\n";
                wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Wholesaler_Init";
        }

        // �����ڿ��� �ŷ� ����
        else if (Stance == L"Wholesaler_Receipt_Producer") {
             // �ŷ� ���� ���̺� ��ȸ sql
             sql = L"select * from pw_recipt where pw_wid = '" + ID_Input + L"';";
             DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
             DB.GetTableData(tableData);

             DB_Table tableBuffer;
             vector<wstring> Rname, ProdName;

             // ������ �̸� ���ϱ�
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 sql = L"select prod_name from producer where prod_id = '" + tableData.Tuples[i][1] + L"';";
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 Rname.push_back(tableBuffer.Tuples[0][0]);
             }

             // ����ǰ �̸� ���ϱ�
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 wstring pid = tableData.Tuples[i][2];
                 if (pid[0] == 'A') {
                     sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                 }
                 else if (pid[0] == 'S') {
                     sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                 }
                 else if (pid[0] == 'L') {
                     sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                 }
                 else {
                     continue;
                 }
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 ProdName.push_back(tableBuffer.Tuples[0][0]);
             }

             wcout << L"------------------------------------------\n";
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 wcout << L"������: " << Rname[i] << L"\n";
                 wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                 wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                 wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                 wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                 wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                 wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                 wcout << L"------------------------------------------\n";
             }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���";
            wstring Input;
            wcin >> Input;
            Stance = L"Wholesaler_Init";
        }

        else if (Stance == L"Wholesaler_Trade") {
            // �����ڵ� �����ֱ�
            sql = L"select * from producer;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"������ ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"������ �̸�: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"������ �ּ�: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"������ ��ȭ��ȣ: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            vector<wstring> rec_Inputs;

            wcout << L"�ŷ��� ������ ID�� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;
            rec_Inputs.push_back(ID_Input);
            rec_Inputs.push_back(Input);

            system("cls");

            // product id ȹ��
            DB_Table tableBuffer;
            sql = L"select * from agriculture where ag_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableBuffer);
            for (int i = 0; i < tableBuffer.Tuples.size(); i++) {
                wcout << L"";
            }
            sql = L"select * from seafood where sea_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableBuffer);
            for (int i = 0; i < tableBuffer.Tuples.size(); i++) {
                
            }
            sql = L"select * from livestock where live_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableBuffer);
            for (int i = 0; i < tableBuffer.Tuples.size(); i++) {
                
            }

            // ���깰 Ư�� ���
            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableBuffer.Tuples.size(); i++) {
                sql = L"select * from product where product_id = '" + tableBuffer.Tuples[i][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"����ǰ: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"������ �̸�: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"������ �ּ�: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"������ ��ȭ��ȣ: " << tableBuffer.Tuples[i][3] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ŷ��� ���깰 ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� �ð� �Է�
            rec_Inputs.push_back(GetCurTime());

            wcout << L"�ŷ��Ͻ� ������ �ݾ�(����: ��)�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� ������
            sql = L"select product_retail_unit from product where product_id = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            rec_Inputs.push_back(tableData.Tuples[0][0]);

            wcout << L"������ �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            wcout << L"Ư�̻����� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            sql = L"insert into wr_recipt values('" + rec_Inputs[0] + L"', '"
                + rec_Inputs[1] + L"', '" + rec_Inputs[2] + L"', '" + rec_Inputs[3] + L"', "
                + rec_Inputs[4] + L", '" + rec_Inputs[5] + L"', " + rec_Inputs[6] + L", '"
                + rec_Inputs[7] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �ŷ��Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Seller_Init";











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