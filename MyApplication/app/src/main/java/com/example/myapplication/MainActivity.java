package com.example.myapplication;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.icu.util.Output;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.Button;
import org.xmlpull.v1.XmlPullParser;
import org.json.*;
import android.widget.TextView;

import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;


import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

class PatientRegister{
    String registerFunc(String getInfo){

        return null;
    }
}

class OutInfo{
    String data;
    int type;
}

class InfoActivity {
    PatientRegister patientWrite;
    OutInfo outputInfo;

    OutInfo analyzeInfo(String getInfo, int getInfoType) {
        if(getInfo == null) {
            //"Invalid Insertion Data!" 출력 어디다가? alert?
            return null;
        }

        if(getInfoType == 1) {
            outputInfo.type = 1;
            outputInfo.data = getGeoInfo(getInfo);
        }else if(getInfoType == 2) {
            outputInfo.type = 2;
            outputInfo.data = uRLtoInfo(getInfo);
        }else if(getInfoType == 3) {
            outputInfo.type = 3;
            outputInfo.data = patientWrite.registerFunc(getInfo);
        }if(outputInfo.data.equals("-1")) {
            //"Output Failure" 출력 어디다가? alert?
            return null;
        }
        return outputInfo;
    }

    String getGeoInfo(String patientID) {
        /*
        DB받아서 데이터 추출 과정 / 확진자 레코드 묶음 = DB_Search(확진자ID)
        if(확진자 레코드 묶음.size == 0) {
            //“Can’t get the Geo Info!” 출력 어디다가?
            return "-1"
        }

        지도정보 = 확진자 레코드 묶음에서 지도 정보 추출
        return 지도정보;
        */

        return null;
    }

    String uRLtoInfo (String uRL) {
        if (uRL.equals("https://coronaboard.kr/")) {
            //print(“Invalid URL!”) 출력 어디다가?
            return "-1";
        }
        try {
            Document doc = Jsoup.connect("http://ncov.mohw.go.kr/bdBoardList_Real.do?brdId=1&brdGubun=11&ncvContSeq=&contSeq=&board_id=&gubun=").timeout(5000).get();
            Elements contents = doc.getElementsByClass("ca_value"); // 국내 총 확진자 수

            //nums += contents.text() + " ";
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    InfoActivity() {
        outputInfo.data = null;
        outputInfo.type = 0;
    }

}


public class MainActivity extends AppCompatActivity {
    String nums;                    //복권 번호을 저장할 변수
        TextView textView1;
        TextView textView2;
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);
            textView1 = (TextView) findViewById(R.id.textView1);
            textView2 = (TextView) findViewById(R.id.textView);
            final Bundle bundle = new Bundle();

        String str = "null";
        boolean initem = false;

        try {
            URL url = new URL("http://openapi.data.go.kr/openapi/service/rest/Covid19/getCovid19InfStateJson?" +
                    "serviceKey=v3HvpeQoPVf3mH1wQJ%2BaTpU2XSMOyloTm6%2BJCgcaYF5Sfu%2FDtwDdFLrctlCzZNhJU4N1OFKMEJPM8" +
                    "5dSRD8rpA%3D%3D&pageNo=1&numOfRows=10&startCreateDt=20201115&endCreateDt=20201115");

            XmlPullParserFactory parserCreateor = XmlPullParserFactory.newInstance();
            XmlPullParser parser = parserCreateor.newPullParser();

            parser.setInput(url.openStream(), null);

            int parserEvent = parser.getEventType();

            textView2.setText(parser.getText());

            while (parserEvent != XmlPullParser.END_DOCUMENT) {
                switch (parserEvent) {
                    case XmlPullParser.START_TAG:
                        if (parser.getName().equals("accDefRate")) {
                            initem = true;
                        }
                        //..
                        break;
                    case XmlPullParser.TEXT:
                        if(initem){
                            str = parser.getText();
                            initem = false;
                        }
                        //...
                        break;
                    case XmlPullParser.END_TAG:
                        //if(parser.getName().equals("item")){
                            textView1.setText(str);
                        //}
                        //...
                        break;
                }
                parserEvent = parser.next();
            }
                    /*
                    doc = Jsoup.connect("http://openapi.data.go.kr/openapi/service/rest/Covid19/getCovid19InfStateJson?serviceKey=v3HvpeQoPVf3mH1wQJ%2BaTpU2XSMOyloTm6%2BJCgcaYF5Sfu%2FDtwDdFLrctlCzZNhJU4N1OFKMEJPM85dSRD8rpA%3D%3D&pageNo=1&numOfRows=10&startCreateDt=20201114&endCreateDt=20201114").timeout(5000).get(); // 현재 날짜 받아와야됨
                    Elements contents = doc.select("[item]");      //회차 id값 가져오기
                    nums = contents +" 명";
//#main-top > div.main-top > div.main-top-article > h4 > a" /col-3 col-sm-3 col-md-2 text-center
                    bundle.putString("numbers", nums);                               //핸들러를 이용해서 Thread()에서 가져온 데이터를 메인 쓰레드에 보내준다.
                    Message msg = handler.obtainMessage();
                    msg.setData(bundle);
                    handler.sendMessage(msg);
                    */
        } catch (IOException e) {
            e.printStackTrace();
        } catch (XmlPullParserException e) {
            e.printStackTrace();
        }
    }
    /*
    Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            Bundle bundle = msg.getData();
            textView1.setText(bundle.getString("numbers"));                      //이런식으로 View를 메인 쓰레드에서 뿌려줘야한다.
        }
    };*/
}
