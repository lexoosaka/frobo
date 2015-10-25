package net.npaka.bluetoothex;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

//Bluetooth通信
public class BluetoothEx extends Activity    
    implements View.OnClickListener {
    private final static String BR=System.getProperty("line.separator");    
    private final static int WC=LinearLayout.LayoutParams.WRAP_CONTENT;
    private final static int MP=LinearLayout.LayoutParams.MATCH_PARENT;
    
    //メッセージ定数
    public static final int MSG_STATE_CHANGE=1;
    public static final int MSG_READ        =2;

    //リクエスト定数
    private static final int RQ_CONNECT_DEVICE=1;
    private static final int RQ_ENABLE_BT     =2;

    //Bluetooth
    private BluetoothAdapter btAdapter;//Bluetoothアダプタ
    private ChatManager      chatManager;//チャットマネージャ

    //UI
    private EditText edtSend;   //送信エディットテキスト
    private Button   btnSend;   //送信ボタン
    private TextView lblReceive;//受信ラベル
    
    private Button B_1;
    private Button B_2;
    private Button B_3;
    private Button B_4;
    private Button B_5;
    private Button B_6;
    private Button B_7;
    private Button B_8;
    private Button B_9;
    
    
    
    //アクティビティ起動時に呼ばれる
    @Override
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        
        //レイアウトの生成
        LinearLayout layout=new LinearLayout(this);
        layout.setBackgroundColor(Color.rgb(255,255,255));
        layout.setOrientation(LinearLayout.VERTICAL);
        setContentView(layout); 
        
        //送信エディットテキストの生成
        edtSend=new EditText(this);
        edtSend.setId(2);
        edtSend.setText("",TextView.BufferType.NORMAL);
        edtSend.setLayoutParams(new LinearLayout.LayoutParams(MP,WC));
        layout.addView(edtSend);
        
        LinearLayout button_l3 = new LinearLayout(this);
        button_l3.setBackgroundColor(Color.rgb(255, 200, 255));
        button_l3.setOrientation(LinearLayout.HORIZONTAL);
        button_l3.setLayoutParams(new LinearLayout.LayoutParams(WC, WC));
        layout.addView(button_l3);
        
        LinearLayout button_l2 = new LinearLayout(this);
        button_l2.setBackgroundColor(Color.rgb(200, 255, 200));
        button_l2.setOrientation(LinearLayout.HORIZONTAL);
        button_l2.setLayoutParams(new LinearLayout.LayoutParams(WC, WC));
        layout.addView(button_l2);
        
        LinearLayout button_l1 = new LinearLayout(this);
        button_l1.setBackgroundColor(Color.rgb(255, 200, 200));
        button_l1.setOrientation(LinearLayout.HORIZONTAL);
        button_l1.setLayoutParams(new LinearLayout.LayoutParams(WC, WC));
        layout.addView(button_l1);
       
        //送信ボタンの生成
        btnSend=new Button(this);
        btnSend.setId(100);
        btnSend.setText("送信");
        btnSend.setOnClickListener(this);
        btnSend.setLayoutParams(new LinearLayout.LayoutParams(WC,WC));
        layout.addView(btnSend);

        B_7=new Button(this);
        B_7.setId(70);
        B_7.setText("7");
        B_7.setOnClickListener(this);
        B_7.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l3.addView(B_7);

        B_8=new Button(this);
        B_8.setId(80);
        B_8.setText("8");
        B_8.setOnClickListener(this);
        B_8.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l3.addView(B_8);

        B_9=new Button(this);
        B_9.setId(90);
        B_9.setText("9");
        B_9.setOnClickListener(this);
        B_9.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l3.addView(B_9);

        B_4=new Button(this);
        B_4.setId(40);
        B_4.setText("4");
        B_4.setOnClickListener(this);
        B_4.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l2.addView(B_4);

        B_5=new Button(this);
        B_5.setId(50);
        B_5.setText("5");
        B_5.setOnClickListener(this);
        B_5.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l2.addView(B_5);

        B_6=new Button(this);
        B_6.setId(60);
        B_6.setText("6");
        B_6.setOnClickListener(this);
        B_6.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l2.addView(B_6);

        B_1=new Button(this);
        B_1.setId(10);
        B_1.setText("1");
        B_1.setOnClickListener(this);
        B_1.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l1.addView(B_1);

        B_2=new Button(this);
        B_2.setId(20);
        B_2.setText("2");
        B_2.setOnClickListener(this);
        B_2.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l1.addView(B_2);

        B_3=new Button(this);
        B_3.setId(30);
        B_3.setText("3");
        B_3.setOnClickListener(this);
        B_3.setLayoutParams(new LinearLayout.LayoutParams(70, 70));
        button_l1.addView(B_3);

       //受信ラベルの生成
        lblReceive=new TextView(this);
        lblReceive.setId(1);
        lblReceive.setText("");
        lblReceive.setTextSize(16.0f);
        lblReceive.setTextColor(Color.rgb(0,0,0));
        lblReceive.setLayoutParams(new LinearLayout.LayoutParams(MP,WC));
        layout.addView(lblReceive);    
        
        //Bluetoothアダプタ
        btAdapter=BluetoothAdapter.getDefaultAdapter();
        
        //チャットマネージャ
        chatManager=new ChatManager(handler);
    }

    //アクティビティ開始時に呼ばれる
    @Override
    public void onStart() {
        super.onStart();
        if (!btAdapter.isEnabled()) {
            Intent intent=new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(intent,RQ_ENABLE_BT);
        }
    }

    //アクティビティ再開時に呼ばれる
    @Override
    public synchronized void onResume() {
        super.onResume();
        
        //サーバの接続待ちスレッドの開始
        if (chatManager.getState()==ChatManager.STATE_NONE) {
            chatManager.start();
        }
    }

    //アクティビティ破棄時に呼ばれる
    @Override
    public void onDestroy() {
        super.onDestroy();
        
        //サーバの接続待ちスレッドの停止
        chatManager.stop();
    }

    //他のBluetooth端末からの発見を有効化(4)
    private void ensureDiscoverable() {
        if (btAdapter.getScanMode()!=
            BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE) {
            Intent intent=new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
            intent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION,300);
            startActivity(intent);
        }
    }

    //チャットサーバから情報を取得するハンドラ
    private final Handler handler=new Handler() {
        @Override
        public void handleMessage(Message msg) {
            //状態変更
            if (msg.what==MSG_STATE_CHANGE) {
                switch (msg.arg1) {
                case ChatManager.STATE_CONNECTED:
                    addText("接続完了");break;
                case ChatManager.STATE_CONNECTING:
                    addText("接続中");break;
                case ChatManager.STATE_LISTEN:
                case ChatManager.STATE_NONE:
                    addText("未接続");break;
                }
            //メッセージ受信
            } else if (msg.what==MSG_READ ){
                addText(new String((byte[])msg.obj,0,msg.arg1));
            }
        }
    };

    //オプションメニュー生成時に呼ばれる
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);
        MenuItem item0=menu.add(0,0,0,"端末検索");
        item0.setIcon(android.R.drawable.ic_search_category_default);
        MenuItem item1=menu.add(0,1,0,"発見有効");
        item1.setIcon(android.R.drawable.ic_menu_view);
        return true;
    }

    //オプションメニュー選択時に呼ばれる
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId()==0) {
            //端末検索
            Intent intent=new Intent(this,DeviceListActivity.class);
            startActivityForResult(intent,RQ_CONNECT_DEVICE);
            return true;
        } else if (item.getItemId()==1) {
            //発見有効
            ensureDiscoverable();
            return true;
        }
        return false;
    }
    

    //アクティビティ復帰時に呼ばれる
    public void onActivityResult(int requestCode,int resultCode,Intent data) {
        //端末検索
        if (requestCode==RQ_CONNECT_DEVICE ){
            if (resultCode==Activity.RESULT_OK) {
                //クライアントの接続要求スレッドの開始
                String address=data.getExtras().getString("device_address");
                chatManager.connect(btAdapter.getRemoteDevice(address));
            }
        }
        //発見有効
        else if (requestCode==RQ_ENABLE_BT) {
            if (resultCode!=Activity.RESULT_OK) {
                addText("Bluetoothが有効ではありません");
            }
        }
    }

    //受信テキストの追加
    private void addText(final String text) {
        lblReceive.setText(text+BR+lblReceive.getText());
    }
    
    //ボタンクリックイベントの処理
    public void onClick(View v) {
        try {
        	String message;
            //メッセージの送信
        	if(5 < v.getId() && v.getId() < 100){
        		message = String.valueOf(v.getId());
        	}else{
        		message = edtSend.getText().toString();
        	}
            if (message.length()>0) chatManager.write(message.getBytes());
            addText(message);
            edtSend.setText("", TextView.BufferType.NORMAL);
        } catch (Exception e) {
            addText("通信失敗しました");
        }           
    }  
}
