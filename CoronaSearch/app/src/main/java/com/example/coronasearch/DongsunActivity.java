package com.example.coronasearch;

import android.graphics.Color;
import android.os.Bundle;

import androidx.fragment.app.FragmentActivity;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;

import static com.example.coronasearch.SearchInput.InfoPatient;

public class DongsunActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;
    private LatLng startLatLng = new LatLng(0, 0);
    private LatLng endLatLng = new LatLng(0, 0);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dongsun);
        /*
        try {
            InfoPatient.GetInfoToURL.execute().get();
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        */
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        InfoPatient.gpsInfo[0][2] = "0"; InfoPatient.gpsInfo[0][3] = "1";
        System.out.println("hellohellohellohellohellohellohellohellohellohellohello");
        System.out.println(InfoPatient.gpsInfo[0][2] + " " + Double.parseDouble(InfoPatient.gpsInfo[0][3]));
        endLatLng = new LatLng(Double.parseDouble(InfoPatient.gpsInfo[0][2]), Double.parseDouble(InfoPatient.gpsInfo[0][3]));

        /*
        mMap.moveCamera(CameraUpdateFactory.newLatLng(endLatLng));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(endLatLng,16));
        for (int i = 1; i < GetPatientInfo.gpsInfo.length; i++){
            startLatLng = new LatLng(endLatLng.latitude, endLatLng.longitude);
            endLatLng = new LatLng(Double.parseDouble(GetPatientInfo.gpsInfo[i][2]), Double.parseDouble(GetPatientInfo.gpsInfo[i][3]));
            drawPath();
        }
        */

        LatLng sydney = new LatLng(-34, 151);
        mMap.addMarker(new MarkerOptions().position(sydney).title("Marker in Sydney"));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(sydney));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(sydney,16));
    }

    private void drawPath()
    {
        PolylineOptions options = new PolylineOptions().add(startLatLng).add(endLatLng).width(15).color(Color.BLACK).geodesic(true);
        mMap.addPolyline(options);
    }
}