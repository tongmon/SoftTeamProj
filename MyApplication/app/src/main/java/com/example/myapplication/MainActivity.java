package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLEncoder;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

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
        String test = "";
        String save;
        TextView textview;
        InfoActivity entity;
        Document doc;
        Elements contents;
        try {
            //나중에 url 받으면 변수로 지정
            doc = Jsoup.connect("https://www.kobic.re.kr/covid19/").timeout(3000).get();
            contents = doc.select("em");
            save = contents.toString();
            save = save.replaceAll("<em>","");
            save = save.replaceAll("</em>","");
            String data[] = save.split("\\n");
            for(int i=1; i<5; i++)
            {
                test += data[i];
            }
            /* data[i], i=0~3 확진자수, 완치, 치료중, 사망*/

        }catch (IOException e) {
            e.printStackTrace();;
        }

        return test;
    }

    InfoActivity() {
        outputInfo.data = null;
        outputInfo.type = 0;
    }

}

public class MainActivity extends AppCompatActivity {
    String test = "";
    String save;
    TextView textview;
    InfoActivity entity;
    Document doc;
    Elements contents;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textview = (TextView) findViewById(R.id.textView1);

        final Bundle bundle = new Bundle();

        new Thread(){
            @Override
            public void run() {
                doc = null;
                try {
                    doc = Jsoup.connect("https://www.kobic.re.kr/covid19/").timeout(3000).get();
                    contents = doc.select("em");
                    save = contents.toString();
                    save = save.replaceAll("<em>","");
                    save = save.replaceAll("</em>","");
                    String data[] = save.split("\\n");
                    for(int i=1; i<5; i++)
                    {
                        test += data[i];
                    }
                    /* data[i], i=0~3 확진자수, 완치, 치료중, 사망*/

                    bundle.putString("numbers", test);
                    Message msg = handler.obtainMessage();
                    msg.setData(bundle);
                    handler.sendMessage(msg);
                }catch (IOException e) {
                    e.printStackTrace();;
                }
            }
        }.start();
    }

    Handler handler = new Handler(){
        @Override
        public void handleMessage(@org.jetbrains.annotations.NotNull Message msg) {
            Bundle bundle = msg.getData();
            textview.setText(bundle.getString("numbers"));

        }
    };
}