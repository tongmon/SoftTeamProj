package com.example.my_application;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private EditText edit1;
    private TextView textView1;
    private Button button1;
    private Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.getViewObject();

        View.OnClickListener clickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.button1) {
                    String locCode = "", Buf = "";
                    boolean Valid = false;
                    String Data = edit1.getText().toString();
                    if(Data.equals("ab1218913c"))
                        Valid = true;
                    if (Valid) // 올바른 입력일 시
                    {
                        // String sel = (String)spinner.getItemAtPosition(spinner.getSelectedItemPosition());
                        Buf = Integer.toString(spinner.getSelectedItemPosition());
                        for(int i =0;i < 5 - Buf.length();i++) {
                            locCode = locCode + '0';
                        }
                        locCode = locCode + Buf;
                        textView1.setText("인증 되었습니다.\n지역 번호: " + locCode);
                    }
                    else // 잘못된 입력일 시
                    {
                        textView1.setText("잘못된 인증 코드 입니다.");
                    }
                }
            }
        };
        button1.setOnClickListener(clickListener);
    }

    private void getViewObject()
    {
        edit1 = findViewById(R.id.edit1);
        textView1 = findViewById(R.id.textView1);
        button1 = findViewById(R.id.button1);
        spinner = findViewById(R.id.spinner);
    }
}