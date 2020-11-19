package com.example.corona;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

public class RegisterInput extends AppCompatActivity {

    private EditText edit1;
    private TextView textView1;
    private Button button1, button2;
    private Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register_input);

        this.getViewObject();

        View.OnClickListener clickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.button1) {
                    String locCode = "", Buf = "";
                    boolean Valid = false;
                    String Data = edit1.getText().toString();
                    if(Data.equals("ab1218913c")) // 인증코드
                        Valid = true;
                    if (Valid) // 올바른 입력일 시
                    {
                        // 지역번호는 locCode에 저장되고 보낼 메소드 필요
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
                else if (v.getId() == R.id.button2) {
                    finish();
                }
            }
        };
        button1.setOnClickListener(clickListener);
        button2.setOnClickListener(clickListener);
    }

    private void getViewObject()
    {
        edit1 = findViewById(R.id.edit1);
        textView1 = findViewById(R.id.textView1);
        button1 = findViewById(R.id.button1);
        button2 = findViewById(R.id.button2);
        spinner = findViewById(R.id.spinner);
    }
}