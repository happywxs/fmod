package com.xue.song.fmod;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;

public class PlayQQEffectActivity extends Activity {

    public static final int NOMAL = 0;
    public static final int LUOLI = 1;
    public static final int DASHU = 2;
    public static final int THRILL = 3;
    public static final int YOULING = 4;

    static {
        /*
         * To simplify our examples we try to load all possible FMOD
         * libraries, the Android.mk will copy in the correct ones
         * for each example. For real products you would just load
         * 'fmod' and if you use the FMOD Studio tool you would also
         * load 'fmodstudio'.
         */

        // Try debug libraries...
    /*	try { System.loadLibrary("fmodD");
    		//  System.loadLibrary("fmodstudioD");
    	}
    	catch (UnsatisfiedLinkError e) { }*/
        // Try logging libraries...
        try {
            System.loadLibrary("fmodL");
            // System.loadLibrary("fmodstudioL");
        } catch (UnsatisfiedLinkError e) {
        }
        // Try release libraries...
        try {
            System.loadLibrary("fmod");
            //  System.loadLibrary("fmodstudio");
        } catch (UnsatisfiedLinkError e) {
        }

        //System.loadLibrary("stlport_shared");
        System.loadLibrary("fmodku");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_qq_play);
        org.fmod.FMOD.init(this);
    }

    public void onclick(final View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                String path = "file:///android_asset/test.mp3";

                // init(path);
                switch (view.getId()) {
                    case R.id.normal:
                        playSound(NOMAL,path);
                        break;
                    case R.id.luo_li:
                        playSound(LUOLI,path);
                        break;
                    case R.id.da_dashu:
                        playSound(DASHU,path);
                        break;
                    case R.id.thrill:
                        playSound(THRILL,path);
                        break;
                    case R.id.youling:
                        playSound(YOULING,path);
                        break;
                }
            }
        }).start();

    }

    public native void init(String path);

    public native void playSound(int type,String path);
}
