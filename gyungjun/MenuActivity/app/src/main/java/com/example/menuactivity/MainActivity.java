package com.example.menuactivity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private EditText InputBox1;
    private TextView textView4;
    private Button button1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.getViewObject();

        View.OnClickListener clickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.button1)
                {
                    boolean Valid = true;
                    String Data = InputBox1.getText().toString();
                    if (Data.length() != 11)
                        Valid = false;
                    for (int i = 0; i < Data.length() && Data.length() == 11; i++) {
                        if ((i == 5 && Data.charAt(i) != '#')
                                || (i != 5 && (Data.charAt(i) < '0' || Data.charAt(i) > '9'))) {
                            Valid = false;
                            break;
                        }
                    }
                    if (Valid) // 올바른 입력일 시
                    {
                        // 확진자 ID 다른 곳으로 전송하는 프로세스 필요
                        textView4.setText("올바른 입력입니다.");
                    }
                    else // 잘못된 입력일 시
                    {
                        textView4.setText("잘못된 입력입니다.\n00000#00000 형식을 맞춰주세요.");
                    }
                }
            }
        };
        button1.setOnClickListener(clickListener);
        /*
        View.OnKeyListener keyListener = new View.OnKeyListener() {
            @Override
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                boolean Valid = false;
                if ((event.getAction() == KeyEvent.ACTION_DOWN)
                        && (event.getAction() == KeyEvent.KEYCODE_ENTER)) {
                    Valid = true;
                    String Data = InputBox1.getText().toString();
                    if (Data.length() > 12 || Data.length() == 0)
                        Valid = false;
                    for (int i = 0; i < Data.length() && Data.length() < 13; i++) {
                        if ((i == 5 && Data.charAt(i) != '#')
                                || (i != 5 && (Data.charAt(i) < '0' || Data.charAt(i) > '9'))) {
                            Valid = false;
                            break;
                        }
                    }
                }
                if (Valid) // 올바른 입력일 시
                {

                }
                else // 잘못된 입력일 시
                {

                }
                return Valid;
            }
        };
        InputBox1.setOnKeyListener(keyListener);
        */
    }

    private void getViewObject()
    {
        InputBox1 = findViewById(R.id.InputBox1);
        textView4 = findViewById(R.id.textView4);
        button1 = findViewById(R.id.button1);
    }
}