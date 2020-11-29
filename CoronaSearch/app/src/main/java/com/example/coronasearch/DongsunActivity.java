package com.example.coronasearch;

import android.graphics.Color;
import android.os.Bundle;

import androidx.fragment.app.FragmentActivity;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;

import static com.example.coronasearch.SearchInput.InfoPatient;

public class DongsunActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;
    private LatLng startLatLng = new LatLng(0, 0);
    private LatLng endLatLng = new LatLng(0, 0);
    private Polyline line;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dongsun);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        InfoPatient.Info.clear();
        line.remove();
        //finish();
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        endLatLng = new LatLng(Double.parseDouble(InfoPatient.Info.get(0).x), Double.parseDouble(InfoPatient.Info.get(0).y));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(endLatLng));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(endLatLng,16));
        for (int i = 1; i < InfoPatient.Info.size(); i++){
            startLatLng = new LatLng(endLatLng.latitude, endLatLng.longitude);
            endLatLng = new LatLng(Double.parseDouble(InfoPatient.Info.get(i).x), Double.parseDouble(InfoPatient.Info.get(i).y));
            drawPath();
        }

        /*
        LatLng sydney = new LatLng(-34, 151);
        mMap.addMarker(new MarkerOptions().position(sydney).title("Marker in Sydney"));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(sydney));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(sydney,16));
        */
    }

    private void drawPath()
    {
        PolylineOptions options = new PolylineOptions().add(startLatLng).add(endLatLng).width(15).color(Color.BLACK).geodesic(true);
        line = mMap.addPolyline(options);
    }
}