package com.example.myapplication;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import java.util.concurrent.ExecutionException;

public class MainActivity extends Activity {
    /*테스트하기위해 사용*/
    protected void onCreate(Bundle savedInstanceState) {
        boolean result = false;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        PatientRegister pr = new PatientRegister();
        try {
           result = pr.registerFunc("888,101");
        } catch (ExecutionException | InterruptedException e) {
            e.printStackTrace();
        }
        TextView textView1 = (TextView) findViewById(R.id.text1);
        textView1.setText(Boolean.toString(result));
    }
}