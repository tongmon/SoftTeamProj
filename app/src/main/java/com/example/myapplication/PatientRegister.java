package com.example.myapplication;

import android.annotation.SuppressLint;
import android.os.AsyncTask;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;

public class PatientRegister {
    public String patientID; // 확진자 ID
    public boolean userStatus = true; // 접근허용상태
    String json;             // 서버에서 텍스트 가져오는 변수

    public boolean registerFunc(String authenticationCode) throws ExecutionException, InterruptedException {
        boolean result = userInputCheck(authenticationCode); // 유효성검사(공인인증코드, 지역번호)
        if (!userStatus || patientID == null || result == false) { // 값이 유효하지 않을 경우 종료
            System.out.println("Invalid Input Data!");
            return false;
        }
        result = patientInfoFinder(authenticationCode);
        return result;
    }

    // 유효성 검사 함수(codeArea(공인인증코드+지역번호))
    public boolean userInputCheck(String codeArea) throws ExecutionException, InterruptedException {
        boolean aCode = false, localCode = true;  // 공인인증코드 유효성
        int patientNum = 0;     // 환자번호
        String[] codeArray;    //공인인증코드, 지역번호
        String url = ""; // 지역을 정하기 위한 url

        if (codeArea == null) {     // 공인인증코드+지역번호 없을 경우 종료
            System.out.println("Wrong input!");
            return false;
        }
        codeArray = codeArea.split(",");
        json = new GetDataJSON().execute("http://18.217.217.150:3000/data").get();
        aCode = userJsonParsing(json, codeArray[0]);
        System.out.println(aCode);

        if (aCode) {      // 지역번호 비교 후 해당 url 저장
            switch (codeArray[1]) {
                case "100":
                    url = "http://18.217.217.150:3000/seoul";       // 예상 url 주소 * 만들어야 함.
                    break;
                case "101":
                    url = "http://18.217.217.150:3000/anyang";
                    break;
                case "102":
                    url = "http://18.217.217.150:3000/suwon";       // 예상 url 주소
                    break;
                default:
                    localCode = false;
                    break;
            }
            if (localCode) {
                json = new GetDataJSON().execute(url).get();
                patientNum = patientCntJsonParsing(json);
                patientID = codeArray[1] + "#" + patientNum;
                return true;
            }
        }
        return false;
    }

    public boolean patientInfoFinder(String codeArea) throws ExecutionException, InterruptedException {
        String[] codeArray;    //공인인증코드, 지역번호
        String url = "";
        boolean localCode = true;

        codeArray = codeArea.split(",");
        switch (codeArray[1]) {
            case "100":
                url = "http://18.217.217.150:3000/seoul/new";       // 예상 url 주소 * 만들어야 함.
                break;
            case "101":
                url = "http://18.217.217.150:3000/anyang/new";
                break;
            case "102":
                url = "http://18.217.217.150:3000/suwon/new";       // 예상 url 주소
                break;
            default:
                localCode = false;
                break;
        }
        if (localCode) {
            String postResult1 = new Post().execute("http://18.217.217.150:3000/data/update", "1", codeArray[0]).get();
            String postResult2 = new Post().execute(url, "2", codeArray[0]).get();
            if(postResult1.equals("true") && postResult2.equals("true"))
                return true;
        }
        return false;
    }

    // 테이블 값을 서버로부터 가져오는 클래스
    @SuppressLint("StaticFieldLeak")
    class GetDataJSON extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... params) {
            String uri = params[0];

            BufferedReader bufferedReader = null;
            try {
                URL url = new URL(uri);
                HttpURLConnection con = (HttpURLConnection) url.openConnection();
                StringBuilder sb = new StringBuilder();

                bufferedReader = new BufferedReader(new InputStreamReader(con.getInputStream()));

                String j;
                while ((j = bufferedReader.readLine()) != null) {
                    sb.append(j).append("\n");
                    System.out.println("sb: " + sb);        // 테스트
                }

                return sb.toString().trim();
            } catch (Exception e) {
                return null;
            }
        }
        protected void onPostExecute(String result) {
            json = result;
        }
    }

    // user 테이블을 데이터로 갖고 온 후 사용자 유효성 확인하는 함수
    protected boolean userJsonParsing(String json, String code) {
        boolean compare = false;        // 유효성 검사 사용자가 있는지 확인 ID 체크
        try {
            JSONArray jsonObject = new JSONArray(json);

            for (int i = 0; i < jsonObject.length(); i++) {
                JSONObject usersObject = jsonObject.getJSONObject(i);
                String id = usersObject.getString("ID");
                if (id.equals(code)) {
                    compare = true;
                    break;
                }
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return compare;
    }

    // patient 테이블을 데이터로 갖고 온 후 확진자 수 구하는 함수
    protected int patientCntJsonParsing(String json) {
        int num = 0;        // 지역 확진자 수
        try {
            JSONArray jsonObject = new JSONArray(json);

            for (int i = 0; i < jsonObject.length(); i++) {
                JSONObject usersObject = jsonObject.getJSONObject(i);
                num = usersObject.getInt("no");
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        num = num + 1;
        return num;
    }

    // user status json 파일로 만드는 함수
    JSONObject makeUserStatus(String id) throws JSONException {
        JSONObject jsonObject = new JSONObject();
        jsonObject.accumulate("choice_id", id);
        return jsonObject;
    }
    // insert json 파일로 만드는 함수
    JSONObject insert(String name) throws JSONException {
        JSONObject jsonObject = new JSONObject();
        jsonObject.accumulate("choice_local", patientID);
        jsonObject.accumulate("choice_name", name);
        return jsonObject;
    }

    // 데이터베이스에 POST 하는 클래스
    class Post extends AsyncTask<String, String, String> {
        @Override
        protected String doInBackground(String... params) {
            try {
                JSONObject jsonObject = new JSONObject();
                if(params[1].equals("1"))
                    jsonObject = makeUserStatus(params[2]);
                else if(params[1].equals("2"))
                    jsonObject = insert(params[2]);
                HttpURLConnection con = null;
                BufferedReader reader = null;
                try {
                    URL url = new URL(params[0]);
                    con = (HttpURLConnection) url.openConnection();
                    con.setRequestMethod("POST");
                    con.setRequestProperty("Cache-Control", "no-cache");    //캐시 설정
                    con.setRequestProperty("Content-Type", "application/json");
                    con.setDoOutput(true);
                    con.setDoInput(true);
                    con.connect();
                    OutputStream outStream = con.getOutputStream();
                    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outStream));
                    writer.write(jsonObject.toString());
                    writer.flush();
                    writer.close();
                    InputStream stream = con.getInputStream();
                    reader = new BufferedReader(new InputStreamReader(stream));
                    StringBuffer buffer = new StringBuffer();
                    String line = "";
                    while((line = reader.readLine()) != null){
                        buffer.append(line);
                    }
                    return "true";
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    if (con != null) {
                        con.disconnect();
                    }
                    try {
                        if (reader != null) {
                            reader.close();
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return "false";
        }
        @Override
        protected void onPostExecute(String result) {
            super.onPostExecute(result);
        }
    }
}
