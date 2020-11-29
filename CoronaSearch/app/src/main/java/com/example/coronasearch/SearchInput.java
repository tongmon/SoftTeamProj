package com.example.coronasearch;

import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.util.HashMap;
import java.util.regex.Pattern;

class GetPatientInfo {
    HashMap local = new HashMap<String, Integer>();
    String test = "";
    String save;
    TextView textview, t2;
    Document doc;
    Elements contents;
    String iD;
    String spData[][];
    String gpsInfo[][]; //x, y
    String url;

    GetPatientInfo() {
        local.put("seoul",100);
        local.put("anyang",101);
        local.put("suwon",102);
    }

    public class GetInfoToURL extends AsyncTask<String,String,String> {
        @Override
        protected String doInBackground(String... params) {
            doc = null;
            try {
                Document doc = (Document) Jsoup.connect("http://18.217.217.150:3000/geo").timeout(3000).get();
                contents = doc.select("pre");
                save = contents.toString();

                JSONArray jsonOb = new JSONArray(save);

                int num=0;
                JSONObject userOb;
                for(int i=0; i<jsonOb.length(); i++){
                    userOb = jsonOb.getJSONObject(i);
                    if(userOb.getString("id") == iD) {
                        gpsInfo[num][0] = userOb.getString("geodate");
                        gpsInfo[num][1] = userOb.getString("geotime");
                        gpsInfo[num][2] = userOb.getString("x_cord");
                        gpsInfo[num++][3] = userOb.getString("y_cord");
                    }
                }
                // gpsInfo [0] [0,1,2,3]->{date, time, x, y}
                // gpsInfo [1] [0,1,2,3]->{date, time, x, y}

                //지도에 그리는거 넣기

            }catch (IOException | JSONException e) {
                e.printStackTrace();;
            }
            return "True";
        }
        @Override
        protected void onPostExecute(String result) {
            super.onPostExecute(result);
        }
    }
}

public class SearchInput extends Activity {

    private EditText InputBox1;
    private TextView textView4;
    static GetPatientInfo InfoPatient = new GetPatientInfo();

    private ImageButton confirm, back;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.search_activity);

        InputBox1 = findViewById(R.id.InputBox1);
        textView4 = findViewById(R.id.textView4);
        final Intent intent = new Intent(getApplicationContext(), DongsunActivity.class);

        confirm = findViewById(R.id.confirm);
        back = findViewById(R.id.back);

        View.OnClickListener clickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.confirm) {
                    boolean Valid = true;
                    String Data = InputBox1.getText().toString();
                    if (Data.length() < 5)
                        Valid = false;
                    if (Pattern.matches("\\d{3}\\#\\d+", Data) == false)
                        Valid = false;
                    if (Valid) // 올바른 입력일 시
                    {
                        // 여기서 넘겨줌
                        // 확인도 필요, Data가 검색할 환자 ID
                        startActivity(intent);
                    } else // 잘못된 입력일 시
                    {
                        textView4.setText("잘못된 입력입니다.\n00000#00000 형식을 맞춰주세요.");
                    }
                } else if (v.getId() == R.id.back) {
                    finish();
                }
            }
        };
        confirm.setOnClickListener(clickListener);
        back.setOnClickListener(clickListener);
    }
}
