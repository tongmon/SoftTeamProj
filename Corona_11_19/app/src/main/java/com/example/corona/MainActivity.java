package com.example.corona;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.content.Intent;

public class MainActivity extends AppCompatActivity {

    private ImageButton imageButton2, imageButton3, imageButton4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.getViewObject();

        View.OnClickListener clickListener = new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.imageButton2) {
                    Intent patSearch = new Intent(getApplicationContext(), SearchInput.class);
                    startActivity(patSearch);
                }
                else if (v.getId() == R.id.imageButton3) {

                }
                else if (v.getId() == R.id.imageButton4) {
                    Intent patRegister = new Intent(getApplicationContext(), RegisterInput.class);
                    startActivity(patRegister);
                }
            }
        };
        imageButton2.setOnClickListener(clickListener);
        imageButton3.setOnClickListener(clickListener);
        imageButton4.setOnClickListener(clickListener);
    }

    private void getViewObject()
    {
        imageButton2 = findViewById(R.id.imageButton2);
        imageButton3 = findViewById(R.id.imageButton3);
        imageButton4 = findViewById(R.id.imageButton4);
    }
}