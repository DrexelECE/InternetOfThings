package com.example.bikecomputerapp;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;


public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
    
    static int rimSize = 700;
    static int tireSize = 25;
    static double wheelCircumference = calcWheelCircumference(rimSize,tireSize);
    
    public static double calcWheelCircumference(int rimSize, int tireSize) {
    	// Wheel circumference in mm
    	double wheelCircumference = 0;
    	
    	// 700c rims same width as 29er
    	if (rimSize == 29) {
    		rimSize = 700;
    	}
    	
    	// First choose rim size, then tire size
    	switch (rimSize) {
    		case 700:	switch (tireSize) {
    						case 20:	wheelCircumference = 2079.73;
    									break;
    						case 23:	wheelCircumference = 2098.58;
    									break;
    						case 25: 	wheelCircumference = 2111.15;
    									break;
    						case 28:	wheelCircumference = 2130.00;
    									break;
    						case 32:	wheelCircumference = 2155.13;
    									break;
    						case 35: 	wheelCircumference = 2173.98;
    									break;
    						case 38:	wheelCircumference = 2192.83;
    									break;
    						case 44:	wheelCircumference = 2230.53;
    									break;
    						case 50:	wheelCircumference = 2268.23;
    									break;
    						case 56: 	wheelCircumference = 2305.93;
    									break;
    	
    					}
    	}
    	
    	return wheelCircumference;
    }
    
    public static double kmhToMph(double kmh) {
    	// Convert km/h to MPH
    	return 0.621371 * kmh;
    }
    
    public static double calcCurrentSpeed(double timeElapsed) {
    	// Compute the current speed after 10 passes of the magnet
    	// Takes in timeElapsed (seconds) data from board
    	// Returns velocity in km/h
    	
    	// Distance traveled in 10 passes
    	double distanceTraveled = wheelCircumference * 10;
    	
    	// Velocity in mm/s
    	double velocity = distanceTraveled/timeElapsed;
    	
    	// Return velocity in km/h
    	return velocity * 0.0036;
    }
}
