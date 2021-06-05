#include "CODBC.h"
#include <conio.h>
using namespace std;

// 201663021 이경준 
// 농수산물 이력제 데이터베이스 C++ 연동

#define DNS_name L"trace_DB" // ODBC와 연동할 데이터베이스
#define User_name L"lee" // 데이터베이스 컨트롤할 계정
#define Password L"1213" // 데이터베이스 컨트롤할 계정 비밀번호

wstring GetPW()
{
    wstring PW;
    int index = 0;
    char chpw[256];
    while (true) // 엔터 전까지 무한 반복
    {
        chpw[index] = _getch(); // 한 글자씩 비밀번호 입력
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
    // DB 연결 안되면 프로그램 종료
    if (DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password) != SQL_SUCCESS) {
        return 1;
    }

    DB_Table tableData;
    wstring Stance = L"Init", ID_Input, PW_Input, sql;
    while (true) {
        system("cls");
        if (Stance == L"Init") {
            wcout << L"1. 로그인\n2. 제작자\n3. 종료\n입력: ";
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

        // 제작자 설명
        else if (Stance == L"Dev_Show") {
            wcout << L"안양대학교 컴퓨터공학과 4학년 201663021 이경준 제작\n";
            wcout << L"농수산물 이력제 정보가 담긴 오라클 데이터베이스를 ODBC를 통해 C++과 연동했습니다.\n";
            wcout << L"인터페이스는 콘솔창 형식으로 제공됩니다.\n";
            wcout << L"사용자, 유통자, 판매자, 생산자, 관리자에 따라 다른 권한이 주어집니다.\n";
            wcout << L"로그인을 통해 인증받고 서비스를 이용하세요.";
            Sleep(5000);
            Stance = L"Init";
        }

        // 로그인 상태
        else if (Stance == L"Login") {
            wcout << L"ID: ";
            wcin >> ID_Input;
            wcout << L"PW: ";
            PW_Input = GetPW();

            sql = L"select acc_pw from accout where acc_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            if (tableData.Tuples.empty() || tableData.Tuples[0][0] != PW_Input) {
                wcout << L"\n알 수 없는 ID 또는 비밀번호입니다.\n다시 입력해 주세요.";
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

        // 고객 메뉴
        else if (Stance == L"Customer_Init") {
            wcout << L"농축수산물 이력제 시스템입니다. 원하시는 기능을 선택해주세요.\n";
            wcout << L"1. 제품 이력조회\n2. 제품 문제 신고\n3. 로그아웃\n입력: ";
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

        // 고객 이력조회
        else if (Stance == L"Customer_Trace") {
            wcout << L"확인하려는 제품이 어디에 속하나요?\n";
            wcout << L"1. 농산물\n2. 축산물\n3. 수산물\n입력: ";
            wstring Input;
            wcin >> Input;
            int classify = stoi(Input);
            wcout << L"조회하려는 제품의 ID를 입력해주세요.\n입력: ";
            wcin >> Input;

            bool Exist = false;
            if (classify == 1) {
                // sql문 실행
            }
            else if (classify == 2) {
                // sql문 실행
            }
            else if (classify == 3) {
                // sql문 실행
            }

            if (Exist) {
                Stance = L"Customer_Result";
            }
            else {
                wcout << L"조회하려는 제품이 없습니다.\n";
                Sleep(2000);
                Stance = L"Customer_Init";
            }
        }

        // 고객 제품 이력조회 결과
        else if (Stance == L"Customer_Result") {
            // 제품 정보 주르륵 출력
            wcout << L"아무 키를 눌러 뒤로가기";
            wstring Input;
            wcin >> Input;
            Stance = L"Customer_Init";
        }

        // 고객 제품 신고
        else if (Stance == L"Customer_Report") {
            wstring Input, P_ID;
            wcout << L"제품의 ID를 입력해주세요.\n입력: ";
            wcin >> P_ID;
            wcout << L"제품의 어떤 점이 문제인가요? 설명을 작성해주세요.\n입력: ";
            wcin >> Input;

            bool Exist = false;
            // 존재 여부 sql 문

            if (!Exist) {
                wcout << L"조회하려는 제품이 없습니다.\n";
            }
            else {
                // 제품 문제 Insert sql문
                wcout << L"제품의 문제가 정상적으로 접수되었습니다!\n";
            }
            Sleep(2000);
            Stance = L"Customer_Init";
        }

        // 판매자 메뉴
        else if (Stance == L"Seller_Init") {
            // 자신의 정보 출력
            sql = L"select * from retailer where ret_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"아이디", L"업체 이름", L"주소", L"전화번호" };
            tableData.PrintRecord(title, 0);

            wcout << L"이용하실 기능을 선택해주세요.\n1. 정보 수정\n2. 거래 내역 확인\n3. 유통업자와 거래\n입력: ";
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

        // 판매자 정보 수정
        else if (Stance == L"Seller_Modify") {
            wcout << L"수정하실 내용이 무엇인가요?\n1. 전화번호\n2. 주소\n3. 이름\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"수정하실 전화번호를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 주소를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 3) {
                wcout << L"수정하실 이름을 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // 판매자 거래 내역 조회
        else if (Stance == L"Seller_Receipt") {
            // 거래 내역 테이블 조회 sql
            wcout << L"아무 키를 눌러 뒤로가기";
            wstring Input;
            wcin >> Input;
            Stance = L"Seller_Init";
        }

        // 판매자 유통업자와 거래
        else if (Stance == L"Seller_Trade") {
            // 유통업자들 보여주는 것 필요, 다음, 이전으로 페이지 넘기면서 보여줄 수 있게 제작

            wcout << L"거래 할 유통업자 ID를 입력해주세요.\n입력: ";
            wstring Input;
            wcin >> Input;

            wcout << L"거래할 작물 ID를 입력해주세요.\n입력: ";
            wcin >> Input;

            wcout << L"단위당 금액을 입력해주세요.\n입력: ";
            wcin >> Input;

            wcout << L"수량을 입력해주세요.\n입력: ";
            wcin >> Input;

            wcout << L"특이사항을 입력해주세요.\n입력: ";
            wcin >> Input;
        }

        // 판매자가 구입할 제품 이력 조회, 유통업자 거래내역에서 작물 ID 뽑고 그 정보들 출력
        else if (Stance == L"Seller_Trace") {
            wcout << L"유통업자 ID를 입력해주세요.\n입력: ";
            wstring Input;
            wcin >> Input;

            // 유통업자가 거래한 작물에 대한 정보를 페이지 넘기면서 보여줄 수 있게 제작
        }

        // 유통자 메뉴
        else if (Stance == L"Wholesaler_Init") {
            // 자신의 정보 출력
            wcout << L"이용하실 기능을 선택해주세요.\n1. 정보 수정\n2. 거래 내역 확인\n3. 생산자와 거래\n입력: ";
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

        // 유통자 수정
        else if (Stance == L"Wholesaler_Modify") {
            wcout << L"수정하실 내용이 무엇인가요?\n1. 전화번호\n2. 주소\n3. 이름\n4. 관리시설 주소\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"수정하실 전화번호를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 주소를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 3) {
                wcout << L"수정하실 이름을 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 4) {
                wcout << L"수정하실 관리시설의 주소를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Wholesaler_Init";
        }

        else if (Stance == L"Wholesaler_Receipt") {
            wcout << L"어떤 거래 내역을 조회하실건가요?\n";
            wcout << L"1. 생산자와의 거래 내역\n2. 판매자와의 거래 내역\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Wholesaler_Receipt_Producer";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Wholesaler_Receipt_Seller";
            }
        }

        // 생산자와의 거래 내역
        else if (Stance == L"Wholesaler_Receipt_Producer") {
            // 거래 내역 테이블 조회 sql
            wcout << L"아무 키를 눌러 뒤로가기";
            wstring Input;
            wcin >> Input;
            Stance = L"Wholesaler_Init";
        }

        // 판매자와의 거래 내역
        else if (Stance == L"Wholesaler_Receipt_Producer") {
            // 거래 내역 테이블 조회 sql
            wcout << L"아무 키를 눌러 뒤로가기";
            wstring Input;
            wcin >> Input;
            Stance = L"Wholesaler_Init";
        }

        else if (Stance == L"Wholesaler_Trade") {
            // 생산자 목록 보여줌
            wcout << L"거래할 생산자의 ID를 적어주세요\n입력: ";
            wstring Input;
            wcin >> Input;

            // 해당 생산자가 파는 작물 보여줌
            wcout << L"거래할 농축수산물의 ID를 적어주세요.\n입력: ";
            wcin >> Input;

            wcout << L"단위당 금액을 입력해주세요.\n입력: ";
            wcin >> Input;

            wcout << L"수량을 입력해주세요.\n입력: ";
            wcin >> Input;

            wcout << L"특이사항을 입력해주세요.\n입력: ";
            wcin >> Input;
        }

        // 생산자 메뉴
        else if (Stance == L"Producer_Init") {
            // 자신의 정보 출력
            wcout << L"이용하실 기능을 선택해주세요.\n1. 정보 수정\n2. 거래 내역 확인\n3. 농축수산물 등록\n4. 농축수산물 수정\n입력: ";
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
            wcout << L"수정하실 내용이 무엇인가요?\n1. 전화번호\n2. 주소\n3. 이름\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"수정하실 전화번호를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 주소를 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            else if (stoi(Input) == 3) {
                wcout << L"수정하실 이름을 적어주세요\n입력: ";
                wcin >> Input;
                // update sql 실행
            }
            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        else if (Stance == L"Producer_Receipt") {
            // 거래 내역 테이블 조회 sql
            wcout << L"아무 키를 눌러 뒤로가기";
            wstring Input;
            wcin >> Input;
            Stance = L"Producer_Init";
        }

        // 농축수산물 등록
        else if (Stance == L"Producer_Prod_Register") {
            // 농축수산물 테이블 보여줌
            wcout << L"등록할 농축수산물 ID를 적어주세요.\n입력: ";
            wstring Input;
            wcin >> Input;

            if (1) // 아이디 맨 앞에 따라 다르게
            {

            }
        }

        // 농축수산물 수정
        else if (Stance == L"Producer_Prod_Modify") {
            // 생산자가 출품한 농산물, 수산물, 축산물 테이블 보여줌
            wcout << L"수정할 농축수산물 ID를 적어주세요.\n입력: ";
            wstring Input;
            wcin >> Input;

            // 수정할 내용 쭉 쓰기
        }

        else if (Stance == L"Admin_Init") {
            wcout << L"이용하실 기능을 선택해주세요.\n1. 민원 조회\n2. 거래 조회\n3. 농축수산물 조회\n4. 이용자 조회\n입력: ";
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

        // 민원 조회
        else if (Stance == L"Admin_Report") {
            // 신고 테이블 조회
        }

        // 거래 조회
        else if (Stance == L"Admin_Recipt") {
            // 신고 테이블 조회
        }

        // 농축수산물 조회
        else if (Stance == L"Admin_Product") {

        }

        // 이용자 조회
        else if (Stance == L"Admin_User") {

        }

        // 종료 상태
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