package com.example.txt_saver;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.Build;
import android.os.IBinder;
import android.support.v4.app.INotificationSideChannel;
import android.util.Log;
import android.widget.TextView;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MyService extends Service {
    private static final String TAG = MyService.class.getSimpleName();

    private Thread mThread;

    public MyService() {
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if ("startForeground".equals(intent.getAction())) {
            // 포그라운드 서비스 시작
            startForegroundService();

        } else if (mThread == null) {
            // 스레드 초기화 및 시작
            mThread = new Thread("My Thread") {
                @Override
                public void run() {
                    while(true) {
                        try {
                            Thread.sleep(1000);
                            // 현재 시각 받기
                            /*
                            long now = System.currentTimeMillis();
                            Date date = new Date(now);
                            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                            String getTime = sdf.format(date);
                            // 위치 받기
                            gpsServ.getLocation();
                            double latitude = gpsServ.getLatitude(); // 위도
                            double longitude = gpsServ.getLongitude(); // 경도
                            */
                            Log.d(TAG, "testtestsetestsesefsfa");
                        } catch (InterruptedException e) {
                            // 스레드에 인터럽트가 걸리면
                            // 오래 걸리는 처리 종료
                            break;
                        }
                    }
                }
            };
            mThread.start();
        }
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "onDestroy: ");
        // stopService 에 의해 호출 됨
        // 스레드를 정지시킴
        if (mThread != null) {
            mThread.interrupt();
            mThread = null;
        }
        super.onDestroy();
    }

    // MyService의 레퍼런스를 반환하는 Binder 객체
    private IBinder mBinder = new MyBinder();

    public class MyBinder extends Binder {
        public MyService getService() {
            return MyService.this;
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(TAG, "onCreate: ");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d(TAG, "onBind: ");
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.d(TAG, "onUnbind: ");
        return super.onUnbind(intent);
    }

    private void startForegroundService() {
        // default 채널 ID로 알림 생성
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "default");
        builder.setSmallIcon(R.mipmap.ic_launcher);
        builder.setContentTitle("포그라운드 서비스");
        builder.setContentText("포그라운드 서비스 실행 중");
        Intent notificationIntent = new Intent(this, MainActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notificationIntent, 0);
        builder.setContentIntent(pendingIntent);

        // 오레오에서는 알림 채널을 매니저에 생성해야 한다
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationManager manager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
            manager.createNotificationChannel(new NotificationChannel("default", "기본 채널", NotificationManager.IMPORTANCE_DEFAULT));
        }

        // 포그라운드로 시작
        startForeground(1, builder.build());
    }
}